#include <linux/delay.h> 
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/version.h> 
#include <linux/sched.h> 
#include <linux/uaccess.h> 
#include <linux/kprobes.h> 
#include <linux/kallsyms.h>

#define DUMMY_SYSCALL 451

MODULE_DESCRIPTION("Module to extract task struct information from a given PID");
MODULE_AUTHOR("BlackPanther112358");
MODULE_LICENSE("GPL");
 
static unsigned long **sys_call_table; 
static asmlinkage int (*original_call)(int, int); 

static asmlinkage int our_sys_open(int flags, int mode) 
{ 
    // int i = 0; 
    // char ch; 
 
    // /* Report the file, if relevant */ 
    // pr_info("Opened file by %d: ", uid); 
    // do { 
    //     get_user(ch, (char __user *)filename + i); 
    //     i++; 
    //     pr_info("%c", ch); 
    // } while (ch != 0); 
    // pr_info("\n"); 
 
    // /* Call the original sys_open - otherwise, we lose the ability to 
    //  * open files. 
    //  */ 
    // return original_call(flags, mode); 



    return 0;
} 
 
static unsigned long **aquire_sys_call_table(void){ 
 
    unsigned long (*kallsyms_lookup_name)(const char *name); 
    struct kprobe kp = { 
        .symbol_name = "kallsyms_lookup_name", 
    }; 
 
    if (register_kprobe(&kp) < 0) 
        return NULL; 
    kallsyms_lookup_name = (unsigned long (*)(const char *name))kp.addr; 
    unregister_kprobe(&kp); 
 
    return (unsigned long **)kallsyms_lookup_name("sys_call_table"); 
} 
 
static inline void __write_cr0(unsigned long cr0) 
{ 
    asm volatile("mov %0,%%cr0" : "+r"(cr0) : : "memory"); 
} 
#define __write_cr0 write_cr0 

 
static void enable_write_protection(void) 
{ 
    unsigned long cr0 = read_cr0(); 
    set_bit(16, &cr0); 
    __write_cr0(cr0); 
} 
 
static void disable_write_protection(void) 
{ 
    unsigned long cr0 = read_cr0(); 
    clear_bit(16, &cr0); 
    __write_cr0(cr0); 
} 
 
static int __init syscall_start(void) 
{ 
    if (!(sys_call_table = aquire_sys_call_table())) 
        return -1; 
 
    disable_write_protection(); 
 
    original_call = (void *)sys_call_table[DUMMY_SYSCALL]; 
    sys_call_table[DUMMY_SYSCALL] = (unsigned long *)our_sys_open; 
 
    enable_write_protection(); 
 
    return 0; 
} 
 
static void __exit syscall_end(void) 
{ 
    if (!sys_call_table) 
        return; 
 
    if (sys_call_table[DUMMY_SYSCALL] != (unsigned long *)our_sys_open) { 
        pr_alert("Somebody else also played with the "); 
        pr_alert("open system call\n"); 
        pr_alert("The system may be left in "); 
        pr_alert("an unstable state.\n"); 
    } 
 
    disable_write_protection(); 
    sys_call_table[DUMMY_SYSCALL] = (unsigned long *)original_call; 
    enable_write_protection(); 
} 
 
module_init(syscall_start); 
module_exit(syscall_end); 

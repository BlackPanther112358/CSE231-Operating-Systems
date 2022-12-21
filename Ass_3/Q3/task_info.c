#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/uaccess.h> 
#include <linux/signal.h>
#include <linux/limits.h>
#include <linux/delay.h> 
#include <linux/string.h>
#include <linux/module.h>
#include <linux/kprobes.h> 
#include <linux/kallsyms.h>
#include <linux/version.h> 
#include <linux/sched.h> 

#define KERNEL_READ_TASK 451

MODULE_DESCRIPTION("Module to extract task struct information from a given PID");
MODULE_AUTHOR("BlackPanther112358");
MODULE_LICENSE("GPL");

static unsigned long **sys_call_table; 

static asmlinkage int (*original_call)(int, int); 

static asmlinkage int task_struct_info(int x, int y){ 

    struct pid *pid_struct;
    struct task_struct *task;

    // We use the variable x to pass our pid to the kernel module
    pid_struct = find_get_pid(x);
    if(pid_struct == NULL){
        printk(KERN_INFO "PID not found");
        return -1;
    }

    task = pid_task(pid_struct, PIDTYPE_PID);

    for_each_process(task){
        printk("Task %s (pid = %d)\n", task->comm, task->pid);
        printk("User ID: %d", task->cred->uid.val);
        printk("PGID: %d", pid_vnr(task_pgrp(task_struct)));
        printk("Command Path: /proc/%d/exe", task->pid);
    }

    return 0; 
} 

static inline void __write_cr0(unsigned long cr0){ 
    asm volatile("mov %0,%%cr0" : "+r"(cr0) : : "memory"); 
} 


static void enable_write_protection(void){ 
    unsigned long cr0 = read_cr0(); 
    set_bit(16, &cr0); 
    __write_cr0(cr0); 
} 
 
static void disable_write_protection(void){ 
    unsigned long cr0 = read_cr0(); 
    clear_bit(16, &cr0); 
    __write_cr0(cr0); 
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

static int __init syscall_start(void){
    if (!(sys_call_table = aquire_sys_call_table())) return -1; 
 
    disable_write_protection(); 
 
    original_call = (void *)sys_call_table[KERNEL_READ_TASK]; 
 
    sys_call_table[KERNEL_READ_TASK] = (unsigned long *)task_struct_info; 
 
    enable_write_protection();  
    return 0;
}

static void __exit syscall_end(void){
        if (!sys_call_table) 
        return; 
 
    disable_write_protection(); 
    sys_call_table[KERNEL_READ_TASK] = (unsigned long *)original_call; 
    enable_write_protection(); 

}

module_init(syscall_start);
module_exit(syscall_end);

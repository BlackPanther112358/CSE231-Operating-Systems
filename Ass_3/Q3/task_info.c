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

MODULE_DESCRIPTION("Module to extract task struct information from a given PID");
MODULE_AUTHOR("BlackPanther112358");
MODULE_LICENSE("GPL");

static int pid = -1;
module_param(pid, int, 0);

static int task_info_start(void){
    
    char pth[1024];
    struct pid *pid_struct;
    struct task_struct *task;

    printk(KERN_INFO "Module Loaded with pid: %d\n", pid);

    pid_struct = find_get_pid(pid);
    if(pid_struct == NULL){
        printk(KERN_INFO "PID not found");
        return -1;
    }

    task = pid_task(pid_struct, PIDTYPE_PID);

    for_each_process(task){
        printk(KERN_INFO "Task %s (pid = %d)\n", task->comm, task->pid);
        printk(KERN_INFO "User ID: %d", task->cred->uid.val);
        printk(KERN_INFO "PGID: %d", pid_vnr(task_pgrp(task)));
        sprintf(pth, "/proc/%d/exe", task->pid);
        printk(KERN_INFO "Command Path: %s", pth);
        // printk(KERN_INFO "Command Path: %s", realpath(pth));
    }

    return 0;
}

static void task_info_end(void){
    
}

module_init(task_info_start);
module_exit(task_info_end);
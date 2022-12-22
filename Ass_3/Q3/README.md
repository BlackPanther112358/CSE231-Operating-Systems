# Kernel Module

First ensure that we are a root user. Then, we need to load the kernel module using the following command:

```insmod task_info.ko pid=<pid>```

Here we will pass the pid of the process we want to access as the argument. The module will then print the information of the process with the given pid. To access the same information from user space, we can use the following command:

```dmesg```

## Implementation

The functions $task\_info\_start$ and $task\_info\_end$ are used to load and remove the module. The start function also has the required code to access the process information. We first obtain the $task\_struct$ of a process using the $pid$ provided and then iterate over the $task\_struct$ to print the required information.
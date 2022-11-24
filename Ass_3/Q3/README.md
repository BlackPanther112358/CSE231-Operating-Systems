# KERNEL MODULE

Since we need to write a function using a system call in a kernel module, we will hijack a dummy system call in the system call table. The coded used for same was obtained from [this](https://linux-kernel-labs.github.io/refs/heads/master/labs/kernel_modules.html) tutorial.

We can now modify the existing system call definition to include our function $our\_sys\_open$. We use the first argument of the dummy call to pass the pid to obtain the $task\_struct$. We can now use the all $task\_struct$ and then the $mm\_struct$ to obtain all the required information.
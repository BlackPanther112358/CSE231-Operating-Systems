# CSE231-Operating-Systems

This repository constains the Assignments and there solutions for my CSE231 Operating Systems course in Monsoon Semester 2022.

There were 4 Assignments throughout the course and can be found in the $Assignments$ directory. There are individual directories for each Assignment.

## Assignments

### [Ass 0](Assignments/Operating_Systems___M22__A0.pdf)

I have written the [code](Ass_0/main) to input and then output a string and a number in assembly

### [Ass 1](Assignments/Operating_Systems___M22__A1.pdf)

The [codebase](Ass_1) tries to simulate some basic commands in a linux kernel like:
- cd
- pwd
- echo
- date
- rm
- ls
- cat
- mkdir

The program can be executed from [```main```](Ass_1/main.c) file after compliling use the [```Makefile```](Ass_1/Makefile) in the same folder

### [Ass 2](Assignments/Operating_Systems___M22__A2.pdf)

The [first part](Ass_2/Q1) of assignment involves running processes in a linux kernel using Threads and Forks, and timing the change in runtimes when using different priority values and scheduling policies.

The [second question](Ass_2/Q2) involves adding a syscall to the linux kernel to copy a 2D matrix from user. A [```diff```](Ass_2/Q2/diff.patch) can be found for changes made for same along with code to [test](Ass_2/Q2/test_syscall.c) it.

### [Ass 3](Assignments/Operating_Systems___M22__A3.pdf)

The [first question](Ass_3/Q1) deals with the [**Dining Philosophers Problem**](https://en.wikipedia.org/wiki/Dining_philosophers_problem#:~:text=The%20problem%20is%20how%20to,an%20issue%20of%20incomplete%20information), further details about the implementation can be found in the folder's [```README file```](Ass_3/Q1/README.md)

For the [second question](Ass_3/Q2), I wrote code to perform Inter-Process Communication in linux using FIFO, Shared Memory and Sockets. More information can be found in the folders [```README file```](Ass_3/Q2/README.md)

For the [third question](Ass_3/Q3), I wrote a simple linux kernel module to display information about current running processes. More information can be found in the folders [```README file```](Ass_3/Q3/README.md)

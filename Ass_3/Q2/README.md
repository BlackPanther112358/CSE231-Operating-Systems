# Interprocess Communication

We have to implement the given problem statement using the following methods:

### FIFO

We will create 2 pipes, $fifo1$ and $fifo2$ in the makefile itself, and use them to communicate between prcosses as pipes are ideally supposed to be unidirectionally. Thus, we can communicate between processes using them.

To run the program, first $cd$ into the directory and run the following command:

```make run_fifo```

### SOCKETS

We can create a single socket on server side and use it to communicate with the client. We will create a socket on server side and bind it to a port. Then, we will listen for connections on that port. Once a connection is established, we will send the data to the client and close the connection.

To run the program, first $cd$ into the directory and run the following command:

```make run_socket```

### SHARED MEMORY

We will create a shared memory segment and use it to communicate between processes. To ensure that the data is not lost, we will use semaphores to lock the shared memory segment while writing to it and unlock it after writing to it, along with sleep statements to ensure that the processes can alternate between writing and reading.

To run the program, first $cd$ into the directory and run the following command:

```make run_shm```
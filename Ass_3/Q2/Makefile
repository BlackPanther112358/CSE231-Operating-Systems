all: socket fifo shm

socket: sockets_p1.c sockets_p2.c
	gcc sockets_p1.c -o sockets_p1
	gcc sockets_p2.c -o sockets_p2

fifo: fifo_p1.c fifo_p2.c
	gcc fifo_p1.c -o fifo_p1
	gcc fifo_p2.c -o fifo_p2

shm: shm_p1.c shm_p2.c
	gcc shm_p1.c -o shm_p1
	gcc shm_p2.c -o shm_p2

run_fifo:
	make fifo
	./fifo_p1 & ./fifo_p2

run_socket:
	make socket
	./sockets_p1 & ./sockets_p2

run_shm:
	make shm
	./shm_p1 & ./shm_p2


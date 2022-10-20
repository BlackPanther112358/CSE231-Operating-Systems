main: main.asm
	yasm -f elf64 -l main.lst main.asm
	gcc -no-pie -o main main.o

clean: 
	rm *.lst *.o main

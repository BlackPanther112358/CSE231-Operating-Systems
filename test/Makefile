exit: exit.asm
	yasm -f elf64 -l exit.lst exit.asm
	gcc -no-pie -o exit exit.o

clean: 
	rm *.lst *.o exit
circuits.out: circuitsmain.o circuitsdriver.o debug.o
	gcc -m64 -o circuits.out circuitsdriver.o circuitsmain.o debug.o

circuitsmain.o: circuitsmain.asm
	nasm -f elf64 -l circuitsmain.lis -o circuitsmain.o circuitsmain.asm

circuitsdriver.o: circuitsdriver.c
	gcc -c -m64 -Wall -std=c99 -l circuitsdriver.lis -o circuitsdriver.o circuitsdriver.c

debug.o: debug.asm
	nasm -f elf64 -l debug.lis -o debug.o debug.asm

clean:
	rm -f circuitsmain.lis circuitsdriver.lis debug.lis circuitsmain.o circuitsdriver.o debug.o circuits.out

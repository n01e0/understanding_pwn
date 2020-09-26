all: increment

increment: src.c
	gcc -fno-stack-protector -no-pie src.c -o increment

clean: increment
	rm increment

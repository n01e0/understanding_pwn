all: stack_again

stack_again: src.c
	gcc -fno-stack-protector -no-pie src.c -o stack_again

clean: stack_again
	rm stack_again

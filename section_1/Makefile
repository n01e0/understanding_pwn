all: hello

hello: hello.c
	gcc -fno-stack-protector -no-pie hello.c -o hello

clean: hello
	rm hello

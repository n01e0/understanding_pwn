all: chall

chall: src.c
	gcc -fno-stack-protector -no-pie src.c -o chall
	cp chall ../../../distfiles/second/

clean: chall
	rm chall

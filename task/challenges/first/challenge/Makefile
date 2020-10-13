all: chall

chall: src.c
	gcc -fno-stack-protector -no-pie src.c -o chall
	cp chall ../../../distfiles/first/

clean: chall
	rm chall

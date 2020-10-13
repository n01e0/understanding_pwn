all: chall

chall: src.c
	gcc -fno-stack-protector -no-pie src.c -o chall
	cp chall ../../../distfiles/zero/

clean: chall
	rm chall

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void read_flag() {
    execve("/bin/cat", (char *[]){"/bin/cat", "/flag", NULL}, NULL);
}

int main() {
    char buf[30];

    printf("buf <");
    gets(buf);
}

__attribute__((constructor))
void setup() {
    if (fopen("/flag", "r") == NULL)
        fprintf(stderr, "Oops!! challenge is broken...\n"),exit(1);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    alarm(60);
}


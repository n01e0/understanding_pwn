#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void read_flag() {
    system("cat flag.txt");
    exit(0);
}

int main() {
    char buf[30];

    printf("buf <");
    gets(buf);
}

__attribute__((constructor))
void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    alarm(60);
}

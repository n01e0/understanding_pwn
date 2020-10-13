#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void read_flag() {
    system("cat flag.txt");
}

int main() {
    char hackme[10];
    char name[30];

    printf("What's your name?\n> ");
    gets(name);
    if (strcmp("hacked!", hackme) == 0)
        read_flag();
    printf("Hello %s!!\n", name);
}

__attribute__((constructor))
void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    alarm(60);
}

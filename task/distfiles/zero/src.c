#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void win() {
    system("cat /home/user/flag");
}

int main() {
    int zero = 0;
    char name[30];
    printf("What's your name?\n> ");
    scanf("%s", name);
    if (zero != 0) {
        win();
    }
    printf("hello %s!\n", name);
}

__attribute__((constructor))
void setup() {
    if (fopen("/home/user/flag", "r") == NULL)
        exit(1), fprintf(stderr, "Oops!, flag is broken.\n");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    alarm(60);
}


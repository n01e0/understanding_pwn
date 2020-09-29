#include <stdio.h>
#include <stdlib.h>

void win() {
    system("sh");
}

int main() {
    int zero = 0;

    char name[30];
    printf("What's your name?\n>");
    fread(name, 1, 100, stdin);
    if (zero == 0xdeafbeef) {
        win();
    }
    printf("hello %s!\n", name);
}

#include <stdio.h>
#include <stdlib.h>

int main() {
    int zero = 0;
    char name[30];
    printf("What's your name?\n>");
    scanf("%s", name);
    if (zero != 0) {
        system("sh");
    }
    printf("hello %s!\n", name);
}

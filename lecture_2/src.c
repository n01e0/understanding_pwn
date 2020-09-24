#include <stdio.h>

int inc(int a) {
    return a + 1;
}

int main() {
    int one = 1;
    int two = inc(one);
    printf("%d + 1 = %d\n", one, two);
}

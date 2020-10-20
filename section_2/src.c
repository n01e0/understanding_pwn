#include <stdio.h>

int inc(int a) {
    return a + 1;
}

int main() {
    int val;
    scanf("%d", &val);
    int ans = inc(val);
    printf("%d + 1 = %d\n", val, ans);
}

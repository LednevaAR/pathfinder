#include <stdio.h>
int main() {
    const int LEN = 1000, x = LEN/2;
    int a[LEN];
    for (int i = 0; i < LEN; i++) {
        a[i] = a[x] * i;
    }
    return 0;
}
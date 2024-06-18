#include <stdio.h>
int main() {
    const int LEN = 1000, x = LEN/2;
    float a[LEN], t = a[x];
    for (int i = 0; i <= x; i++) {
        a[i] = t * i;
    }
    t = a[x];
    for (int i = x + 1; i < LEN; i++) {
        a[i] = t * i;
    }
    return 0;
}
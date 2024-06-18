#include <stdio.h>
int main() {
    const int LEN = 1000;
    int a[LEN], ind[LEN], min = LEN;
    for (int i = 0; i < LEN; i++) {
        a[i] += 17;
        if (a[i] > 0) {
            ind[i] = i;
        } else ind[i] = LEN;
        if (ind[i] < min) min = ind[i];
    }
    for (int i = min + 1; i < LEN; i++) {
        a[i] -= 17;
    }
    return 0;
}


#include <stdio.h>
int main() {
    const int LEN = 1000;
    int a[LEN];
    for (int i = 0; i < LEN; i++) {
        a[i] += 17;
        if (a[i] > 0) break;
    }
    return 0;
}


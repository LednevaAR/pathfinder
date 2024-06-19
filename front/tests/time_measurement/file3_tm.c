#include <stdio.h>
#include <time.h>
int main() {
    clock_t start, end;
    double cpu_time_used;
    const int LEN = 1000;
    int a[LEN];
    for (int i = 0; i < LEN; i++) {
        a[i] = -i - 170000000;
    }
    start = clock();
    for (long long int j = 0; j < 10000000; j++) {
        for (int i = 0; i < LEN; i++) {
            a[i] += 17;
            if (a[i] > 0) break;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f", cpu_time_used);
    return 0;
}
#include <stdio.h>
#include <time.h>
int main() {
    clock_t start, end;
    double cpu_time_used;
    const int LEN = 1000, x = LEN/2;
    int a[LEN];
    start = clock();
    for (long long int j = 0; j < 10000000; j++) {
    	for (int i = 0; i < LEN; i++) {
            a[i] = a[x] * i;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f", cpu_time_used);
    return 0;
}
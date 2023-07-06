#include <stdio.h>
void main () {
	int a [128];
	int * a2 = 1 + a ;
	int * a1 = a ;
	for ( long unsigned int i = 0; i < 64; ++ i ) {
		a2 [ i ] = a1 [ i ] + 1;
	}
}
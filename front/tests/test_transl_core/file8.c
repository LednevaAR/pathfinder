#include <stdio.h>
void main () {
	int a [128];
	for ( int i = 0; i < 128; i ++) {
		if ( a [ i ] > 0) {
			a [ i ] = 6;
		} else {
			a [ i ] = 9;
		}
	}
}

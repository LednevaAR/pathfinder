#include <stdio.h>
void copyElems64AndAdd1 ( int * a , int * b ) {
	for ( long unsigned int i = 0; i < 64; ++ i ) {
		a [ i ] = b [ i ] + 1;
	}
}
void main () {
	int a [512];
	int * a1 = a ;
	int * a2 = a + 1;
	copyElems64AndAdd1 ( a1 , a2 ) ;
}
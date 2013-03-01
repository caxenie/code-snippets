#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
  {
	double a[10];

  // Fill the array = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
  for (int i = 0; i < sizeof( a ) / sizeof( a[ 0 ] ); i++)
    a[ i ] = i;

  // shift up
  memmove( a + 1, a, sizeof( a ) - sizeof( a[ 0 ] ) );
  a[0] = 99.99;

  // print it
  for (int i = 0; i < sizeof( a ) / sizeof( a[ 0 ] ); i++)
    printf("a[ %d ] = %lf\n", i, a[ i ]);

  return EXIT_SUCCESS;
  }

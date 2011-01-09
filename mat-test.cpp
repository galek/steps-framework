#include	<stdio.h>
#include	"matrix3d.h"

int main ()
{
	Matrix3D m1, m2, inv;

	m1 [0][0] = 1;
	m1 [0][1] = 1;
	m1 [0][2] = 1;
	m1 [1][1] = 0;
	m1 [1][1] = 1;
	m1 [1][2] = 1;
	m1 [2][0] = 0;
	m1 [2][1] = 0;
	m1 [2][2] = 1;
	
	m2  = m1;
	inv = m1;

	inv.invert ();

	Matrix3D a = m1 * inv;
	Matrix3D b = inv * m1;

	printf ( "A=\n" );

	for ( int i = 0; i < 3; i++ ) {
		for ( int j = 0; j < 3; j++ )
			printf ( "%5f ", b [i][j] );

		printf ( "\n" );
	}

	return 0;
}

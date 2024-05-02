
#include	"shslib.h"
#include	"shsprivate.h"

double factorial ( int number )
{
	double	rv = 1.0;

	if ( number < 0 )
	{
		fprintf ( stderr, "Cannot call factorial() with a negative number!\n" );
		exit ( 1 );
	}

	if ( number == 1 )
	{
		return ( 1.0 );
	}

	rv = 1.0;
	for ( int ndx = 2; ndx <= number; ndx++ )
	{
		rv = rv * ndx;
	}

	return ( rv );
}

#ifdef TESTMAIN
int main ( int argc, char *argv[] )
{
	int number = atoi ( argv[1] );
	printf ( "%d %.4f\n", number, factorial(number) );
	return ( 0 );
}
#endif

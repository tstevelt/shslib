/*---------------------------------------------------------------------------
	from: https://www.khanacademy.org/math/statistics-probability/summarizing-quantitative-data/variance-standard-deviation-population/a/calculating-standard-deviation-step-by-step
---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdio.h>
#include	<math.h>


double stddev ( double Array[], int Count )
{
	double	Mean = 0.0;
	double	SumDiffSq = 0.0;
	double	rv;

	for (  int i = 0; i < Count; i++ )
	{
		Mean += Array[i];
	}
	Mean = Mean / Count;
	
	for ( int i = 0; i < Count; i++ )
	{
		SumDiffSq += pow(Array[i] - Mean,2);
	}

	rv = sqrt ( SumDiffSq / (double) Count );

	return ( rv );
}

#ifdef TESTMAIN
int main ()
{
	double	Array[] = { 6, 2, 3, 1 };

	printf ( "stddev = %.2f\n", stddev ( Array, 4 ));

	return ( 0 );
}
#endif

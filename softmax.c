/*----------------------------------------------------------------------------
	Program : softmax.c
	From    : https://slaystudy.com/implementation-of-softmax-activation-function-in-c-c/
	Modifed : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Aug 2023
	Synopsis: 
	Return  : changed from void to int.

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		08/31/2023	Added debug.  Returned index of maximum probablity.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include <assert.h>

static int Debug = 0;

int softmax(double* Array, size_t size) 
{
	int i;
	double r, m, sum, constant;
	int	rv;

	m = -INFINITY;
	for (i = 0; i < size; ++i) 
	{
		if (m < Array[i]) 
		{
			m = Array[i];
		}
	}

	sum = 0.0;
	for (i = 0; i < size; ++i) 
	{
		sum += exp(Array[i] - m);
	}

	constant = m + log(sum);
	if ( Debug ) printf ( "m %g constant %g\n", m, constant );
	for (i = 0; i < size; ++i) 
	{
		r = Array[i] - constant;
		if ( Debug ) printf ( "r %g\n", r );
		Array[i] = exp(r);
	}

	m = Array[0];
	rv = 0;
	for (i = 1; i < size; ++i) 
	{
		if ( m < Array[i] )
		{
			m = Array[i];
			rv = i;
		}
	}

	return ( rv );
}

#ifdef TESTMAIN
int main() 
{
	double Array[] = { 1. , 4.2 , 0.6 , 1.23 , 4.3 , 1.2, 2.5 };
	int i, n = sizeof(Array) / sizeof(double);

	printf("Input Array: ");
	for (i = 0; i < n; ++i)
		printf("%lf ", Array[i]);
	printf("\n\n");

	softmax(Array, n);

	printf("Softmax Array: ");
	double Total = 0.0;
	for (i = 0; i < n; ++i)
	{
		printf("%lf ", Array[i]);
		Total += Array[i];
	}
	printf("\nTotal %g\n", Total );
}
#endif

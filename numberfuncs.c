/*----------------------------------------------------------------------------
	Program : numberfuncs.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2018
	Synopsis: various min and max functions, based on data type.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		2023-10-05	added dminArra and dmaxArray

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int cmax ( char number1, char number2 )
{
	if ( number1 > number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

int smax ( short number1, short number2 )
{
	if ( number1 > number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

int imax ( int number1, int number2 )
{
	if ( number1 > number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

int lmax ( long number1, long number2 )
{
	if ( number1 > number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

double dmax ( double number1, double number2 )
{
	if ( number1 > number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

int cmin ( char number1, char number2 )
{
	if ( number1 < number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

int smin ( short number1, short number2 )
{
	if ( number1 < number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

int imin ( int number1, int number2 )
{
	if ( number1 < number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

int lmin ( long number1, long number2 )
{
	if ( number1 < number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

double dmin ( double number1, double number2 )
{
	if ( number1 < number2 )
	{
		return ( number1 );
	}
	return ( number2 );
}

double dmaxArray ( double number[], int count )
{
	double	rv;

	rv = number[0];

	for ( int ndx = 1; ndx < count; ndx++ )
	{
		if ( rv < number[ndx] )
		{
			rv = number[ndx];
		}
	}
	return ( rv );
}

double dminArray ( double number[], int count )
{
	double	rv;

	rv = number[0];

	for ( int ndx = 1; ndx < count; ndx++ )
	{
		if ( rv > number[ndx] )
		{
			rv = number[ndx];
		}
	}
	return ( rv );
}

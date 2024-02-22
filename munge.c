/*----------------------------------------------------------------------------
	Program : munge.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 06/03/2019
	Synopsis: Functions to mess (a little bit) with numbers and strings.
			  Assumes calling program has called srand.  If not, these
			  functions don't care.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

double dblMunge ( double number, double min, double max )
{
	double	range, amount;

	if ( min >= max )
	{
		return ( number );
	}

	range = max - min;

	amount = range * (double) rand() / (double) RAND_MAX;

	amount = amount + min;

	number = number + amount;

	return ( number );
}

int intMunge ( int number, int min, int max )
{
	if ( min >= max )
	{
		return ( number );
	}

	return ( number );
}

long longMunge ( long number, long min, long max )
{
	if ( min >= max )
	{
		return ( number );
	}

	return ( number );
}

#define		MAXMUNGESTRING		1024
typedef struct
{
	char	Upper;
	char	Lower;
	long	Random;
} ALPHA_RECORD;

static ALPHA_RECORD		AlphaArray[26] =
{
	{ 'A', 'a', 0 },
	{ 'B', 'b', 0 },
	{ 'C', 'c', 0 },
	{ 'D', 'd', 0 },
	{ 'E', 'e', 0 },
	{ 'F', 'f', 0 },
	{ 'G', 'g', 0 },
	{ 'H', 'h', 0 },
	{ 'I', 'i', 0 },
	{ 'J', 'j', 0 },
	{ 'K', 'k', 0 },
	{ 'L', 'l', 0 },
	{ 'M', 'm', 0 },
	{ 'N', 'n', 0 },
	{ 'O', 'o', 0 },
	{ 'P', 'p', 0 },
	{ 'Q', 'q', 0 },
	{ 'R', 'r', 0 },
	{ 'S', 's', 0 },
	{ 'T', 't', 0 },
	{ 'U', 'u', 0 },
	{ 'V', 'v', 0 },
	{ 'W', 'w', 0 },
	{ 'X', 'x', 0 },
	{ 'Y', 'y', 0 },
	{ 'Z', 'z', 0 },
};

static int cmpalpha ( ALPHA_RECORD *a, ALPHA_RECORD *b )
{
	if ( a->Random < b->Random )
	{
		return ( -1 );
	}
	if ( a->Random > b->Random )
	{
		return ( 1 );
	}
	return ( 0 );
}

char *strMunge ( char String[] )
{
	static	char	WorkString[MAXMUNGESTRING];
	int		xl, xi;
	static	int		Index = -1;

	xl = nsStrlen ( String );
	if ( xl > MAXMUNGESTRING )
	{
		return ( String );
	}

	if ( Index == -1 )
	{
		for ( xi = 0; xi < 26; xi++ )
		{
			AlphaArray[xi].Random = rand();
		}
		qsort ( AlphaArray, 26, sizeof(ALPHA_RECORD), (int(*)())cmpalpha );
		Index = 0;
	}

	for ( xi = 0; xi < xl; xi++ )
	{
		if ( String[xi] >= 'A' && String[xi] <= 'Z' )
		{
			if ( Index >= 26 )
			{
				Index = 0;
			}
			WorkString[xi] = AlphaArray[Index++].Upper;
		}
		else if ( String[xi] >= 'a' && String[xi] <= 'z' )
		{
			if ( Index >= 26 )
			{
				Index = 0;
			}
			WorkString[xi] = AlphaArray[Index++].Lower;
		}
		else
		{
			WorkString[xi] = String[xi];
		}
	}
	WorkString[xi] = '\0';

	return ( WorkString );
}


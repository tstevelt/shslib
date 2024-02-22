/*----------------------------------------------------------------------------
	Program : trimfuncs.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time, perhaps 1989
	Synopsis: Trim white space.  Originally writtern for textp app.
	Return  : 

	Who		Date	Modification
	---------------------------------------------------------------------
	tms		2020	Changed function names to avoid name space collisions.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

void TrimRight ( char *b )
{
	int		bl;

	if ( b == (char *)0 )
	{
		return;
	}

	for ( bl = nsStrlen ( b ); bl; bl -- )
	{
		if ( (int) b[bl-1] <= 32 || (int) b[bl-1] > 126 )
		{
			b[bl-1] = '\0';
		}
		else
		{
			return;
		}
	}

    return;
}

void TrimLeft ( char *b )
{
	int		xl, xs, xi, xo;

	/*----------------------------------------------------------
		find starting char ...
	----------------------------------------------------------*/
	if ( b == (char *)0 )
	{
		return;
	}

	xl = nsStrlen ( b );
	for ( xs = 0; xs < xl; )
	{
		if ( (int) b[xs] > 32 && (int) b[xs] <= 126)
			break;
		
		xs++;
	}
	if (xs == xl )
	{
		b[0] = '\0';
		return;
	}

	/*----------------------------------------------------------
		if leading white, then shift everything to the 
		left, including the trailing zero.
	----------------------------------------------------------*/
	if ( xs > 0 )
	{
		for ( xi = xs, xo = 0; xi <= xl; xi++, xo++ )
		{
			b[xo] = b[xi];
		}
	}
}

void TrimRightAndLeft ( char b[] )
{
	int		xs, xl, xi, xo;

	/*----------------------------------------------------------
		find starting char ...
	----------------------------------------------------------*/
	if ( b == (char *)0 )
	{
		return;
	}

	xl = nsStrlen ( b );
	for ( xs = 0; xs < xl; )
	{
		if ( (int) b[xs] > 32 && (int) b[xs] <= 126)
			break;
		
		xs++;
	}

	/*----------------------------------------------------------
		right TrimRightAndLeft, smashing white with nulls ...
	----------------------------------------------------------*/
	for ( xi = xl - 1; xi >= xs; xi-- )
	{
		if ( (int) b[xi] > 32 && (int) b[xi] <= 126 )
			break;

		b[xi] = '\0';
		xl--;
	}

	/*----------------------------------------------------------
		if leading white, then shift everything to the 
		left, including the trailing zero.
	----------------------------------------------------------*/
	if ( xs > 0 )
	{
		for ( xi = xs, xo = 0; xi <= xl; xi++, xo++ )
			b[xo] = b[xi];
	}
}

void TrimOptionalLength ( char SomeString[], int OptionalLength )
{
	int	xl;

	if ( SomeString == (char *)0 )
	{
		return;
	}

	if ( OptionalLength > 0 )
		xl = OptionalLength;
	else
		xl = nsStrlen ( SomeString );
	
	xl--;

	while ( xl >= 0 )
	{
		if ( SomeString [xl] == '\0' )
		{
			xl = -1;
		}
		else if ( SomeString [xl] <= ' ' || SomeString[xl] > 126 )
		{
			SomeString[xl] = '\0';
			xl--;
		}
		else
		{
			xl = -1;
		}
	}
}

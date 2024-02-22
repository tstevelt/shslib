/*----------------------------------------------------------------------------
	Program : nsSimilar.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2020
	Synopsis: See how similar two strings are.  Null safe.
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

#include	"shslib.h"

double nsSimilar ( char *String1, char *String2 )
{
	double	dblRV;
	int		Length1, Length2, MinLength, MaxLength;
	int		ndx;
	int		Count;

	if ( String1 == NULL || String2 == NULL )
	{
		return ( 0.0 );
	}
	if (( Length1 = nsStrlen(String1)) == 0 )
	{
		return ( 0.0 );
	}
	if (( Length2 = nsStrlen(String2)) == 0 )
	{
		return ( 0.0 );
	}

	MinLength = imin ( Length1, Length2 );
	MaxLength = imax ( Length1, Length2 );

	for ( ndx = 0, Count = 0; ndx < MinLength; ndx++ )
	{
		if ( String1[ndx] == String2[ndx] )
		{
			Count++;
		}
	}

	dblRV = (double) Count / (double) MaxLength;

	return ( dblRV );
}

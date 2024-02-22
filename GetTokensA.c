/*----------------------------------------------------------------------------
	Program : GetTokensA.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2020
	Synopsis: This is the same as gettok3() in pwlib
			  tokcnt = GetTokensA ( WorkBuffer, ":\n", tokens, 20 );
			  leading and empty delimiters are significant
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

#include	<string.h>
#include	"shslib.h"

int GetTokensA ( char Buffer[], char Delim[], char *tokens[], int maxtoks )
{
	int		rv, xi, xn, xd, xl;

	xl = nsStrlen ( Delim );

	for ( xi = 0, rv = 0, xn = 1; Buffer[xi]; xi++ )
	{
		if ( xn == 1 )
		{
			tokens[rv] = &Buffer[xi];
			rv++;
			if ( rv == maxtoks )
			{
				break;
			}
			xn = 0;
		}

		for ( xd = 0; xd < xl; xd++ )
		{
			if ( Buffer[xi] == Delim[xd] )
			{
				Buffer[xi] = '\0';
				xn = 1;
				break;
			}
		}
	}

	return ( rv );

}

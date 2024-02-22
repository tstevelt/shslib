/*----------------------------------------------------------------------------
	Program : GetTokensD.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 11/13/2002
	Synopsis: based on gettoks - but takes a string of delimeters.
			  extract tokens from text line.  
			  DESTROYS original (fill whitespace with nulls).
	Return  : number of tokens extracted.

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		11/13/2020	renamed GetTokensD  in shslib.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdio.h>
#include	<string.h>

#include	"shslib.h"

int GetTokensD ( char xbuf[], char delim[], char *toks[], int maxtoks )
{
	int		rv = 0;
	int		xl, xi, xf;

	if ( maxtoks < 0 )
		return ( rv );	

	xl = nsStrlen ( xbuf );
	xf = 1;
	for ( xi = 0; xi < xl; xi++ )
	{
		if ( nsStrchr ( delim, xbuf[xi] ) != (char *) 0 )
		{
			xbuf[xi] = '\0';
			if ( xf == 0 )
				xf = 1;
		}
		else
		{
			if ( xf )
			{
				xf = 0;
				toks[rv] = &xbuf[xi];
				rv++;

				if ( rv >= maxtoks )
					return ( rv );	
			}
		}
	}

	return ( rv );
}

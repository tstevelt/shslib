/*----------------------------------------------------------------------------
	Program : GetTokensW.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 09/08/1997
	Synopsis: extract tokens from text line.  
			  DESTROYS original (fill whitespace with nulls).
	Return  : number of tokens extracted.

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		04/11/2002	stop complaining and exitting if reaches maxtoks.  
						just return what we got.
	tms		11/13/2020	renamed GetTokensW in shslib

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int GetTokensW ( char xbuf[], char *toks[], int maxtoks )
{
	int		rv = 0;
	int		xl, xi, xf;

	if ( maxtoks < 0 )
		return ( rv );	

	xl = nsStrlen ( xbuf );
	xf = 1;
	for ( xi = 0; xi < xl; xi++ )
	{
		switch ( xbuf[xi] )
		{
			case ' ':
			case '\n':
			case '\r':
			case '\t':
			case '\b':	xbuf[xi] = '\0';
						if ( xf == 0 )
							xf = 1;
						break;

			default:	if ( xf )
						{
							xf = 0;
							toks[rv] = &xbuf[xi];
							rv++;

							if ( rv >= maxtoks )
								return ( rv );	

						}
						break;
		}
	}

	return ( rv );
}

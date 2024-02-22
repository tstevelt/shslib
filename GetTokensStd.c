/*----------------------------------------------------------------------------
	Program : GetTokensStd.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 01/19/2021
	Synopsis: Get tokens from string separated by specified delimiters.
			  Handle "empty" fields, ie. ",,"
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

int GetTokensStd ( char xbuf[], char delim[], char *toks[], int maxtoks, int Verbose )
{
	int		rv = 0;
	int		xi, xl;

	/*---------------------------------------------------------------------------
		this was supposed to use standard string function strtok()
		but that won't work as needed. because:
		1. "All the initial bytes that are members of this set are discarded"
		2. "... if the remainder of string consists only of delimiter bytes, strtok returns a null pointer."

		This example illustrates the problem

DATE,TRANSACTION ID,DESCRIPTION,QUANTITY,SYMBOL,PRICE,COMMISSION,AMOUNT,REG FEE,SHORT-TERM RDM FEE,FUND REDEMPTION FEE, DEFERRED SALES CHARGE
07/02/2013,10228476688,CASH RECEIPTS THIRD PARTY,,,,,100000.00,,,,
07/02/2013,10228575171,REBATE,,,,,100.00,,,,
07/02/2013,10228575176,REBATE,,,,,200.00,,,,

	---------------------------------------------------------------------------*/

	xl = nsStrlen(delim);
	if ( xl == 0 )
	{
		return ( 0 );
	}

	xl = nsStrlen(xbuf);
	if ( xl == 0 )
	{
		return ( 0 );
	}
	
	if ( Verbose )
	{
		printf ( "%s<br>\n", xbuf );
	}

	toks[rv] = &xbuf[0];
	for ( xi = 0; xi < xl; xi++ )
	{
		if ( nsStrchr ( delim, xbuf[xi] ) != (char *)0 )
		{
			xbuf[xi] = '\0';
			
			if ( Verbose )
			{
				printf ( "%d %s<br>\n", rv, toks[rv] );
			}

			rv++;
			toks[rv] = &xbuf[xi+1];
		}
	}

	if ( Verbose )
	{
		printf ( "%d %s<br>\n", rv, toks[rv] );
	}

	rv++;

	return ( rv );
}

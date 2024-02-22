/*----------------------------------------------------------------------------
	Program : lset.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time, perhaps 1989
	Synopsis: Write chars into buffer, space pad right to length.
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

void lset ( void *dest, void *from, int number )
{
	int		xl, xi;
	char 	*cpd, *cps;

	cpd = dest;
	cps = from;

	xl = (int) nsStrlen ( cps );

	if ( xl > number )
		xl = number;

	for ( xi = 0; xi < xl; xi++ )
		cpd[xi] = cps[xi];

	for ( ; xi < number; xi++ )
		cpd[xi] = ' ';
}

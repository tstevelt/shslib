/*----------------------------------------------------------------------------
	Program : SessionFuncs.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: Contains only one function, MakeSessionID()
			  Create random letters and numbers session code.
			  SessionBuffer must have room for Length plus one null char.
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

int MakeSessionID ( char SessionBuffer[], int Length, int InitRandom )
{
	static	int		firstpass = 1;
	int		ndx;
	int		Letter, Number;
	double	dblValue;

	if ( firstpass )
	{
		firstpass = 0;
		if ( InitRandom )
		{
			seed_random_with_usec ();
		}
	}

	for ( ndx = 0; ndx < Length; ndx++ )
	{
		Letter = 0;
		Number = 0;
		while ( Letter == 0 && Number == 0 )
		{
			Letter = random_range ( 65, 90 );
			Number = random_range ( 49, 57 );
		}
		dblValue = d_random ();
		if ( dblValue < 0.8 )
		{
			SessionBuffer[ndx] = Letter;
		}
		else
		{
			SessionBuffer[ndx] = Number;
		}
	}
	
	SessionBuffer[ndx] = '\0';

	return ( 0 );
}

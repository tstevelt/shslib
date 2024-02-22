/*----------------------------------------------------------------------------
	Program : ValidZipCode.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2019
	Synopsis: Count numeric characters in zip code.  No lookup.  No Canada.
	Return  : Count.

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

int ValidZipCode ( char *TestZipCode )
{
	int		len, ndx, count;

	if (( len = nsStrlen ( TestZipCode )) == 0 )
	{
		return ( 0 );
	}

	for ( ndx = 0, count = 0; ndx < len; ndx++ )
	{
		if ( TestZipCode[ndx] >= '0' && TestZipCode[ndx] <= '9' )
		{
			count++;
		}
	}

	return ( count );
}

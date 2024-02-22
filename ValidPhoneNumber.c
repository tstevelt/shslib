/*----------------------------------------------------------------------------
	Program : ValidPhoneNumber.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2019
	Synopsis: Count numeric characters in string. Null safe
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

int ValidPhoneNumber ( char *TestPhoneNumber )
{
	int		len, ndx, count;

	if (( len = nsStrlen ( TestPhoneNumber )) == 0 )
	{
		return ( 0 );
	}

	for ( ndx = 0, count = 0; ndx < len; ndx++ )
	{
		if ( TestPhoneNumber[ndx] >= '0' && TestPhoneNumber[ndx] <= '9' )
		{
			count++;
		}
	}

	return ( count );
}

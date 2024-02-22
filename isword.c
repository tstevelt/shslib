/*----------------------------------------------------------------------------
	Program : isword.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 12/06/2020
	Synopsis: Determine if a string of characters might be a word.
	          Written for acct/import to bettter parse CSV files.
	Return  : 1 if word, 0 otherwise.

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		02/24/2021	Moved test program into ../test/subdir

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int isword ( char *SomeString )
{
	int		Length, ndx, hyphencount;

	if ( SomeString == (char *)0 )
	{
		return ( 0 );
	}

	if (( Length = strlen ( SomeString )) == 0 )
	{
		return ( 0 );
	}

	for ( ndx = 2; ndx < Length; ndx++ )
	{
		if (( SomeString[ndx-2] == SomeString[ndx-1] ) &&
			( SomeString[ndx-1] == SomeString[ndx]   ))
		{
			return ( 0 );
		}
	}

	hyphencount = 0;
	for ( ndx = 0; ndx < Length; ndx++ )
	{
		if ( SomeString[ndx] == '-' )
		{
			hyphencount++;
			if ( hyphencount == 2 )
			{
				return ( 0 );
			}
		}
		else if (( SomeString[ndx] >= 'A' ) &&
				 ( SomeString[ndx] <= 'Z' ))
		{
			continue;
		}
		else if (( SomeString[ndx] >= 'a' ) &&
				 ( SomeString[ndx] <= 'z' ))
		{
			continue;
		}
		else
		{
			return ( 0 );
		}
	}
	return ( 1 );
}

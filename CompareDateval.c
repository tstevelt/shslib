/*----------------------------------------------------------------------------
	Program : CompareDateval.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: xxxxxxxxxxx
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

int CompareDateval ( DATEVAL *a, DATEVAL *b )
{
	if ( a->year4 < b->year4 )
	{
		return ( -1 );
	}
	if ( a->year4 > b->year4 )
	{
		return ( 1 );
	}

	if ( a->month < b->month )
	{
		return ( -1 );
	}
	if ( a->month > b->month )
	{
		return ( 1 );
	}

	if ( a->day < b->day )
	{
		return ( -1 );
	}
	if ( a->day > b->day )
	{
		return ( 1 );
	}

	return ( 0 );
}

/*----------------------------------------------------------------------------
	Program : DateDiff.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2020
	Synopsis: Return difference between two dates
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

int DebugDateDiff = 0;

long DateDiff ( DATEVAL *a, DATEVAL *b )
{
	long	Difference;
	struct	tm	timeptr;
	time_t	answer1;
	time_t	answer2;

	if ( DebugDateDiff )
	{
		printf ( "%d/%d/%d %d/%d/%d : ", a->month, a->day, a->year4, b->month, b->day, b->year4 );
	}

	Difference = 0;

	memset ( &timeptr, 0, sizeof(struct tm) );
	timeptr.tm_mon  = a->month - 1;
	timeptr.tm_mday = a->day;
	timeptr.tm_year = a->year4 - 1900;
	answer1 = mktime ( &timeptr );

	if ( DebugDateDiff )
	{
		printf ( "%d %d %d ... ", timeptr.tm_mon, timeptr.tm_mday, timeptr.tm_year );
	}
	
	memset ( &timeptr, 0, sizeof(struct tm) );
	timeptr.tm_mon  = b->month - 1;
	timeptr.tm_mday = b->day;
	timeptr.tm_year = b->year4 - 1900;
	answer2 = mktime ( &timeptr );

	Difference = (answer2 - answer1) / 86400;

	if ( DebugDateDiff )
	{
		printf ( " : %d %d %d = %ld\n", timeptr.tm_mon, timeptr.tm_mday, timeptr.tm_year, Difference );
	}
	
	return ( Difference );
}

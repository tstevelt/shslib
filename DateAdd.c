/*----------------------------------------------------------------------------
	Program : DateAdd.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2020
	Synopsis: Add number of days to starting date
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		02/25/2021	Match output year digit count to input year.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int		DebugDateAdd = 0;

int DateAdd ( DATEVAL *a, int NumberOfDays, DATEVAL *b )
{
	struct	tm	timeptr;
	struct	tm	*tp;
	time_t	answer1;
	time_t	answer2;

	memset ( &timeptr, 0, sizeof(struct tm) );
	timeptr.tm_mon  = a->month - 1;
	timeptr.tm_mday = a->day;

	timeptr.tm_year = a->year4 - 1900;

	answer1 = mktime ( &timeptr );

	if ( DebugDateAdd )
	{
		printf ( "%d/%d/%d %ld + %ld = ", timeptr.tm_mon + 1, timeptr.tm_mday, timeptr.tm_year, answer1, ((time_t)NumberOfDays * 86400) );
	}

	answer2 = answer1 + ((time_t)NumberOfDays * 86400);

	tp = localtime ( &answer2 );

	if ( DebugDateAdd )
	{
		printf ( "%d/%d/%d ... ", tp->tm_mon + 1,  tp->tm_mday, tp->tm_year );
	}

	b->month  = tp->tm_mon + 1;
	b->day    = tp->tm_mday;
	b->year2  = tp->tm_year % 100;
	b->year4  = tp->tm_year + 1900;


	return ( 0 );
}

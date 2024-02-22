/*--------------------------------------------------------------------
    CurrentDateTime.c
--------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int CurrentDateTime ( DATETIMEVAL *Now )
{
	time_t	tvec;
	struct	tm	*t;
	char	*cp;
	DATEVAL	Today;

	(void) time ( &tvec );
	t  = localtime ( &tvec );
	if ( t == NULL )
	{
		fprintf ( stderr, "CurrentDateTime: this is weird\n" );
		exit ( 1 );
	}

	CurrentDateval ( &Today );

	Now->epoch = tvec;
	Now->dst = t->tm_isdst;

	Now->month  = Today.month;
	Now->day    = Today.day;
	Now->year2  = Today.year2;
	Now->year4  = Today.year4;

	Now->hour   = t->tm_hour;
	Now->minute = t->tm_min;
	Now->second = t->tm_sec;

	switch ( Now->month )
	{
		case 1: cp = "Jan"; break;
		case 2: cp = "Feb"; break;
		case 3: cp = "Mar"; break;
		case 4: cp = "Apr"; break;
		case 5: cp = "May"; break;
		case 6: cp = "Jun"; break;
		case 7: cp = "Jul"; break;
		case 8: cp = "Aug"; break;
		case 9: cp = "Sep"; break;
		case 10: cp = "Oct"; break;
		case 11: cp = "Nov"; break;
		case 12: cp = "Dec"; break;
		default: cp = "Unk"; break;
	}

	sprintf ( Now->AsciiDateTime, "%s %d, %d - %02d:%02d",
			cp,
			Now->day,
			Now->year4,
			Now->hour,
			Now->minute );

	return ( (t->tm_wday + 1) );
}

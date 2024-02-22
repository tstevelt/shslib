/*----------------------------------------------------------------------------
	Program : fmtGetTodayDate.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: Return today's date in selected format.
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

#include	<stdio.h>
#include	<time.h>
#include	"shslib.h"

static	char	DateString[48];

char *fmtGetTodayDate ( int Format )
{
	time_t		tvec;
	struct tm	*tm;
	int			year2, year4, month, day;
	char		*ascii_month;

	tvec = time ( NULL );
	tm = localtime ( &tvec );
	year2  = tm->tm_year % 100;
	year4  = tm->tm_year + 1900;
	month = tm->tm_mon + 1;
	day   = tm->tm_mday;

	switch ( Format )
	{
		case DATEFMT_MM_DD_YY:
			sprintf ( DateString, "%02d/%02d/%02d", month, day, year2 );
			break;
		case DATEFMT_MMDDYY:
			sprintf ( DateString, "%02d%02d%02d", month, day, year2 );
			break;
		case DATEFMT_YYYY_MM_DD:
			sprintf ( DateString, "%04d-%02d-%02d", year4, month, day );
			break;
		case DATEFMT_TIMESTAMP:
			/*---+---------+---------------------+---------+---------------------+
			| id | Ydivcnt | Ydivtime            | Ystkcnt | Ystktime            |
			+----+---------+---------------------+---------+---------------------+
			|  1 |      10 | 2019-02-19 21:18:01 |    6880 | 2019-02-19 21:18:01 |
			+----+---------+---------------------+---------+--------------------*/
			sprintf ( DateString, "%04d-%02d-%02d %02d:%02d:%04d", 
						year4, month, day, tm->tm_hour, tm->tm_min, tm->tm_sec );
			break;
		case DATEFMT_MM_DD_YYYY:
			sprintf ( DateString, "%02d/%02d/%04d", month, day, year4 );
			break;
		case DATEFMT_AAA_DD_YYYY:
			switch ( month )
			{
				case 1: ascii_month = "Jan"; break;
				case 2: ascii_month = "Feb"; break;
				case 3: ascii_month = "Mar"; break;
				case 4: ascii_month = "Apr"; break;
				case 5: ascii_month = "May"; break;
				case 6: ascii_month = "Jun"; break;
				case 7: ascii_month = "Jul"; break;
				case 8: ascii_month = "Aug"; break;
				case 9: ascii_month = "Sep"; break;
				case 10: ascii_month = "Oct"; break;
				case 11: ascii_month = "Nov"; break;
				case 12: ascii_month = "Dec"; break;
			}
			sprintf ( DateString, "%s %02d, %04d", ascii_month, day, year4 );
			break;
		case DATEFMT_SYSTEM_DAYS:
			tvec = tvec / ( 24 * 60 * 60 );
			sprintf ( DateString, "%ld", tvec );
			break;
		default:
			sprintf ( DateString, "UNKNOWN FORMAT" );
			break;
	}
	return ( DateString );
}

/*----------------------------------------------------------------------------
	Program : StrToDatetimevalFmt.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
	Synopsis: Works with DATETIMEVAL instead of DATEVAL. See StrToDateval.c
	Return  : 

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

int DebugStrToDatetimevalFmt = 0;

int StrToDatetimevalFmt ( char datestr [], int Format, DATETIMEVAL *datetimeval )
{
	char	tempstr[40];
	long long	EpochMilliseconds;
	long		UnixSystemDate;
	struct tm	*tm;

	datetimeval->year2 = 0;
	datetimeval->year4 = 0;
	datetimeval->month = 0;
	datetimeval->day   = 0;
	datetimeval->hour = 0;
	datetimeval->minute = 0;
	datetimeval->second = 0;
	datetimeval->millisec = 0;

	if ( nsStrlen ( datestr ) >= 40 )
	{
		fprintf ( stderr, "StrToDatetimevalFmt: input string not recognized.\n" );
		return ( 1 );
	}

	snprintf ( tempstr, sizeof(tempstr), "%s", datestr );

	switch ( Format )
	{
		case DATEFMT_MM_DD_YY:
		case DATEFMT_MM_DD_YYYY:
		case DATEFMT_MMDDYY:
		case DATEFMT_AAA_DD_YYYY:
		case DATEFMT_YYYY_MM_DD:
			fprintf ( stderr, "StrToDatetimevalFmt: call StrToDatevalFmt for format %d\n", Format );
			break;

		case DATEFMT_EPOCH_MILLISEC:
			EpochMilliseconds = atoll ( datestr );
			datetimeval->millisec = EpochMilliseconds % 1000;
			UnixSystemDate        = EpochMilliseconds / 1000;

			if ( DebugStrToDatetimevalFmt )
			{
				printf ( "%s: %ld + %d\n", datestr, UnixSystemDate, datetimeval->millisec );
			}

			tm = localtime ( &UnixSystemDate );

			datetimeval->year2  = 2000 + tm->tm_year % 100;
			datetimeval->month  = tm->tm_mon + 1;
			datetimeval->day    = tm->tm_mday;
			datetimeval->hour   = tm->tm_hour;
			datetimeval->minute = tm->tm_min;
			datetimeval->second = tm->tm_sec;

			if ( DebugStrToDatetimevalFmt )
			{
				printf ( "%d/%d/%d %d:%d::%d\n", 
						tm->tm_mon + 1,
						tm->tm_mday,
						2000 + tm->tm_year % 100,
						tm->tm_hour,
						tm->tm_min,
						tm->tm_sec );
			}

			break;

		default:
			fprintf ( stderr, "StrToDatetimevalFmt: unknown format %d\n", Format );
			return ( 1 );
	}

//	return ( ValidDateval((DATEVAL *) datetimeval,0) );
	return ( 0 );
}

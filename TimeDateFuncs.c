/*----------------------------------------------------------------------------
	Program : TimeDateFuncs.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Long time ago ...
	Synopsis: 
	Return  : 

char *TodayDate ( void );
char *AsciiTime ( void );
char *DateYYYY_MM_DD ( time_t TimeValue );
char *DayOfWeek ( int TimeDayOfWeek );
char *MonthOfYear ( int TimeMonth );
char *TimeHHMMSS ( time_t TimeValue );
char *TimeMMDDHHMM ( time_t TimeValue );
void ConvertSecondsToDateTimeVal ( time_t Seconds, DATETIMEVAL *dtValue );


	Who			Date		Modification
	---------------------------------------------------------------------
	tms			?			TodayDate
	tms			11/18/2018	DayOfWeek		
	tms			11/18/2018	MonthOfYear		

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

char *TodayDate ()
{
	time_t			CurrentTime;
	struct tm		*unixtime;
	static char		AsciiDate[11];

// int tm_sec;     /* seconds (0 - 60) */
// int tm_min;     /* minutes (0 - 59) */
// int tm_hour;    /* hours (0 - 23) */
// int tm_mday;    /* day of month (1 - 31) */
// int tm_mon;     /* month of year (0 - 11) */
// int tm_year;    /* year - 1900 */
// int tm_wday;    /* day of week (Sunday = 0) */
// int tm_yday;    /* day of year (0 - 365) */
// int tm_isdst;   /* is summer time in effect? */
// char *tm_zone;  /* abbreviation of timezone name */
// long tm_gmtoff; /* offset from UTC in seconds */

	time ( &CurrentTime );
    unixtime = localtime ( &CurrentTime );

	unixtime->tm_year = 2000 + unixtime->tm_year % 100;

	sprintf ( AsciiDate, "%04d-%02d-%02d", unixtime->tm_year, unixtime->tm_mon + 1, unixtime->tm_mday );

	return ( AsciiDate );
}

char *AsciiTime ()
{
	time_t			CurrentTime;
//	struct tm		*unixtime;
	static char		AsciiTime[24];

// int tm_sec;     /* seconds (0 - 60) */
// int tm_min;     /* minutes (0 - 59) */
// int tm_hour;    /* hours (0 - 23) */
// int tm_mday;    /* day of month (1 - 31) */
// int tm_mon;     /* month of year (0 - 11) */
// int tm_year;    /* year - 1900 */
// int tm_wday;    /* day of week (Sunday = 0) */
// int tm_yday;    /* day of year (0 - 365) */
// int tm_isdst;   /* is summer time in effect? */
// char *tm_zone;  /* abbreviation of timezone name */
// long tm_gmtoff; /* offset from UTC in seconds */

	time ( &CurrentTime );
 //   unixtime = localtime ( &CurrentTime );

	sprintf ( AsciiTime, "%s", ctime(&CurrentTime) );

	return ( AsciiTime );
}


char *TimeHHMMSS ( time_t TimeValue )
{
	struct tm	*unixtime;
	static char	TimeBuffer[10];

	unixtime = localtime ( &TimeValue );

	sprintf ( TimeBuffer, "%02d:%02d:%02d",
		unixtime->tm_hour, unixtime->tm_min, unixtime->tm_sec );

	return ( TimeBuffer );
}

char *TimeMMDDHHMM ( time_t TimeValue )
{
	struct tm	*unixtime;
	static char	TimeBuffer[12];

	unixtime = localtime ( &TimeValue );

	sprintf ( TimeBuffer, "%02d/%02d %02d:%02d",
		unixtime->tm_mon + 1,
		unixtime->tm_mday,
		unixtime->tm_hour,
		unixtime->tm_min );

	return ( TimeBuffer );
}

char *DateYYYY_MM_DD ( time_t TimeValue )
{
	struct tm	*unixtime;
	static char	DateBuffer[12];

	unixtime = localtime ( &TimeValue );

	sprintf ( DateBuffer, "20%02d-%02d-%02d",
		unixtime->tm_year % 100,
		unixtime->tm_mon + 1,
		unixtime->tm_mday );

	return ( DateBuffer );
}

char * DayOfWeek ( int TimeDayOfWeek )
{
	switch ( TimeDayOfWeek )
	{
		case 0: return ( "Sun" );
		case 1: return ( "Mon" );
		case 2: return ( "Tue" );
		case 3: return ( "Wed" );
		case 4: return ( "Thu" );
		case 5: return ( "Fri" );
		case 6: return ( "Sat" );
	}
	return ( "???" );
}

char * MonthOfYear ( int TimeMonth )
{
	switch ( TimeMonth )
	{
		case 0: return ( "Jan" );
		case 1: return ( "Feb" );
		case 2: return ( "Mar" );
		case 3: return ( "Apr" );
		case 4: return ( "May" );
		case 5: return ( "Jun" );
		case 6: return ( "Jul" );
		case 7: return ( "Aug" );
		case 8: return ( "Sep" );
		case 9: return ( "Oct" );
		case 10: return ( "Nov" );
		case 11: return ( "Dec" );
	}
	return ( "???" );
}

/*---------------------------------------------------------------------
	This is a mis-leading name.  Only uses hour, minute and second.
---------------------------------------------------------------------*/
void ConvertSecondsToDateTimeVal ( time_t Seconds, DATETIMEVAL *dtValue )
{
	memset ( dtValue, '\0', sizeof(DATETIMEVAL) );

	dtValue->hour = Seconds / 3600;

	Seconds = Seconds - dtValue->hour * 3600;
	dtValue->minute = Seconds / 60;

	dtValue->second = Seconds - dtValue->minute * 60;
}

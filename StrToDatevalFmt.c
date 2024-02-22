/*----------------------------------------------------------------------------
	Program : StrToDatevalFmt.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
	Synopsis: Extract DATEVAL from string with specified format.
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

int StrToDatevalFmt ( char datestr [], int Format, DATEVAL *dateval )
{
	char	tempstr[40];

	dateval->year2 = 0;
	dateval->year4 = 0;
	dateval->day   = 0;
	dateval->month = 0;

	if ( nsStrlen ( datestr ) >= 40 )
	{
		fprintf ( stderr, "StrToDatevalFmt: input string not recognized.\n" );
		return ( 1 );
	}

	snprintf ( tempstr, sizeof(tempstr), "%s", datestr );

	switch ( Format )
	{
		case DATEFMT_MM_DD_YY:
		case DATEFMT_MM_DD_YYYY:
			dateval->year2  = nsAtoi ( &tempstr[6] ) % 100;
			dateval->year4  = nsAtoi ( &tempstr[6] );
			tempstr[5] = '\0';
			dateval->day   = nsAtoi ( &tempstr[3] );
			tempstr[2] = '\0';
			dateval->month = nsAtoi ( &tempstr[0] );
			break;
		case DATEFMT_MMDDYY:
			dateval->year2  = nsAtoi ( &tempstr[4] );
			dateval->year4  = nsAtoi ( &tempstr[4] );
			tempstr[4] = '\0';
			dateval->day   = nsAtoi ( &tempstr[2] );
			tempstr[2] = '\0';
			dateval->month = nsAtoi ( &tempstr[0] );
			break;
		case DATEFMT_AAA_DD_YYYY:
			dateval->year2  = nsAtoi ( &tempstr[7] ) % 100;
			dateval->year4  = nsAtoi ( &tempstr[7] );
			tempstr[6] = '\0';
			dateval->day   = nsAtoi ( &tempstr[4] );
			tempstr[3] = '\0';
			if ( strcasecmp ( tempstr, "Jan" ) == 0 )
			{
				dateval->month = 1;
			}
			else if ( strcasecmp ( tempstr, "Feb" ) == 0 )
			{
				dateval->month = 2;
			}
			else if ( strcasecmp ( tempstr, "Mar" ) == 0 )
			{
				dateval->month = 3;
			}
			else if ( strcasecmp ( tempstr, "Apr" ) == 0 )
			{
				dateval->month = 4;
			}
			else if ( strcasecmp ( tempstr, "May" ) == 0 )
			{
				dateval->month = 5;
			}
			else if ( strcasecmp ( tempstr, "Jun" ) == 0 )
			{
				dateval->month = 6;
			}
			else if ( strcasecmp ( tempstr, "Jul" ) == 0 )
			{
				dateval->month = 7;
			}
			else if ( strcasecmp ( tempstr, "Aug" ) == 0 )
			{
				dateval->month = 8;
			}
			else if ( strcasecmp ( tempstr, "Sep" ) == 0 )
			{
				dateval->month = 9;
			}
			else if ( strcasecmp ( tempstr, "Oct" ) == 0 )
			{
				dateval->month = 10;
			}
			else if ( strcasecmp ( tempstr, "Nov" ) == 0 )
			{
				dateval->month = 11;
			}
			else if ( strcasecmp ( tempstr, "Dec" ) == 0 )
			{
				dateval->month = 12;
			}
			else
			{
				fprintf ( stderr, "StrToDatevalFmt: month not recognized.\n" );
				dateval->year2  = 0;
				dateval->year4  = 0;
				dateval->day   = 0;
				return ( 1 );
			}
			break;
		case DATEFMT_YYYY_MM_DD:
			dateval->day   = nsAtoi ( &tempstr[8] );
			tempstr[7] = '\0';
			dateval->month = nsAtoi ( &tempstr[5] );
			tempstr[4] = '\0';
			dateval->year4  = nsAtoi ( &tempstr[0] );
			dateval->year2  = nsAtoi ( &tempstr[0] ) % 100;
			break;
//                   012345678
		case DATEFMT_YYYYMMDD:
			tempstr[8] = '\0';
			dateval->day   = nsAtoi ( &tempstr[6] );
			tempstr[6] = '\0';
			dateval->month = nsAtoi ( &tempstr[4] );
			tempstr[4] = '\0';
			dateval->year4  = nsAtoi ( &tempstr[0] );
			dateval->year2  = nsAtoi ( &tempstr[0] ) % 100;
			break;

		default:
			fprintf ( stderr, "StrToDatevalFmt: unknown format %d\n", Format );
			return ( 1 );
	}

	if ( dateval->year4 < 100 )
	{
		dateval->year4 += 2000;
	}

	return ( ValidDateval(dateval,0) );
}

/*----------------------------------------------------------------------------
	Program : StrToDateval.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
    Synopsis: Convert an Ascii date to a DATEVAL.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		04/08/2010	restructured and added call to ValidDateval()
	tms		01/13/2012	Fix buffer over-write
	tms		01/16/2012	Fix new bug truncate long dates 02/12/2012
	tms		12/04/2018	Added to shslib
	
--------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int DebugStrToDateval = 0;

int StrToDateval ( char datestr[], DATEVAL *dateval )
{
	int		xl, xi, xo, xf;
	int		mdy[3];
	char	tempstr[20];

	mdy[0] = 0;
	mdy[1] = 0;
	mdy[2] = 0;

	xl = nsStrlen ( datestr );
	if ( xl > 19 )
	{
		xl = 19;
	}
	snprintf ( tempstr, sizeof(tempstr), "%-*.*s", xl, xl, datestr );

	TrimRightAndLeft ( tempstr );

	xl = nsStrlen ( tempstr );

	if ( DebugStrToDateval )
	{
		printf ( "[%s] [%d]\n", tempstr, xl );
		// sprintf ( msgbuf, "[%s] [%d]\n", tempstr, xl );
		// logmsg ( LogFileName, msgbuf );
	}

	if ( xl == 6 && nsAtoi(tempstr) > 10101 )
	{
		/*------------------
			012345
			mmddyy
		------------------*/
		dateval->year2  = nsAtoi ( &tempstr[4] );
		dateval->year4  = nsAtoi ( &tempstr[4] ) + 2000;
		tempstr[4] = '\0';
		dateval->day   = nsAtoi ( &tempstr[2] );
		tempstr[2] = '\0';
		dateval->month = nsAtoi ( &tempstr[0] );

		return ( ValidDateval(dateval,0)  );
	}
	else if ( xl == 8 && nsAtoi(tempstr) > 19000101 )
	{
		if ( tempstr[0] == '2' )
		{
			/*------------------
				01234567
				yyyymmdd
			------------------*/
			dateval->day   = nsAtoi ( &tempstr[6] );
			tempstr[6] = '\0';
			dateval->month = nsAtoi ( &tempstr[4] );
			tempstr[4] = '\0';
			dateval->year4 = nsAtoi ( &tempstr[0] );
			dateval->year2 = nsAtoi ( &tempstr[0] ) % 100;
		}
		else
		{
			/*------------------
				01234567
				mmddyyyy
			------------------*/
			dateval->year4  = nsAtoi ( &tempstr[4] );
			dateval->year2  = nsAtoi ( &tempstr[4] ) % 100;
			tempstr[4] = '\0';
			dateval->day   = nsAtoi ( &tempstr[2] );
			tempstr[2] = '\0';
			dateval->month = nsAtoi ( &tempstr[0] );
		}

		return ( ValidDateval(dateval,0)  );
	}

	if ( DebugStrToDateval )
	{
		printf ( "keep going ...\n" );
	}

	dateval->month = 0;
	dateval->day   = 0;
	dateval->year2  = 0;
	dateval->year4  = 0;

	for ( xi = 0,    xf = 0,   xo = 0;  
		  xi < xl && xf < 3; 
		  xi++ )
	{
		switch ( datestr[xi] )
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				tempstr[xo] = datestr[xi];
				xo++;
				break;

			default:
				switch ( xf )
				{
					case 0:
					case 1:
					case 2:
						tempstr[xo] = '\0';
						mdy[xf] = nsAtoi ( tempstr );
						xo = 0;
						xf++;
						break;
				}
				break;
		}
	}

	if ( xf < 2 )
	{
		return ( -1 );
	}
	else if ( xf == 2 )
	{
		tempstr[xo] = '\0';
		mdy[xf] = nsAtoi ( tempstr );
	}

	/*----------------------------------------------------------
		original
	xxx	dateval->month = mdy[0];
	xxx	dateval->day   = mdy[1];
	xxx	dateval->year  = mdy[2];
	----------------------------------------------------------*/

	/*----------------------------------------------------------
		detect four digit year as  yyyy/mm/dd or mm/dd/yyyy
		and adjust accordingly.
	----------------------------------------------------------*/
	if ( mdy[0] > 100 )
	{
		dateval->month = mdy[1];
		dateval->day   = mdy[2];
		dateval->year2  = mdy[0] % 100;
		dateval->year4  = dateval->year2 + 2000;
	}
	else if ( mdy[2] > 100 )
	{
		dateval->month = mdy[0];
		dateval->day   = mdy[1];
		dateval->year2  = mdy[2] % 100;
		dateval->year4  = dateval->year2 + 2000;
	}
	else
	{
		dateval->month = mdy[0];
		dateval->day   = mdy[1];
		dateval->year2  = mdy[2];
		dateval->year4  = dateval->year2 + 2000;
	}

	return ( ValidDateval(dateval,0) );
}


/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>
#include	<stdint.h>
#include	<errno.h>
#include	<libgen.h>		// for basename()
#include	"shslib.h"

#include	"NullSafeFuncs.c"
#include	"trimfuncs.c"
#include	"ValidDateval.c"
#include	"CurrentDateval.c"
#include	"DateAdd.c"
#include	"DateDiff.c"
#include	"StrToDatevalFmt.c"
#include	"StrToDateval.c"

int main  ( int argc, char *argv[] )
{
	DATEVAL	Today;
	DATEVAL	NewDate;
	int		UnixYear;
	int		Diff;

	CurrentDateval ( &Today );

//	UnixYear = Today.year4 % 1000;

//	UnixYear = Today.year2 + 100;
	
	UnixYear = Today.year4 - 1900;
	printf ( "UnixYear %d\n", UnixYear );

	DateAdd ( &Today, -45, &NewDate );
	printf ( "%d %d %d %d\n",
		NewDate.month, NewDate.day, NewDate.year2, NewDate.year4 );

	Diff = DateDiff ( &Today, &NewDate );
	printf ( "Diff %d\n", Diff );

	void PrintDate ( DATEVAL *d )
	{
		printf ( "%d %d %d %d\n", d->month, d->day, d->year2, d->year4 );
	}

	StrToDatevalFmt ( "01/15/23", DATEFMT_MM_DD_YY,  &NewDate ); PrintDate ( &NewDate );
	StrToDatevalFmt ( "01/15/2023", DATEFMT_MM_DD_YYYY,  &NewDate ); PrintDate ( &NewDate );
	StrToDatevalFmt ( "011523", DATEFMT_MMDDYY,  &NewDate ); PrintDate ( &NewDate );
	StrToDatevalFmt ( "Jan 15 1950", DATEFMT_AAA_DD_YYYY,  &NewDate ); PrintDate ( &NewDate );
	StrToDatevalFmt ( "2023-01-15", DATEFMT_YYYY_MM_DD,  &NewDate ); PrintDate ( &NewDate );
	StrToDatevalFmt ( "20230115", DATEFMT_YYYYMMDD,  &NewDate ); PrintDate ( &NewDate );

	StrToDateval ( "01/15/23", &NewDate ); PrintDate ( &NewDate );
	StrToDateval ( "01/15/2023", &NewDate ); PrintDate ( &NewDate );
	StrToDateval ( "011523", &NewDate ); PrintDate ( &NewDate );
	StrToDateval ( "Jan 15 1950", &NewDate ); PrintDate ( &NewDate );
	StrToDateval ( "2023-01-15", &NewDate ); PrintDate ( &NewDate );
	StrToDateval ( "20230115", &NewDate ); PrintDate ( &NewDate );



	
	return ( 0 );
}

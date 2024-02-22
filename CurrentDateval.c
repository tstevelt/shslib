/*----------------------------------------------------------------------------
	Program    : CurrentDateval.c
    Author     : Tom Stevelt
    Date       : 2002
    Description: Get the current date into a DATEVAL structure.

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		05/15/2023	changeed year to year2 and year4

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

void CurrentDateval ( DATEVAL *Today )
{
	long	tvec;
	struct	tm	*t;

	(void) time ( &tvec );
	t  = localtime ( &tvec );
	if ( t == NULL )
	{
		fprintf ( stderr, "CurrentDateTime: this is weird\n" );
		exit ( 1 );
	}

	Today->month = t->tm_mon + 1;
	Today->day   = t->tm_mday;
	Today->year2 = t->tm_year;

	while ( Today->year2 > 99 )
		Today->year2 -= 100;

	Today->year4 = Today->year2 + 2000;
}

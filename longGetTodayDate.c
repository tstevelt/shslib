/*----------------------------------------------------------------------------
	Program : longGetTodayDate.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 01/19/2021
	Synopsis: Convert system time (seconds) to system "date".  Number 
			  of days since Jan 1, 1970.
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

#include	<time.h>
#include	"shslib.h"

long longGetTodayDate ()
{
	time_t	tvec;

	tvec = time ( NULL );

	tvec = tvec / ( 24 * 60 * 60 );

	return ( tvec );
}

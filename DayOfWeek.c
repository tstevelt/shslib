/*----------------------------------------------------------------------------
	Program : DayOfWeek.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 11/18/2018
	Synopsis: Return day of week 
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

#include	"shslib.h"


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

/*----------------------------------------------------------------------------
	Program : IsMarketOpen.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 01/19/2021
	Synopsis: Check time of week day between 9:30 AM and 4:00 PM
	Return  : 1 = market is open, 0 = not open

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		unknown		This function does not account for holidays.
						Replaced with call, at 12:01 PM, to IEX for quote
						on SPY, which contains response field 'isUSMarketOpen'

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int IsMarketOpen ()
{
	time_t			CurrentTime;
	struct tm		*unixtime;

	time ( &CurrentTime );
    unixtime = localtime ( &CurrentTime );
	switch ( unixtime->tm_wday )
	{
		case 0:
		case 6:
			return ( 0 );
		default:
			if ( unixtime->tm_hour == 9 && unixtime->tm_min >= 30 )
			{
				return ( 1 );
			}
			else if ( unixtime->tm_hour >= 10 && unixtime->tm_hour <= 15 )
			{
				return ( 1 );
			}
			break;
	}
	return ( 0 );
}

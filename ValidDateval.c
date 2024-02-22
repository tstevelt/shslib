/*----------------------------------------------------------------------------
	Module  : ValidDateval.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 04/08/2010
	Synopsis: hacked from screen library function ValMDY.c

	Return  : 0 on valid
			  -1 on bad date

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		12/04/2018	Added to shslib

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int ValidDateval ( DATEVAL *TestDate, int NullDateOkay )
{
	int		maxdays;

	if ( TestDate->month == 0 && TestDate->day == 0 && TestDate->year4 == 0 )
	{
		if ( NullDateOkay )
		{
			return ( 0 );
		}
		else
		{
			return ( -1 );
		}
	}

	switch ( TestDate->month )
	{
		case 2:
			if ( (TestDate->year4 % 400) == 0 )
			{
				/*----------------------------------------------------------
					2000, 2400, 2800 ...
				----------------------------------------------------------*/
				maxdays = 29;
			}
			else if ( (TestDate->year4 % 100) == 0 )
			{
				/*----------------------------------------------------------
					2100, 2200, 2300, 2500 ...
				----------------------------------------------------------*/
				maxdays = 28;
			}
			else if ( (TestDate->year4 % 4) != 0 )
			{
				/*----------------------------------------------------------
					normal year
				----------------------------------------------------------*/
				maxdays = 28;
			}
			else
			{
				/*----------------------------------------------------------
					leap year
				----------------------------------------------------------*/
				maxdays = 29;
			}
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			maxdays = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			maxdays = 30;
			break;
		default:
			return ( -1 );
	}

	if ( TestDate->day >= 1 && TestDate->day <= maxdays )
	{
		return ( 0 );
	}
	else
	{
		return ( -1 );
	}
}

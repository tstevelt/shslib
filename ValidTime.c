/*----------------------------------------------------------------------------
	Module  : ValidTime.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 07/26/2022
	Synopsis: validate mm:ss or hh:mm:ss strings

	Return  : 1 = valid
			  0 = not valid

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		07/26/2022	also m:ss and h:mm:ss

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int ValidTime ( char *TimeString )
{
	int		Hour, Minute, Second;
	int		Length, ndx;

	Length = nsStrlen ( TimeString );

	for ( ndx = 0; ndx < Length; ndx++ )
	{
		switch ( TimeString[ndx] )
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
			case ':':
				break;
			default:
				return ( 0 );
		}
	}

	Hour = 0;

	if ( Length == 4 )
	{
		if ( TimeString[1] != ':' )
		{
			return ( 0 );
		}
		Minute = nsAtoi (  TimeString );
		Second = nsAtoi ( &TimeString[2] );
	}
	else if ( Length == 5 )
	{
		if ( TimeString[2] != ':' )
		{
			return ( 0 );
		}
		Minute = nsAtoi (  TimeString );
		Second = nsAtoi ( &TimeString[3] );
	}
	else if ( Length == 7 )
	{
		if ( TimeString[1] != ':' || TimeString[4] != ':' )
		{
			return ( 0 );
		}
		Hour   = nsAtoi (  TimeString );
		Minute = nsAtoi ( &TimeString[2] );
		Second = nsAtoi ( &TimeString[5] );
	}
	else if ( Length == 8 )
	{
		if ( TimeString[2] != ':' || TimeString[5] != ':' )
		{
			return ( 0 );
		}
		Hour   = nsAtoi (  TimeString );
		Minute = nsAtoi ( &TimeString[3] );
		Second = nsAtoi ( &TimeString[6] );
	}
	else
	{
		return ( 0 );
	}

	if ( Hour < 0 || Hour > 23 )
	{
		return ( 0 );
	}

	if ( Minute < 0 || Minute > 59 )
	{
		return ( 0 );
	}

	if ( Second < 0 || Second > 59 )
	{
		return ( 0 );
	}

	return ( 1 );
}

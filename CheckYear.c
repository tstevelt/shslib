/*----------------------------------------------------------------------------
	Program : CheckYear.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2020
	Synopsis: Place two digit year in correct century.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		02/24/2021	use env var CENTURY_CUTOFF if available

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int CheckYear ( int Year )
{
	static	int		Century_Cutoff = 70;
	static	int		firstpass = 1;
			char	*cp;

	if ( firstpass )
	{
		firstpass = 0;
	
		if (( cp = getenv ( "CENTURY_CUTOFF" )) != NULL )
		{
			Century_Cutoff = nsAtoi ( cp );
		}
	}

	if ( Year < 1900 )
	{
		Year = Year % 100;

		if ( Year < Century_Cutoff )
			Year = 2000 + Year;
		else
			Year = 1900 + Year;
	}

	return ( Year );
}


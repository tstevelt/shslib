/*----------------------------------------------------------------------------
	Program : FourDigitYear.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Dec 2020
	Synopsis: change two digit year to four digits.
	Return  : four digit year

	Who		Date		Modification
	---------------------------------------------------------------------

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/



static int CenturyCutoff = 70;
static int ThisCentury = 2000;
static int PreviousCentury = 1900;

int FourDigitYear ( int Year )
{
	if ( Year > 999 )
	{
		return ( Year );
	}

	if ( Year > 0 && Year < CenturyCutoff )
	{
		Year = ThisCentury + Year;
	}
	else if ( Year >= CenturyCutoff )
	{
		Year = PreviousCentury + Year;
	}

	return ( Year );
}

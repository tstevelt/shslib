/*----------------------------------------------------------------------------
	Program : dbldiff.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: evaluate the difference between two doubles, compare to allowable
			  differnce.
	Return  : 1 if difference exceeds allowable difference.
			  0 if difference is within the allowable difference.

	Who		Date		Modification
	---------------------------------------------------------------------

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

int dbldiff ( double d1, double d2, double allow )
{
	double	diff;

	if ( allow < 0.0 )
		allow = 0.0 - allow;
	
	diff = d1 - d2;

	if ( diff < 0.0 )
		diff = 0.0 - diff;
	
	if ( diff <= allow )
	{
		return ( 0 );
	}
	else
	{
		return ( 1 );
	}
}


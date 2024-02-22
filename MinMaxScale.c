/*----------------------------------------------------------------------------
	Program : MinMaxScale.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2017-2018
	Synopsis: Used to scale number for neural network programs.
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



/*---------------------------------------------------------------------------
	Start 1
	Length 17
0	1	2	3	4	5	6	7	8	9	0	1	2	3	4	5	6	7	8
IBM	12	89	89	89	89	98	98	98	89	89	89	89	8	98	98	98	98	B
---------------------------------------------------------------------------*/

void MinMaxScale ( double Array[], int StartIndex, int Length )
{
	int		ndx;
	double	Min, Max;

	Min = Max = -1.0;

	for ( ndx = StartIndex; ndx < StartIndex + Length; ndx++ )
	{
		if ( Min == -1.0 || Min > Array[ndx] )
		{
			Min = Array[ndx];
		}
		if ( Max == -1.0 || Max < Array[ndx] )
		{
			Max = Array[ndx];
		}
	}

	for ( ndx = StartIndex; ndx < StartIndex + Length; ndx++ )
	{
		Array[ndx] = ( Array[ndx] - Min ) / ( Max - Min );
	}
}

/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/



//  int MaxIndex = findmax ( OutputArray, OutputCount );
int findmax ( double Array[], int Count )
{
	double m = Array[0];
	int MaxIndex = 0;

	for ( int i = 1; i < Count; ++i) 
	{
		if ( m < Array[i] )
		{
			m = Array[i];
			MaxIndex = i;
		}
	}

	return ( MaxIndex );
}

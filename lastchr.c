/*----------------------------------------------------------------------------
	Program : lastchr.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: Rewrite of Unify HLI function for web side programming.
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


long lastchr ( char *s, int n )
{
	for ( ; n > 0; n-- )
	{
		if ( s[n-1] > ' ' )
		{
			return ( n );
		}
	}

	return ( 0 );
}

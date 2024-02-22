/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

long shsLastChr ( char *s, long n )
{
	for ( ; n > 0; n-- )
		if ( s[n-1] > ' ' )
			return ( n );

	return ( 0L );
}

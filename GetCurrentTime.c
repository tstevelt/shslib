/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include <sys/timeb.h>
#include	"shsprivate.h"
#include	"shslib.h"

double GetCurrentTime ( int Debug )
{
static	double		Current = 0.0;
		struct timeb		tp;

	ftime ( &tp );
	Current = tp.time + (double)tp.millitm / 1000.0;

	if ( Debug )
	{
		printf ( "CurrentTime: %.4f\n", Current );
	}

	return ( Current );
}

/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/


#include	"shsprivate.h"
#include	"shslib.h"


double shsLoadAverage ()
{
	FILE		*fp;
	char		xbuf[128];
	double		rv = 0.0;

	if (( fp = fopen ( "/proc/loadavg", "r" )) != (FILE *)0 )
	{
		fgets ( xbuf, sizeof(xbuf), fp );
		rv = nsAtof ( xbuf );
		fclose ( fp );
	}

	return ( rv );
}

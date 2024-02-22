/*----------------------------------------------------------------------------
	Program : shsUsage.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
	Synopsis: Print usage messge for program.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		2020		file pointer and count arguments.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

void shsUsage ( FILE *fp, char *error, char *msg[], int count, int fatal )
{
	int		ndx;

	if ( error != (char *)0 && nsStrlen ( error ) > 0 )
	{
		fprintf ( fp, "%s\n", error );
	}


	for ( ndx = 0; ndx < count; ndx++ )
	{
		fprintf ( fp, "%s\n", msg[ndx] );
	}
	
	if ( fatal )
	{
		exit ( fatal );
	}
}

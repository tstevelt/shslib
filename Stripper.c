/*----------------------------------------------------------------------------
	Program : Stripper.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
	Synopsis: Remove selected characters from string.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		2020		Called null safe functions.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"shslib.h"

void Stripper ( char String[], char Remove[] )
{
	int		xi, xo, xl;

	if (( xl = nsStrlen ( Remove )) == 0 )
	{
		return;
	}

	if (( xl = nsStrlen ( String )) == 0 )
	{
		return;
	}

	for ( xi = 0; xi < xl; xi++ )
	{
		if ( nsStrchr ( Remove, String[xi] ) != (char *)0 )
		{
			for ( xo = xi + 1; xo < xl; xo++ )
			{
				String[xo-1] = String[xo];
				String[xo] = '\0';
			}
		}
	}
}

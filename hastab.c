/*----------------------------------------------------------------------------
	Program : hastab.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 1987
	Synopsis: Determine if string contains a tab
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		2020		Called null safe nsStrchr*()

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/
#include    <string.h>
#include    "shslib.h"

int  hastab ( char *s )
{
    return ((int)(nsStrchr(s, '\t') != (char *)0 ));
}


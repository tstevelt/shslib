/*----------------------------------------------------------------------------
	Program : ErrorColor.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2020
	Synopsis: Set (escalate) color based on error levels
	Return  : Color define

	Who		Date		Modification
	---------------------------------------------------------------------

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shslib.h"

int ErrorColor ()
{
	int		rv = COLOR_NORMAL;
	int		xe;

	for ( xe = 0; xe < ErrorCount; xe++ )
	{
		if ( ErrorArray[xe].Color == COLOR_SUCCESS && rv < COLOR_SUCCESS )
		{
			rv = COLOR_SUCCESS;
		}
		else if ( ErrorArray[xe].Color == COLOR_WARN && rv < COLOR_WARN )
		{
			rv = COLOR_WARN;
		}
		else if ( ErrorArray[xe].Color == COLOR_ERROR && rv < COLOR_ERROR )
		{
			rv = COLOR_ERROR;
			break;
		}
	}

	return ( rv );
}

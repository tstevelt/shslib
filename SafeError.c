/*----------------------------------------------------------------------------
	Program : SafeError.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
	Synopsis: Store error (or other) messages in an array.  Used for web
			  programning, because can not output to screen prior to
			  output of Content-Type.
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

#include	"shsprivate.h"
#include	<stdarg.h>
#include	"shslib.h"

void SafeError ( int Color, char *MessageFormat, ... )
{
	va_list ap;

	if ( ErrorCount == MAXERR )
	{
		return;
	}

	switch ( Color )
	{
		case COLOR_ERROR:
		case COLOR_WARN:
		case COLOR_SUCCESS:
		case COLOR_NORMAL:
			break;
		default:
			Color = COLOR_ERROR;
			break;
	}

	if ( ErrorCount + 1 == MAXERR )
	{
		ErrorArray[ErrorCount].Color = Color;
		sprintf ( ErrorArray[ErrorCount].Message, "Error message array is full" );
		ErrorCount++;
		return;
	}

	ErrorArray[ErrorCount].Color = Color;

	va_start ( ap, MessageFormat );
	vsnprintf ( ErrorArray[ErrorCount].Message, ERRMSGSZ, MessageFormat, ap );
	va_end ( ap );

	ErrorCount++;
}

void SaveError ( char *ErrorMessage )
{
	if ( ErrorCount < MAXERR )
	{
		snprintf ( ErrorArray[ErrorCount].Message, ERRMSGSZ, "%s", ErrorMessage );
		ErrorCount++;
	}
}

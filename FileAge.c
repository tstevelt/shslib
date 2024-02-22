/*----------------------------------------------------------------------------
	Program : FileAge.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: How old a file is, in seconds
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
#include	"shslib.h"

int FileAge ( char *FileName )
{
	struct stat		buffer;
	time_t			FileTime;
	time_t			CurrentTime;
	int				rv;

	if ( stat ( FileName, &buffer ) != 0 )
	{
		return ( -1 );
	}

	FileTime = buffer.st_mtime;
	
	time ( &CurrentTime );

	rv = CurrentTime - FileTime;

	return ( rv );
}

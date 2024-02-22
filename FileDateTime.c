/*----------------------------------------------------------------------------
	Program : cpFileDateTime.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: xxxxxxxxxxx
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

char *cpFileDateTime ( char *FileName, int Format )
{
	static char		AsciiDateTime[48];
	struct stat		buffer;
	struct tm		*unixtime;

	if ( stat ( FileName, &buffer ) != 0 )
	{
		memset ( AsciiDateTime, '\0', sizeof(AsciiDateTime) );
	}
	else
	{
    	unixtime = localtime ( &buffer.st_mtime );
		
		switch ( Format )
		{
			case 101:
				sprintf ( AsciiDateTime, "%02d/%02d %02d:%02d",
					unixtime->tm_mon + 1,
					unixtime->tm_mday,
					unixtime->tm_hour,
					unixtime->tm_min );
				break;
			default:
				sprintf ( AsciiDateTime, "%02d/%02d/%02d %02d:%02d",
					unixtime->tm_mon + 1,
					unixtime->tm_mday,
					unixtime->tm_year = unixtime->tm_year % 100,
					unixtime->tm_hour,
					unixtime->tm_min );
				break;
		}
	}

	return ( AsciiDateTime );
}

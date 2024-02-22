/*----------------------------------------------------------------------------
	Program : WhoisSystem.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
	Synopsis: Tries to determine who owns an IP.
			  This should be a separate app.  
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

extern char *strcasestr (const char *__haystack, const char *__needle);

char * WhoisSystem ( char *Address  )
{
	char	*rv = (char *)0;
	char	cmdline[256];
	FILE	*fp;
	char	FileName[128];
	char	xbuffer[1024];
	int		Column = 16;

	sprintf ( FileName, "/tmp/whois.txt" );

	sprintf ( cmdline, "whois %s > %s 2> /dev/null", Address, FileName );
	system ( cmdline );

	if (( fp = fopen ( FileName, "r" )) == (FILE *)0 )
	{
		return ( rv );
	}

	while ( fgets ( xbuffer, sizeof(xbuffer), fp ) != (char *)0 )
	{
		TrimRightAndLeft ( xbuffer );

		if ( strcasestr ( xbuffer, "orgname" ) != (char *)0 )
		{
			rv = &xbuffer[Column];
			break;
		}
		else if ( strcasestr ( xbuffer, "org-name" ) != (char *)0 )
		{
			rv = &xbuffer[Column];
			break;
		}
		else if ( strcasestr ( xbuffer, "netname" ) != (char *)0 )
		{
			rv = &xbuffer[Column];
			break;
		}
		else if ( strcasestr ( xbuffer, "person" ) != (char *)0 )
		{
			rv = &xbuffer[Column];
			break;
		}
	}

	nsFclose ( fp );

	return ( rv );
}

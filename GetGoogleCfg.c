/*----------------------------------------------------------------------------
	Program : GetGoogleCfg.c
	Author  : Tom Stevelt
	Date    : March 2024
	Synopsis: get config from /var/local/google
	Return  : Succeed or die.

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

void GetGoogleCfg()
{
//	char	*Logname;
	char	fn[1024];
	FILE	*fp;
	char	xbuffer[1024];
	char	*tokens[4];
	int		tokcnt;
	int		GotKey = 0;
//	int		GotURL = 0;
//	int		GotPaypalKey = 0;
//	int		GotPaypalURL = 0;
	int		ErrorCount = 0;
    char	*ptrName;
	char	*ptrValue;

	sprintf ( fn, "/var/local/google/.Google.cfg" );

	if (( fp = fopen ( fn, "r" )) == NULL )
	{
		fprintf ( stderr, "%s not found, errno %d %s.\n", fn, errno, strerror(errno) );
		exit ( 1 );
	}

	while ( fgets ( xbuffer, sizeof(xbuffer), fp ) != NULL )
	{
		if (( tokcnt = GetTokensW ( xbuffer, tokens, 3 )) < 2 )
		{
			continue;
		}

		if ( nsStrcmp ( tokens[0], "GOOGLE_MAP_APISTR" ) == 0 )
		{
			snprintf ( env_GoogleMapKey, sizeof(env_GoogleMapKey), "%s", tokens[1] );
			GotKey = 1;
		}
	}
	
	nsFclose ( fp );

	if ( GotKey == 0 )
	{
		ptrValue = "GOOGLE_MAP_APISTR";
    	if (( ptrName = getenv ( ptrValue )) == NULL )
		{
			fprintf ( stderr, "%s not found in %s\n", ptrValue, fn );
			fprintf ( stderr, "%s not found in environment\n", ptrValue );
			ErrorCount++;
		}
		else
		{
			snprintf ( env_GoogleMapKey, sizeof(env_GoogleMapKey), "%s", ptrName );
		}
	}

	if ( ErrorCount )
	{
		exit ( 1 );
	}
}

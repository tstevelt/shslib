/*----------------------------------------------------------------------------
	Program : GetDomainName.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2020
	Synopsis: Extract domain name from hostname if possible.
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


#include	<stdio.h>
#include	<unistd.h>
#include	<string.h>
#include	"shslib.h"


char *GetDomainName ()
{
	static	char	DomainName[64];
	char	HostName[64];
	int		Length, Index, DotCount;

	if ( gethostname ( HostName, sizeof(HostName) ) == -1 )
	{
		return ( NULL );
	}

	/*----------------------------------------------------------
		lambda.stevelt.com
	----------------------------------------------------------*/
	Length = nsStrlen ( HostName );
	for ( Index = Length - 1, DotCount = 0; Index >= 0; Index-- )
	{
		if ( HostName[Index] == '.' )
		{
			DotCount++;
		}
		if ( DotCount == 2 )
		{
			break;
		}
	}

	switch ( DotCount )
	{
		case 0:
		case 1:
			sprintf ( DomainName, "%s", HostName );
			break;
		case 2:
			Index++;
			sprintf ( DomainName, "%s", &HostName[Index] );
			break;
	}

	return ( DomainName );
}

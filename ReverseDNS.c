/*----------------------------------------------------------------------------
	Program : ReverseDNS.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2019
	Synopsis: Reverse DNS
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

char *ReverseDNS ( char Address[] )
{
	#define		MAXNAMELEN		128
	static char Name[MAXNAMELEN];
	struct sockaddr	sa, *ptr;
	socklen_t		len;
	struct sockaddr_in 	*ipv4;

	sa.sa_family = AF_INET;

	/*------------------------------------------------------------------------------
		thanks to Antonio MG for sample code used in next 3 lines.
		https://stackoverflow.com/questions/13014801/how-do-i-populate-socket-address-properly
	------------------------------------------------------------------------------*/
	ptr = &sa;
	ipv4 = (struct sockaddr_in *) ptr;
	inet_pton ( AF_INET, Address, &ipv4->sin_addr );

	len = sizeof(sa);

	if ( getnameinfo ( &sa, len, Name, sizeof(Name), NULL, 0, NI_NAMEREQD ) != 0 )
	{
		char	*cp;

		cp = WhoisSystem ( Address );
		if ( cp == (char *) 0 )
		{
			snprintf ( Name, sizeof(Name), "could not resolve hostname" );
		}
		else
		{
			snprintf ( Name, sizeof(Name), "%s", cp );
		}
	}


	return ( Name );
}

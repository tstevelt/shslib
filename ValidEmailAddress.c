/*----------------------------------------------------------------------------
	Program : ValidEmailAddress.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2017
	Synopsis: Make sure address includes an @ sign, followed by period.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		07/26/2022	validate domain name portion of email address.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shsprivate.h"
#include	"shslib.h"

int ValidEmailAddress ( char *TestAddress )
{
	int		len, ndx, posAtSign, posDot, count;
	char	*DomainName;
	struct hostent		*he;

	if (( len = nsStrlen ( TestAddress )) == 0 )
	{
		return ( 0 );
	}

	for ( ndx = 1, posAtSign = 0, posDot = 0, count = 0; ndx < len && count < 2; ndx++ )
	{
		if ( TestAddress[ndx] == '@' )
		{
			posAtSign = ndx;
			count++;
		}
		else if ( posAtSign > 0 && TestAddress[ndx] == '.' )
		{
			posDot = ndx;
			count++;
		}
	}

	if ( count != 2 )
	{
		return ( 0 );
	}

	if ( posAtSign > posDot )
	{
		return ( 0 );
	}

	DomainName = &TestAddress[posAtSign+1];

	if (( he = gethostbyname ( DomainName )) == NULL )
	{
		return ( 0 );
	}

	return ( 1 );
}

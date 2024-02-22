/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/


#include	"shslib.h"
#include	"shsCountries.h"

COUNTRY_RECORD *LookupCountry ( int Method, char *Input )
{
	int				ndx;
//	COUNTRY_RECORD	*ptr;

	switch ( Method )
	{
		case COUNTRY_BY_NAME:
			for ( ndx = 0; ndx < CountryCount; ndx++ )
			{
				if ( nsStrcasestr ( CountryArray[ndx].Name, Input )  != NULL )
				{
					return ( &CountryArray[ndx] );
				}
			}
			break;

		case COUNTRY_BY_ALPHA2:
			for ( ndx = 0; ndx < CountryCount; ndx++ )
			{
				if ( nsStrcmp ( CountryArray[ndx].Alpha2, Input ) == 0 )
				{
					return ( &CountryArray[ndx] );
				}
			}
			break;

		case COUNTRY_BY_ALPHA3:
			for ( ndx = 0; ndx < CountryCount; ndx++ )
			{
				if ( nsStrcmp ( CountryArray[ndx].Alpha3, Input ) == 0 )
				{
					return ( &CountryArray[ndx] );
				}
			}
			break;

		case COUNTRY_BY_ISO:
			for ( ndx = 0; ndx < CountryCount; ndx++ )
			{
				if ( nsStrcmp ( CountryArray[ndx].ISO, Input ) == 0 )
				{
					return ( &CountryArray[ndx] );
				}
			}
			break;

		default:
			return ( NULL );
	}

	return ( NULL );
}

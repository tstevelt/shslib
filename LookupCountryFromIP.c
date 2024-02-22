/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/


#include	"shslib.h"
#include	"shsprivate.h"
#include	"maxminddb.h"

#define GEO_DB "/usr/local/share/GeoDB/GeoLite2-Country_20210608/GeoLite2-Country.mmdb"


char *LookupCountryFromIP ( char *IP_Address )
{
	static char						CountryCode[3];
	char	*mmdb_file = GEO_DB;
	int		status, gai_error, mmdb_error;
	struct MMDB_lookup_result_s		result;
	MMDB_entry_data_s				entry_data;
	MMDB_s mmdb;
	
	CountryCode[0] = '\0';
	CountryCode[1] = '\0';
	CountryCode[2] = '\0';

	if (( status = MMDB_open(mmdb_file,MMDB_MODE_MMAP, &mmdb)) != MMDB_SUCCESS )
	{
		fprintf ( stderr, "Cannot open %s\n", mmdb_file );
		return ( NULL );
	}

	result = MMDB_lookup_string( &mmdb, IP_Address, &gai_error, &mmdb_error);
	if ( gai_error != 0 )
	{
		fprintf ( stderr, "gai_error - %s\n", gai_strerror(gai_error) );
		MMDB_close(&mmdb);
		return ( NULL );
	}

	if ( mmdb_error != 0 )
	{
		fprintf ( stderr, "mmdb_error - %s\n", MMDB_strerror(mmdb_error) );
		MMDB_close(&mmdb);
		return ( NULL );
	}
	
	if ( ! result.found_entry )
	{
		fprintf ( stderr, "No MMDB entry for %s\n", IP_Address );
		MMDB_close(&mmdb);
		return ( NULL );
	}

	MMDB_entry_data_list_s *entry_data_list = NULL;

	status = MMDB_get_entry_data_list ( &result.entry, &entry_data_list);

	if ( status != MMDB_SUCCESS )
	{	 
		fprintf ( stderr, "Got error looking up entry data - %s\n", MMDB_strerror(status) );
	}
	else if ( entry_data_list != NULL )
	{
		// MMDB_dump_entry_data_list ( stdout, entry_data_list, 2 );
		MMDB_get_value ( &result.entry, &entry_data, "country", "iso_code", NULL );

		if ( entry_data.has_data)
		{
			sprintf ( CountryCode, "%2.2s", entry_data.utf8_string );
			return ( &CountryCode[0] );
		}
	}

	MMDB_close(&mmdb);

/*---------------------------------------------------------------------------
p entry_data
$1 = {has_data = true, {pointer = 4133506570, 
utf8_string = 0x7ffff6604e0a "US #\350BdeCUSABenMUnited StatesBesNEstados UnidosBfrKÃtats-UnisBjaUã¢ã¡ãªã«åèå½ U(\bVBruFÐ¡Ð¨Ð mFçå½ \374(\002\035\343 \001!\314 z\"A \374(\002\035\343 \001\"\317 z\344 \024\303(\006\070(", 
double_value = 6.9533478306152174e-310, 
bytes = 0x7ffff6604e0a "US #\350BdeCUSABenMUnited StatesBesNEstados UnidosBfrKÃtats-UnisBjaUã¢ã¡ãªã«åèå½ U(\bVBruFÐ¡Ð¨Ð mFçå½ \374(\002\035\343 \001!\314 z\"A \374(\002\035\343 \001\"\317 z\344 \024\303(\006\070(", uint16 = 19978, 
uint32 = 4133506570, int32 = -161460726, uint64 = 140737326894602, uint128 = 1027705005975243866525194, boolean = 10, 
float_value = -1.13736066e+33}, offset = 4149, offset_to_next = 4152, data_size = 2, type = 2}
(gdb) p entry_data->utf8_string
$2 = 0x7ffff6604e0a "US #\350BdeCUSABenMUnited StatesBesNEstados UnidosBfrKÃtats-UnisBjaUã¢ã¡ãªã«åèå½ U(\bVBruFÐ¡Ð¨Ð mFçå½ \374(\002\035\343 \001!\314 z\"A \374(\002\035\343 \001\"\317 z\344 \024\303(\006\070("
(gdb) 
---------------------------------------------------------------------------*/
	return ( CountryCode );
}

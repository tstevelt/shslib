/*----------------------------------------------------------------------------
	Program : pw_sha.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 02/24/2019
	Synopsis: SHA1 password routines
	Return  : 
	Example : https://stackoverflow.com/questions/9284420/how-to-use-sha1-hashing-in-c-programming

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

unsigned char * pw_sha_make_pw ( unsigned char * plaintext )
{
	static	unsigned char	hash     [SHA_DIGEST_LENGTH];
	static	unsigned char	encrypted[SHA_DIGEST_LENGTH*2];
			int				ndx;

	SHA1 ( plaintext, (size_t)nsStrlen((char *) plaintext), hash );

	for ( ndx = 0; ndx < SHA_DIGEST_LENGTH; ndx++ )
	{
		sprintf ( (char *) &encrypted[ndx*2], "%02x", hash[ndx] );
	}

	return ( encrypted );
}

int pw_sha_login_pw ( unsigned char * plaintext, unsigned char * filepw )
{
	static	unsigned char	*encrypted;

	encrypted = pw_sha_make_pw ( plaintext );

	if ( nsStrcmp ( (char *) encrypted, (char *) filepw ) == 0 )
	{
		return ( 0 );
	}

	return ( -1 );
}


/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/


#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"shslib.h"

char *JsonOpenFileAndRead ( char *filename )
{
	static	char	*ptr;
			FILE	*fp;
			long	filesize;
			int		nr;

	if (( fp = fopen ( filename, "r" )) == NULL )
	{
		return ( NULL );
	}

	fseek ( fp, 0L, SEEK_END );
	filesize = ftell ( fp );
	fseek ( fp, 0L, SEEK_SET );

	if (( ptr = malloc ( filesize )) == NULL )
	{
		nsFclose ( fp );
		return ( NULL );
	}

	if (( nr = fread ( ptr, filesize, 1, fp )) != 1 )
	{
		nsFclose ( fp );
		free ( ptr );
		return ( NULL );
	}

	nsFclose ( fp );

	return ( ptr );
}

/*---------------------------------------------------------------------------
			if (( ptrNameValue = JsonScan ( ptrResults, "msg" )) == NULL )
			{
				ShowMessage ( "'msg' not found in results", 0 );
			}
			else
			{
				ShowMessage ( ptrNameValue->Value, 0 );
			}
---------------------------------------------------------------------------*/

static int DebugJsonScan = 0;

JSON_NAME_VALUE *JsonScan ( char *buffer, char *target, int Direction )
{
	static	char	*CurrentPosition = NULL;
	static	int		Offset = 0;
			char	*cp;
	static	JSON_NAME_VALUE	ptrJson;
			int		target_length;
			int		saw_a_quote;

	ptrJson.Name = NULL;
	ptrJson.Value = NULL;

	if ( Direction == JSON_FIRST )
	{
		CurrentPosition = buffer;
		Offset = 0;
	}
	else if ( CurrentPosition == NULL )
	{
		fprintf ( stderr, "JsonScan should be called with JSON_FIRST first\n" );
		exit ( 1 );
	}
		
	cp = CurrentPosition;

	target_length = nsStrlen ( target );

	/*----------------------------------------------------------
		scan for target
	----------------------------------------------------------*/
	while ( *cp != '\0' )
	{
		if ( DebugJsonScan )
		{
			printf ( "%-*.*s\n", target_length, target_length, cp );
		}

		if ( nsStrncmp ( cp, target, target_length ) == 0 )
		{
			/*------------------------------------------------------------------
				found target, save it. 
				step CurrentPosition in case we get called with JSON_NEXT
			------------------------------------------------------------------*/
			ptrJson.Name = cp;
			CurrentPosition = cp + 1;

			/*----------------------------------------------------------
				scan for colon between name and value
			----------------------------------------------------------*/
			while ( *cp != '\0' && *cp != ':' )
			{
				cp++;
				Offset++;
			}

			if ( *cp == '\0' )
			{
				CurrentPosition = NULL;
				return ( NULL );
			}

			/*----------------------------------------------------------
				on colon, step one
			----------------------------------------------------------*/
			cp++;
			Offset++;

			/*----------------------------------------------------------
				see if it is a quote mark, if so, step one more
			----------------------------------------------------------*/
			if ( *cp == '"' )
			{
				saw_a_quote = 1;
				cp++;
				Offset++;
			}
			else
			{
				saw_a_quote = 0;
			}

			/*----------------------------------------------------------
				this is the value. save it.
			----------------------------------------------------------*/
			ptrJson.Value = cp;
			ptrJson.Offset = Offset;
			ptrJson.Length = 0;

			/*----------------------------------------------------------
				if we saw a quote, find next and null it.
				if no quote, then scan for comma and null that
			----------------------------------------------------------*/
			if ( saw_a_quote )
			{
				while ( *cp != '\0' && *cp != '"' )
				{
					cp++;
					Offset++;
					ptrJson.Length++;
				}
				if ( *cp == '"' )
				{
					// can't do this, screws up subsequent calls. *cp = '\0';
				}
			}
			else
			{
				while ( *cp != '\0' && *cp != ',' )
				{
					cp++;
					Offset++;
					ptrJson.Length++;
				}
				if ( *cp == ',' )
				{
					// can't do this, screws up subsequent calls. *cp = '\0';
				}
			}

			return ( &ptrJson );
		}

		cp++;
		Offset++;
	}

	if ( *cp == '\0' )
	{
		CurrentPosition = NULL;
	}

	return ( NULL );
}

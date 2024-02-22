/*----------------------------------------------------------------------------
	Program : GetTokensCSV.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 12/07/2020
	Synopsis: Get tokens from comma separtated string.
			  1. Lose double quotes.
			  2. Change delimiter commas to pipes
			  3. Optional, lose internaal commas.
			  4. Call GetTokensStd on pipes
			  5. As with other GetTokens functions, original string is mod.
	Return  : Token Count on success

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

static char WorkBuffer[2048];

int GetTokensCSV ( char *Buffer, char *tokens[], int MaxToks, int KeepInternalCommas, int Verbose )
{
	int		TokenCount = 0;
	int		Length;
	int		ndx, inquote, NewLength;

	if (( Length = nsStrlen ( Buffer )) == 0 )
	{
		return ( TokenCount );
	}

	if ( Length > 2048 )
	{
		if ( Verbose )
		{
			printf ( "GetTokensCSV: input string exceeds 2048 characters\n" );
		}
		return ( TokenCount );
	}

	inquote = 0;
	memset ( WorkBuffer, '\0', sizeof(WorkBuffer) );
	NewLength = 0;
	for ( ndx = 0; ndx < Length; ndx++ )
	{
		if ( Buffer[ndx] == '"' )
		{
			if ( inquote == 0 )
			{
				inquote = 1;
			}
			else
			{
				inquote = 0;
			}
			continue;
		}

		if ( Buffer[ndx] == ',' )
		{
			if ( inquote == 0 )
			{
				WorkBuffer[NewLength++] = '|';
			}
			else if ( KeepInternalCommas )
			{
				WorkBuffer[NewLength++] = Buffer[ndx];
			}
			else
			{
				/* lose internal commas */
			}

			continue;
		}

		WorkBuffer[NewLength++] = Buffer[ndx];
	}

	TokenCount = GetTokensStd ( WorkBuffer, "|", tokens, MaxToks, Verbose );

	memcpy ( Buffer, WorkBuffer, NewLength );

	return ( TokenCount );
}

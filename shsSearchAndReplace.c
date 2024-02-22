/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	"shslib.h"
#include	"shsprivate.h"

static	char *Destination = NULL;

char *shsSearchAndReplace ( char *Source, char *Pattern, char *Replacement )
{
	int		SourceLength, PatternLength, ReplacementLength, Count, xi, xo;
	int		SpaceNeeded;

	SourceLength = strlen ( Source );
	PatternLength = strlen ( Pattern );
	ReplacementLength = strlen ( Replacement );
	Count = 0;
	for ( xi = 0; xi < SourceLength; xi++ )
	{
		if ( strncmp ( &Source[xi], Pattern, PatternLength ) == 0 )
		{
			Count++;
			xi += PatternLength;
		}
	}

	SpaceNeeded = 4 + SourceLength + Count * ( ReplacementLength - PatternLength );

	if ( Destination )
	{
		free ( Destination );
	}

	if (( Destination = calloc ( SpaceNeeded, 1 )) == NULL )
	{
		return ( Destination );
	}

	for ( xi = 0, xo = 0; xi < SourceLength; xi++ )
	{
		if ( strncmp ( &Source[xi], Pattern, PatternLength ) == 0 )
		{
			memcpy ( &Destination[xo], Replacement, ReplacementLength );
			xi += PatternLength - 1;
			xo += ReplacementLength;
		}
		else
		{
			Destination[xo] = Source[xi];	
			xo++;
		}
	}

	return ( Destination );
}

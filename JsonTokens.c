/*----------------------------------------------------------------------------
	Program : JsonTokens.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 06/12/2019
	Synopsis: Dirt simple parser. Ignores arrays.
	Return  : 


	Who		Date		Modification
	---------------------------------------------------------------------
	tms		02/24/2021	Moved test program into ../test/subdir

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdio.h>
#include	<string.h>
#include	"shslib.h"

#define		MAXELEM		100000

int JsonTokens ( char Buffer[], char *Tags[], char *Values[], int maxtoks )
{
	int		xi, xl, xp, InPair, InTag, InValue;
	char	*Pairs[MAXELEM];
	int		PairCount;
	char	*cp;

	xl = nsStrlen ( Buffer );

	/*---------------------------------------------------------------------------
		{"date":"2019-06-11","open":290.99,"high":291.4,"low":288.18,"close":288.9,"volume":58641325}
		[{"close":72.23,"high":72.86,"low":71.75,"open":72.63,"symbol":"ABBV","volume":5269109,"id":"HISTORICAL_PRICES","key":"ABBV","subkey":"","date":"2017-07-18","updated":1606830572000,"changeOverTime":0,"marketChangeOverTime":0,"uOpen":72.63,"uClose":72.23,"uHigh":72.86,"uLow":71.75,"uVolume":5269109,"fOpen":62.2599,"fClose":61.9171,"fHigh":62.4571,"fLow":61.5056,"fVolume":5269109,"label":"Jul 18, 17","change":0,"changePercent":0}]
	---------------------------------------------------------------------------*/
	PairCount = 0;
	InPair = 0;
	for ( xi = 0; xi < xl; xi++ )
	{
		if (( Buffer[xi] == '{' ) ||
			( Buffer[xi] == '[' ))
		{
			continue;
		}

		if ( InPair == 0 )
		{
			if ( PairCount >= maxtoks )
			{
				return ( -1 );
			}
			InPair = 1;
			Pairs[PairCount] = &Buffer[xi];
			PairCount++;
		}
		else if ( Buffer[xi] == ',' || Buffer[xi] == '}' || Buffer[xi] == ']' )
		{
			InPair = 0;
			Buffer[xi] = '\0';
		}

	}
	
	/*----------------------------------------------------------
		"date":"2019-06-11"
		"open":290.99
		"high":291.4
		"low":288.18
		"close":288.9
		"volume":58641325
	----------------------------------------------------------*/
#undef DEBUG
	for ( xp = 0; xp < PairCount; xp++ )
	{
		InTag = InValue = 0;
		xl = nsStrlen(Pairs[xp]);
#ifdef DEBUG
printf ( "%s  %d\n", Pairs[xp], xl );
#endif
		for ( xi = 0, cp = Pairs[xp]; xi < xl; xi++, cp++ )
		{
			if ( InTag == 0 )
			{
				if ( Pairs[xp][xi] == '"' )
				{
					continue;
				}
				else 
				{
					InTag = 1;
					Tags[xp] = cp;
				}
			}
			else if ( InTag == 1 )
			{
				if ( Pairs[xp][xi] == '"' )
				{
					*cp = '\0';
					InTag = 2;
					continue;
				}
			}
			else if ( InTag == 2 && InValue == 0 )
			{
				if ( Pairs[xp][xi] == ':' || Pairs[xp][xi] == '"' )
				{
					continue;
				}
				else
				{
					InValue = 1;
					Values[xp] = cp;
				}
			}
			else if ( InValue )
			{
				if ( Pairs[xp][xi] == '"' || Pairs[xp][xi] == '\0' )
				{
					*cp = '\0';
					InValue = InTag = 0;
					break;
				}
			}
		}
	}

	return ( PairCount );

}

/*----------------------------------------------------------------------------
	Program : StrInitialCaps.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2017
	Synopsis: Make strings pretty.
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


#include	<ctype.h>

void StrInitialCaps  ( char *String )
{
	int		FirstLetter;

	if ( isalpha ( *String ) )
	{
		FirstLetter = 1;
	}
	else
	{
		FirstLetter = 0;
	}
	while ( *String )
	{
		if ( isalpha ( *String ) )
		{
			if ( FirstLetter )
			{
				*String = toupper ( *String );
				FirstLetter = 0;
			}
			else
			{
				*String = tolower ( *String );
			}
		}
		else
		{
			FirstLetter = 1;
		}
		
		String++;
	}
}

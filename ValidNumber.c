/*----------------------------------------------------------------------------
	Module  : ValidNumber.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 07/26/2022
	Synopsis: validate mm:ss or hh:mm:ss strings

	Return  : 1 = valid
			  0 = not valid

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

int ValidNumber ( char *NumberString, int Float, int Signed )
{
	int		Length, ndx;

	Length = nsStrlen ( NumberString );

	for ( ndx = 0; ndx < Length; ndx++ )
	{
		switch ( NumberString[ndx] )
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				break;
			case '.':
				if ( Float == 0 )
				{
					return ( 0 );
				}
				break;
			case '-':
			case '+':
				if ( Signed == 0 )
				{
					return ( 0 );
				}
				break;
			default:
				return ( 0 );
		}
	}

	return ( 1 );
}

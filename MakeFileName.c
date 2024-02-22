/*----------------------------------------------------------------------------
	Program : MakeFileName.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
	Synopsis: Make file based on stock ticker. For app ivdays, so this 
			  function should not be in this higher level library.
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

#include	"shsprivate.h"
#include	"shslib.h"

int MakeFileName (  char Symbol[], char Phrase [], char tmpfile[], int tmpsize )
{
	switch ( Symbol[0] )
	{
		case '_':
			tmpfile[0] = '\0';
			break;
		case '^':
			sprintf ( tmpfile, "/var/local/ivdays/%s_%s.dat", &Symbol[1], Phrase );
			break;
		default:
			sprintf ( tmpfile, "/var/local/ivdays/%s_%s.dat", Symbol, Phrase );
			break;
	}
	return ( 0 );
}

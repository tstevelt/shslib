/*----------------------------------------------------------------------------
	Program : PtrToStrg.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2018
	Synopsis: Print 64 bit pointer as hex values.
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


typedef union
{
	char	*Ptr;
	unsigned char	Array[8];
} PTR_RECORD;

char *PtrToStr ( char * Ptr )
{
	PTR_RECORD	data;
	static	char	Answer [30];

	memcpy ( &data.Ptr, Ptr, sizeof(data.Ptr) );

	sprintf ( Answer, "%02x %02x %02x %02x %02x %02x %02x %02x",
		data.Array[0],
		data.Array[1],
		data.Array[2],
		data.Array[3],
		data.Array[4],
		data.Array[5],
		data.Array[6],
		data.Array[7] );

	return ( Answer );
}

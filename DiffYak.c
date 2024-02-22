/*----------------------------------------------------------------------------
	Program : DiffYak.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: This program is not finished.
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

void DiffYak ( char *Label, void *Mem1, void *Mem2, size_t MemSize, int Datatype )
{
	int		rv, ndx;

	if (( rv = memcmp ( Mem1, Mem2, MemSize )) != 0 )
	{
		SHS_DATA_UNION	Data1, Data2;
		
		Data1.String = Mem1;
		Data2.String = Mem2;

		switch ( Datatype )
		{
			case DATATYPE_CHAR:
				fprintf ( stderr, "%s differ %c %c\n", Label, Data1.Character, Data2.Character );
				break;
			case DATATYPE_STRING:
			case DATATYPE_MYSQL_DATE:
				fprintf ( stderr, "%s differ [%s] [%s], rv %d\n", Label, Data1.String, Data2.String, rv );
				for ( ndx = 0; ndx < MemSize; ndx++ )
				{
					fprintf ( stderr, "%02x ", Data1.String[ndx] );
				}
				fprintf ( stderr, "\n" );
				for ( ndx = 0; ndx < MemSize; ndx++ )
				{
					fprintf ( stderr, "%02x ", Data2.String[ndx] );
				}
				fprintf ( stderr, "\n" );

				break;
			case DATATYPE_SHORT:
				fprintf ( stderr, "%s differ %d %d\n", Label, Data1.Short, Data2.Short );
				break;
			case DATATYPE_DOUBLE:
				fprintf ( stderr, "%s differ %f %f\n", Label, Data1.Double, Data2.Double );
				break;
			case DATATYPE_LONG:
			case DATATYPE_SYSTEM_DATE:
				fprintf ( stderr, "%s differ %ld %ld\n", Label, Data1.Long, Data2.Long );
				break;
		}
	}
}


/*----------------------------------------------------------------------------
	Program : detab.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time, perhaps 1989
	Synopsis: replace tabs with spaces
	Return  : 1 = everything fit
			  0 = not enough room

	Who		Date		Modification
	---------------------------------------------------------------------

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

int  detab ( char *src, char *dst, int dstsize, short tabsize )
{
    int     srcpos, dstpos, j;

    dstpos = 0;
    for ( srcpos = 0; src [ srcpos ] != '\0'; srcpos ++ )
    {
        if ( src [ srcpos ] == '\t' )
        {
            for ( j = tabsize - dstpos % tabsize; j > 0; j -- )
            {
                if ( dstpos >= dstsize - 1 )
                {
                    dst  [ dstpos ] = '\0';
                    return ( 0 );
                }
                dst [ dstpos++ ] = ' ';
            }
        }
        else
        {
            if ( dstpos >= dstsize - 1 )
            {
                dst  [ dstpos ] = '\0';
                return ( 0 );
            }
            dst [ dstpos++ ] = src [ srcpos ];
        }
    }
    dst[dstpos] = '\0';
    return ( 1 );
}

/*----------------------------------------------------------
	go into background automatically

	modification
	---------------------------------------------------
	tms		11/13/2003		handle with fd 0, 1 and 2.

----------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<errno.h>
#include	<fcntl.h>

#include	"shslib.h"

void background ( char *outfile, char *errfile )
{
	int				xpid;

	switch ( fork () )
	{
		case -1:
			printf ( "can not fork" );
			exit ( 1 );
			
		case 0:
			xpid = getpid ();
			break;

		default:
			exit ( 0 );
	}

	/*----------------------------------------------------------
		ps -eao '%p %P %r %c %a' | grep dmn
	----------------------------------------------------------*/
	if ( setpgid ( 0, xpid ) == -1 )
	{
		printf ( "setpgid: %d\n", errno );
		exit ( 1 );
	}

	/*----------------------------------------------------------
		close 0.  reopen on /dev/null.
		close 1 and 2.  reopen on as specified, or on /dev/null.
	----------------------------------------------------------*/
	close ( 0 );
	if ( open ( "/dev/null", O_RDONLY ) < 0 )
		exit ( 2 );

	close ( 1 );
	if ( outfile == NULL )
		outfile = "/dev/null";
	if ( fopen ( outfile, "a" ) == NULL )
	{
		fprintf ( stderr, "Can not re-open stdout on [%s]\n", outfile );
		exit ( 3 );
	}

	close ( 2 );
	if ( errfile == NULL )
		errfile = "/dev/null";
	if ( fopen ( errfile, "a" ) == NULL )
	{
		printf ( "Can not re-open stderr on [%s]\n", outfile );
		exit ( 4 );
	}
}

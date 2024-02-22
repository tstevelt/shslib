/*----------------------------------------------------------------------------
	Program : ForkAndExec.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time, perhaps 1991
	Synopsis: fork and exec from K&R, piped according to "printf" destination
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

#include 	"shsprivate.h"
#include 	"shslib.h"

static	char	xbuf[2048];
#define	MAXTOKS		100
static	char	*tokens[MAXTOKS];
static	int		tokcnt;

void ForkAndExec ( char *CommandLine, int PrintDestination )
{
	int		pfd[2];
	int		currpid;
	FILE	*ChildIFP;

	switch ( PrintDestination )
	{
		case PRINT_DESTINATION_STDOUT:
		case PRINT_DESTINATION_STDERR:
		case PRINT_DESTINATION_ERROR_ARRAY:
		case PRINT_DESTINATION_SILENT:
			break;
		default:
			printf ( "ForkAndExec: Unknown print destination.\n" );
			return;
	}


	if ( pipe ( pfd ) == -1 )
	{
		printf ( "ForkAndExec: can not make pipe.\n" );
		return;
	}

	currpid = fork ();
	switch ( currpid )
	{
		case -1:
			printf ( "ForkAndExec: fork failed\n" );
			return;

		case 0: 
			/*----------------------------
				child
			----------------------------*/
			close ( pfd[0] );	/* child does not read from parent */
			close ( 1 );		/* so I have a slot for dup() */

			if ( dup ( pfd[1] ) == -1 )
				exit (1);

			/*----------------------------------------------------------
				map stderr to stdout
			----------------------------------------------------------*/
			close ( 2 );
			dup ( 1 );

			close ( pfd[1] );	/* no longer needed */

			tokcnt = GetTokensW ( CommandLine, tokens, (MAXTOKS-1) );
			tokens[tokcnt] = (char *)0;

// int xt;
// for ( xt = 0; xt < tokcnt; xt++ )
// {
// 	printf ( "%d %s<br>\n", xt, tokens[xt] );
// }
// fflush ( stdout );

			execvp ( tokens[0], tokens );

			fprintf ( stderr, "execl failed (maybe), errno %d", errno );
			
			printf ( "Can not exec [%s]\n", CommandLine );

			exit ( 0 );

		default:
			/*----------------------------
				parent
			----------------------------*/
			close ( pfd[1] );					/* not going to write */

			ChildIFP = fdopen ( pfd[0], "r" );	/* want to read with buffered functions */

			while ( fgets ( xbuf, sizeof(xbuf), ChildIFP ) != (char *)0 )
			{
				switch ( PrintDestination )
				{
					case PRINT_DESTINATION_SILENT:
						printf ( "%s > /dev/null", xbuf );
						break;
					case PRINT_DESTINATION_STDOUT:
						printf ( "%s", xbuf );
						break;
					case PRINT_DESTINATION_STDERR:
						fprintf ( stderr, "%s", xbuf );
						break;
					case PRINT_DESTINATION_ERROR_ARRAY:
/*----------------------------------------------------------
xxx						if ( ErrorCount < MAXERR )
xxx						{
xxx							snprintf ( ErrorArray[ErrorCount++].Message, sizeof(ErrorArray[ErrorCount]), "%s", xbuf );
xxx						}
xxx						else
xxx						{
xxx							printf ( "%s > /dev/null", xbuf );
xxx						}
----------------------------------------------------------*/
						SafeError ( COLOR_NORMAL, "%s", xbuf );
						break;
				}

			}
			break;
	}
}

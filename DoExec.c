/*----------------------------------------------------------------------------
	Program : progname.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 01/19/2021
	Synopsis: xxxxxxxxxxx
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
/*--------------------------------------------------------------------
    DoExec.c

    TCP/IP Based Database Server
    This source code is copyright 2002 by Victory Wholesale Grocers.
    Use, copying, or disclosure subject to signed License Agreement
    with Victory Wholesale Grocers.

    Author     : Tom Stevelt
    Date       : 2002
    Description: Run a system command using fork and exec. Map 
				 stderr to stdout.  Return combined stderr and stdout
				 to client.  Can return unlimited output.

--------------------------------------------------------------------*/


#include 	"elsdmn.h"

static	unsigned char	ChildBuffer[MAXCOMMBUFFER];

static	char	xbuf[1024];
#define	MAXTOKS		50
static	char	*tokens[MAXTOKS];
static	int		tokcnt;

void DoExec ( FILE *DaemonIFP, FILE *DaemonOFP, char *CommandLine )
{
	int		pfd[2];
	int		currpid;
	FILE	*ChildIFP;
	int		xl, rv;
	int		Command;
	int		BuffSize;

	if ( pipe ( pfd ) == -1 )
	{
		sprintf ( msgbuf, "DoExec: can not make pipe: %s", CommandLine );
		logmsg ( LogFileName, msgbuf );
		return;
	}

	currpid = fork ();
	switch ( currpid )
	{
		case -1:
			sprintf ( msgbuf, "DoExec: fork failed: %s", CommandLine );
			logmsg ( LogFileName, msgbuf );
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

			execvp ( tokens[0], tokens );

			sprintf ( msgbuf, "execl failed (maybe), errno %d", errno );
			logmsg ( LogFileName, msgbuf );
			
			printf ( "Can not exec [%s]\n", CommandLine );

			exit ( 0 );

		default:
			/*----------------------------
				parent
			----------------------------*/
			close ( pfd[1] );					/* not going to write */
			ChildIFP = fdopen ( pfd[0], "r" );	/* want to read with buffered functions */

#ifdef ASCII_LINE_ORIENTED
			while ( fgets ( xbuf, sizeof(xbuf), ChildIFP ) != (char *)0 )
			{
				Command = CMD_EXEC;
				rv = DB_SUCCESS;
				xl = nsStrlen ( xbuf );
				xl++;
				BuffSize = MakeExecBuffer ( ChildBuffer, Command, rv, xl, xbuf );
				WriteBuffer ( DaemonOFP, (unsigned char *)ChildBuffer, BuffSize );

				ReadBuffer ( DaemonIFP, (unsigned char *)ChildBuffer, sizeof(ChildBuffer) );
				Command = GetBufferType ( ChildBuffer );
				if ( Command != CMD_EXEC_NEXT )
					break;
			}
#else
			while ( feof ( ChildIFP ) == 0 )
			{
				xl = fread ( xbuf, 1, sizeof(xbuf), ChildIFP );

				if ( xl > 0 )
				{
					Command = CMD_EXEC;
					rv = DB_SUCCESS;
					BuffSize = MakeExecBuffer ( ChildBuffer, Command, rv, xl, xbuf );
					WriteBuffer ( DaemonOFP, (unsigned char *)ChildBuffer, BuffSize );

					ReadBuffer ( DaemonIFP, (unsigned char *)ChildBuffer, sizeof(ChildBuffer) );
					Command = GetBufferType ( ChildBuffer );
					if ( Command != CMD_EXEC_NEXT )
						break;
				}
			}
#endif

			Command = CMD_EXEC;
			rv = DB_END_OF_SET;
			xl = 0;
			BuffSize = MakeExecBuffer ( ChildBuffer, Command, rv, xl, xbuf );
			WriteBuffer ( DaemonOFP, ChildBuffer, BuffSize );

			break;
	}
}

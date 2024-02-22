/*----------------------------------------------------------------------------
	Program : MemoryMonitor.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Jan 2021
	Synopsis: Monitor out-of-memory mysql_query or any other type of process.
	Return  : PID of watcher.  Calling program must kill(rv,SIGKILL) the 
			  watcher, or he will go back to PPID of 1.

	Who		Date		Modification
	---------------------------------------------------------------------

----------------------------------------------------------------------------*/
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
#include	<signal.h>

#include	"shslib.h"

static	int		DebugMemoryMonitor = 0;

int MemoryMonitor ( double LimitPercent )
{
	int		CallerPID;
	int		ChildPID;
	PROCESS_RECORD *ptrPS;
	double	MemoryPercent;

	CallerPID = getpid ();
	ptrPS = ProcessStats ( CallerPID ); 

	if ( DebugMemoryMonitor )
	{
		printf ( "MemoryMonitor: Caller  %d\n",   CallerPID );
		printf ( "MemoryMonitor: memory  %ld\n",  ptrPS->MemAvailable );
		printf ( "MemoryMonitor: percent %.2f\n", LimitPercent );
	}

	ChildPID = fork ();

	switch ( ChildPID )
	{
		case -1:
			fprintf ( stderr, "MemoryMonitor: fork failed, errno %d\n", errno );
			exit ( 1 );

		case 0:
			/*----------------------------
				child
			----------------------------*/
			while ( 1 )
			{
				sleep ( 1 );
				ptrPS = ProcessStats ( CallerPID ); 
				MemoryPercent = 100.0 * ( (double)ptrPS->Vsize / (double)ptrPS->MemAvailable );
				if ( DebugMemoryMonitor )
				{
					printf ( "MemoryMonitor: %.2f\n", MemoryPercent );
					fflush ( stdout );
				}
				if ( MemoryPercent > LimitPercent )
				{
					kill ( CallerPID, SIGALRM );
					exit ( 0 );
				}
			}
			break;

		default:
			/*----------------------------
				parent
			----------------------------*/
			
			break;
	}

	return ( ChildPID );
}

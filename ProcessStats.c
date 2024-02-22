/*----------------------------------------------------------------------------
	Program : ProcessStats.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Feb 2021
	Synopsis: Return pointer to structure containing load averge and memory usage.
	Return  : 
	ThanksTo: https://unix.stackexchange.com/questions/356532/see-how-much-memory-was-reserved-with-malloc-by-a-process-on-linux#356541
	ManPage : man proc
	See Also: man 2 getrlimit

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		02/05/2021	Added StartTime, CurrentTime and MemAvailable,
						along with supporting functions();

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/times.h>

#include	"shslib.h"

static	PROCESS_RECORD		ProcessRecord;
static	int					ClockTicksPerSecond;

#define		MAXTOKS		53
static	char	*tokens[MAXTOKS];
static	int		tokcnt;

/*----------------------------------------------------------
	better implementation would use [man 2] clock_gettime.
----------------------------------------------------------*/
/*----------------------------------------------------------
$ cat /proc/meminfo
MemTotal:        1821464 kB
MemFree:          713836 kB
MemAvailable:     981368 kB
----------------------------------------------------------*/
void ProcessStatsInit ( int Verbose )
{
	struct tms 		xtms;
	FILE		*fp;
	char		xbuf[1024];

	ClockTicksPerSecond = sysconf(_SC_CLK_TCK);

	ProcessRecord.StartTime  = times ( &xtms );;
	ProcessRecord.CurrentTime = ProcessRecord.StartTime;

	if (( fp = fopen ( "/proc/meminfo", "r" )) != (FILE *)0 )
	{
		while ( fgets ( xbuf, sizeof(xbuf), fp ) != (char *)0 )
		{
			if ( nsStrncmp ( xbuf, "MemAvailable", 12 ) == 0 )
			{
				tokcnt = GetTokensW ( xbuf, tokens, MAXTOKS );
				if ( tokcnt >= 2 )
				{
					ProcessRecord.MemAvailable = nsAtol ( tokens[1] );
				}
				break;
			}
		}
		fclose ( fp );
	}
	
	if ( Verbose )
	{
		printf ( "clock ticks per second: %d\n", ClockTicksPerSecond );
		printf ( "MemAvailable %ld\n", ProcessRecord.MemAvailable );
		fflush ( stdout );
	}
}

PROCESS_RECORD *ProcessStats ( int ProcessPID )
{
	char		fn[256];
	FILE		*fp;
	char		xbuf[1024];
	struct tms 		xtms;

	if ( ProcessRecord.StartTime == 0 )
	{
		ProcessStatsInit ( 0 );
	}

	ProcessRecord.Success = 1;
	ProcessRecord.LoadAverage = 0.0;
	ProcessRecord.Vsize = 0;
	ProcessRecord.RSS = 0;
	ProcessRecord.CurrentTime  = times ( &xtms );;

	if (( fp = fopen ( "/proc/loadavg", "r" )) != (FILE *)0 )
	{
		fgets ( xbuf, sizeof(xbuf), fp );
		fclose ( fp );
		ProcessRecord.LoadAverage = nsAtof ( xbuf );
	}
	else 
	{
		ProcessRecord.Success = 0;
	}

	sprintf ( fn, "/proc/%d/stat", ProcessPID );
	if (( fp = fopen ( fn, "r" )) != (FILE *)0 )
	{
		fgets ( xbuf, sizeof(xbuf), fp );
		fclose ( fp );
		tokcnt = GetTokensStd ( xbuf, " ", tokens, MAXTOKS, 0 );
		if ( tokcnt < 25 )
		{
			ProcessRecord.Success = 0;
		}
		else
		{
			ProcessRecord.Vsize     = nsAtol ( tokens[22] ) / 1024;
			ProcessRecord.RSS       = nsAtol ( tokens[23] ) * 4;
		}
	}
	else 
	{
		ProcessRecord.Success = 0;
	}

	return ( &ProcessRecord );
}

void PrintProcessStats ( int ProcessPID )
{
	double		ProcessTime;
	double		MemoryPercent;

	ProcessStats ( ProcessPID );
	if ( ProcessRecord.Success == 0 )
	{ 
		printf ( "Could not retrieve process stats\n" );
	}
	else
	{
		ProcessTime = ((double)ProcessRecord.CurrentTime - (double)ProcessRecord.StartTime) / (double) ClockTicksPerSecond;
		MemoryPercent = 100.0 * (double) ProcessRecord.Vsize / (double)ProcessRecord.MemAvailable;
		printf ( "Process stats: loadavg %.2f vsize %ld (%.1f%%) rss %ld time %.2f\n",
				ProcessRecord.LoadAverage, ProcessRecord.Vsize, MemoryPercent, ProcessRecord.RSS, ProcessTime );
	}
	fflush ( stdout );
}

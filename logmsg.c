/*----------------------------------------------------------------------------
	Program : logmsg.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : May 21, 2002
	Synopsis: made this a library function.
	          given file name and string, open the file, write string and
			  close the file again.
	Return  : none, sets int logerrno to errno on error.

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		10/1/2		Added logDTUmsg() to add date, time and user to msg.
	tms		04/28/2010	Added logDSUmsg() which uses military time to the second.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<errno.h>
#include	"shslib.h"

#undef		DEBUG_LOG_MSG	

int	logerrno;

int include_pid = 1;

void logmsg ( char *Filename, char *Message )
{
	FILE	*logfp;
	int		pid;
	int		NeedToClose = 0;

#ifdef DEBUG_LOG_MSG	
printf ( "logmsg<br>\n" );
#endif

	logerrno = 0;

	if ( nsStrcmp ( Filename, "stdout" ) == 0 )
    {
        logfp = stdout;
    }
	else 
	{
		if (( logfp = fopen ( Filename, "a+" )) == (FILE *)0 )
		{
			logfp = stdout;
			fprintf ( logfp,
	                "Could not open [%s] for append, errno %d\n", Filename, errno );
		}
		else
		{
			NeedToClose = 1;
		}
	}

	if ( include_pid )
	{
		pid = getpid ();

		if ( fprintf ( logfp, "PID: %d ", pid ) < 0 )
		{
			logerrno = errno;
			nsFclose ( logfp );
			return;
		}
	}

	if ( fprintf ( logfp, "%s\n", Message ) < 0 )
	{
		logerrno = errno;
		nsFclose ( logfp );
		return;
	}

	if ( NeedToClose == 1 )
	{
		if ( nsFclose ( logfp ) != 0 )
		{
			logerrno = errno;
		}
	}
	else
	{
		fflush ( logfp );
	}
}

static	char	MyBuffer[256];
static	char	PrevMsg [256];

void logDSUmsg ( char *Filename, char *Message )
{
	char	AsciiDate[9], AsciiTime[9];
	char	*UserName;
	int		MsgLen;

#ifdef DEBUG_LOG_MSG	
printf ( "logDTUmsg<br>\n" );
#endif

	Xgetdates ( AsciiDate, AsciiTime );

	if (( UserName = getenv("LOGNAME")) == (char *)0 )
	{
		if (( UserName = getenv("REMOTE_USER")) == (char *)0 )
		{
			UserName = "UNKNOWN";
		}
	}

	MsgLen = nsStrlen ( Message );
	if ( MsgLen > sizeof(MyBuffer) - 30 )
	{
		MsgLen = sizeof(MyBuffer) - 45;

		snprintf ( MyBuffer, sizeof(MyBuffer),
			"%-9.9s %-9.9s %-8.8s TRUNCATED %*.*s ...", 
				AsciiDate, AsciiTime, UserName, MsgLen, MsgLen, Message );
	}
	else
	{
		snprintf ( MyBuffer, sizeof(MyBuffer),
			"%-9.9s %-9.9s %-8.8s %s", 
				AsciiDate, AsciiTime, UserName, Message );
	}

	if ( memcmp ( PrevMsg, MyBuffer, sizeof(PrevMsg) ) != 0 )
	{
		logmsg ( Filename, MyBuffer );
	}

	memcpy ( PrevMsg, MyBuffer, sizeof(PrevMsg) );
}

void logDTUmsg ( char *Filename, char *Message )
{
	char	AsciiDate[9], AsciiTime[9];
	char	*UserName;
	int		MsgLen;

#ifdef DEBUG_LOG_MSG	
printf ( "logDTUmsg<br>\n" );
#endif

	Xgetdate ( AsciiDate, AsciiTime );

	if (( UserName = getenv("LOGNAME")) == (char *)0 )
	{
		if (( UserName = getenv("REMOTE_USER")) == (char *)0 )
		{
			UserName = "UNKNOWN";
		}
	}

	MsgLen = nsStrlen ( Message );
	if ( MsgLen > sizeof(MyBuffer) - 30 )
	{
		MsgLen = sizeof(MyBuffer) - 45;

		snprintf ( MyBuffer, sizeof(MyBuffer),
			"%-9.9s %-9.9s %-8.8s TRUNCATED %*.*s ...", 
				AsciiDate, AsciiTime, UserName, MsgLen, MsgLen, Message );
	}
	else
	{
		snprintf ( MyBuffer, sizeof(MyBuffer),
			"%-9.9s %-9.9s %-8.8s %s", 
				AsciiDate, AsciiTime, UserName, Message );
	}

	if ( memcmp ( PrevMsg, MyBuffer, sizeof(PrevMsg) ) != 0 )
	{
		logmsg ( Filename, MyBuffer );
	}

	memcpy ( PrevMsg, MyBuffer, sizeof(PrevMsg) );
}

void logDTmsg ( char *Filename, char *UserName, char *Message )
{
	char	*cp;
	char	AsciiDate[9], AsciiTime[9];
	int		MsgLen;

#ifdef DEBUG_LOG_MSG	
printf ( "logDTmsg<br>\n" );
#endif

	Xgetdate ( AsciiDate, AsciiTime );

	cp = getenv ( "REMOTE_ADDR" );
	if ( cp == (char *)0 )
	{
		cp = "-";
	}

	MsgLen = nsStrlen ( Message );
	if ( MsgLen > sizeof(MyBuffer) - 30 )
	{
		MsgLen = sizeof(MyBuffer) - 45;

		snprintf ( MyBuffer, sizeof(MyBuffer),
			"%s %-9.9s %-9.9s %-8.8s TRUNCATED %*.*s ...", 
				cp, AsciiDate, AsciiTime, UserName, MsgLen, MsgLen, Message );
	}
	else
	{
		snprintf ( MyBuffer, sizeof(MyBuffer),
			"%s %-9.9s %-9.9s %-8.8s %s", 
				cp, AsciiDate, AsciiTime, UserName, Message );
	}

	if ( memcmp ( PrevMsg, MyBuffer, sizeof(PrevMsg) ) != 0 )
	{
		logmsg ( Filename, MyBuffer );
	}

	memcpy ( PrevMsg, MyBuffer, sizeof(PrevMsg) );
}

void LogFirstLineOrSixty ( char *Filename, const char *SomeString )
{
	int			xl, xm, xn, xo;
	char		msgbuf[100];

#ifdef DEBUG_LOG_MSG	
printf ( "LogFirstLineOrSixty<br>\n" );
#endif

	xm = xl = nsStrlen ( SomeString );
	if ( xm > 60 )
	{
		xm = 60;
	}
	xo = xm;

	for ( xn = 0; xn < xm; xn++ )
	{
		if ( SomeString[xn] == '\n' )
		{
			xo = xn;
			break;
		}
	}

	if ( xo < xl )
	{
		snprintf ( msgbuf, sizeof(msgbuf), "[%.*s] TRUNC", xo, SomeString );
	}
	else
	{
		snprintf ( msgbuf, sizeof(msgbuf), "[%s]", SomeString );
	}

	logDTUmsg ( Filename, msgbuf );
}

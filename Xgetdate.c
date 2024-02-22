/*----------------------------------------------------------------------------
	Program : Xgetdate.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: Does not need Unify
	Who		Date		Modification
	---------------------------------------------------------------------
	tms		04/28/2010	Xgetdatems - military time including seconds.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdlib.h>
#include	<time.h>
#include	"shslib.h"

void Xgetdatem ( char *cday, 	/* must be at least 9 chars */
				 char *miltm )	/* must be at least 6 chars */
{
	int		arr[3];
	long	tvec;
	struct	tm *t;
	char	*cp, xbuf[10];

	(void)time (&tvec);
	t = localtime (&tvec);
	if ( t == NULL )
	{
		fprintf ( stderr, "this is messed up\n" );
		exit ( 1 );
	}

	if (( cp = getenv ( "SYSDATE" )) == (char *)0 )
	{
		arr[0] = (t->tm_mon) + 1;
		arr[1] = t->tm_mday;
		while ( t->tm_year > 99 )
			t->tm_year -= 100;
		arr[2] = t->tm_year ;
	}
	else
	{
		/*----------------------------
			012345
			mmddyy
		----------------------------*/
		nsStrncpy ( xbuf, cp, 6 );
		arr[2] = nsAtoi ( &xbuf[4] );
		xbuf[4] = '\0';
		arr[1] = nsAtoi ( &xbuf[2] );
		xbuf[2] = '\0';
		arr[0] = nsAtoi ( &xbuf[0] );
	}

	if (cday != (char *) 0)
		sprintf(cday, "%02d/%02d/%02d", arr[0], arr[1], arr[2]);

	if (miltm  != (char *) 0)
		sprintf( miltm, "%2d:%02d", t->tm_hour, t->tm_min );
}

void Xgetdates ( char *cday, 	/* mm/dd/yy must be at least 9 chars */
				 char *miltm )	/* hh:mm:ss must be at least 9 chars */
{
	int		arr[3];
	long	tvec;
	struct	tm *t;
	char	*cp, xbuf[10];

	(void)time (&tvec);
	t = localtime (&tvec);
	if ( t == NULL )
	{
		fprintf ( stderr, "this is messed up\n" );
		exit ( 1 );
	}

	if (( cp = getenv ( "SYSDATE" )) == (char *)0 )
	{
		arr[0] = (t->tm_mon) + 1;
		arr[1] = t->tm_mday;
		while ( t->tm_year > 99 )
			t->tm_year -= 100;
		arr[2] = t->tm_year ;
	}
	else
	{
		/*----------------------------
			012345
			mmddyy
		----------------------------*/
		nsStrncpy ( xbuf, cp, 6 );
		arr[2] = nsAtoi ( &xbuf[4] );
		xbuf[4] = '\0';
		arr[1] = nsAtoi ( &xbuf[2] );
		xbuf[2] = '\0';
		arr[0] = nsAtoi ( &xbuf[0] );
	}

	if (cday != (char *) 0)
		sprintf(cday, "%02d/%02d/%02d", arr[0], arr[1], arr[2]);

	if (miltm  != (char *) 0)
		sprintf( miltm, "%2d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec );
}

void Xgetdate ( char *cday, 	/* must be at least 9 chars */
				char *ctm )		/* must be at least 9 chars */
{
	char	ampm[3];
	int		xhour, xmin;

	Xgetdatem ( cday, ctm );

	if (ctm  != (char *) 0)
	{
		xhour = nsAtoi ( ctm );
		xmin  = nsAtoi ( &ctm[3] );

		if ( xhour > 11 )
			nsStrcpy ( ampm, "PM" );
		else
			nsStrcpy ( ampm, "AM" );

		if ( xhour > 12 )
			xhour -= 12;

		if ( xhour == 0 )
			xhour = 12;

		sprintf ( ctm, "%2d:%02d %s", xhour, xmin, ampm );
	}
}

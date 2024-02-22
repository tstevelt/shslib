/*----------------------------------------------------------------------------
	Program : NullSafeFuncs.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2020
	Synopsis: Wrapper functions for C functions which puke on NULL pointers.
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

#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	"shslib.h"

int nsAtoi (const char *cpOne )
{
	if ( cpOne == (char *)0  )
		return ( 0.0 );

	return ( atoi(cpOne) );
}

long nsAtol (const char *cpOne )
{
	if ( cpOne == (char *)0  )
		return ( 0.0 );

	return ( atol(cpOne) );
}

double nsAtof (const char *cpOne )
{
	if ( cpOne == (char *)0  )
		return ( 0.0 );

	if (( strncasecmp ( cpOne, "inf", 3 ) == 0 ) ||
		( strncasecmp ( cpOne, "nan", 3 ) == 0 ))
	{
		return ( 0.0 );
	}
	
	return ( atof(cpOne) );
}

int nsStrlen (const char *cpOne )
{
	if ( cpOne == (char *)0  )
		return ( 0 );

	return ( strlen( cpOne ) );
}

int nsStrcmp(const char *cpOne, const char *cpTwo )
{
	if (( cpOne == (char *)0 ) && ( cpTwo == (char *)0 ))
		return ( 0 );

	if ( cpOne == (char *)0  )
		return ( -1 );
	
	if ( cpTwo == (char *)0  )
		return ( 1 );
	
	return ( strcmp(cpOne, cpTwo ) );
}

int nsStrncmp(const char *cpOne, const char *cpTwo, int Number )
{
	if (( cpOne == (char *)0 ) && ( cpTwo == (char *)0 ))
		return ( 0 );

	if ( cpOne == (char *)0  )
		return ( -1 );
	
	if ( cpTwo == (char *)0  )
		return ( 1 );
	
	return ( strncmp(cpOne, cpTwo, Number ) );
}


/*----------------------------------------------------------
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
----------------------------------------------------------*/

int nsStrcasecmp(const char *cpOne, const char *cpTwo )
{
	if (( cpOne == (char *)0 ) && ( cpTwo == (char *)0 ))
		return ( 0 );

	if ( cpOne == (char *)0  )
		return ( -1 );
	
	if ( cpTwo == (char *)0  )
		return ( 1 );
	
	return ( strcasecmp(cpOne, cpTwo ) );
}

int nsStrncasecmp(const char *cpOne, const char *cpTwo, int Number )
{
	if (( cpOne == (char *)0 ) && ( cpTwo == (char *)0 ))
		return ( 0 );

	if ( cpOne == (char *)0  )
		return ( -1 );
	
	if ( cpTwo == (char *)0  )
		return ( 1 );
	
	return ( strncasecmp(cpOne, cpTwo, Number ) );
}

/*----------------------------------------------------------
----------------------------------------------------------*/
char * nsStrnstr(const char *cpOne, const char *cpTwo, int Number )
{
	char	*rv = NULL;
	char	*haystack;
	int		ndx, Length;

	if (( cpOne == (char *)0 ) && ( cpTwo == (char *)0 ))
		return ( rv );

	if ( cpOne == (char *)0  )
		return ( rv );
	
	if ( cpTwo == (char *)0  )
		return ( rv );
	
	haystack = (char *) cpOne;
	Length = strlen ( cpOne );
	for ( ndx = 0; ndx < Length - Number + 1; ndx++ )
	{
		if ( strncmp ( haystack, cpTwo, Number ) == 0 )
		{
			rv = haystack;
			break;
		}
		haystack++;
	}

	return ( rv );
}

char *nsStrcpy(char *cpOne, const char *cpTwo)
{
	if ( cpOne == (char *)0  )
		return ( (char *)0 );
	
	if ( cpTwo == (char *)0  )
		return ( (char *)0 );
	
	return ( strcpy(cpOne, cpTwo) );
}

char *nsStrncpy(char *cpOne, const char *cpTwo, int Number )
{
	if ( cpOne == (char *)0  )
		return ( (char *)0 );
	
	if ( cpTwo == (char *)0  )
		return ( (char *)0 );
	
	return ( strncpy(cpOne, cpTwo, Number ) );
}

char *nsStrchr(const char *cpOne, int intChar )
{
	if ( cpOne == (char *)0  )
		return ( (char *)0 );
	
	return ( strchr(cpOne, intChar ) );
}

char *nsStrrchr(const char *cpOne, int intChar )
{
	if ( cpOne == (char *)0  )
		return ( (char *)0 );
	
	return ( strrchr(cpOne, intChar ) );
}

char *nsStrstr(const char *cpOne, const char *cpTwo)
{
	if ( cpOne == (char *)0  )
		return ( (char *)0 );
	
	if ( cpTwo == (char *)0  )
		return ( (char *)0 );
	
	return ( strstr(cpOne, cpTwo) );
}

char *strcasestr(const char *cpOne, const char *cpTwo);

char *nsStrcasestr(const char *cpOne, const char *cpTwo)
{
	if ( cpOne == (char *)0  )
		return ( (char *)0 );
	
	if ( cpTwo == (char *)0  )
		return ( (char *)0 );
	
	return ( strcasestr(cpOne, cpTwo) );
}

char *nsStrcat(char *cpOne, char *cpTwo)
{
	if ( cpOne == (char *)0  )
		return ( (char *)0 );
	
	if ( cpTwo == (char *)0  )
		return ( (char *)0 );
	
	return ( strcat(cpOne, cpTwo) );
}

int nsFclose ( FILE *fp )
{
	if ( fp == (FILE *)0 )
		return ( 0 );

	return ( fclose ( fp ));
}

static	char	*TempString = (char *)0;
static	int		TempLength = 0;

char *nsStrToUpcase ( char *InString )
{
	int		len, ndx;

	len = nsStrlen ( InString );
	if ( len == 0 )
	{
		return ( NULL );
	}

	if ( TempLength < len + 1 )
	{
		TempLength = len + 1;
		if (( TempString = realloc ( TempString, TempLength )) == (char *)0 )
		{
			return ( NULL );
		}
	}

	for ( ndx = 0; ndx < len; ndx++ )
	{
		TempString[ndx] = toupper ( InString[ndx] );
	}
	TempString[ndx] = '\0';

	return ( TempString );
}

char *nsStrToLowcase ( char *InString )
{
	int		len, ndx;

	len = nsStrlen ( InString );
	if ( len == 0 )
	{
		return ( NULL );
	}

	if ( TempLength < len + 1 )
	{
		TempLength = len + 1;
		if (( TempString = realloc ( TempString, TempLength )) == (char *)0 )
		{
			return ( NULL );
		}
	}

	for ( ndx = 0; ndx < len; ndx++ )
	{
		TempString[ndx] = tolower ( InString[ndx] );
	}
	TempString[ndx] = '\0';

	return ( TempString );
}

int nsCharCount ( char *InString, char Character )
{
	int		len, ndx, cnt;

	len = nsStrlen ( InString );
	if ( len == 0 )
	{
		return ( 0 );
	}

	for ( ndx = 0, cnt = 0; ndx < len; ndx++ )
	{
		if ( InString[ndx] == Character )
		{
			cnt++;
		}
	}

	return ( cnt );
}


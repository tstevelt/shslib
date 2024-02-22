/*----------------------------------------------------------------------------
	Program : pwfuncs.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: Pass word rules, generation.
				char *pw_genpw ( int Length , int Complexity );
				void pw_genkey ( int Length , int Salt );
				void pw_encode ( char *s , int Length , int Salt );
				char *pw_policy_string ( int ErrorCode );
				int pw_policy ( char *PlainText , int ComplexityCount );
				int pw_check ( char *PlainText , char *SaltEncoded );
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		02/24/2021	Moved test program into ../test/subdir

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#undef DEBUG 

#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

#include	"shslib.h"

/*----------------------------------------------------------
	Complexity
	1 = lower case
	2 = and upper case
	3 = and digits
	4 = and punctuation
----------------------------------------------------------*/
char *pw_genpw ( int Length, int Complexity )
{
	int		Index, Character;
	int		SawUpper, SawLower, SawDigit, SawPunct, SawTotal;
	static	char	NewPassword [ MAX_PASSWORD_LENGTH + 1 ];

	srand ( (unsigned int) time ( NULL ) );

	if ( Length < MIN_PASSWORD_LENGTH )
	{
		Length = MIN_PASSWORD_LENGTH * 2;
	}

	if ( Length > MAX_PASSWORD_LENGTH )
	{
		Length = MAX_PASSWORD_LENGTH;
	}

	if ( Complexity == 0 )
	{
		Complexity = 3;
	}

	memset ( NewPassword, '\0', sizeof(NewPassword) );

	while ( 1 )
	{
		SawUpper = SawLower = SawDigit = SawPunct = SawTotal = 0;

		for ( Index = 0;; )
		{
			Character = rand ();
			
			Character = 32 + Character % 95;

			if ( nsStrchr ( "abcdefghijklmnopqrstuvwxyz", Character ) != (char *)0 )
			{
				SawLower = 1;
			}
			else if ( nsStrchr ( "ABCDEFGHIJKLMNOPQRSTUVWXYZ", Character ) != (char *)0 )
			{
				if ( Complexity < 2 )
				{
					continue;
				}
				SawUpper = 1;
			}
			else if ( nsStrchr ( "0123456789", Character ) != (char *)0 )
			{
				if ( Complexity < 3 )
				{
					continue;
				}
				SawDigit = 1;
			}
			else if (( Character >= 33 && Character <= 47 ) ||
					 ( Character >= 58 && Character <= 64 ))
			{
				if ( Complexity < 4 )
				{
					continue;
				}
				SawPunct = 1;
			}
			else
			{
				continue;
			}

			NewPassword[Index] = Character;
			Index++;
			if ( Index >= Length )
			{
				break;
			}
		}

		SawTotal = SawUpper + SawLower + SawDigit + SawPunct;
		if ( SawTotal < Complexity )
		{
#ifdef DEBUG
			printf ( "  <<=== NOT COMPLEX ENOUGH\n" );
#endif
			memset ( NewPassword, '\0', sizeof(NewPassword) );
		}
		else
		{
			break;
		}
	}

	return ( NewPassword );
}

void pw_genkey ( int Length, int Salt )
{
	int		xi, ndx;
	static unsigned char itoa62[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	srand ( Salt );
	
	printf ( "pw_genkey length %d salt %d\n", Length, Salt );

	for  ( xi = 0; xi < Length; xi++ )
	{
		if ( xi % 76 == 0 )
		{
			printf ( "\n" );
		}

		ndx = rand ();
		ndx = ndx % 62;
		printf ( "%c", itoa62[ndx] );
	}

	printf ( "\n\n" );
}

void pw_encode(char *s, int Length, int Salt)
{
	int		ndx, xi;
	static char RandomArray[] = "DjxZMFRLy8Xqn6ghnLMcuvPAgWY5KIkVzf4MtVhpbFdOJK36fNhXI6hxcD0vWiQTNTpGwV3Yihu11w5gJmBaqsVT3TMXBk1WDqnALog3Va2WU8AmsLKjBpAFIUmREnxSciaxXGz2o1XJ7f50zPh8CrLSL6tXrozTXXR2lO2aPZrXDuVCHCKT1gtKmkrdYp53MU58s8gHfXmsPF2gRL9Q12ilmaMINRMhtPplVT1Byn1N143QNArMAZ7u7RBUrXCk";
	int			RandomCount = sizeof(RandomArray) / sizeof(char);

	for ( ndx = 0; ndx < Length; ndx++ )
	{
		xi = *s + Salt;
		xi = xi % RandomCount;
		*s = RandomArray[xi];

		s++;
	}
}

char *pw_policy_string ( int ErrorCode )
{
	static	char	msgbuf[128];

	switch ( ErrorCode )
	{
		case 0:
			return ( "Okay" );
		case -1:
			snprintf ( msgbuf, sizeof(msgbuf),
				"Password is too short, minimum is %d characters.", MIN_PASSWORD_LENGTH );
			return ( msgbuf );
		case -2:
			snprintf ( msgbuf, sizeof(msgbuf),
				"Password is too long, maximum is %d characters.", MAX_PASSWORD_LENGTH );
			return ( msgbuf );
		case -3:
			snprintf ( msgbuf, sizeof(msgbuf),
				"Password too simple, must contain %d of upper, lower, numbers or puntuation.", PASSWORD_POLICY_COUNT );
			return ( msgbuf );
	}
	return ( "pw_policy_string: unknown error code." );
}

int	pw_policy ( char * PlainText, int ComplexityCount )
{
	int		Index, PasswordLength, SawUpper, SawLower, SawDigit, SawPunct, SawTotal;

	PasswordLength = nsStrlen ( PlainText );
	if ( PasswordLength < MIN_PASSWORD_LENGTH )
	{
		return ( -1 );
	}
	if ( PasswordLength > MAX_PASSWORD_LENGTH )
	{
		return ( -2 );
	}

	SawUpper = SawLower = SawDigit = SawPunct = 0;
	
	for ( Index = 0; Index < PasswordLength; Index++ )
	{
		if (( PlainText[Index] >= 'A' ) && ( PlainText[Index] <= 'Z' ))
		{
			SawUpper = 1;
		}
		else if (( PlainText[Index] >= 'a' ) && ( PlainText[Index] <= 'z' ))
		{
			SawLower = 1;
		}
		else if (( PlainText[Index] >= '0' ) && ( PlainText[Index] <= '9' ))
		{
			SawDigit = 1;
		}
		else if (( PlainText[Index] >= 32 ) && ( PlainText[Index] <= 127 ))
		{
			SawPunct = 1;
		}
	}

	SawTotal = SawUpper + SawLower + SawDigit + SawPunct;
	
	if ( SawTotal < ComplexityCount )
	{
		return ( -3 );
	}

	return ( 0 );
}

int pw_check ( char * PlainText, char * SaltEncoded )
{
	char	SaltBuffer [ PASSWORD_SALT_DIGITS + 1 ];
	char	EncodeBuffer [ MAX_PASSWORD_LENGTH + 1 ];
	int		Salt, PasswordLength;
	char	TestBuffer [ MAX_PASSWORD_LENGTH + 1 ];

	sprintf ( SaltBuffer, "%*.*s", PASSWORD_SALT_DIGITS, PASSWORD_SALT_DIGITS, SaltEncoded );
	Salt = nsAtoi ( SaltBuffer );

	sprintf ( EncodeBuffer, "%s", &SaltEncoded[PASSWORD_SALT_DIGITS] );

	PasswordLength = sprintf ( TestBuffer, "%s", PlainText );
	
#ifdef DEBUG
	printf ( "Test: %s (%d)\n", TestBuffer, PasswordLength );
#endif

	pw_encode ( TestBuffer, PasswordLength, Salt );

#ifdef DEBUG
	printf ( "Salt: %d\n", Salt );
	printf ( "Test: %s\n", TestBuffer );
	printf ( "File: %s\n", EncodeBuffer );
#endif

	if ( nsStrcmp ( TestBuffer, EncodeBuffer ) == 0 )
	{
		return ( 0 );
	}
	return ( -1 );
}

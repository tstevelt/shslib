/*----------------------------------------------------------------------------
	Program : randfunc.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time

	Synopsis: Various functions for random numbers. Originally written 
			  for "grotto" card game, to shuffle the deck of cards.

	Return  : 	void shs_seed_random ( void );
				double d_random ( void );
				long random_range ( long low , long high );

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
#include	<sys/time.h>

unsigned long num_Random;

void shs_seed_random ( void )
{
	struct timeval		tv;
	unsigned int		Nut;
	unsigned int		Corn;
	unsigned int		Seed;

	gettimeofday ( &tv, NULL );

	Nut  = tv.tv_usec % 3;
	Nut  = Nut *  1000000000;

	Corn = tv.tv_sec % 1000;
	Corn = Corn * 1000000;

	Seed = Nut + Corn + tv.tv_usec;

	srand ( Seed );

}

double d_random ()
{
	long 	xl;
	double	rv;

	// xl = rand ();
	xl = random ();

	num_Random++;

	rv = (double) xl / (double)RAND_MAX;

	return ( rv );
}

short flip ( double probability )
{
	double	rv;

	if ( probability == 1.0 )
	{
		return ( 1 );
	}
	else
	{
		rv = d_random ();
		if ( rv <= probability )
			return ( 1 );
		else
			return ( 0 );
	}
}

/*------------------------------------------------------------------
	fixit someday many programs use this, rename to l_random_range
------------------------------------------------------------------*/
long random_range ( long low, long high )
{
	double	xd;
	long	rv;

	if ( low >= high )
		return ( low );

	xd = d_random ();

	rv = xd * ( high - low + 1 ) + low;
	
	if ( rv > high ) 
		rv = high;

	return ( rv );
}

double d_random_range ( double low, double high )
{
	double	xd, rv;

	if ( low >= high )
	{
		return ( low );
	}

	xd = d_random ();

	rv = xd * ( high - low ) + low;
	
	if ( rv > high ) 
		rv = high;

	return ( rv );
}

/*----------------------------------------------------------------------------
	Program : CalcDistance.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 04/22/2014
	Synopsis: distance calculation 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		12/26/2018	Took distance calculation from CalcTransport.c
	tms		02/24/2021	Moved test program into ../test/subdir

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<stdio.h>
#include	<string.h>
#include	<math.h>

#include	"shslib.h"

#define	EARTH_CIRCUM	24903
#define	FROMNP(x)		90.0-x;

#ifdef NOT_USED
static double ddhh2double ( short x )
{
	double	rv;

	rv = (double) x / (double) 100.0;

	return ( rv );
}
#endif

/*
 *	double2ddhh()
 *		converts from  +-ddd.nnnn to +-ddd (short, rounded to nearest degree)
 *		output range from 0 to 359
 */
static short double2ddhh ( double x)
{
	short	rv;

	rv = (short)( x + 0.5 );
	while ( rv >= 360 )
		rv -= 360;

	return( rv );
}

/*
 *	deg2rad()	convert from degrees to radians
 */
static double deg2rad ( double x )
{
	return((double)(2.0 * M_PI * x / 360.0 ));
}

/*
 *	rad2deg()	convert from radians to degrees
 */
static double rad2deg ( double x )
{
	return ( 360.0 * x / (2.0 * M_PI));
}

int CalcDistance (  double olatitude, double olongitude, 
			        double dlatitude, double dlongitude, 
   			        int *mileage, int *bearing )
{
	double		a, b, c, A, B, x;
	double		dOrgLong, dDstLong, dBearing;
	int			westward = 0;
	double		numer, denom;

	*mileage = 0;
	*bearing = 0;

	if ( olatitude == dlatitude && olongitude == dlongitude )
		return(0);

/*----------------------------------------------------------
xxx	c = ddhh2double(olatitude);
xxx	a = ddhh2double(dlatitude);
xxx	dOrgLong = ddhh2double(olongitude);
xxx	dDstLong = ddhh2double(dlongitude);
----------------------------------------------------------*/

	c = olatitude;
	a = dlatitude;
	dOrgLong = olongitude;
	dDstLong = dlongitude;

	c = FROMNP(c);
	a = FROMNP(a);

	if ( c < -90.0 || c > 90.0 )
		return(1);
	if ( a < -90.0 || a > 90.0 )
		return(1);
	if ( dOrgLong < -180.0 || dOrgLong > 180.0 )
		return(1);
	if ( dDstLong < -180.0 || dDstLong > 180.0 )
		return(1);

	B = dOrgLong - dDstLong;
	if ( B < 0.0 )
	{
		if ( B < -180.0 )
			B = -360.0 + B;
	}
	else
	{
		westward = 1;
		if ( B > 180.0 )
			B = 360.0 - B;
	}

	a = deg2rad(a);
	c = deg2rad(c);
	B = deg2rad(B);

/*
 *	calc the side of the spherical triangle.
 *	cos(b) = cos(a) * cos(c) + sin(a) * sin(c) * cos(B);
 */
	b = acos ( cos(a) * cos(c) + sin(a) * sin(c) * cos(B));

/*
 *	convert side of triangle to degrees, then to mileage
 */
	x = rad2deg(b);
	*mileage = (short)((EARTH_CIRCUM * (x / 360.0)) + 0.5 );

	if ( olatitude == 90.0 )
	{
		*bearing = 18000;
		return(0);
	}
	else if ( olatitude == -90.0 )
	{
		*bearing = 0;
		return(0);
	}

/*
 *	calc the bearing of from the first place to the second
 *	cos(a) = cos(b) * cos(c) + sin(b) * sin(c) * cos(A);
 *	sin(b) * sin(c) * cos(A) = cos(a) - cos(b) * cos(c);
 *	cos(A) = ( cos(a) - cos(b) * cos(c) ) / ( sin(b) * sin(c) );
 */
	x = sin(b);
	if ( x < 0.000005 && x > -0.000005 )
	{
		*bearing = 0;
		return(0);
	}

/*
	DOMAIN error results if arg is +1 or -1
	A = acos ( ( cos(a) - cos(b) * cos(c) ) / ( sin(b) * sin(c) ));
*/
	numer = cos(a) - cos(b) * cos(c);
	denom = sin(b) * sin(c);
	A = numer / denom;
	if ( dbldiff ( A, 1.0, 0.000001 ) == 0 )
	{
		*bearing = 9000;
		return ( 0 );
	}
	else if ( dbldiff ( A, -1.0, 0.000001 ) == 0 )
	{
		*bearing = 27000;
		return ( 0 );
	}

	A = acos ( numer / denom );

	dBearing = rad2deg(A);
	if ( westward )
		dBearing = 360.0 - dBearing;

	*bearing = double2ddhh(dBearing);

	return (0);
}

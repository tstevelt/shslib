/*----------------------------------------------------------------------------
	Program : nap.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 06/05/2021
	Synopsis: 
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

#include	<unistd.h>
#include	<time.h>

void nap ( int milliseconds )
{
	struct timespec		req;

	/*----------------------------------------------------------
		nanosecond is a billionth of a second
		1000 is a millionth
		1000000 is a thousanths
		1000000000 is a hundredth
		10000000000 is a tenth
	----------------------------------------------------------*/
	req.tv_sec = 0;
	req.tv_nsec = milliseconds * 1000000;

	nanosleep( &req, NULL);
}

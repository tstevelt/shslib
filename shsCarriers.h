/*----------------------------------------------------------------------------
	Program : shsCarriers.h
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 01/10/2021
	Synopsis: Phone carriers for two-factor auth.
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


typedef struct
{
	char	*Label;
	char	*Address;
} CARRIER_RECORD;

#ifdef MAIN

CARRIER_RECORD	CarrierArray [] =
{
	{ "ATT", "txt.att.net" },
	{ "Airtouch", "airtouch.net" },
	{ "Alphapage", "alphapage.airtouch.com" },
	{ "Hotmail", "hotmail.com" },
	{ "Pagenet", "pagenet.net" },
	{ "Skytel", "skytel.com" },
	{ "Tmomail", "tmomail.net" },
	{ "Verizon", "vtext.com" },
};

int				CarrierCount = sizeof(CarrierArray)/sizeof(CARRIER_RECORD);

#else

extern CARRIER_RECORD	CarrierArray [];
extern int				CarrierCount;

#endif

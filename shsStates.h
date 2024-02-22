/*----------------------------------------------------------------------------
	Program : shsState.h
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 2020
	Synopsis: 50 state abbreviations and names.
			  https://abbreviations.yourdictionary.com/articles/state-abbrev.html
			  https://www.einvestigator.com/area-codes-by-state/
	Return  : 

	Who		Date	Modification
	---------------------------------------------------------------------
	tms		2020	Added area codes by state. Used for acctdemo program

---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#define		MAXAREACODES		100

typedef	struct
{
	char	*Name;
	char	*Abbreviation;
	int		AreaCodes[MAXAREACODES];
} STATE_RECORD;

#ifdef	MAIN

STATE_RECORD	StatesArray[] = 
{
	{ "Alabama", "AL", 205, 251, 256, 334, 0 },
	{ "Alaska", "AK", 907, 0 },
	{ "Arizona", "AZ", 480, 520, 602, 623, 928, 0 },
	{ "Arkansas", "AR", 479, 501, 870, 0 },
	{ "California", "CA", 209, 213, 310, 323, 408, 415, 424, 510, 530, 559, 562, 619, 626, 650, 661, 707, 714, 760, 805, 818, 831, 858, 909, 916, 925, 949, 0 },
	{ "Colorado", "CO", 303, 719, 720, 970, 0 },
	{ "Connecticut", "CT", 203, 475, 860, 959, 0 },
	{ "Delaware", "DE", 302, 0 },
	{ "Florida", "FL", 239, 305, 321, 352, 386, 407, 561, 727, 754, 772, 786, 813, 850, 863, 904, 941, 954, 0 },
	{ "Georgia", "GA", 229, 404, 470, 478, 678, 706, 770, 912, 0 },
	{ "Hawaii", "HI", 808, 0 },
	{ "Idaho", "ID", 208, 0 },
	{ "Illinois", "IL", 217, 224, 309, 312, 331, 464, 618, 630, 708, 773, 815, 847, 872, 0 },
	{ "Indiana", "IN", 219, 260, 317, 574, 765, 812, 0 },
	{ "Iowa", "IA", 319, 515, 563, 641, 712, 0 },
	{ "Kansas", "KS", 316, 620, 785, 913, 0 },
	{ "Kentucky", "KY", 270, 502, 606, 859, 0 },
	{ "Louisiana", "LA", 225, 318, 337, 504, 985, 0 },
	{ "Maine", "ME", 207, 0 },
	{ "Maryland", "MD", 227, 240, 301, 410, 443, 667, 0 },
	{ "Massachusetts", "MA", 339, 351, 413, 508, 617, 774, 781, 857, 978, 0 },
	{ "Michigan", "MI", 231, 248, 269, 313, 517, 586, 616, 734, 810, 906, 947, 989, 0 },
	{ "Minnesota", "MN", 218, 320, 507, 612, 651, 763, 952, 0 },
	{ "Mississippi", "MS", 228, 601, 662, 0 },
	{ "Missouri", "MO", 314, 417, 557, 573, 636, 660, 816, 975, 0 },
	{ "Montana", "MT", 406, 0 },
	{ "Nebraska", "NE", 308, 402, 0 },
	{ "Nevada", "NV", 702, 775, 0 },
	{ "New Hampshire", "NH", 603, 0 },
	{ "New Jersey", "NJ", 201, 551, 609, 732, 848, 856, 862, 908, 973, 0 },
	{ "New Mexico", "NM", 505, 575, 0 },
	{ "New York", "NY", 212, 315, 347, 516, 518, 585, 607, 631, 646, 716, 718, 845, 914, 917, 0 },
	{ "North Carolina", "NC", 252, 336, 704, 828, 910, 919, 980, 984, 0 },
	{ "North Dakota", "ND", 701, 0 },
	{ "Ohio", "OH", 216, 234, 283, 330, 419, 440, 513, 567, 614, 740, 937, 0 },
	{ "Oklahoma", "OK", 405, 580, 918, 0 },
	{ "Oregon", "OR", 503, 541, 971, 0 },
	{ "Pennsylvania", "PA", 215, 267, 412, 445, 484, 570, 610, 717, 724, 814, 835, 878, 0 },
	{ "Rhode Island", "RI", 401, 0 },
	{ "South Carolina", "SC", 803, 843, 864, 0 },
	{ "South Dakota", "SD", 605, 0 },
	{ "Tennessee", "TN", 423, 615, 731, 865, 901, 931, 0 },
	{ "Texas", "TX", 210, 214, 254, 281, 361, 409, 469, 512, 682, 713, 737,806, 817, 830, 832, 903, 915, 936, 940, 956, 972, 979, 0 },
	{ "Utah", "UT", 435, 801, 0 },
	{ "Vermont", "VT", 802, 0 },
	{ "Virginia", "VA", 276, 434, 540, 571, 703, 757, 804, 0 },
	{ "Washington", "WA", 206, 253, 360, 425, 509, 564, 0 },
	{ "Washington DC", "DC", 202, 0 },
	{ "West Virginia", "WV", 304, 0 },
	{ "Wisconsin", "WI", 262, 414, 608, 715, 920, 0 },
	{ "Wyoming", "WY", 307, 0 },
};

short	StatesCount = sizeof(StatesArray)/sizeof(STATE_RECORD);

#else

extern	STATE_RECORD	StatesArray[];
extern	short			StatesCount;

#endif


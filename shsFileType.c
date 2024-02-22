/*----------------------------------------------------------------------------
	Program : shsFileType.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time
	Synopsis: Originally written to determine type of image uploaded
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		Nov 2020	Added CSV, OFX and QIF for accounting package

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#include	<string.h>
#include	"shslib.h"

/*---------------------------------------------------------------------------
ADP_64x31.gif
 0  47 49 46 38 39 61 w(40 00) h(1f 00) c6 00 00 ff ff ff   GIF89a@.........

ADP_64x64.gif
 0  47 49 46 38 39 61 w(40 00) h(40 00) c6 48 00 c3 1f 25   GIF89a@.@..H...%

ADP_92x44.gif
 0  47 49 46 38 39 61 w(5c 00) h(2c 00) e6 00 00 ff ff ff   GIF89a\.,.......
---------------------------------------------------------------------------*/
static int GIF_Size ( unsigned char xbuffer[], int numread, int *Height, int *Width  )
{
	int				rv;
	int				Value;

	*Height = 0;
	*Width = 0;

	Value = 256 * xbuffer[7] + xbuffer[6];
	*Width = Value;

	Value = 256 * xbuffer[9] + xbuffer[8];
	*Height = Value;

	rv = *Height * *Width;

	return ( rv );
}

/*---------------------------------------------------------------------------
Samples/upload_11504.png
 0  89 50 4e 47 0d 0a 1a 0a 00 00 00 0d 49 48 44 52   .PNG........IHDR
16  00 00 w(01 f2) 00 00 h(01 15) 08 06 00 00 00 1b d0 67   ...............g
32  ea 00 00 0a a5 69 43 43 50 49 43 43 20 50 72 6f   .....iCCPICC Pro
48  66 69 6c 65 00 00 48 89 95 97 07 54 13 d9 1a c7   file..H....T....
---------------------------------------------------------------------------*/
static int PNG_Size ( unsigned char xbuffer[], int numread, int *Height, int *Width  )
{
	int				rv, ndx;
	unsigned char	Data [] = { 0x49, 0x48, 0x44, 0x52 };
	int				Length = 4;
	int				Value;

	*Height = 0;
	*Width = 0;

	for ( ndx = 0; ndx < numread - Length - 7; ndx++ )
	{
		if ( xbuffer[ndx] == Data[0] && xbuffer[ndx+1] == Data[1] )
		{
			Value = 256 * xbuffer[ndx+6] + xbuffer[ndx+7];
			*Width = Value;
			Value = 256 * xbuffer[ndx+10] + xbuffer[ndx+11];
			*Height = Value;
			break;
		}
	}

	rv = *Height * *Width;

	return ( rv );
}

/*---------------------------------------------------------------------------
motus_monochrome.jpg                                                                                        
  0  ff d8 ff e0 00 10 4a 46 49 46 00 01 01 01 00 64   ......JFIF.....d
 16  00 64 00 00 ff db 00 43 00 09 06 07 08 07 06 09   .d.....C........
 32  08 07 08 0a 0a 09 0b 0d 16 0f 0d 0c 0c 0d 1b 14   ................
 48  15 10 16 20 1d 22 22 20 1d 1f 1f 24 28 34 2c 24   ... ."" ...$(4,$
 64  26 31 27 1f 1f 2d 3d 2d 31 35 37 3a 3a 3a 23 2b   &1'..-=-157:::#+
 80  3f 44 3f 38 43 34 39 3a 37 SOF0(ff c0) 00 0b 08 h(0a bc)   ?D?8C49:7.......
 96  w(10 c0) 01 01 22 00 ff c4 00 1b 00 01 01 01 00 03   ...."...........
112  01 01 00 00 00 00 00 00 00 00 00 00 03 02 04 05   ................
128  06 07 08 ff c4 00 5c 10 00 03 00 02 01 04 02 01   ......\.........
IMG_1201.JPG
  0  ff d8 ff e1 29 1c 45 78 69 66 00 00 4d 4d 00 2a   ....).Exif..MM.*
 16  00 00 00 08 00 0a 01 0f 00 02 00 00 00 06 00 00   ................
 32  00 86 01 10 00 02 00 00 00 09 00 00 00 8c 01 12   ................
 48  00 03 00 00 00 01 00 06 00 00 01 1a 00 05 00 00   ................
 64  00 01 00 00 00 96 01 1b 00 05 00 00 00 01 00 00   ................
 first image is an embedded thumbnail ....
---------------------------------------------------------------------------*/
static int JPG_Size ( unsigned char xbuffer[], int numread, int *Height, int *Width  )
{
	int				rv, ndx;
	unsigned char	Data [] = { 0xff, 0xc0 };
	int				Length = 2;
	int				Value;

	*Height = 0;
	*Width = 0;

	for ( ndx = 0; ndx < numread - Length - 7; ndx++ )
	{
		if ( xbuffer[ndx] == Data[0] && xbuffer[ndx+1] == Data[1] )
		{
			Value = 256 * xbuffer[ndx+5] + xbuffer[ndx+6];
			*Height = Value;
			Value = 256 * xbuffer[ndx+7] + xbuffer[ndx+8];
			*Width = Value;
			break;
		}
	}

	rv = *Height * *Width;

	return ( rv );
}

typedef struct
{
	int				TypeID;
	char			*Description;
	unsigned char	Magic[24];
	short			Length;
	int				(*GetSize)(); 
	int				Executable;
} MAGIC_RECORD;

/*---------------------------------------------------------------------------
https://en.wikipedia.org/wiki/Magic_number_(programming)
---------------------------------------------------------------------------*/


/*----------------------------------------------------------
	order elements from longest Length to shortest.
	EXIF has to be the next one after JPG!!
----------------------------------------------------------*/
static	MAGIC_RECORD	Array [] =
{
	{ SHS_FILE_TYPE_PNG, "PNG",				{ 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a }, 8, PNG_Size, 0 },
	{ SHS_FILE_TYPE_ARCHIVE, "ARCH",		{ 0x21, 0x3c, 0x61, 0x72, 0x63, 0x68, 0x3e }, 7, NULL, 0 },
	{ SHS_FILE_TYPE_GIF, "GIF89a",			{ 0x47, 0x49, 0x46, 0x38, 0x39, 0x61 }, 6, GIF_Size, 0 },
	{ SHS_FILE_TYPE_GIF, "GIF87a",			{ 0x47, 0x49, 0x46, 0x38, 0x37, 0x61 }, 6, GIF_Size, 0 },
	{ SHS_FILE_TYPE_FINANCE_QIF, "QIF", "!Type:", 6, NULL, 0 },
	{ SHS_FILE_TYPE_PDF, "PDF", 			{ 0x25, 0x50, 0x44, 0x46 }, 4, NULL, 0 }, 
	{ SHS_FILE_TYPE_MSOFFICE, "MS_Office",	{ 0xd0, 0xcf, 0x11, 0xe0 }, 4, NULL, 0 },
	{ SHS_FILE_TYPE_ELF, "ELF",				{ 0x7f, 0x45, 0x4c, 0x46 }, 4, NULL, 1 },
	{ SHS_FILE_TYPE_JPG, "JPG",				{ 0xff, 0xd8, 0xff }, 3, JPG_Size, 0 }, 
	{ SHS_FILE_TYPE_EXIF, "EXIF",			{ 0xff, 0xd8, 0xff }, 3, NULL, 0 }, 
	{ SHS_FILE_TYPE_PS, "PostScript", 		{ 0x25, 0x21 }, 2, NULL, 0 }, 
	{ SHS_FILE_TYPE_ZIP, "ZIP", 			{ 0x50, 0x4b }, 2, NULL, 0 }, 
	{ SHS_FILE_TYPE_SHELL, "Shell",			{ 0x23, 0x21 }, 2, NULL, 1 },
	{ SHS_FILE_TYPE_EXE, "EXE",				{ 0x4d, 0x5a }, 2, NULL, 1 },
	{ SHS_FILE_TYPE_EXE_ZM, "EXE_ZM",		{ 0x5a, 0x4d }, 2, NULL, 1 },
	{ SHS_FILE_TYPE_TEXT, "TEXT",			{ 0x00 }, 0, NULL, 0 },
	{ SHS_FILE_TYPE_FINANCE_CSV, "CSV", 	{ 0x00 }, 0, NULL, 0 },
	{ SHS_FILE_TYPE_FINANCE_OFX, "OFX",		{ 0x00 }, 0, NULL, 0 },
};

static	int				Count = sizeof(Array) / sizeof(MAGIC_RECORD);

static	SHS_FILE_TYPE	BufferFileType = { SHS_FILE_TYPE_UNKNOWN, "Unknown" };

SHS_FILE_TYPE *BufferType ( unsigned char xbuffer[], int numread, int Verbose )
{
	int		xa, xm;
	double	NoPrintCount, AlphaCount, NumberCount, PunctuationCount, OtherCount;
	int		InQuote, QuoteCount, CommaCount;
#ifdef MOVED_TO_GLOBAL
	static	SHS_FILE_TYPE	BufferFileType;

	memset ( &BufferFileType, '\0', sizeof(SHS_FILE_TYPE) );
	BufferFileType.TypeID = SHS_FILE_TYPE_UNKNOWN;
	BufferFiletype.Description = "Unknown";
#endif

	for ( xa = 0; xa < Count; xa++ )
	{
		xm = 0;

		if ( Array[xa].Length == 0 )
		{
			if ( Array[xa].TypeID == SHS_FILE_TYPE_FINANCE_CSV )
			{
				InQuote = QuoteCount = CommaCount = 0;
				for ( xm = 0; xm < numread; xm++ )
				{
					if ( xbuffer[xm] == '"' )
					{
						QuoteCount++;
						if ( InQuote )
						{
							InQuote = 0;
						}
						else
						{
							InQuote = 1;
						}
					}
					else if ( xbuffer[xm] == ',' && InQuote == 0 )
					{
						CommaCount++;
					}
					else if ( xbuffer[xm] == '\n' || xbuffer[xm] == '\r' )
					{
						break;
					}
				}

				if ( CommaCount == 0 )
				{
					continue;
				}

				xm = 1;
			}
#ifdef THIS_HAS_MAGIC
			else if ( Array[xa].TypeID == SHS_FILE_TYPE_FINANCE_QIF )
			{
				/*---------------------------------------------------------------------------
					https://en.wikipedia.org/wiki/Quicken_Interchange_Format
				---------------------------------------------------------------------------*/
				if ( nsStrncmp ( (char *) xbuffer, "!Type:", 6 ) == 0 )
				{
					xm = 1;
				}
				else
				{
					continue;
				}

			}
#endif
			else if ( Array[xa].TypeID == SHS_FILE_TYPE_FINANCE_OFX )
			{
				if (( nsStrstr ( (char *)xbuffer, "<?xml version="   ) == (char *)0 ) &&
					( nsStrstr ( (char *)xbuffer, "<?OFX OFXHEADER=" ) == (char *)0 ) &&
					( nsStrstr ( (char *)xbuffer, "OFXHEADER:"       ) == (char *)0 ))
				{
					continue;
				}
				xm = 1;
			}
			else if ( Array[xa].TypeID == SHS_FILE_TYPE_TEXT )
			{
				NoPrintCount = AlphaCount = NumberCount = PunctuationCount = OtherCount = 0.0;
				for ( xm = 0; xm < numread; xm++ )
				{
					if ( xbuffer[xm] == '\t' || xbuffer[xm] == '\n' || xbuffer[xm] == '\r' )
					{
						AlphaCount++;
					}
					else if ( xbuffer[xm] < ' ' || xbuffer[xm] > 127 )
					{
						NoPrintCount++;
					}
					else if (( xbuffer[xm] >= 'A' && xbuffer[xm] <= 'Z' ) ||
							 ( xbuffer[xm] >= 'a' && xbuffer[xm] <= 'z' ) ||
							 ( xbuffer[xm] == ' '                       ))
					{
						AlphaCount++;
					}
					else if (( xbuffer[xm] >= '0' && xbuffer[xm] <= '9' ) ||
							 ( xbuffer[xm] == '-'                       ))
					{
						NumberCount++;
					}
					else
					{
						switch ( xbuffer[xm] )
						{
							case '.':
							case ',':
							case ';':
							case ':':
							case '\n':
							case '\r':
							case '\t':
							case '<':
							case '>':
							case '/':
							case '[':
							case ']':
							case '"':
							case '$':
							case '#':
							case '?':
							case '=':
								PunctuationCount++;
								break;
							default:
								if ( Verbose > 1 )
								{
									if ( OtherCount == 0 )
									{
										printf ( "other: " );
									}
									printf ( "%c", xbuffer[xm] );
								}
								OtherCount++;
								break;
						}
					}
				}

				// NoPrintCount
				// AlphaCount
				// NumberCount
				// PunctuationCount
				// OtherCount
				// fixit
				if ( Verbose )
				{
					printf ( "numread %d NoPrint %.1f Numbers %.1f Alpha %.1f Other %.1f Punctuation %.1f ==> ",
							numread, NoPrintCount, NumberCount, AlphaCount, OtherCount, PunctuationCount );
						
				}
				if ( NoPrintCount > (double) numread * 0.05 )
				{
					if ( Verbose )
					{
						printf ( "number no print\n" );
					}
					continue;
				}
				else if ( NumberCount > AlphaCount * 0.1 )
				{
					if ( Verbose )
					{
						printf ( "more numbers\n" );
					}
					continue;
				}
				else if ( OtherCount > (AlphaCount + NumberCount + PunctuationCount) * 0.02 )
				{
					if ( Verbose )
					{
						printf ( "more others\n" );
					}
					continue;
				}
				else
				{
					if ( Verbose )
					{
						printf ( "text\n" );
					}
					// xm will be greated than zero.  let code below else block handle it from here.
				}
			}
			else
			{
				if ( Verbose )
				{
					printf ( "No test coded for file type %d with Length = 0\n", Array[xa].TypeID  );
				}	
				return ( NULL );
			}
		}
		else
		{
			for ( xm = 0; xm < Array[xa].Length; xm++ )
			{
				if  ( xbuffer[xm] != Array[xa].Magic[xm] )
				{
					break;
				}
			}
		}

		if ( xm >= Array[xa].Length )
		{
			BufferFileType.Description = Array[xa].Description;
			BufferFileType.TypeID      = Array[xa].TypeID;

			/*----------------------------------------------------------
				if JPG, see if really Exif
			----------------------------------------------------------*/
			if ( BufferFileType.TypeID == SHS_FILE_TYPE_JPG )
			{
				if ( nsStrncmp ( (char *) &xbuffer[6], "Exif", 4 ) == 0 )
				{
					xa++;
					BufferFileType.Description = Array[xa].Description;
					BufferFileType.TypeID      = Array[xa].TypeID;
				}
			}

			if ( Verbose )
			{
				printf ( "%s file type." , Array[xa].Description );
			}

			if ( Array[xa].GetSize != NULL )
			{
				BufferFileType.ImageSize = Array[xa].GetSize ( xbuffer, numread, &BufferFileType.ImageHeight, &BufferFileType.ImageWidth );

				if ( Verbose )
				{
					printf ( "  height %d, width %d, image size %d.", 
							BufferFileType.ImageHeight, BufferFileType.ImageWidth, BufferFileType.ImageSize );
				}
			}

			if ( Array[xa].Executable )
			{
				BufferFileType.Executable = 1;

				if ( Verbose )
				{
					printf ( " Executable!" );
				}
			}

			if ( Verbose )
			{
				printf ( "\n" );
			}

			break;
		}
	}

	if ( xa >= Count )
	{
		if ( Verbose )
		{
			printf ( "unknown file type\n" );
		}
	}
	
	return ( &BufferFileType );
}

SHS_FILE_TYPE *shsFileType ( char Filename [], int Verbose )
{
	FILE	*fp;
	static	SHS_FILE_TYPE	*ptrFileType;
	static	SHS_FILE_TYPE	ThisFileType;
	unsigned char	xbuffer[10240];
	int		numread;
	long	FileSize;

	if (( fp = fopen ( Filename, "r" )) == (FILE *)0 )
	{
		if ( Verbose )
		{
			printf ( "Cannot open file %s\n", Filename );
		}
		return ( (SHS_FILE_TYPE *) 0 );
	}

	fseek ( fp, 0, SEEK_END );
	FileSize = ftell ( fp );
	rewind ( fp );

	if (( numread = fread ( xbuffer, 1, 10240, fp )) <= 0 )
	{
		if ( Verbose )
		{
			printf ( "Read error on file %s\n", Filename );
		}
		nsFclose ( fp );
		return ( (SHS_FILE_TYPE *) 0 );
	}

	nsFclose ( fp );

	if ( Verbose )
	{
		printf ( "file size %ld.\n", FileSize );
		printf ( "numread %d\n", numread );
	}

	ptrFileType = BufferType ( xbuffer, numread, Verbose );
	memcpy ( &ThisFileType, ptrFileType, sizeof(SHS_FILE_TYPE) );
	ThisFileType.FileSize = FileSize;

	return ( &ThisFileType );
}

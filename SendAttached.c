/*----------------------------------------------------------------------------
	Program : SendAttached.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : 11/14/2018
	Synopsis: C-Function replacement for command line postie (which
			  disappeard from the face of the earth) and mailx (which
			  does not work from system() call.).
	Return  : 

	This program contains code and logic from Barry Steyn which is released under the MIT License.  Thank you Barry!

	https://gist.github.com/barrysteyn/7308212

	The MIT License (MIT)

	Copyright (c) 2013 Barry Steyn

	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWAR

	gcc -o base64 Main.c Base64Encode.c Base64Decode.c -lcrypto -lm -w

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		01/01/2018	Added Sender:  and re-order To: and From:

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <libgen.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <sys/types.h>


#include "shslib.h"

size_t calcDecodeLength(const char* b64input) { //Calculates the length of a decoded string
	size_t len = nsStrlen(b64input),
		padding = 0;

	if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
		padding = 2;
	else if (b64input[len-1] == '=') //last char is =
		padding = 1;

	return (len*3)/4 - padding;
}


int Base64Decode(char* b64message, unsigned char** buffer, size_t* length) 
{
	//Decodes a base64 encoded string
	BIO *bio, *b64;

	int decodeLen = calcDecodeLength(b64message);
	*buffer = (unsigned char*)malloc(decodeLen + 1);
	(*buffer)[decodeLen] = '\0';

	bio = BIO_new_mem_buf(b64message, -1);
	b64 = BIO_new(BIO_f_base64());
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
	*length = BIO_read(bio, *buffer, nsStrlen(b64message));
	assert(*length == decodeLen); //length should equal decodeLen, else something went horribly wrong
	BIO_free_all(bio);

	return (0); //success
}


int Base64Encode(const unsigned char* buffer, size_t length, char** b64text) 
{
	//Encodes a binary safe base 64 string
	BIO *bio, *b64;
	BUF_MEM *bufferPtr;

	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
	BIO_write(bio, buffer, length);
	BIO_flush(bio);
	BIO_get_mem_ptr(bio, &bufferPtr);
	BIO_set_close(bio, BIO_NOCLOSE);
	BIO_free_all(bio);

	*b64text=(*bufferPtr).data;

	return (0); //success
}

char *Generate_UUID ()
{
	static char UUID_Buffer[40];
	long	tvec;
	unsigned int		num1;
	unsigned int		num2;
	unsigned int		num3;
	unsigned int		num4;
	unsigned int		num5;
	unsigned int		num6;
	unsigned int		num7;
	unsigned int		num8;

	time ( &tvec );
	srand ( tvec );

	num1 =   rand() & 0xffff;     
	num2 =   rand() & 0xffff; 
	num3 =   rand() & 0xffff; 
	num4 = ((rand() & 0x0fff) | 0x4000); 
	num5 =   rand() % 0x3fff + 0x8000;
	num6 =   rand() & 0x0fff;
	num7 =   rand() & 0x0fff;
	num8 =   rand() & 0x0fff;

	memset ( UUID_Buffer, '\0', sizeof(UUID_Buffer) );

	snprintf ( UUID_Buffer, sizeof(UUID_Buffer), "%04x%04x-%04x-%04x-%04x-%04x%04x%04x", 
		num1, num2,          // Generates a 64-bit Hex number
		num3,                // Generates a 32-bit Hex number
		num4,                // Generates a 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
		num5,                // Generates a 32-bit Hex number in the range [0x8000, 0xbfff]
		num6, num7, num8 );  // Generates a 96-bit Hex number
	

	return ( UUID_Buffer );
}

int SendAttached ( char *FromAddress, 
					char *ToAddress, 
					char *CcAddress, 
					char *BccAddress, 
					char *Subject, 
					int BodyIsHTML, 
					char *BodyFile, 
					int AttachmentCount, 
					char *AttachFiles[] )
{
	char	TempFN[128];
	long	tvec;
	struct tm	*tm;
	FILE	*TempFP;
	FILE	*BodyFP;
	char	xbuffer[10240];
	char	cmdline[1024];
	char 	*MyUUID;
	int		xa, xn;
	FILE	*AttachFP;
	unsigned char binbuffer[58];
	char	*asciibuffer;
	static	int		SequenceNumber = 1;
	char	*cp;


	MyUUID = Generate_UUID();

	time ( &tvec );
	tm = localtime ( &tvec );

	sprintf ( TempFN, "/var/local/tmp/SendAttached_%d_%d.txt", getpid(), SequenceNumber++ );

	if (( TempFP = fopen ( TempFN, "w" )) == (FILE *)0 )
	{
		fprintf ( stderr, "SendAttached: Cannot create %s\n", TempFN );
		return ( -1 );
	}

	/*----------------------------------------------------------
		no trailing newlines!  tms 06/18/2019
	----------------------------------------------------------*/
	TrimRightAndLeft ( FromAddress );
	TrimRightAndLeft ( FromAddress );
	TrimRightAndLeft ( ToAddress );
	TrimRightAndLeft ( Subject );

	fprintf ( TempFP, "From: %s\n", FromAddress );
	fprintf ( TempFP, "Sender: %s\n", FromAddress );
	fprintf ( TempFP, "To: %s\n", ToAddress );

	if ( nsStrlen ( CcAddress ) > 0 )
	{
		fprintf ( TempFP, "Cc: %s\n", CcAddress );
	}
	if ( nsStrlen ( BccAddress ) > 0 )
	{
		fprintf ( TempFP, "Bcc: %s\n", BccAddress );
	}
	fprintf ( TempFP, "Subject: %s\n", Subject );
	fprintf ( TempFP, "MIME-Version: 1.0\n" );
	fprintf ( TempFP, "Date: %s, %d %s %d %d:%02d:%02d %ld\n", 
		DayOfWeek ( tm->tm_wday ),
		tm->tm_mday,
		MonthOfYear ( tm->tm_mon ),
		tm->tm_year + 1900,
		tm->tm_hour,
		tm->tm_min,
		tm->tm_sec,
		tm->tm_gmtoff );


	if ( AttachmentCount == 0 )
	{
		if ( BodyIsHTML == 0 )
		{
			fprintf ( TempFP, "Content-Type: text/plain; charset=iso-8859-1\n" );
		}
		else
		{
			fprintf ( TempFP, "Content-Type: text/html; charset=iso-8859-1\n" );
		}
		// fprintf ( TempFP, "Content-Transfer-Encoding: quoted-printable\n" );
		fprintf ( TempFP, "Content-Transfer-Encoding: 7bit\n" );
		// fprintf ( TempFP, "Content-Length, %d\n, xxx );
	}
	else
	{
		fprintf ( TempFP, "Content-Type: multipart/mixed; boundary=\"%s\"\n", MyUUID );
		// fprintf ( TempFP, "Content-Length, %d\n, xxx );
	}

	/*----------------------------------------------------------
		blank line at end of header info.
	----------------------------------------------------------*/
	fprintf ( TempFP, "\n" );

	/*----------------------------------------------------------
		print body
	----------------------------------------------------------*/
	if ( AttachmentCount > 0 )
	{
		fprintf ( TempFP, "--%s\n", MyUUID );
		if ( BodyIsHTML == 0 )
		{
			fprintf ( TempFP, "Content-Type: text/plain; charset=iso-8859-1\n" );
		}
		else
		{
			fprintf ( TempFP, "Content-Type: text/html; charset=iso-8859-1\n" );
		}
		fprintf ( TempFP, "Content-Transfer-Encoding: quoted-printable\n\n" );
	}

	if (( BodyFP = fopen ( BodyFile, "r" )) != (FILE *)0 )
	{
		while ( fgets ( xbuffer, sizeof(xbuffer), BodyFP ) != (char *)0 )
		{
			fprintf ( TempFP, "%s", xbuffer );
		}
	}
	else if ( AttachmentCount > 0 )
	{
		fprintf ( TempFP, "See attached\n" );
	}
	else
	{
		fprintf ( TempFP, "No message and no attachment, hope this is okay\n" );
	}

	if ( BodyFP != NULL )
	{
		nsFclose ( BodyFP );
	}

	
	/*----------------------------------------------------------
		print attachments 
		1. remove path to file name
		2. don't pad last line
	----------------------------------------------------------*/
	for ( xa = 0; xa < AttachmentCount; xa++ )
	{
		if (( AttachFP = fopen ( AttachFiles[xa], "r" )) == (FILE *)0 )
		{
			fprintf ( stderr, "SendAttached: Cannot open %s\n", AttachFiles[xa] );
			continue;
		}

		fprintf ( TempFP, "\n--%s\n", MyUUID );
		cp = basename(AttachFiles[xa]);
		fprintf ( TempFP, "Content-Type: application/octet-stream; name=\"%s\"; type=Binary\n", cp );
		fprintf ( TempFP, "Content-Disposition: attachment; filename=\"%s\"\n", cp );
		fprintf ( TempFP, "Content-Transfer-Encoding: base64\n\n" );

		/*----------------------------------------------------------
			57 * 8 / 6 = 76
		   size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
		----------------------------------------------------------*/
		while (( xn = fread ( binbuffer, 1, 57, AttachFP )) > 0 )
		{
			Base64Encode( binbuffer, xn, &asciibuffer ) ;

			fprintf ( TempFP, "%-76.76s\n", asciibuffer );
		}

		nsFclose ( AttachFP );

	}

	if ( AttachmentCount > 0 )
	{
		fprintf ( TempFP, "\n--%s--\n\n", MyUUID );
	}

	nsFclose ( TempFP );

	sprintf ( cmdline, "sendmail -t < %s", TempFN );

	system ( cmdline );

	unlink ( TempFN );

	return ( 0 );
}

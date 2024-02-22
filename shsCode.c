/*----------------------------------------------------------------------------
	Program : shsCode.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
	Synopsis: Encode and Decode ASCII strings with simple substiution algo.
			  26 different "salts"
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

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

#include	"shslib.h"

#define KEY62

static char *Keys [] =
{
#ifdef KEY62
	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
	"T2Kc9WElhAf6qo3rJ8aUjCDIZVReSGbNOLiQBYzsv0twH5P4dFpyg1xnkX7Mmu",
	"2goJnYcWdfMIrA37hOBRL5xzVl6S1upk9THte8QFCjX04wNKvGZyEbqUmaDsPi",
	"rVQJ78oeWElaTdk4tCh91vKH36Mn2yYiIpA5UN0cRsuwjBzmgfbSqOPZFLDxXG",
	"Vpz4TFHJoue8yatikCmdfR70M19SZqsbO6Dgh2L53YGXWBxwrUQKvENlAcIPnj",
	"6JpUWdtzIKuEZviwPk9Rjmn2Xeo8L1HGVsyOFSMrQ75TABxDh03Nagqb4flcYC",
	"7GmZOJ0W5qahbkCQj4zeylvdPEHNoVLKnR261tTYcfDXMSF8s3wrgu9IiBUxpA",
	"AH8rwk57UItbaljONm9hq4VcJZYvFuX6Df3PEWoxzs0LByTR1dMCeiG2pnSKgQ",
	"2ziSDAqQdOt1CYxGgFfaTmMulVJXkyKcsjUow7hZR4I6LeE8bNW59vnp3HBP0r",
	"wxK65D42jLa7tYFAReNpEzG19b8kZ3VWmXn0TyoMhPBvsQglduiHfScJIOUCrq",
	"4DlPtXruLoKw1sjpHNRTI0dW3SxUY82b6niCGkzyQqFOvm79efBAJaghcV5MZE",
	"0V2x6yqh4sUpN395OjAwlFdMTKcZWvkJminYL1Gb8SRPoCfI7zaXEruDgBteQH",
	"7aGL3EVSIg4oYN1Qh5OWD0zqFdHA6s9yuwftxenZkbTKlMXvCrPJU82jRBmcip",
	"2hCc57px9rmNXzbUyMq3WnuSGvYKAVBPJOiesHt8Do4awd1Tj6kEIZRgfLl0FQ",
	"JW5BQsZdjfr8zpqc03uTw9vNbgRGDi7hSElICHU26ox1mnAyYPKekXV4tOFLMa",
	"CKIyOwB4bH9rYvEJ6tFDiZh0pc5knLulom3V1g2eNqMjaxUfs8G7PXWTdzSQRA",
	"fpmU70stcxoBuANy4ieElzrR9C1WI23kPShwvaG8DKVLZHOQMXJYgjTqd65nFb",
	"iCVDUhYdapxEWIvtojSkmqeAzP9y2L0TGF6QnMgJ1Ou34H5lf8wB7XNcKRbsrZ",
	"UiX04Zs9omvb5fA87IpQtj6Nuq1zc3RlHakJVxeOwhgWGSMyrLBCnEK2YFPdDT",
	"b1WVDfHngjOdcm3tNxhl7K4q0eG65CpBMLTzI8k9youaFiZUXvAEQwJSPYRs2r",
	"fPGWAkp07OR9XBiY5MlmjrNLEKIJ8eUtxyThHsovZQcDF312gn6qzaSw4uVbdC",
	"mxyhboTEtcYRfQPzwu129nODVsg3dCvW6BiIGA5ZpkLSe8alUJrHMqjK4X07FN",
	"zvFw4NOuS9ksJymT72qU1CiKcIWL0HnAgV8BEjXG36M5hedpfxPDYZtabolQrR",
	"L0YfNvCnU6aPT8tczxRwjd53DkiBmQhWyIJOsV91eKo4q2lXAZrGgbuE7SHpMF",
	"pKXhYCns6L20O7IVdDGcAfvyuF1QNkPHMbze8lTZwar4WogJj5SEx9i3UmtBRq",
	"7OLNWKYwEfpPMZUc1tzn9x8DCqs234kmuGFTJghoHilvbryXdAaIj5B6SeV0QR",
	"R6leFtmYSXWE5JyjrMnKOZqT0hHgapUGCvxfcQ384bo1BudNI9w72AkszDPLVi",
#endif
#ifdef KEY63
	" 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
	"tzqwDMHxCe0VdihWA1X79JLK4lR6Psugjk FTySmYIn8GfoBQ5braOc32EpUNZv",
	"xcO0Zg bzSn3MXojyFVvHD2AfL7JmC8ewdYiWPBQpKr6EIqs4N9th1TlUuk5aRG",
	"nKW VSFDNIXweP8R4ckray7xGvOjziCdhTq6bmHJlAf0Zp93YsUt5LE2B1gouMQ",
	"KXL5J0ouIH7hxnMf1daGWAvj3lgSZ y8N6w4DpsirEUPCQBzkbeYVcFqR29OTtm",
	"ON54vGf9BYbSs2ucrzVp6RgnDUjdx0WTtwLZ1Meal8HyhK mXE7QqC3PFJioAkI",
	"2TSG6z4sieaqrHUyn7w 0chOFgm3CZP8lKVd9XWkvAJjDMRLENtb5B1uIpYoxQf",
	"eXRQBp8PwtcFMSb0 GHU4xyTKOjN2fsLzmvkiu9qWlAICaJE5dh1Zor6Y3nD7gV",
	"jmRJq6t0X3hHo57Kw1rpOukLedPaiC QUFfyMvgzZnWDAsNcS2E8Vb9GxY4lBIT",
	"N2FrosHCZpblg zRn0XQYiwTUdqxSBML4KPfkc89u1J6h7GVI3OytWamv5eDEAj",
	"BFCKUNZRVk1Ld8G9gO0np6czu7 ExYJiawqlyIjfoXr4TQ32HehS5PtvmDsWMAb",
	"2r QA5PHME7IzsqZKW4fwSbkgRe913tOYmDFcnlXNUBiJ8TGjdLhxyvoCpV0a6u",
	"vFTSUynDO kMPfRHx2czd7gJC6ZIBthemEYlGXV1pN8wsou3iQjrb0a5W9ALK4q",
	"Xh1C9n0O4WQVsilNHg6DGKyp8ofdaFz2jcA 7tw5rRMLxubBSqUkEPvIeTYZ3mJ",
	"Y7JMsVieTy9DAKWE PUHOv1IG3CgpbNlmFQ8B5qa0tznukXRo6hrd42jLfSwZcx",
	"MXv4nJw8bePZG7HxjoS RgC6TlNrIpFqWVB9AyzsDYOQUt52uKakL0cdEh13imf",
	"rxQZ7g24joCiyaFpR01ABfMX6JPeknVKGhuW3 9OY8mIvTHtbL5wDcqdlSsNEUz",
	"O6HYjmEiTRbyr1vgaUIK07ltzFB 4dcuDM5JXPLsoCf2xShwN3QAeqpZGn8kW9V",
	"EYvzL80Iui fhdOUTKSytrBZWMH9Q3xjpXoq5Jmc2Vk6DC4saw7GlR1NnegbFAP",
	"5PYCSQOij3WAJl8X7ebLEKma9Bzq6ZUcRkT2FIr4tu h1MvsgGNoxpnyd0fwVDH",
	"EYie3ysj6RDdVh0qZon4WQcuAgLz9x8akJKlXG1CNS5TM fmUwObPtv7BFHI2pr",
	"mMJ2jKCOekI0Bq9bUPfH6aFo3uc1 hDVxpWg8wRQsNvdtrzlYG5yiTEAL4XnZS7",
	"4c8RoWT0KabrZjVnDIgmNJdUeBLYyMGxzu 7qhA36kSEliFsXOvfCwt2p9HQ5P1",
	"gGw9zeHS Nt54jQml0dh1Y837PATaMDXpJLWucksyBiKv2oVZrn6CIUqEFfRObx",
	"8CE O1oTp6DwhJP2jImfraM0yYlRk75NAF3gbKZLz9sXSdWt4qiGVecUvHnQxBu",
	"2NwraX8gmMYLGnTo5hbUIqi16Ct9Bvx4JAfZuRDOz7FPlKyscSj0pk dW3HVeQE",
	"8ghGw7VE9WDujFlTPUC2tKdJvX5Ho1skyxaAe rLBp3YnziQSNfqM0R6mZb4IcO",
#endif
};

static	char	*Buffer = (char *)0;
static	int			BufSize = 0;

char *tmsEncode ( char Salt, char PlainText[] )
{
	int		Index, xl, xi, xo, Offset;

	if ( Salt < 'a' || Salt > 'z' )
	{
		return ( (char *)0 );
	}

	xl = nsStrlen ( PlainText );

	if ( xl + 10 > BufSize )
	{
		BufSize = xl + 10;
		if (( Buffer = realloc ( Buffer, BufSize )) == (char *)0 )
		{
			return ( (char *)0 );
		}
	}

	Index = Salt - 'a' + 1;

	Buffer[0] = Salt;

	for ( xi = 0, xo = 1; xi < xl; xi++, xo++ )
	{
		for ( Offset = 0; Keys[0][Offset] != '\0'; Offset++ )
		{
			if ( Keys[0][Offset] == PlainText[xi] )
			{
				break;
			}
		}

		if ( Keys[0][Offset] != '\0' )
		{
			Buffer[xo] = Keys[Index][Offset];
		}
		else
		{
			Buffer[xo] = PlainText[xi];
		}
	}
	Buffer[xo] = '\0';

	return ( Buffer );
}

char *tmsDecode ( char Encrypted[] )
{
	char	Salt;
	int		Index, xl, xi, xo, Offset;

	Salt = Encrypted[0];

	if ( Salt < 'a' || Salt > 'z' )
	{
		return ( (char *)0 );
	}

	Index = Salt - 'a' + 1;

	xl = nsStrlen ( Encrypted );
	if ( xl + 1 > BufSize )
	{
		BufSize = xl + 1;
		if (( Buffer = realloc ( Buffer, BufSize )) == (char *)0 )
		{
			return ( (char *)0 );
		}
	}

	for ( xi = 1, xo = 0; xi < xl; xi++, xo++ )
	{
		for ( Offset = 0; Keys[Index][Offset] != '\0'; Offset++ )
		{
			if ( Keys[Index][Offset] == Encrypted[xi] )
			{
				break;
			}
		}

		if ( Keys[Index][Offset] != '\0' )
		{
			Buffer[xo] = Keys[0][Offset];
		}
		else
		{
			Buffer[xo] = Encrypted[xi];
		}
	}
	Buffer[xo] = '\0';

	return ( Buffer );
}

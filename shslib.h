/*----------------------------------------------------------------------------
	Program : shslib.h
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Once upon a time.
	Synopsis: header file for shslib.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		various		added defines, typedefs and functions as needed.

----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
	Copyright © 2024 Tom Stevelt
	Tom Stevelt <tstevelt@silverhammersoftware.com>
	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.
---------------------------------------------------------------------------*/

#ifndef	SHSLIB_H
#define	SHSLIB_H

#include	<stdio.h>
#include	<time.h>
#include    <sys/times.h>

#define		PASSWORD_SALT_DIGITS	3
#define 	MIN_PASSWORD_LENGTH		6 
#define		MAX_PASSWORD_LENGTH		30
#define		PASSWORD_POLICY_COUNT	3

#define		DATATYPE_CHAR			1
#define		DATATYPE_STRING			2
#define		DATATYPE_SHORT			3
#define		DATATYPE_INT			4
#define		DATATYPE_LONG			5
#define		DATATYPE_FLOAT			6
#define		DATATYPE_DOUBLE			7
#define		DATATYPE_MYSQL_DATE		8
#define		DATATYPE_SYSTEM_DATE	9

#define		SEEK_FIRST				1
#define		SEEK_NEXT				2
#define		SEEK_PREV				3
#define		SEEK_LAST				4

#define		PRINT_NULL_DATE		"&nbsp;"

typedef union
{
	char	Array[128];
	char	*String;
	char	Character;
	short	Short;
	int		Integer;
	long	Long;
	float	Float;
	double	Double;
} SHS_DATA_UNION;

#ifndef DATEVAL_DEFINED
#define DATEVAL_DEFINED
typedef struct
{
	int		month;
	int		day;
	int		year2;
	int		year4;
} DATEVAL;
#endif

#ifndef DATETIMEVAL_DEFINED
#define DATETIMEVAL_DEFINED
typedef struct
{
	int		month;
	int		day;
	int		year2;
	int		year4;
	int		hour;
	int		minute;
	int		second;
	int		millisec;
	char    AsciiDateTime[30];
	long	epoch;
	int     dst;
} DATETIMEVAL;
#endif

#ifndef TYPE
#ifdef MAIN
#define		TYPE		/* */
#else
#define		TYPE		extern
#endif
#endif

/*----------------------------------------------------------
	removed HAVE_ERROR_ARRAY
----------------------------------------------------------*/
/*----------------------------------------------------------
	color defines are in order of severity. see ErrorColor.c
----------------------------------------------------------*/
#define		COLOR_NORMAL	1
#define		COLOR_SUCCESS	2
#define		COLOR_WARN		3
#define		COLOR_ERROR		4
#define		MAXERR		100
#define		ERRMSGSZ	80
typedef struct 
{
	int		Color;
	char	Message[ERRMSGSZ];
} ERROR_RECORD;
TYPE	ERROR_RECORD	ErrorArray[MAXERR];
TYPE	int				ErrorCount;

TYPE	char		env_GoogleMapKey[65];
// not used TYPE	char		env_GoogleMapURL[65];

#define		DATEFMT_MM_DD_YY		101
#define		DATEFMT_MMDDYY			102
#define		DATEFMT_YYYY_MM_DD		103
#define		DATEFMT_MM_DD_YYYY		104
#define		DATEFMT_AAA_DD_YYYY		105
#define		DATEFMT_SYSTEM_DAYS		106
#define		DATEFMT_TIMESTAMP		107
#define		DATEFMT_EPOCH_MILLISEC	108
#define		DATEFMT_YYYYMMDD		109

#define		PRINT_DESTINATION_STDOUT		701
#define		PRINT_DESTINATION_STDERR		702
#define		PRINT_DESTINATION_ERROR_ARRAY	703
#define		PRINT_DESTINATION_SILENT		704

#define		SHS_FILE_TYPE_UNKNOWN	101
#define		SHS_FILE_TYPE_JPG		102
#define		SHS_FILE_TYPE_EXIF		103
#define		SHS_FILE_TYPE_PNG		104
#define		SHS_FILE_TYPE_GIF		105
#define		SHS_FILE_TYPE_PS		106
#define		SHS_FILE_TYPE_PDF		107
#define		SHS_FILE_TYPE_ZIP		108
#define		SHS_FILE_TYPE_MSOFFICE	109
#define		SHS_FILE_TYPE_ELF		110
#define		SHS_FILE_TYPE_SHELL		111
#define		SHS_FILE_TYPE_EXE		112
#define		SHS_FILE_TYPE_EXE_ZM	113
#define		SHS_FILE_TYPE_ARCHIVE	114
#define		SHS_FILE_TYPE_TEXT		115

#define		SHS_FILE_TYPE_FINANCE_CSV		120
#define		SHS_FILE_TYPE_FINANCE_QIF		121
#define		SHS_FILE_TYPE_FINANCE_OFX		122

typedef struct
{
	int		TypeID;
	char	*Description;
	int		FileSize;
	int		ImageHeight;
	int		ImageWidth;
	int		ImageSize;
	int		ImageOrientation;
	int		Executable;
} SHS_FILE_TYPE;


typedef struct
{
	short		Success;
	double		LoadAverage;
	long		Vsize;
	long		RSS;
	clock_t		StartTime;
	clock_t		CurrentTime;
	long		MemAvailable;
} PROCESS_RECORD;

typedef struct
{
	char	*Name;
	char	*Value;
	int		Offset;
	int		Length;
} JSON_NAME_VALUE;

#define	JSON_FIRST	1
#define	JSON_NEXT	2


/*----------------------------
:.,$-1d
:$-1
:r ! mkproto -p *.c
----------------------------*/

/* background.c */
void background ( char *outfile , char *errfile );

/* JsonFuncs.c */
char *JsonOpenFileAndRead ( char *filename );
JSON_NAME_VALUE *JsonScan ( char *buffer , char *target , int Direction );

/* CalcDistance.c */
int CalcDistance ( double olatitude , double olongitude , double dlatitude , double dlongitude , int *mileage , int *bearing );

/* CheckYear.c */
int CheckYear ( int Year );

/* CompareDateval.c */
int CompareDateval ( DATEVAL *a , DATEVAL *b );

/* CurrentDateval.c */
void CurrentDateval ( DATEVAL *Today );

/* CurrentDateTime.c */
int CurrentDateTime ( DATETIMEVAL *Now );

/* GetCurrentTime.c */
double GetCurrentTime ( int Debug );

/* DateAdd.c */
int DateAdd ( DATEVAL *a , int NumberOfDays , DATEVAL *b );

/* DateDiff.c */
long DateDiff ( DATEVAL *a , DATEVAL *b );

/* DayOfWeek.c */
char *DayOfWeek ( int TimeDayOfWeek );

/* dbldiff.c */
int dbldiff ( double d1 , double d2 , double allow );

/* DiffYak.c */
void DiffYak ( char *Label , void *Mem1 , void *Mem2 , size_t MemSize , int Datatype );

/* DoExec.c */
void DoExec ( FILE *DaemonIFP , FILE *DaemonOFP , char *CommandLine );

/* ErrorColor.c */
int ErrorColor ( void );

/* factorial.c */
double factorial ( int number );

/* FileAge.c */
int FileAge ( char *FileName );

/* FileDateTime.c */
char *cpFileDateTime ( char *FileName , int Format );

/* findmax.c */
int findmax ( double Array [], int Count );

/* fmtGetTodayDate.c */
char *fmtGetTodayDate ( int Format );

/* ForkAndExec.c */
void ForkAndExec ( char *CommandLine , int PrintDestination );

/* FourDigitYear.c */
int FourDigitYear ( int Year );

/* GetDomainName.c */
char *GetDomainName ( void );

/* GetGoogleCfg.c */
void GetGoogleCfg ( void );

/* GetTokensA.c */
int GetTokensA ( char Buffer [], char Delim [], char *tokens [], int maxtoks );

/* GetTokensCSV.c */
int GetTokensCSV ( char *Buffer , char *tokens [], int MaxToks , int KeepInternalCommas , int Verbose );

/* GetTokensD.c */
int GetTokensD ( char xbuf [], char delim [], char *toks [], int maxtoks );

/* GetTokensStd.c */
int GetTokensStd ( char xbuf [], char delim [], char *toks [], int maxtoks , int Verbose );

/* GetTokensW.c */
int GetTokensW ( char xbuf [], char *toks [], int maxtoks );

/* IsMarketOpen.c */
int IsMarketOpen ( void );

/* isword.c */
int isword ( char *SomeString );

/* JsonTokens.c */
int JsonTokens ( char Buffer [], char *Tags [], char *Values [], int maxtoks );

/* lastchr.c */
long lastchr ( char *s , int n );

/* logmsg.c */
void logmsg ( char *Filename , char *Message );
void logDSUmsg ( char *Filename , char *Message );
void logDTUmsg ( char *Filename , char *Message );
void logDTmsg ( char *Filename , char *UserName , char *Message );
void LogFirstLineOrSixty ( char *Filename , const char *SomeString );

/* longGetTodayDate.c */
long longGetTodayDate ( void );

char *LookupCountryFromIP ( char *IP_Address );

/* lset.c */
void lset ( void *dest , void *from , int number );

/* MakeFileName.c */
int MakeFileName ( char Symbol [], char Phrase [], char tmpfile [], int tmpsize );

/* MemoryMonitor.c */
int MemoryMonitor ( double LimitPercent );

/* MinMaxScale.c */
void MinMaxScale ( double Array [], int StartIndex , int Length );

/* munge.c */
double dblMunge ( double number , double min , double max );
int intMunge ( int number , int min , int max );
long longMunge ( long number , long min , long max );
char *strMunge ( char String []);

/* nap.c */
void nap ( int milliseconds );

/* nsSimilar.c */
double nsSimilar ( char *String1 , char *String2 );

/* NullSafeFuncs.c */
int nsAtoi ( const char *cpOne );
long nsAtol ( const char *cpOne );
double nsAtof ( const char *cpOne );
int nsStrlen ( const char *cpOne );
int nsStrcmp ( const char *cpOne , const char *cpTwo );
int nsStrncmp ( const char *cpOne , const char *cpTwo , int Number );
int nsStrcasecmp ( const char *cpOne , const char *cpTwo );
int nsStrncasecmp ( const char *cpOne , const char *cpTwo , int Number );
char *nsStrnstr ( const char *cpOne , const char *cpTwo , int Number );
char *nsStrcpy ( char *cpOne , const char *cpTwo );
char *nsStrncpy ( char *cpOne , const char *cpTwo , int Number );
char *nsStrchr ( const char *cpOne , int intChar );
char *nsStrrchr ( const char *cpOne , int intChar );
char *nsStrstr ( const char *cpOne , const char *cpTwo );
char *nsStrcasestr ( const char *cpOne , const char *cpTwo );
char *nsStrcat ( char *cpOne , char *cpTwo );
int nsFclose ( FILE *fp );
char *nsStrToUpcase ( char *InString );
char *nsStrToLowcase ( char *InString );
int nsCharCount ( char *InString , char Character );

/* numberfuncs.c */
int cmax ( char number1 , char number2 );
int smax ( short number1 , short number2 );
int imax ( int number1 , int number2 );
int lmax ( long number1 , long number2 );
double dmax ( double number1 , double number2 );
int cmin ( char number1 , char number2 );
int smin ( short number1 , short number2 );
int imin ( int number1 , int number2 );
int lmin ( long number1 , long number2 );
double dmin ( double number1 , double number2 );
double dminArray ( double number[], int count );
double dmaxArray ( double number[], int count );

/* ProcessStats.c */
void ProcessStatsInit ( int Verbose );
PROCESS_RECORD *ProcessStats ( int ProcessPID );
void PrintProcessStats ( int ProcessPID );

/* PtrToStr.c */
char *PtrToStr ( char *Ptr );

/* pwfuncs.c */
char *pw_genpw ( int Length , int Complexity );
void pw_genkey ( int Length , int Salt );
void pw_encode ( char *s , int Length , int Salt );
char *pw_policy_string ( int ErrorCode );
int pw_policy ( char *PlainText , int ComplexityCount );
int pw_check ( char *PlainText , char *SaltEncoded );

/* pw_sha.c */
unsigned char *pw_sha_make_pw ( unsigned char *plaintext );
int pw_sha_login_pw ( unsigned char *plaintext , unsigned char *filepw );

/* randfuncs.c */
void shs_seed_random ( void );
double d_random ( void );
short flip ( double probability );
long random_range ( long low , long high );
double d_random_range ( double low, double high );

/* ReverseDNS.c */
char *ReverseDNS ( char Address []);

/* SafeError.c */
void SafeError ( int Color , char *MessageFormat , ...);
void SaveError ( char *ErrorMessage );

/* SendAttached.c */
size_t calcDecodeLength ( const char *b64input );
int Base64Decode ( char *b64message , unsigned char **buffer , size_t *length );
int Base64Encode ( const unsigned char *buffer , size_t length , char **b64text );
char *Generate_UUID ( void );
int SendAttached ( char *FromAddress , char *ToAddress , char *CcAddress , char *BccAddress , char *Subject , int BodyIsHTML , char *BodyFile , int AttachmentCount , char *AttachFiles []);

/* SessionFuncs.c */
int MakeSessionID ( char SessionBuffer [], int Length , int InitRandom );

/* shsCode.c */
char *tmsEncode ( char Salt , char PlainText []);
char *tmsDecode ( char Encrypted []);

/* shsFileType.c */
SHS_FILE_TYPE *BufferType ( unsigned char xbuffer [], int numread , int Verbose );
SHS_FILE_TYPE *shsFileType ( char Filename [], int Verbose );

/* shsLastChr.c */
long shsLastChr ( char *s , long n );

/* shsLoadAverage.c */
double shsLoadAverage ( void );

/* shsSearchAndReplace.c */
char *shsSearchAndReplace ( char *Source , char *Pattern , char *Replacement );

/* shsUsage.c */
void shsUsage ( FILE *fp , char *error , char *msg [], int count , int fatal );

/* softmax.c */
int softmax ( double *Array , size_t size );

/* SoundEx.c */
int SoundEx ( char *SoundEx , char *WordString , int LengthOption , int CensusOption );

/* stddev.c */
double stddev ( double Array [], int Count );

/* StrInitialCaps.c */
void StrInitialCaps ( char *String );

/* Stripper.c */
void Stripper ( char String [], char Remove []);

/* StrToDatetimevalFmt.c */
int StrToDatetimevalFmt ( char datestr [], int Format , DATETIMEVAL *datetimeval );

/* StrToDateval.c */
int StrToDateval ( char datestr [], DATEVAL *dateval );

/* StrToDatevalFmt.c */
int StrToDatevalFmt ( char datestr [], int Format , DATEVAL *dateval );

/* TimeDateFuncs.c */
char *TodayDate ( void );
char *AsciiTime ( void );
char *DateYYYY_MM_DD ( time_t TimeValue );
char *DayOfWeek ( int TimeDayOfWeek );
char *MonthOfYear ( int TimeMonth );
char *TimeHHMMSS ( time_t TimeValue );
char *TimeMMDDHHMM ( time_t TimeValue );
void ConvertSecondsToDateTimeVal ( time_t Seconds, DATETIMEVAL *dtValue );

/* trimfuncs.c */
void TrimRightAndLeft ( char b []);
void TrimRight ( char *b );
void TrimLeft ( char *b );
void TrimOptionalLength ( char SomeString [], int OptionalLength );

/* ValidDateval.c */
int ValidDateval ( DATEVAL *TestDate , int NullDateOkay );

/* ValidEmailAddress.c */
int ValidEmailAddress ( char *TestAddress );

/* ValidNumber.c */
int ValidNumber ( char *NumberString , int Float , int Signed );

/* ValidPhoneNumber.c */
int ValidPhoneNumber ( char *TestPhoneNumber );

/* ValidZipCode.c */
int ValidZipCode ( char *TestZipCode );

/* ValidTime.c */
int ValidTime ( char *TimeString );

/* WhoisSystem.c */
char *WhoisSystem ( char *Address );

/* Xgetdate.c */
void Xgetdatem ( char *cday , char *miltm );
void Xgetdates ( char *cday , char *miltm );
void Xgetdate ( char *cday , char *ctm );
#endif

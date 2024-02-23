PROG = shslib

ifeq ($(LDFLAGS),"-m32")
LIB = /usr/local/lib/shslib.a
else
LIB = /usr/local/lib64/shslib.a
endif

DEF = /usr/local/include

FILES = \
	$(LIB)(background.o)		\
	$(LIB)(LookupCountryFromIP.o)	\
	$(LIB)(CalcDistance.o)	\
	$(LIB)(CheckYear.o)	\
	$(LIB)(CurrentDateval.o)	\
	$(LIB)(CurrentDateTime.o)	\
	$(LIB)(GetCurrentTime.o)	\
	$(LIB)(CompareDateval.o)	\
	$(LIB)(DateAdd.o)	\
	$(LIB)(DateDiff.o)	\
	$(LIB)(dbldiff.o)	\
	$(LIB)(detab.o)		\
	$(LIB)(DiffYak.o)		\
	$(LIB)(ErrorColor.o)	\
	$(LIB)(FileAge.o)		\
	$(LIB)(FileDateTime.o)	\
	$(LIB)(findmax.o)	\
	$(LIB)(fmtGetTodayDate.o)	\
	$(LIB)(ForkAndExec.o)	\
	$(LIB)(FourDigitYear.o)	\
	$(LIB)(GetDomainName.o)	\
	$(LIB)(GetTokensA.o)		\
	$(LIB)(GetTokensCSV.o)	\
	$(LIB)(GetTokensD.o)	\
	$(LIB)(GetTokensStd.o)	\
	$(LIB)(GetTokensW.o)	\
	$(LIB)(IsMarketOpen.o)	\
	$(LIB)(isword.o)	\
	$(LIB)(JsonTokens.o)	\
	$(LIB)(JsonFuncs.o)	\
	$(LIB)(lastchr.o)		\
	$(LIB)(logmsg.o)	\
	$(LIB)(longGetTodayDate.o)	\
	$(LIB)(LookupCountry.o)	\
	$(LIB)(lset.o)	\
	$(LIB)(MakeFileName.o)	\
	$(LIB)(MinMaxScale.o)	\
	$(LIB)(munge.o)	\
	$(LIB)(NapMillisec.o)	\
	$(LIB)(nap.o)	\
	$(LIB)(nsSimilar.o)	\
	$(LIB)(NullSafeFuncs.o)	\
	$(LIB)(numberfuncs.o)	\
	$(LIB)(ProcessStats.o)	\
	$(LIB)(PtrToStr.o)		\
	$(LIB)(pwfuncs.o)		\
	$(LIB)(pw_sha.o)		\
	$(LIB)(randfuncs.o)	\
	$(LIB)(ReverseDNS.o)	\
	$(LIB)(SafeError.o)		\
	$(LIB)(SendAttached.o)	\
	$(LIB)(SessionFuncs.o)	\
	$(LIB)(shsCode.o)		\
	$(LIB)(shsFileType.o)	\
	$(LIB)(shsLastChr.o)	\
	$(LIB)(shsLoadAverage.o)	\
	$(LIB)(shsUsage.o)	\
	$(LIB)(shsSearchAndReplace.o)	\
	$(LIB)(softmax.o)	\
	$(LIB)(stddev.o)	\
	$(LIB)(StrInitialCaps.o)	\
	$(LIB)(Stripper.o)	\
	$(LIB)(StrToDatetimevalFmt.o)	\
	$(LIB)(StrToDatevalFmt.o)	\
	$(LIB)(StrToDateval.o)	\
	$(LIB)(TimeDateFuncs.o)	\
	$(LIB)(trimfuncs.o)		\
	$(LIB)(ValidDateval.o)	\
	$(LIB)(ValidEmailAddress.o)	\
	$(LIB)(ValidNumber.o)	\
	$(LIB)(ValidPhoneNumber.o)	\
	$(LIB)(ValidZipCode.o)	\
	$(LIB)(ValidTime.o)	\
	$(LIB)(WhoisSystem.o)	\
	$(LIB)(Xgetdate.o)

.SILENT:

$(LIB): $(FILES)
	make include

$(FILES): shslib.h shsCountries.h shsStates.h shsCarriers.h

include: $(DEF)/shslib.h $(DEF)/shsStates.h $(DEF)/shsCarriers.h $(DEF)/shsCountries.h

$(DEF)/shslib.h: shslib.h 
	cp -pv shslib.h $(DEF)/shslib.h

$(DEF)/shsStates.h: shsStates.h 
	cp -pv shsStates.h $(DEF)/shsStates.h

$(DEF)/shsCarriers.h: shsCarriers.h 
	cp -pv shsCarriers.h $(DEF)/shsCarriers.h

$(DEF)/shsCountries.h: shsCountries.h 
	cp -pv shsCountries.h $(DEF)/shsCountries.h

strip:
	ls -l $(LIB)
	strip --strip-unneeded $(LIB)
	ls -l $(LIB)

clean:
	rm -f $(LIB)

all:
	make clean
	make

.PRECIOUS: $(LIB)


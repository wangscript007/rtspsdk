//
// Poco/SDP/SDP.h
//
// Library: SDP
// Package: SDP
// Module:  SDP
//
// Basic definitions for the Poco SDP library.
// This file must be the first file included by every other SDP
// header file.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SDP_SDP_INCLUDED
#define SDP_SDP_INCLUDED

#include "Poco/Foundation.h"

//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SDP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SDP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(SDP_EXPORTS)
		#define SDP_API __declspec(dllexport)
	#else
		#define SDP_API __declspec(dllimport)
	#endif
#endif


#if !defined(SDP_API)
	#if !defined(POCO_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define SDP_API __attribute__ ((visibility ("default")))
	#else
		#define SDP_API
	#endif
#endif


//
// Automatically link SDP library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(SDP_EXPORTS)
		#pragma comment(lib, "PocoSDP" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // SDP_SDP_INCLUDED
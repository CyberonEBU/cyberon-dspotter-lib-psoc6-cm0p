/*
PLEASE READ THE CYBERON END USER LICENSE AGREEMENT ("LICENSE(Cyberon)") CAREFULLY BEFORE DOWNLOADING, INSTALLING, COPYING, OR USING THIS SOFTWARE AND ACCOMPANYING DOCUMENTATION.
BY DOWNLOADING, INSTALLING, COPYING OR USING THE SOFTWARE, YOU ARE AGREEING TO BE BOUND BY THE AGREEMENT.
IF YOU DO NOT AGREE TO ALL OF THE TERMS OF THE AGREEMENT, PROMPTLY RETURN AND DO NOT USE THE SOFTWARE.
*/

#ifndef	BASE_TYPES_H__
#define	BASE_TYPES_H__


//#define CEVA_SIMULATE_
//#define DIM_40_

#include <stdlib.h>
#include <string.h>

// from <stdint.h>. for uintptr_t
// Define _W64 macros to mark types changing their size, like intptr_t.
#if defined(_WIN32)
#ifndef _W64
#  if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#     define _W64 __w64
#  else
#     define _W64
#  endif
#endif	// _W64

#ifdef _WIN64 // [
	typedef signed __int64    intptr_t;
	typedef unsigned __int64  uintptr_t;
	typedef unsigned __int64 ULONG_PTR;
#else // _WIN64 ][
	typedef _W64 signed int   intptr_t;
	typedef _W64 unsigned int uintptr_t;
	typedef _W64 unsigned long ULONG_PTR;
#endif // _WIN64 ]

#else	// WIN32

/* Types for `void *' pointers.  */
//#if __WORDSIZE == 64
#if defined(__LP64__) || defined(_LP64)
	#ifndef __intptr_t_defined
		typedef long int                intptr_t;
		#define __intptr_t_defined
	#endif	// __intptr_t_defined
	typedef unsigned long int           uintptr_t;
#else	// __LP64__ || _LP64
	#ifndef __intptr_t_defined
		typedef int                     intptr_t;
		#define __intptr_t_defined
	#endif	// __intptr_t_defined
	typedef unsigned int                uintptr_t;
#endif	// __LP64__ || _LP64

#endif	// _WIN32

#if !defined(BUILD_DSPOTTER_ENGINE_)
	#ifndef CEVA_SIMULATE_
		//#include <windows.h>
	#endif	// CEVA_SIMULATE_
#else	// _WIN32
	#ifdef EVENT_DETECT_
		#include "SubName_EventSpotter.h"
	#else	// EVENT_DETECT_
//		#ifndef _DEBUG
			#include "SubName.h"
//		#endif
	#endif	// EVENT_DETECT_
#endif	// _WIN32


#if defined(_WIN32)

#ifdef CEVA_SIMULATE_
	typedef signed short CHAR;
	typedef unsigned short BYTE;
	typedef signed short INT8;
	typedef unsigned short UINT8;
	typedef signed short SHORT;
	typedef unsigned short WORD;
	typedef unsigned short USHORT;
	typedef signed long LONG;
	typedef unsigned int DWORD;
	typedef unsigned long ULONG;
	typedef signed int INT;
	typedef unsigned int UINT;
	typedef int BOOL;
#ifndef VOID
	#define VOID void
#endif	// VOID
	typedef unsigned short WCHAR;	/*typedef wchar_t WCHAR;*/
	typedef float FLOAT;
#else	// CEVA_SIMULATE_
	// in <windows.h>
	//typedef signed char CHAR;		// define this for more portability while building engine
	typedef char CHAR;				// define this for application under Windows
	typedef unsigned char BYTE;
	typedef signed short SHORT;
	typedef unsigned short WORD;
	typedef signed long LONG;
	typedef unsigned long DWORD;
	typedef unsigned long ULONG;
	typedef signed int INT;
	typedef int BOOL;

	typedef signed char INT8;
	typedef unsigned char UINT8;
	typedef unsigned short USHORT;
	typedef unsigned int UINT;
	typedef unsigned long ULONG;
#ifndef VOID
	#define VOID void	// void is not a type, can't use typedef
#endif	// VOID
	#define SIZE_T ULONG_PTR	// 	using typedef UINT SIZE_T; will get warning C4142: benign redefinition of type
	typedef float FLOAT;

#endif	// CEVA_SIMULATE_


#if (_MSC_VER < 1400)
	typedef unsigned short WCHAR;
#endif	// _MSC_VER

#else	// _WIN32

#ifdef CEVA_SIMULATE_
	typedef signed short CHAR;
	typedef unsigned short BYTE;
	typedef signed short INT8;
	typedef unsigned short UINT8;
#else	// CEVA_SIMULATE_
	typedef signed char CHAR;
	typedef unsigned char BYTE;
	typedef signed char INT8;
	typedef unsigned char UINT8;
#endif	// CEVA_SIMULATE_

	typedef signed short SHORT;
	typedef unsigned short WORD;
	typedef unsigned short USHORT;
	typedef signed long LONG;
	typedef unsigned int DWORD;
	typedef unsigned long ULONG;
	typedef signed int INT;
	typedef unsigned int UINT;
	typedef int BOOL;
#ifndef VOID
	#define VOID void
#endif	// VOID
	typedef unsigned short WCHAR;	/*typedef wchar_t WCHAR;*/
	typedef float FLOAT;

	#define SIZE_T uintptr_t	// 	using typedef UINT SIZE_T; will get warning C4142: benign redefinition of type


#endif	// _WIN32

#ifdef UNICODE
#undef UNICODE
#endif	// UNICODE

//#define UNICODE WCHAR
#define UNICODE unsigned short

//#ifdef LPVOID
//#undef LPVOID	// Non-compliant: MISRA Rule 20.5
//#endif	// LPVOID
//#define LPVOID	void*


#ifndef TRUE
#define TRUE	(INT)1
#endif	// TRUE

#ifndef FALSE
#define FALSE	(INT)0
#endif	// FALSE

#ifndef HANDLE
//#define HANDLE	VOID*
typedef void* HANDLE;
#endif	// HANDLE


#ifdef __cplusplus
#define NULL 0
#else	// __cplusplus
#ifndef NULL
#define NULL	((VOID*)0)	//Non-compliant: MISRA Rule 21.1
#endif	// NULL
#endif	// __cplusplus

#define PNULL	((VOID*)0)

#ifndef STATIC
#define STATIC 	static
#endif	// STATIC

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif	// max

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif	// min

#if defined(_WIN32)
	#define EXPAPI WINAPI
#else	// _WIN32
	#define EXPAPI
#endif	// _WIN32

#ifndef SAFE_DELETE
#define SAFE_DELETE(a)	if ( (a) != NULL ) {delete (a); (a) = NULL;}
#endif	// SAFE_DELETE

#ifndef SAFE_FREE
#define SAFE_FREE(a)	if ( (a) != NULL ) {free(a); (a) = NULL;}
#endif	// SAFE_FREE

//#include "DMemory.h"

#ifndef INLINE
#if defined ( _WIN32 )
	#define INLINE		__inline		// inline keyword for WIN32 Compiler
#elif defined ( __CC_ARM )
	#define INLINE		__inline		// inline keyword for ARM Compiler
#elif defined ( __ICCARM__ )
	#define INLINE		inline			// inline keyword for IAR Compiler. Only available in High optimization mode!
#elif defined ( __GNUC__ )
	#define INLINE		inline			// inline keyword for GNU Compiler
#else	// _WIN32, __CC_ARM, __ICCARM__, __GNUC__
	#define INLINE		inline
#endif	// _WIN32, __CC_ARM, __ICCARM__, __GNUC__
#endif	// INLINE

#endif	// BASE_TYPES_H__

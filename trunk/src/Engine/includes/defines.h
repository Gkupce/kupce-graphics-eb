#ifndef __DEFINES_H__
#define __DEFINES_H__

#ifdef __ENGINE_API
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif //__ENGINE_API

//----------------------------------------------------------------
// Includes Standar
#ifdef _WIN64
   //defines Windows (64-bit)
	#include <windows.h>
#elif _WIN32
   //defines Windows (32-bit)
	#include <windows.h>
#endif
//----------------------------------------------------------------

#endif //__DEFINES_H__
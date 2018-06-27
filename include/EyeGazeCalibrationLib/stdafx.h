// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#ifdef _WINDOWS

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#endif

#define EYEGAZECALIBRATION_DLL_EXPORTS

#if _WINDOWS
#ifdef EYEGAZECALIBRATION_DLL_EXPORTS
#define EYEGAZECALIBRATION_API __declspec(dllexport)   
#else  
#define EYEGAZECALIBRATION_API __declspec(dllimport)   
#endif
#else
#define EYEGAZECALIBRATION_API 
#endif

// TODO: reference additional headers your program requires here

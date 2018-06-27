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

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#define EYEGAZECAMERA_DLL_EXPORTS

#if _WINDOWS
    #ifdef EYEGAZECAMERA_DLL_EXPORTS
        #define EYEGAZECAMERA_API __declspec(dllexport)   
    #else  
        #define EYEGAZECAMERA_API __declspec(dllimport)   
    #endif
    #define EYEGAZECAMERA_API_LOCAL
#else
    #if __GNUC__ >= 4
        #define EYEGAZECAMERA_API __attribute__ ((visibility ("default")))
        #define EYEGAZECAMERA_API_LOCAL __attribute__ ((visibility ("hidden")))
    #else
        #define EYEGAZECAMERA_API
        #define EYEGAZECAMERA_API_LOCAL
    #endif 
#endif




// TODO: reference additional headers your program requires here

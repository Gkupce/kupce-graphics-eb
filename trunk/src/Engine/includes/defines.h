#ifndef __DEFINES_H__
#define __DEFINES_H__

#ifdef __ENGINE_API
#define ENGINE_EXPORT __declspec(dllexport)
#else
#define ENGINE_EXPORT __declspec(dllimport)
#endif //__ENGINE_API

#endif //__DEFINES_H__
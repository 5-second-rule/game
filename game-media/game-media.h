#pragma once

#ifdef WIN32
// disable warning about zero-length arrays in MSVC
// exporting STL classes, and strerror security warning
#pragma warning( disable : 4200 )
#pragma warning( disable : 4251 )
#pragma warning( disable : 4996 )
#ifdef _IS_GAME_MEDIA
#define GAMEMEDIADLL __declspec(dllexport)
#else
#define GAMEMEDIADLL __declspec(dllimport)
#endif
#else
#define GAMEMEDIADLL
#endif
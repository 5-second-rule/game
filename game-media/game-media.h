#pragma once

#ifdef _IS_GAME_MEDIA
#define GAMEMEDIADLL __declspec(dllexport)
#else
#define GAMEMEDIADLL __declspec(dllimport)
#endif
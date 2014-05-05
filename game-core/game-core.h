#pragma once

#ifdef _IS_GAME_CORE
#define GAMECOREDLL __declspec(dllexport)
#else
#define GAMECOREDLL __declspec(dllimport)
#endif

#define VERBOSITY 10
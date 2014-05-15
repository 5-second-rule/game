#pragma once

#ifdef _IS_GAME_CORE
#define GAMECOREDLL __declspec(dllexport)
#else
#define GAMECOREDLL __declspec(dllimport)
#endif

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "engine-core/ConfigSettings.h"

#include "common/common.h"
#include "common/4D/Transformation.h"
#include "common/Matrix4.h"
#include "common/misc/utils.h"

#include "TypeDefinition.h"

const int VERBOSITY = 10;
using namespace Common;
using namespace std;
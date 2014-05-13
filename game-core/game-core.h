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

#include "../../engine/engine-core/ConfigSettings.h"

#include "../../common/common/common.h"
#include "../../common/common/4D/Matrix4.h"
#include "../../common/common/misc/utils.h"

#include "TypeDefinition.h"

const int VERBOSITY = 10;
using namespace Common;
using namespace std;
/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Path/Windows/PathModule.h"

PONY_MODULE(PonyEngine::Path::Windows::GetPathModule, PonyEngineWindowsPathService, PONY_ENGINE_PATH_MAIN_ORDER);

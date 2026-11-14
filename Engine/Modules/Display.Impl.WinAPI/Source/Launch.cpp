/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Display/WinAPI/DisplayServiceModule.h"

PONY_ENGINE_MODULE(PonyEngine::Display::CreateDisplayServiceModule, PonyEngineDisplayService, PONY_ENGINE_DISPLAY_ORDER);

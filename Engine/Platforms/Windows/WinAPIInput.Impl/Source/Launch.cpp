/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/WinAPIInput/Windows/WinAPIInputModule.h"

PONY_ENGINE_MODULE(PonyEngine::WinAPIInput::CreateWinAPIInputModule, PonyEngineWinAPIInput, PONY_ENGINE_WINAPI_INPUT_ORDER);

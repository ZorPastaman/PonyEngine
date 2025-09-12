/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Log/WinCore/PlatformConsoleModule.h"

PONY_MODULE(PonyEngine::Log::WinCore::GetPlatformConsoleModule, PonyEngineWinCorePlatformConsoleSubLogger, PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER);

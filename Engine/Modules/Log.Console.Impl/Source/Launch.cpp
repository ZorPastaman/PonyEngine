/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Log/ConsoleLoggerModule.h"

PONY_LOG_MODULE(PonyEngine::Log::Console::CreateConsoleLoggerModule, PonyEngineConsoleLogger, PONY_ENGINE_LOG_CONSOLE_ORDER)

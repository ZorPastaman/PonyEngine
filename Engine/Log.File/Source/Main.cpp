/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Log/FileSubLoggerModule.h"

PONY_MODULE(PonyEngine::Log::GetFileSubLoggerModule, PonyEngineFileSubLogger, PONY_ENGINE_LOG_FILE_ORDER);

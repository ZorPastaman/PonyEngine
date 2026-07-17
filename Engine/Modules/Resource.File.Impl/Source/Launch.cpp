/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Resource/FileResourceProviderModule.h"

PONY_ENGINE_MODULE(PonyEngine::Resource::File::GetFileResourceProviderModule, PonyEngineFileResourceProvider, PONY_ENGINE_RESOURCE_FILE_ORDER);

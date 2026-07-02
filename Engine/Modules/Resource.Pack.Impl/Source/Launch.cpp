/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Resource/PackResourceProviderModule.h"

PONY_MODULE(PonyEngine::Resource::Pack::GetPackResourceProviderModule, PonyEnginePackResourceProvider, PONY_ENGINE_RESOURCE_PACK_ORDER);

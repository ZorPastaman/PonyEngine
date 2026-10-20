/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Resource/World/WorldDefinitionLoaderModule.h"

PONY_ENGINE_MODULE(PonyEngine::Resource::World::CreateWorldDefinitionLoaderModule, PonyEngineResourceWorldDefinitionLoader, PONY_ENGINE_RESOURCE_WORLD_ORDER);

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Surface/SurfaceModule.h"

PONY_MODULE(PonyEngine::Surface::GetSurfaceModule, PonyEngineWindowsSurfaceService, PONY_ENGINE_SURFACE_MAIN_ORDER);

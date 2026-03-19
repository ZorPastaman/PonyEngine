/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/RenderDevice/RenderDeviceServiceModule.h"

PONY_MODULE(PonyEngine::RenderDevice::GetRenderDeviceServiceModule, PonyEngineRenderDeviceService, PONY_ENGINE_RENDER_DEVICE_ORDER);

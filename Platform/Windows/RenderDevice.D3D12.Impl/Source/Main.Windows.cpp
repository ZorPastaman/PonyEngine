/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Render/Windows/D3D12BackendModule.h"

PONY_MODULE(PonyEngine::Render::Windows::GetD3D12BackendModule, PonyEngineRenderDeviceD3D12Backend, PONY_ENGINE_RENDER_DEVICE_D3D12_ORDER);

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/RenderDevice/Windows/D3D12BackendModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.RenderDevice.Direct3D12.Impl.Windows;

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Application::IModule* GetD3D12BackendModule()
	{
		static D3D12BackendModule d3D12BackendModule;
		return &d3D12BackendModule;
	}
}

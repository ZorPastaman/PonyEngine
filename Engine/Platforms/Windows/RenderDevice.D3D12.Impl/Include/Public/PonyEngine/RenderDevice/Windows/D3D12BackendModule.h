/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyCompiler.h"

import PonyEngine.Application;

namespace PonyEngine::RenderDevice::D3D12
{
	/// @brief Gets the D3D12 backend module.
	/// @return D3D12 backend module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetD3D12BackendModule();
}

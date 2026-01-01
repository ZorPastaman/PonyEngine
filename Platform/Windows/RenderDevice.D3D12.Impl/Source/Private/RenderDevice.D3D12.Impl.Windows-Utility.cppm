/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Render/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:Utility;

import std;

export namespace PonyEngine::Render::Windows
{
	/// @brief Sets the object name.
	/// @param object Target object.
	/// @param name Name to set.
	void SetName(ID3D12Object& object, std::string_view name);
}

namespace PonyEngine::Render::Windows
{
	void SetName(ID3D12Object& object, const std::string_view name)
	{
		if (const HRESULT result = object.SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(name.size()), name.data()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set name: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:ObjectUtility;

import <stdexcept>;
import <string_view>;

import PonyBase.Utility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Sets the @p name to the @p object.
	/// @param object Object to set a name to.
	/// @param name Name to set.
	void SetName(ID3D12Object& object, std::string_view name);
}

namespace PonyEngine::Render::Direct3D12
{
	void SetName(ID3D12Object& object, const std::string_view name)
	{
		if (const HRESULT result = object.SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(name.size()), name.data()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set name with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}

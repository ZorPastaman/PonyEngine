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

export module PonyEngine.Render.Direct3D12.Detail:BackParams;

import <vector>;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 back parameters.
	struct BackParams final
	{
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> backBuffers; ///< Back buffers.
		DXGI_FORMAT backViewFormat; ///< Back view format.
	};
}

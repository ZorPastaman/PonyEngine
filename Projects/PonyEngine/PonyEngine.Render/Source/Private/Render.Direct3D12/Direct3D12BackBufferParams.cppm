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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12BackBufferParams;

import <vector>;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 back buffer parameters.
	struct Direct3D12BackBufferParams final
	{
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> backBuffers; ///< Back buffers.
		DXGI_FORMAT backBufferFormat; ///< Back buffer format.
	};
}

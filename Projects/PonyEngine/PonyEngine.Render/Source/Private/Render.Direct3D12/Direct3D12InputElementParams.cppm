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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12InputElementParams;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 input element parameters.
	struct Direct3D12InputElementParams final
	{
		LPCSTR semanticName; ///< Semantic name.
		UINT semanticIndex; ///< Semantic index.
		UINT inputSlot; ///< Input slot.
	};
}

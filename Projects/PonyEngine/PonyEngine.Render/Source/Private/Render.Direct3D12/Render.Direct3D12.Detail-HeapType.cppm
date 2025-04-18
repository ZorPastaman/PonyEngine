/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Detail:HeapType;

import <cstdint>;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Heap type.
	enum class HeapType : std::uint8_t
	{
		Default,
		Upload,
		Readback
	};
}

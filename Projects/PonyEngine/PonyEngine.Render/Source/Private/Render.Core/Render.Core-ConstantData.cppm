/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Core:ConstantData;

import <cstddef>;
import <cstdint>;
import <span>;

export namespace PonyEngine::Render::Core
{
	/// @brief Constant data reference.
	struct ConstantData final
	{
		std::span<const std::byte> data; ///< Data.
		std::span<const std::uint32_t> scheme; ///< Data scheme. It set a size of each sub-element in bytes.
	};
}

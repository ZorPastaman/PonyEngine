/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render:ISwapChain;

import <cstdint>;

import PonyMath.Utility;

import :TextureFormat;

export namespace PonyEngine::Render
{
	/// @brief Swap chain.
	class ISwapChain
	{
		INTERFACE_BODY(ISwapChain)

		/// @brief Gets the resolution.
		/// @return Resolution.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Utility::Resolution<std::uint32_t>& Resolution() const noexcept = 0;
		/// @brief Gets the buffer count.
		/// @return Buffer count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t BufferCount() const noexcept = 0;

		/// @brief Gets the buffer format.
		/// @return Buffer format.
		[[nodiscard("Pure function")]]
		virtual TextureFormat BufferFormat() const noexcept = 0;
		/// @brief Gets if the output is gamma-corrected.
		/// @return @a True if it's gamma-corrected; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool SRGBOutput() const noexcept = 0;
	};
}

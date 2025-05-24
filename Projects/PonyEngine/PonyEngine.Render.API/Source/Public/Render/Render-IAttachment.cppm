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

export module PonyEngine.Render:IAttachment;

import <cstdint>;

import PonyMath.Utility;

import :TextureFormat;

export namespace PonyEngine::Render
{
	/// @brief Frame attachment.
	class IAttachment
	{
		INTERFACE_BODY(IAttachment)

		/// @brief Gets the texture format.
		/// @return Texture format.
		[[nodiscard("Pure function")]]
		virtual TextureFormat Format() const noexcept = 0;
		/// @brief Gets the texture resolution.
		/// @return Resolution.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Utility::Resolution<std::uint32_t>& Size() const noexcept = 0;
		/// @brief Gets the sample count.
		/// @return Sample count.
		[[nodiscard("Pure function")]]
		virtual std::uint8_t SampleCount() const noexcept = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
	};
}
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

export module PonyEngine.Render:IShader;

import <cstddef>;
import <span>;
import <string_view>;

export namespace PonyEngine::Render
{
	/// @brief Shader.
	class IShader
	{
		INTERFACE_BODY(IShader)

		/// @brief Gets the byte code.
		/// @return Byte code.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> ByteCode() const noexcept = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}

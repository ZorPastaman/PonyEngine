/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:IShader;

import std;

export namespace PonyEngine::RenderDevice
{
	class IShader
	{
		PONY_INTERFACE_BODY(IShader)

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> ByteCode() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		virtual void Name(std::string_view name) = 0;
	};
}

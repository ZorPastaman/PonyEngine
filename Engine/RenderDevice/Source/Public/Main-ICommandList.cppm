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

export module PonyEngine.RenderDevice:ICommandList;

import std;

export namespace PonyEngine::RenderDevice
{
	class ICommandList
	{
		PONY_INTERFACE_BODY(ICommandList)

		virtual void Reset() = 0;
		virtual void Close() = 0;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		virtual void Name(std::string_view name) = 0;
	};
}

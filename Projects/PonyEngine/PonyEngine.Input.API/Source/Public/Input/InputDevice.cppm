/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Base.h"

export module PonyEngine.Input:InputDevice;

import <span>;
import <utility>;

import :InputEntry;

export namespace PonyEngine::Input
{
	class InputDevice
	{
		BASE_BODY(InputDevice)

	public:
		virtual void Begin() = 0;
		virtual void End() = 0;

		virtual void Tick() = 0;

		[[nodiscard("Pure function")]]
		virtual std::span<const InputEntry> GetInputs() const noexcept = 0;
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Input:IInputSystem;

import <functional>;
import <memory>;
import <string_view>;

import :InputHandle;

export namespace PonyEngine::Input
{
	/// @brief Input system.
	class IInputSystem
	{
		INTERFACE_BODY(IInputSystem)

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputHandle> Bind(std::string_view id, const std::function<void(bool)>& action) = 0;
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputHandle> Bind(std::string_view id, const std::function<void(float)>& action) = 0;
	};
}

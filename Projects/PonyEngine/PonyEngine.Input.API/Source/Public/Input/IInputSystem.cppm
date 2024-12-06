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

		/// @brief Binds the action to the input.
		/// @param id Input ID.
		/// @param action Action to bind.
		/// @param magnitudeThreshold Magnitude threshold. The input is @a true if its magnitude is greater than this value.
		/// @return Input handle. It must be kept till the input is needed.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputHandle> Bind(std::string_view id, const std::function<void(bool)>& action, float magnitudeThreshold = 0.2f) = 0;
		/// @brief Binds the action to the input.
		/// @param id Input ID.
		/// @param action Action to bind.
		/// @return Input handle. It must be kept till the input is needed.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputHandle> Bind(std::string_view id, const std::function<void(float)>& action) = 0;
	};
}

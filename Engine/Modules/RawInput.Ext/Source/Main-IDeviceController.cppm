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

export module PonyEngine.RawInput.Ext:IDeviceController;

import std;

import PonyEngine.RawInput;

import :IInputRegistry;

export namespace PonyEngine::RawInput
{
	/// @brief Device controller.
	class IDeviceController
	{
		PONY_INTERFACE_BODY(IDeviceController)

		/// @brief Ticks the controller.
		/// @param inputRegistry Input registry.
		/// @note The function is always called on a main thread.
		virtual void Tick(IInputRegistry& inputRegistry) = 0;

		/// @brief Tries to find a feature of the type @p featureType.
		/// @param featureType Feature type.
		/// @return Feature or nullptr if not found.
		/// @note The function is always called on a main thread.
		[[nodiscard("Pure function")]]
		virtual void* FindFeature(std::type_index featureType) = 0;
	};
}

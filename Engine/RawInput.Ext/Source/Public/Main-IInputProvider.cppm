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

export module PonyEngine.RawInput.Ext:IInputProvider;

export namespace PonyEngine::RawInput
{
	/// @brief Input provider.
	class IInputProvider
	{
		PONY_INTERFACE_BODY(IInputProvider)

		/// @brief Invoked before a first tick.
		/// @note The function is always called on a main thread.
		virtual void Begin() = 0;
		/// @brief Invoked after a last tick.
		/// @note The function is always called on a main thread.
		virtual void End() = 0;
		/// @brief Ticks the provider.
		/// @note The function is always called on a main thread.
		virtual void Tick() = 0;
	};
}

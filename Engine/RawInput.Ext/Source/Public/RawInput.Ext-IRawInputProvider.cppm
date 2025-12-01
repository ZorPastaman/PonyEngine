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

export module PonyEngine.RawInput.Ext:IRawInputProvider;

export namespace PonyEngine::Input
{
	/// @brief Raw input provider.
	/// @note The provider must write to an input service only inside its tick or begin/end.
	class IRawInputProvider
	{
		INTERFACE_BODY(IRawInputProvider)

		/// @brief Invoked before a first tick.
		virtual void Begin() = 0;
		/// @brief Invoked after a last tick.
		virtual void End() = 0;
		/// @brief Ticks the provider.
		virtual void Tick() = 0;
	};
}

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

export module PonyEngine.Input:IInputSystemContext;

import PonyDebug.Log;

import PonyEngine.Core;

import :IDevice;
import :InputEvent;

export namespace PonyEngine::Input
{
	/// @brief Input system context.
	class IInputSystemContext
	{
		INTERFACE_BODY(IInputSystemContext)

		/// @brief Gets the current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const noexcept = 0;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		/// @brief Gets the system manager.
		/// @return System manager.
		[[nodiscard("Pure function")]]
		virtual const Core::ISystemManager& SystemManager() const noexcept = 0;

		/// @brief Is the engine running now?
		/// @return @a True if it's running; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsRunning() const noexcept = 0;

		/// @brief Adds the event to an input queue.
		/// @param inputEvent Input event.
		virtual void AddInputEvent(const InputEvent& inputEvent) = 0;
	};
}

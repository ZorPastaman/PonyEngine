/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.IEngine;

import <cstddef>;

import PonyEngine.Debug.Log.ILogger;

namespace PonyEngine::Core
{
	/// @brief Main Pony Engine interface.
	export class IEngine
	{
	public:
		virtual ~IEngine() noexcept = default;

		/// @brief Gets current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept = 0;

		/// @brief Gets an engine logger.
		/// @return Engine logger.
		[[nodiscard("Pure function")]]
		virtual Debug::Log::ILogger* GetLogger() const noexcept = 0;

		/// @brief Ticks the engine and increments its frame count.
		virtual void Tick() = 0;
	};
}

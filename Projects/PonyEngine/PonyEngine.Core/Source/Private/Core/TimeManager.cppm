/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:TimeManager;

import <cstddef>;

import PonyEngine.Core;

export namespace PonyEngine::Core
{
	/// @brief Engine time manager.
	class TimeManager final : public ITimeManager
	{
	public:
		TimeManager() noexcept = default;
		TimeManager(const TimeManager&) = delete;
		TimeManager(TimeManager&&) = delete;

		~TimeManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept override;

		/// @brief Tick the time manager.
		void Tick() noexcept;

		TimeManager& operator =(const TimeManager&) = delete;
		TimeManager& operator =(TimeManager&&) = delete;

	private:
		std::size_t frameCount; ///< Current frame.
	};
}

namespace PonyEngine::Core
{
	std::size_t TimeManager::GetFrameCount() const noexcept
	{
		return frameCount;
	}

	void TimeManager::Tick() noexcept
	{
		++frameCount;
	}
}

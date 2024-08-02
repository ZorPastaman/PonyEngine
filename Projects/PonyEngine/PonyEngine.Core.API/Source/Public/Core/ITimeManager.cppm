/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ITimeManager;

import <cstddef>;

export namespace PonyEngine::Core
{
	/// @brief Time manager.
	class ITimeManager
	{
	public:
		ITimeManager(const ITimeManager&) = delete;
		ITimeManager(ITimeManager&&) = delete;

		/// @brief Gets the current frame count.
		/// @return Current frame count.
		[[nodiscard("Pure function")]]
		virtual std::size_t GetFrameCount() const noexcept = 0;

		/// @brief Gets the target frame time.
		/// @return Target frame time in seconds. 0 means no target frame time (it's not restricted).
		[[nodiscard("Pure function")]]
		virtual float GetTargetFrameTime() const noexcept = 0;
		/// @brief Sets the target frame time.
		/// @param frameTime Target frame time in seconds. 0 means no target frame time (it's not restricted).
		virtual void SetTargetFrameTime(float frameTime) noexcept = 0;
		/// @brief Gets the target frame rate.
		/// @return Target frame rate in fps. 0 means no target frame rate (it's uncapped).
		[[nodiscard("Pure function")]]
		float GetTargetFrameRate() const noexcept;
		/// @brief Sets the target frame rate.
		/// @param frameRate Target frame rate in fps. 0 means no target frame rate (it's uncapped).
		void SetTargetFrameRate(float frameRate) noexcept;

		ITimeManager& operator =(const ITimeManager&) = delete;
		ITimeManager& operator =(ITimeManager&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ITimeManager() noexcept = default;

		~ITimeManager() noexcept = default;
	};
}

namespace PonyEngine::Core
{
	float ITimeManager::GetTargetFrameRate() const noexcept
	{
		const float frameTime = GetTargetFrameTime();

		return frameTime > 0.f ? 1.f / frameTime : 0.f;
	}

	void ITimeManager::SetTargetFrameRate(const float frameRate) noexcept
	{
		const float frameTime = frameRate > 0.f ? 1.f / frameRate : 0.f;

		SetTargetFrameTime(frameTime);
	}
}
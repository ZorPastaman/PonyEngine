/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time.Factory:IFrameRateSystemFactory;

import PonyEngine.Core.Factory;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory.
	class IFrameRateSystemFactory : public Core::ISystemFactory
	{
	public:
		IFrameRateSystemFactory(const IFrameRateSystemFactory&) = delete;
		IFrameRateSystemFactory(IFrameRateSystemFactory&&) = delete;

		/// @brief Gets the target frame time of the next system.
		/// @return Target frame time in seconds. 0 means no target frame time (it's not restricted).
		[[nodiscard("Pure function")]]
		virtual float TargetFrameTime() const noexcept = 0;
		/// @brief Sets the target frame time of the next system.
		/// @param frameTime Target frame time in seconds. 0 means no target frame time (it's not restricted).
		virtual void TargetFrameTime(float frameTime) noexcept = 0;
		/// @brief Gets the target frame rate of the next system.
		/// @return Target frame rate in fps. 0 means no target frame rate (it's uncapped).
		[[nodiscard("Pure function")]]
		float TargetFrameRate() const noexcept;
		/// @brief Sets the target frame rate of the next system.
		/// @param frameRate Target frame rate in fps. 0 means no target frame rate (it's uncapped).
		void TargetFrameRate(float frameRate) noexcept;

		IFrameRateSystemFactory& operator =(const IFrameRateSystemFactory&) = delete;
		IFrameRateSystemFactory& operator =(IFrameRateSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IFrameRateSystemFactory() noexcept = default;

		~IFrameRateSystemFactory() noexcept = default;
	};
}

namespace PonyEngine::Time
{
	float IFrameRateSystemFactory::TargetFrameRate() const noexcept
	{
		const float frameTime = TargetFrameTime();

		return frameTime > 0.f ? 1.f / frameTime : 0.f;
	}

	void IFrameRateSystemFactory::TargetFrameRate(const float frameRate) noexcept
	{
		const float frameTime = frameRate > 0.f ? 1.f / frameRate : 0.f;
		TargetFrameTime(frameTime);
	}
}

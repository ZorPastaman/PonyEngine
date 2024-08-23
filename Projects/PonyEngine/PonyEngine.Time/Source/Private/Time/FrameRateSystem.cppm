/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time.Implementation:FrameRateSystem;

import <chrono>;

import PonyEngine.Core;
import PonyEngine.Time;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system.
	class FrameRateSystem final : public Core::ISystem, public Core::ITickableSystem, public IFrameRateSystem
	{
	public:
		/// @brief Creates a @p FrameRateSystem.
		/// @param engine Engine that owns the system.
		/// @param frameTime Target frame time.
		[[nodiscard("Pure constructor")]]
		explicit FrameRateSystem(const Core::IEngine& engine, float frameTime) noexcept;
		FrameRateSystem(const FrameRateSystem&) = delete;
		FrameRateSystem(FrameRateSystem&&) = delete;

		~FrameRateSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual float TargetFrameTime() const noexcept override;
		virtual void TargetFrameTime(float frameTime) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		FrameRateSystem& operator =(const FrameRateSystem&) = delete;
		FrameRateSystem& operator =(FrameRateSystem&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Time::FrameRateSystem"; ///< Class name.

	private:
		std::chrono::duration<float> targetFrameTime; ///< Target frame time.
		std::chrono::time_point<std::chrono::steady_clock> previousTickTime; ///< Previous tick time.

		std::size_t frameCount; ///< Current frame.

		const Core::IEngine* const engine; ///< Engine that owns the system.
	};
}

namespace PonyEngine::Time
{
	FrameRateSystem::FrameRateSystem(const Core::IEngine& engine, float frameTime) noexcept :
		targetFrameTime(frameTime),
		frameCount{0},
		engine{&engine}
	{
	}

	void FrameRateSystem::Begin()
	{
	}

	void FrameRateSystem::End()
	{
	}

	void FrameRateSystem::Tick()
	{
		std::chrono::time_point<std::chrono::steady_clock> now;

		do
		{
			now = std::chrono::steady_clock::now();
		} while (std::chrono::duration<float>(now - previousTickTime) < targetFrameTime);

		previousTickTime = now;
	}

	float FrameRateSystem::TargetFrameTime() const noexcept
	{
		return targetFrameTime.count();
	}

	void FrameRateSystem::TargetFrameTime(const float frameTime) noexcept
	{
		targetFrameTime = std::chrono::duration<float>(frameTime);
	}

	const char* FrameRateSystem::Name() const noexcept
	{
		return StaticName;
	}
}
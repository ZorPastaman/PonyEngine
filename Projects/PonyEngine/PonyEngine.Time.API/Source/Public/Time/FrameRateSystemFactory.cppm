/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time:FrameRateSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory.
	class FrameRateSystemFactory : public Core::ISystemFactory
	{
	public:
		FrameRateSystemFactory(const FrameRateSystemFactory&) = delete;
		FrameRateSystemFactory(FrameRateSystemFactory&&) = delete;

		virtual ~FrameRateSystemFactory() noexcept = default;

		FrameRateSystemFactory& operator =(const FrameRateSystemFactory&) = delete;
		FrameRateSystemFactory& operator =(FrameRateSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		FrameRateSystemFactory() noexcept = default;
	};
}

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

		IFrameRateSystemFactory& operator =(const IFrameRateSystemFactory&) = delete;
		IFrameRateSystemFactory& operator =(IFrameRateSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IFrameRateSystemFactory() noexcept = default;

		~IFrameRateSystemFactory() noexcept = default;
	};
}

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

import :FrameRateSystemParams;

export namespace PonyEngine::Time
{
	class IFrameRateSystemFactory : public Core::ISystemFactory
	{
	public:
		IFrameRateSystemFactory(const IFrameRateSystemFactory&) = delete;
		IFrameRateSystemFactory(IFrameRateSystemFactory&&) = delete;

		[[nodiscard("Pure function")]]
		virtual FrameRateSystemParams& SystemParams() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const FrameRateSystemParams& SystemParams() const noexcept = 0;

		IFrameRateSystemFactory& operator =(const IFrameRateSystemFactory&) = delete;
		IFrameRateSystemFactory& operator =(IFrameRateSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IFrameRateSystemFactory() noexcept = default;

		~IFrameRateSystemFactory() noexcept = default;
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderSystemFactory;

import PonyEngine.Core;

export namespace PonyEngine::Render
{
	class RenderSystemFactory : public Core::ISystemFactory
	{
	public:
		RenderSystemFactory(const RenderSystemFactory&) = delete;
		RenderSystemFactory(RenderSystemFactory&&) = delete;

		virtual ~RenderSystemFactory() noexcept = default;

		RenderSystemFactory& operator =(const RenderSystemFactory&) = delete;
		RenderSystemFactory& operator =(RenderSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		RenderSystemFactory() noexcept = default;
	};
}

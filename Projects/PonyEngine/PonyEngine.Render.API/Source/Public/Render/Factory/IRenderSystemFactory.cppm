/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Factory:IRenderSystemFactory;

import :RenderParams;

export namespace PonyEngine::Render
{
	class IRenderSystemFactory
	{
	public:
		IRenderSystemFactory(const IRenderSystemFactory&) = delete;
		IRenderSystemFactory(IRenderSystemFactory&&) = delete;

		[[nodiscard("Pure function")]]
		virtual RenderParams& RenderSystemParams() noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const RenderParams& RenderSystemParams() const noexcept = 0;

		IRenderSystemFactory& operator =(const IRenderSystemFactory&) = delete;
		IRenderSystemFactory& operator =(IRenderSystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderSystemFactory() noexcept = default;

		~IRenderSystemFactory() noexcept = default;
	};
}

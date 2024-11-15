/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:IRendererContext;

import PonyDebug.Log;

export namespace PonyEngine::Render
{
	class IRendererContext
	{
	public:
		IRendererContext(const IRendererContext&) = delete;
		IRendererContext(IRendererContext&&) = delete;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		IRendererContext& operator =(const IRendererContext&) = delete;
		IRendererContext& operator =(IRendererContext&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRendererContext() noexcept = default;

		~IRendererContext() noexcept = default;
	};
}

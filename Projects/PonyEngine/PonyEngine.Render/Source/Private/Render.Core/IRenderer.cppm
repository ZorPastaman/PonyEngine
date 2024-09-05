/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Core:IRenderer;

import PonyEngine.Core;

export namespace PonyEngine::Render
{
	class IRenderer
	{
	public:
		IRenderer(const IRenderer&) = delete;
		IRenderer(IRenderer&&) = delete;

		[[nodiscard("Pure function")]]
		virtual Core::IEngine& Engine() const noexcept = 0; // TODO: Don't return a parent context. The main reason to use it here is access to a logger. I should add a better logging system with wrappers in each context and with single Macro system.

		IRenderer& operator =(const IRenderer&) = delete;
		IRenderer& operator =(IRenderer&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderer() noexcept = default;

		~IRenderer() noexcept = default;
	};
}

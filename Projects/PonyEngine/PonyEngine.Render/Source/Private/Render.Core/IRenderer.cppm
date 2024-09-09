/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Core:IRenderer;

import PonyDebug.Log;

export namespace PonyEngine::Render
{
	class IRenderer
	{
	public:
		IRenderer(const IRenderer&) = delete;
		IRenderer(IRenderer&&) = delete;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept = 0;

		IRenderer& operator =(const IRenderer&) = delete;
		IRenderer& operator =(IRenderer&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderer() noexcept = default;

		~IRenderer() noexcept = default;
	};
}

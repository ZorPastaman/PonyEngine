/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:IRenderTarget;

import PonyMath.Color;

export namespace PonyEngine::Render
{
	class IRenderTarget
	{
	public:
		IRenderTarget(const IRenderTarget&) = delete;
		IRenderTarget(IRenderTarget&&) = delete;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> ClearColor() const noexcept = 0;
		virtual void ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept = 0;

		IRenderTarget& operator =(const IRenderTarget&) = delete;
		IRenderTarget& operator =(IRenderTarget&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderTarget() noexcept = default; // TODO: Make INTERFACE_BODY() macro

		~IRenderTarget() noexcept = default;
	};
}

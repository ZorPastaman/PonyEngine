/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:IRenderSystem;

import PonyBase.Math;

export namespace PonyEngine::Render
{
	/// @brief Render system.
	class IRenderSystem
	{
	public:
		IRenderSystem(const IRenderSystem&) = delete;
		IRenderSystem(IRenderSystem&&) = delete;

		[[nodiscard("Pure function")]]
		virtual PonyBase::Math::RGBA<float> ClearColor() const noexcept = 0;
		virtual void ClearColor(const PonyBase::Math::RGBA<float>& color) noexcept = 0;

		IRenderSystem& operator =(const IRenderSystem&) = delete;
		IRenderSystem& operator =(IRenderSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderSystem() noexcept = default;

		~IRenderSystem() noexcept = default;
	};
}

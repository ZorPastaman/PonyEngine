/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:IRenderSystem;

import <string_view>;

import :IRenderObjectManager;
import :IRenderTarget;
import :IRenderView;

export namespace PonyEngine::Render
{
	/// @brief Render system.
	class IRenderSystem
	{
	public:
		IRenderSystem(const IRenderSystem&) = delete;
		IRenderSystem(IRenderSystem&&) = delete;

		[[nodiscard("Pure function")]]
		virtual IRenderTarget& RenderTarget() const noexcept = 0; // TODO: make const, non-const pairs of functions. Return const from const only.
		[[nodiscard("Pure function")]]
		virtual IRenderView& RenderView() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual IRenderObjectManager& RenderObjectManager() const noexcept = 0;

		/// @brief Gets the system name.
		/// @return System name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;

		IRenderSystem& operator =(const IRenderSystem&) = delete;
		IRenderSystem& operator =(IRenderSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IRenderSystem() noexcept = default;

		~IRenderSystem() noexcept = default;
	};
}

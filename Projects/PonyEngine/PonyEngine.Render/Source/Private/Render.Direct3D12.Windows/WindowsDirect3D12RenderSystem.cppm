/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Windows.Implementation:WindowsDirect3D12RenderSystem;

import PonyEngine.Core;
import PonyEngine.Render;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows.
	class WindowsDirect3D12RenderSystem final : public Core::ISystem, public Core::ITickableSystem, public IRenderSystem
	{
	public:
		/// @brief Creates a @p WindowsDirect3D12RenderSystem.
		/// @param engine Engine.
		[[nodiscard("Pure constructor")]]
		explicit WindowsDirect3D12RenderSystem(Core::IEngine& engine) noexcept;
		WindowsDirect3D12RenderSystem(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem(WindowsDirect3D12RenderSystem&&) = delete;

		~WindowsDirect3D12RenderSystem() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsDirect3D12RenderSystem& operator =(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem& operator =(WindowsDirect3D12RenderSystem&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystem"; ///< Class name.

	private:
		Core::IEngine* engine; ///< Engine.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystem::WindowsDirect3D12RenderSystem(Core::IEngine& engine) noexcept :
		engine{&engine}
	{
	}

	void WindowsDirect3D12RenderSystem::Begin()
	{
	}

	void WindowsDirect3D12RenderSystem::End()
	{
	}

	void WindowsDirect3D12RenderSystem::Tick()
	{
	}

	const char* WindowsDirect3D12RenderSystem::Name() const noexcept
	{
		return StaticName;
	}
}

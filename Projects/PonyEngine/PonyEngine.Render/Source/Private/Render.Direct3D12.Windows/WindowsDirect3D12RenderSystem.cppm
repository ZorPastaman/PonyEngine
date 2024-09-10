/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Windows.Implementation:WindowsDirect3D12RenderSystem;

import <stdexcept>;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Render;
import PonyEngine.Window.Windows;

import PonyEngine.Render.Core;
import PonyEngine.Render.Direct3D12;
import PonyEngine.Render.DXGI;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows.
	class WindowsDirect3D12RenderSystem final : public Core::ISystem, public Core::ITickableSystem, public IRenderSystem, public IRenderer
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
		virtual PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsDirect3D12RenderSystem& operator =(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem& operator =(WindowsDirect3D12RenderSystem&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystem"; ///< Class name.

	private:
		Core::IEngine* engine; ///< Engine.

		DXGISubSystem dxgiSubSystem; ///< DXGI sub-system.
		Direct3D12SubSystem direct3D12SubSystem; ///< Direct3D 12 sub-system.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystem::WindowsDirect3D12RenderSystem(Core::IEngine& engine) noexcept :
		engine{&engine},
		dxgiSubSystem(*this),
		direct3D12SubSystem(*this)
	{
	}

	void WindowsDirect3D12RenderSystem::Begin()
	{
		dxgiSubSystem.CreateFence(direct3D12SubSystem.GetDevice(), direct3D12SubSystem.GetCommandQueue());

		if (const auto windowSystem = engine->SystemManager().FindSystem<Window::IWindowsWindowSystem>())
		{
			dxgiSubSystem.CreateSwapChain(direct3D12SubSystem.GetCommandQueue(), windowSystem->WindowHandle());
		}
		else
		{
			throw std::runtime_error("Failed to find Windows window system.");
		}
	}

	void WindowsDirect3D12RenderSystem::End()
	{
	}

	void WindowsDirect3D12RenderSystem::Tick()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Tick Direct3D 12 sub-system.");
		direct3D12SubSystem.Tick();
		dxgiSubSystem.Tick();
	}

	PonyDebug::Log::ILogger& WindowsDirect3D12RenderSystem::Logger() const noexcept
	{
		return engine->Logger();
	}

	const char* WindowsDirect3D12RenderSystem::Name() const noexcept
	{
		return StaticName;
	}
}

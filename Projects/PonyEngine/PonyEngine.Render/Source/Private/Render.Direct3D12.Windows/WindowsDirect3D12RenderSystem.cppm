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

#include "PonyEngine/Render/Direct3D12/Framework.h"
#include "PonyEngine/Render/DXGI/Framework.h"

export module PonyEngine.Render.Direct3D12.Windows.Implementation:WindowsDirect3D12RenderSystem;

import <stdexcept>;
import <type_traits>;

import PonyEngine.Render.Direct3D12.Windows.Factory;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;
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
		/// @param params Render system parameters.
		[[nodiscard("Pure constructor")]]
		WindowsDirect3D12RenderSystem(Core::IEngine& engine, const WindowsDirect3D12RenderParams& params);
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
		static constexpr UINT BufferCount = 2u; ///< Buffer count.

		Core::IEngine* engine; ///< Engine.

		DXGISubSystem dxgiSubSystem; ///< DXGI sub-system.
		Direct3D12SubSystem direct3D12SubSystem; ///< Direct3D 12 sub-system.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystem::WindowsDirect3D12RenderSystem(Core::IEngine& engine, const WindowsDirect3D12RenderParams& params) :
		engine{&engine},
		dxgiSubSystem(*this, BufferCount, params.resolution),
		direct3D12SubSystem(*this, BufferCount, params.featureLevel, params.commandQueuePriority, params.fenceTimeout)
	{
	}

	void WindowsDirect3D12RenderSystem::Begin()
	{
		if (const auto windowSystem = engine->SystemManager().FindSystem<Window::IWindowsWindowSystem>())
		{
			dxgiSubSystem.AcquireSwapChain(direct3D12SubSystem.GetCommandQueue(), windowSystem->WindowHandle());
		}
		else
		{
			throw std::runtime_error("Failed to find Windows window system.");
		}

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Get swap chain buffers.");
		IDXGISwapChain4* const swapChain = dxgiSubSystem.GetSwapChain();
		for (UINT i = 0u; i < BufferCount; ++i)
		{
			if (const HRESULT result = swapChain->GetBuffer(i, IID_PPV_ARGS(direct3D12SubSystem.GetBufferPointer(i))); FAILED(result))
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get swap chain buffer at index '{}' with '0x{:X}' result.", i, static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
		}
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Swap chain buffers gotten.");
	}

	void WindowsDirect3D12RenderSystem::End()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Wait for end of frame of Direct3D 12 sub-system.");
		direct3D12SubSystem.WaitForEndOfFrame();
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "End of frame of Direct3D 12 sub-system waited for.");
	}

	void WindowsDirect3D12RenderSystem::Tick()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Clear Direct3D 12 sub-system.");
		direct3D12SubSystem.Clear();
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Execute Direct3D 12 sub-system.");
		direct3D12SubSystem.Execute();
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Present DXGI sub-system.");
		dxgiSubSystem.Present();
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Wait for end of frame of Direct3D 12 sub-system.");
		direct3D12SubSystem.WaitForEndOfFrame();
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

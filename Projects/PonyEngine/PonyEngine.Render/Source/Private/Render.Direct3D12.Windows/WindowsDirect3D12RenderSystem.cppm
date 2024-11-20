/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Windows/Framework.h"
#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Windows.Detail:WindowsDirect3D12RenderSystem;

import <array>;
import <cstdint>;
import <memory>;
import <optional>;
import <span>;
import <stdexcept>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Geometry;
import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Window.Windows;

import PonyEngine.Render.Direct3D12.Windows;

import PonyEngine.Render.Detail;
import PonyEngine.Render.Direct3D12.Detail;

import :WindowsDirect3D12DXGISubSystem;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows.
	class WindowsDirect3D12RenderSystem final : public Core::TickableSystem, public IWindowsDirect3D12RenderSystem, public IRenderContext
	{
	public:
		/// @brief Creates a @p WindowsDirect3D12RenderSystem.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param renderParams Render system parameters.
		[[nodiscard("Pure constructor")]]
		WindowsDirect3D12RenderSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowsDirect3D12RenderSystemParams& renderParams);
		WindowsDirect3D12RenderSystem(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem(WindowsDirect3D12RenderSystem&&) = delete;

		virtual ~WindowsDirect3D12RenderSystem() noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderTarget& RenderTarget() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderTarget& RenderTarget() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderView& RenderView() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderView& RenderView() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderObjectManager& RenderObjectManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderObjectManager& RenderObjectManager() const noexcept override;

		WindowsDirect3D12RenderSystem& operator =(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem& operator =(WindowsDirect3D12RenderSystem&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		std::unique_ptr<WindowsDirect3D12DXGISubSystem> CreateDXGISubSystem();
		[[nodiscard("Pure function")]]
		std::unique_ptr<Direct3D12SubSystem> CreateDirect3D12SubSystem(const Direct3D12RenderSystemParams& params);

		static constexpr UINT BufferCount = 2u; ///< Buffer count.
		static constexpr DXGI_FORMAT RtvFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

		std::unique_ptr<WindowsDirect3D12DXGISubSystem> dxgiSubSystem; ///< DXGI sub-system.
		std::unique_ptr<Direct3D12SubSystem> direct3D12SubSystem; ///< Direct3D 12 sub-system.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystem::WindowsDirect3D12RenderSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowsDirect3D12RenderSystemParams& renderParams) :
		TickableSystem(engine, systemParams),
		dxgiSubSystem(CreateDXGISubSystem()),
		direct3D12SubSystem(CreateDirect3D12SubSystem(renderParams))
	{
		PonyMath::Utility::Resolution<UINT> renderResolution;

		if (const auto windowSystem = Engine().SystemManager().FindSystem<Window::IWindowsWindowSystem>()) [[likely]]
		{
			const HWND windowHandle = windowSystem->WindowHandle();

			if (renderParams.renderViewParams.resolution.has_value())
			{
				renderResolution = static_cast<PonyMath::Utility::Resolution<UINT>>(renderParams.renderViewParams.resolution.value());
				PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Use custom resolution: '{}'.", renderResolution.ToString());
			}
			else
			{
				renderResolution = static_cast<PonyMath::Utility::Resolution<UINT>>(windowSystem->Resolution());
				PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Use window resolution.");
			}

			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Initialize DXGI sub-system.");
			dxgiSubSystem->Initialize(direct3D12SubSystem->GetCommandQueue(), windowHandle, renderResolution, RtvFormat, BufferCount);
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system initialized.");
		}
		else [[unlikely]]
		{
			throw std::runtime_error("Failed to find Windows window system.");
		}

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Get swap chain buffers.");
		std::array<Microsoft::WRL::ComPtr<ID3D12Resource2>, BufferCount> backBuffers;
		for (UINT i = 0u; i < BufferCount; ++i)
		{
			if (const HRESULT result = dxgiSubSystem->GetBuffer(i, backBuffers[i].GetAddressOf()); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get swap chain buffer at index '{}' with '0x{:X}' result.", i, static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Buffer at index '{}' gotten at '0x{:X}'.", i, reinterpret_cast<std::uintptr_t>(backBuffers[i].Get()));
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Swap chain buffers gotten.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Initialize Direct3D 12 sub-system.");
		std::array<ID3D12Resource2*, BufferCount> rawBackBuffers;
		for (std::size_t i = 0; i < BufferCount; ++i)
		{
			rawBackBuffers[i] = backBuffers[i].Get();
		}

		direct3D12SubSystem->Initialize(renderResolution, rawBackBuffers);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 sub-system initialized.");
	}

	WindowsDirect3D12RenderSystem::~WindowsDirect3D12RenderSystem() noexcept
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 sub-system.");
		direct3D12SubSystem.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 sub-system destroyed.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy DXGI sub-system.");
		dxgiSubSystem.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system destroyed.");
	}

	void WindowsDirect3D12RenderSystem::Begin()
	{
	}

	void WindowsDirect3D12RenderSystem::End()
	{
	}

	void WindowsDirect3D12RenderSystem::Tick()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Populate commands.");
		direct3D12SubSystem->PopulateCommands(dxgiSubSystem->GetCurrentBackBufferIndex());
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Execute.");
		direct3D12SubSystem->Execute();

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Present.");
		dxgiSubSystem->Present();

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Wait for end of previous frame.");
		direct3D12SubSystem->WaitForEndOfFrame();
	}

	PonyDebug::Log::ILogger& WindowsDirect3D12RenderSystem::Logger() noexcept
	{
		return Engine().Logger();
	}

	const PonyDebug::Log::ILogger& WindowsDirect3D12RenderSystem::Logger() const noexcept
	{
		return Engine().Logger();
	}

	IDirect3D12RenderTarget& WindowsDirect3D12RenderSystem::RenderTarget() noexcept
	{
		return *direct3D12SubSystem->RenderTarget();
	}

	const IDirect3D12RenderTarget& WindowsDirect3D12RenderSystem::RenderTarget() const noexcept
	{
		return *direct3D12SubSystem->RenderTarget();
	}

	IDirect3D12RenderView& WindowsDirect3D12RenderSystem::RenderView() noexcept
	{
		return *direct3D12SubSystem->RenderView();
	}

	const IDirect3D12RenderView& WindowsDirect3D12RenderSystem::RenderView() const noexcept
	{
		return *direct3D12SubSystem->RenderView();
	}

	IDirect3D12RenderObjectManager& WindowsDirect3D12RenderSystem::RenderObjectManager() noexcept
	{
		return *direct3D12SubSystem->RenderObjectManager();
	}

	const IDirect3D12RenderObjectManager& WindowsDirect3D12RenderSystem::RenderObjectManager() const noexcept
	{
		return *direct3D12SubSystem->RenderObjectManager();
	}

	std::unique_ptr<WindowsDirect3D12DXGISubSystem> WindowsDirect3D12RenderSystem::CreateDXGISubSystem()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create DXGI sub-system.");
		auto createdDxgiSubSystem = std::make_unique<WindowsDirect3D12DXGISubSystem>(*this);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system created.");

		return createdDxgiSubSystem;
	}

	std::unique_ptr<Direct3D12SubSystem> WindowsDirect3D12RenderSystem::CreateDirect3D12SubSystem(const Direct3D12RenderSystemParams& params)
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 sub-system.");
		auto createdDirect3D12SubSystem = std::make_unique<Direct3D12SubSystem>(*this, params, RtvFormat);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 sub-system created.");

		return createdDirect3D12SubSystem;
	}
}

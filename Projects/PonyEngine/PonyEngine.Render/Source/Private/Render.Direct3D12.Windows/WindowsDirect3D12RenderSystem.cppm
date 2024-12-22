/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"
#include "PonyBase/Core/DXGI/Framework.h"
#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Windows.Detail:WindowsDirect3D12RenderSystem;

import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Render.Direct3D12.Windows;
import PonyEngine.Render.Direct3D12.Detail;
import PonyEngine.Render.DXGI.Detail;
import PonyEngine.Window.Windows;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows.
	class WindowsDirect3D12RenderSystem final : public Core::TickableSystem, public IWindowsDirect3D12RenderSystem, private IDXGIRenderSystemContext, private IDirect3D12RenderSystemContext
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

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;

		virtual void Tick() override;

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
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IUnknown* Device() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IUnknown* Device() const noexcept override;

		std::unique_ptr<DXGISystem> dxgiSubSystem; ///< DXGI sub-system.
		std::unique_ptr<Direct3D12System> direct3D12SubSystem; ///< Direct3D12 sub-system.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystem::WindowsDirect3D12RenderSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const WindowsDirect3D12RenderSystemParams& renderParams) :
		TickableSystem(engine, systemParams)
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create DXGI sub-system.");
		dxgiSubSystem = std::make_unique<DXGISystem>(*static_cast<IDXGIRenderSystemContext*>(this));
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(dxgiSubSystem.get()));

		PonyMath::Utility::Resolution<UINT> renderResolution;
		HWND windowHandle;
		if (const auto windowSystem = Engine().SystemManager().FindSystem<Window::IWindowsWindowSystem>()) [[likely]]
		{
			windowHandle = windowSystem->WindowHandle();

			if (renderParams.renderTargetParams.resolution.has_value())
			{
				renderResolution = static_cast<PonyMath::Utility::Resolution<UINT>>(renderParams.renderTargetParams.resolution.value());
				PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Use custom resolution: '{}'.", renderResolution.ToString());
			}
			else
			{
				renderResolution = PonyMath::Utility::Resolution<UINT>(static_cast<PonyMath::Core::Vector2<UINT>>(windowSystem->WindowClientRect().Size()));
				PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Use window resolution.");
			}
		}
		else [[unlikely]]
		{
			throw std::runtime_error("Failed to find Windows window system.");
		}

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D12 sub-system.");
		const auto direct3D12SystemParams = Direct3D12SystemParams
		{
			.featureLevel = D3D_FEATURE_LEVEL_12_2,
			.commandQueuePriority = renderParams.commandQueuePriority,
			.renderTimeout = renderParams.renderTimeout,
		};
		direct3D12SubSystem = std::make_unique<Direct3D12System>(*static_cast<IDirect3D12RenderSystemContext*>(this), direct3D12SystemParams);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D12 sub-system created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(direct3D12SubSystem.get()));

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create swap chain.");
		const UINT bufferCount = renderParams.swapChainParams.bufferCount;
		const auto swapChainParams = DXGISwapChainParams
		{
			.hWnd = windowHandle,
			.resolution = renderResolution,
			.rtvFormat = renderParams.swapChainParams.rtvFormat,
			.bufferCount = bufferCount
		};
		IDXGISwapChain& swapChain = dxgiSubSystem->CreateSwapChain(swapChainParams);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Swap chain created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&swapChain));

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Get swap chain buffers.");
		auto backBufferParams = Direct3D12BackBufferParams
		{
			.backBufferFormat = swapChainParams.rtvFormat,
		};
		backBufferParams.backBuffers.reserve(bufferCount);
		for (UINT i = 0u; i < bufferCount; ++i)
		{
			Microsoft::WRL::ComPtr<ID3D12Resource2> backBuffer;
			if (const HRESULT result = dxgiSubSystem->SwapChain()->GetBackBuffer(i, backBuffer.GetAddressOf()); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get swap chain buffer at index '{}' with '0x{:X}' result.", i, static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
			backBufferParams.backBuffers.push_back(backBuffer);
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Buffer at index '{}' gotten at '0x{:X}'.", i, reinterpret_cast<std::uintptr_t>(backBuffer.Get()));
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Swap chain buffers gotten.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create render system.");
		const auto renderTargetParams = Direct3D12RenderTargetParams
		{
			.resolution = renderResolution,
			.clearColor = renderParams.renderTargetParams.clearColor,
			.msaaParams = renderParams.renderTargetParams.msaaParams
		};
		const auto renderViewParams = Direct3D12RenderViewParams
		{
			.viewMatrix = static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(renderParams.renderViewParams.viewMatrix),
			.projectionMatrix = static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(renderParams.renderViewParams.projectionMatrix)
		};
		direct3D12SubSystem->CreateRenderSystem(backBufferParams, renderTargetParams, renderViewParams);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Render system created.");
	}

	WindowsDirect3D12RenderSystem::~WindowsDirect3D12RenderSystem() noexcept
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D12 sub-system.");
		direct3D12SubSystem.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D12 sub-system destroyed.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy DXGI sub-system.");
		dxgiSubSystem.reset();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system destroyed.");
	}

	void WindowsDirect3D12RenderSystem::Begin() noexcept
	{
	}

	void WindowsDirect3D12RenderSystem::End() noexcept
	{
	}

	void WindowsDirect3D12RenderSystem::Tick()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Begin frame.");
		direct3D12SubSystem->BeginFrame();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Render.");
		direct3D12SubSystem->Render(dxgiSubSystem->SwapChain()->GetCurrentBackBufferIndex());
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Present.");
		dxgiSubSystem->Present();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Wait for end of frame.");
		direct3D12SubSystem->EndFrame();
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

	PonyDebug::Log::ILogger& WindowsDirect3D12RenderSystem::Logger() noexcept
	{
		return Engine().Logger();
	}

	const PonyDebug::Log::ILogger& WindowsDirect3D12RenderSystem::Logger() const noexcept
	{
		return Engine().Logger();
	}

	IUnknown* WindowsDirect3D12RenderSystem::Device() noexcept
	{
		return &direct3D12SubSystem->GraphicsCommandQueue();
	}

	const IUnknown* WindowsDirect3D12RenderSystem::Device() const noexcept
	{
		return &direct3D12SubSystem->GraphicsCommandQueue();
	}
}

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

export module PonyEngine.Render.Direct3D12.Windows.Detail:RenderSystem;

import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyBase.Utility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Render.Direct3D12.Windows;
import PonyEngine.Render.Direct3D12.Detail;
import PonyEngine.Render.DXGI.Detail;
import PonyEngine.Window.Windows;

export namespace PonyEngine::Render::Direct3D12::Windows
{
	/// @brief Direct3D 12 render system for Windows.
	class RenderSystem final : public Core::TickableSystem, public IRenderSystem, private Direct3D12::IRenderSystemContext, private DXGI::IRenderSystemContext
	{
	public:
		/// @brief Creates a @p RenderSystem.
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param renderParams Render system parameters.
		[[nodiscard("Pure constructor")]]
		RenderSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const RenderSystemParams& renderParams);
		RenderSystem(const RenderSystem&) = delete;
		RenderSystem(RenderSystem&&) = delete;

		virtual ~RenderSystem() noexcept override;

		virtual void Begin() noexcept override;
		virtual void End() noexcept override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual IRenderTarget& RenderTarget() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IRenderTarget& RenderTarget() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual IRenderView& RenderView() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IRenderView& RenderView() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual IRenderObjectManager& RenderObjectManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IRenderObjectManager& RenderObjectManager() const noexcept override;

		RenderSystem& operator =(const RenderSystem&) = delete;
		RenderSystem& operator =(RenderSystem&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IUnknown* Device() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IUnknown* Device() const noexcept override;

		std::unique_ptr<DXGI::SubSystem> dxgiSubSystem; ///< DXGI sub-system.
		std::unique_ptr<Direct3D12::SubSystem> direct3D12SubSystem; ///< Direct3D12 sub-system.
	};
}

namespace PonyEngine::Render::Direct3D12::Windows
{
	RenderSystem::RenderSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const RenderSystemParams& renderParams) :
		TickableSystem(engine, systemParams)
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create DXGI sub-system.");
		dxgiSubSystem = std::make_unique<DXGI::SubSystem>(*static_cast<DXGI::IRenderSystemContext*>(this));
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system created.");

		PonyMath::Utility::Resolution<UINT> renderResolution;
		HWND windowHandle;
		if (const auto windowSystem = Engine().SystemManager().FindSystem<Window::Windows::IWindowSystem>()) [[likely]]
		{
			windowHandle = windowSystem->WindowHandle();

			if (renderParams.renderTargetParams.resolution.has_value())
			{
				renderResolution = static_cast<PonyMath::Utility::Resolution<UINT>>(renderParams.renderTargetParams.resolution.value());
				PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Use custom resolution: '{}'.", renderResolution.ToString());
			}
			else
			{
				renderResolution = PonyMath::Utility::Resolution<UINT>(static_cast<PonyMath::Core::Vector2<UINT>>(windowSystem->WindowClientRect().Size()));
				PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Use window resolution: '{}'.", renderResolution.ToString());
			}
		}
		else [[unlikely]]
		{
			throw std::runtime_error("Failed to find Windows window system.");
		}

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D12 sub-system.");
		const auto direct3D12SystemParams = Direct3D12::SubSystemParams
		{
			.featureLevel = D3D_FEATURE_LEVEL_12_2,
			.commandQueuePriority = renderParams.commandQueuePriority,
			.renderTimeout = renderParams.renderTimeout,
		};
		direct3D12SubSystem = std::make_unique<Direct3D12::SubSystem>(*static_cast<Direct3D12::IRenderSystemContext*>(this), direct3D12SystemParams);
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Direct3D12 sub-system created.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create swap chain.");
		const UINT bufferCount = renderParams.swapChainParams.bufferCount;
		const auto swapChainParams = DXGI::SwapChainParams
		{
			.hWnd = windowHandle,
			.resolution = renderResolution,
			.bufferCount = bufferCount
		};
		const DXGI::ISwapChain& swapChain = dxgiSubSystem->CreateSwapChain(swapChainParams);
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Swap chain created.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Get swap chain buffers.");
		auto backParams = Direct3D12::BackParams
		{
			.backViewFormat = swapChain.Format(),
		};
		backParams.backBuffers.reserve(bufferCount);
		for (UINT i = 0u; i < bufferCount; ++i)
		{
			Microsoft::WRL::ComPtr<ID3D12Resource2> backBuffer;
			if (const HRESULT result = swapChain.GetBackBuffer(i, backBuffer.GetAddressOf()); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get swap chain buffer at index '{}' with '0x{:X}' result.", i, static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
			backParams.backBuffers.push_back(backBuffer);
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Swap chain buffers gotten.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create render system.");
		const auto renderTargetParams = Direct3D12::RenderTargetParams
		{
			.resolution = renderResolution,
			.clearColor = renderParams.renderTargetParams.clearColor,
			.msaaParams = renderParams.renderTargetParams.msaaParams
		};
		const auto renderViewParams = Direct3D12::RenderViewParams
		{
			.viewMatrix = static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(renderParams.renderViewParams.viewMatrix),
			.projectionMatrix = static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(renderParams.renderViewParams.projectionMatrix)
		};
		direct3D12SubSystem->CreateRenderSystem(backParams, renderTargetParams, renderViewParams);
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Render system created.");
	}

	RenderSystem::~RenderSystem() noexcept
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D12 sub-system.");
		direct3D12SubSystem.reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Direct3D12 sub-system destroyed.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy DXGI sub-system.");
		dxgiSubSystem.reset();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system destroyed.");
	}

	void RenderSystem::Begin() noexcept
	{
	}

	void RenderSystem::End() noexcept
	{
	}

	void RenderSystem::Tick()
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Begin frame.");
		direct3D12SubSystem->BeginFrame();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Render.");
		direct3D12SubSystem->Render(dxgiSubSystem->SwapChain()->GetCurrentBackBufferIndex());
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Present.");
		dxgiSubSystem->Present();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "End frame.");
		direct3D12SubSystem->EndFrame();
	}

	IRenderTarget& RenderSystem::RenderTarget() noexcept
	{
		return *direct3D12SubSystem->RenderTarget();
	}

	const IRenderTarget& RenderSystem::RenderTarget() const noexcept
	{
		return *direct3D12SubSystem->RenderTarget();
	}

	IRenderView& RenderSystem::RenderView() noexcept
	{
		return *direct3D12SubSystem->RenderView();
	}

	const IRenderView& RenderSystem::RenderView() const noexcept
	{
		return *direct3D12SubSystem->RenderView();
	}

	IRenderObjectManager& RenderSystem::RenderObjectManager() noexcept
	{
		return *direct3D12SubSystem->RenderObjectManager();
	}

	const IRenderObjectManager& RenderSystem::RenderObjectManager() const noexcept
	{
		return *direct3D12SubSystem->RenderObjectManager();
	}

	PonyDebug::Log::ILogger& RenderSystem::Logger() noexcept
	{
		return Engine().Logger();
	}

	const PonyDebug::Log::ILogger& RenderSystem::Logger() const noexcept
	{
		return Engine().Logger();
	}

	IUnknown* RenderSystem::Device() noexcept
	{
		return &direct3D12SubSystem->GraphicsCommandQueue();
	}

	const IUnknown* RenderSystem::Device() const noexcept
	{
		return &direct3D12SubSystem->GraphicsCommandQueue();
	}
}

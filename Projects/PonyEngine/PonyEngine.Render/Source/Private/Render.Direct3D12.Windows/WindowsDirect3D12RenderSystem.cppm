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

export module PonyEngine.Render.Direct3D12.Windows.Implementation:WindowsDirect3D12RenderSystem;

import <array>;
import <cstdint>;
import <memory>;
import <optional>;
import <span>;
import <stdexcept>;
import <string_view>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Geometry;
import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Window.Windows;

import PonyEngine.Render.Direct3D12.Windows.Factory;

import PonyEngine.Render.Core;
import PonyEngine.Render.Direct3D12.Implementation;

import :WindowsDirect3D12DXGISubSystem;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 render system for Windows.
	class WindowsDirect3D12RenderSystem final : public Core::ITickableEngineSystem, public IWindowsDirect3D12RenderSystem, public IRenderer
	{
	public:
		/// @brief Creates a @p WindowsDirect3D12RenderSystem.
		/// @param engine Engine.
		/// @param params Render system parameters.
		[[nodiscard("Pure constructor")]]
		WindowsDirect3D12RenderSystem(Core::IEngineContext& engine, const WindowsDirect3D12RenderSystemParams& params);
		WindowsDirect3D12RenderSystem(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem(WindowsDirect3D12RenderSystem&&) = delete;

		~WindowsDirect3D12RenderSystem() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IRenderTarget& RenderTarget() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual IRenderView& RenderView() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual IRenderObjectManager& RenderObjectManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsDirect3D12RenderSystem& operator =(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem& operator =(WindowsDirect3D12RenderSystem&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystem"; ///< Class name.

	private:
		[[nodiscard("Pure function")]]
		std::unique_ptr<WindowsDirect3D12DXGISubSystem> CreateDXGISubSystem();
		[[nodiscard("Pure function")]]
		std::unique_ptr<Direct3D12SubSystem> CreateDirect3D12SubSystem(D3D_FEATURE_LEVEL featureLevel, INT commandQueuePriority, DWORD fenceTimeout);

		static constexpr UINT BufferCount = 2u; ///< Buffer count.
		static constexpr DXGI_FORMAT RtvFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

		Core::IEngineContext* engine; ///< Engine.

		std::unique_ptr<WindowsDirect3D12DXGISubSystem> dxgiSubSystem; ///< DXGI sub-system.
		std::unique_ptr<Direct3D12SubSystem> direct3D12SubSystem; ///< Direct3D 12 sub-system.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystem::WindowsDirect3D12RenderSystem(Core::IEngineContext& engine, const WindowsDirect3D12RenderSystemParams& params) :
		engine{&engine},
		dxgiSubSystem(CreateDXGISubSystem()),
		direct3D12SubSystem(CreateDirect3D12SubSystem(params.featureLevel, params.commandQueuePriority, params.fenceTimeout))
	{
		PonyMath::Utility::Resolution<UINT> renderResolution;

		if (const auto windowSystem = this->engine->SystemManager().FindSystem<Window::IWindowsWindowSystem>()) [[likely]]
		{
			const HWND windowHandle = windowSystem->WindowHandle();

			if (params.resolution.has_value())
			{
				renderResolution = static_cast<PonyMath::Utility::Resolution<UINT>>(params.resolution.value());
				PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Debug, "Use custom resolution: '{}'.", renderResolution.ToString());
			}
			else
			{
				renderResolution = static_cast<PonyMath::Utility::Resolution<UINT>>(windowSystem->Resolution());
				PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Debug, "Use window resolution.");
			}

			PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Info, "Initialize DXGI sub-system.");
			dxgiSubSystem->Initialize(direct3D12SubSystem->GetCommandQueue(), windowHandle, renderResolution, RtvFormat, BufferCount);
			PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system initialized.");
		}
		else [[unlikely]]
		{
			throw std::runtime_error("Failed to find Windows window system.");
		}

		PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Info, "Get swap chain buffers.");
		std::array<Microsoft::WRL::ComPtr<ID3D12Resource2>, BufferCount> backBuffers;
		for (UINT i = 0u; i < BufferCount; ++i)
		{
			if (const HRESULT result = dxgiSubSystem->GetBuffer(i, backBuffers[i].GetAddressOf()); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get swap chain buffer at index '{}' with '0x{:X}' result.", i, static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
			PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Info, "Buffer at index '{}' gotten at '0x{:X}'.", i, reinterpret_cast<std::uintptr_t>(backBuffers[i].Get()));
		}
		PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Info, "Swap chain buffers gotten.");

		PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Info, "Initialize Direct3D 12 sub-system.");
		std::array<ID3D12Resource2*, BufferCount> rawBackBuffers;
		for (std::size_t i = 0; i < BufferCount; ++i)
		{
			rawBackBuffers[i] = backBuffers[i].Get();
		}

		direct3D12SubSystem->Initialize(static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(params.viewMatrix), static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(params.projectionMatrix), renderResolution, rawBackBuffers, RtvFormat);
		PONY_LOG(this->engine->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 sub-system initialized.");
	}

	WindowsDirect3D12RenderSystem::~WindowsDirect3D12RenderSystem() noexcept
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 sub-system.");
		direct3D12SubSystem.reset();
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 sub-system destroyed.");

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Destroy DXGI sub-system.");
		dxgiSubSystem.reset();
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system destroyed.");
	}

	void WindowsDirect3D12RenderSystem::Begin()
	{
	}

	void WindowsDirect3D12RenderSystem::End()
	{
	}

	void WindowsDirect3D12RenderSystem::Tick()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Populate commands.");
		direct3D12SubSystem->PopulateCommands(dxgiSubSystem->GetCurrentBackBufferIndex());
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Execute.");
		direct3D12SubSystem->Execute();

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Present.");
		dxgiSubSystem->Present();

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Wait for end of previous frame.");
		direct3D12SubSystem->WaitForEndOfFrame();
	}

	PonyDebug::Log::ILogger& WindowsDirect3D12RenderSystem::Logger() const noexcept
	{
		return engine->Logger();
	}

	IRenderTarget& WindowsDirect3D12RenderSystem::RenderTarget() const noexcept
	{
		return *direct3D12SubSystem->RenderTarget();
	}

	IRenderView& WindowsDirect3D12RenderSystem::RenderView() const noexcept
	{
		return *direct3D12SubSystem->RenderView();
	}

	IRenderObjectManager& WindowsDirect3D12RenderSystem::RenderObjectManager() const noexcept
	{
		return *direct3D12SubSystem->RenderObjectManager();
	}

	std::string_view WindowsDirect3D12RenderSystem::Name() const noexcept
	{
		return StaticName;
	}

	std::unique_ptr<WindowsDirect3D12DXGISubSystem> WindowsDirect3D12RenderSystem::CreateDXGISubSystem()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create DXGI sub-system.");
		auto createdDxgiSubSystem = std::make_unique<WindowsDirect3D12DXGISubSystem>(*this);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system created.");

		return createdDxgiSubSystem;
	}

	std::unique_ptr<Direct3D12SubSystem> WindowsDirect3D12RenderSystem::CreateDirect3D12SubSystem(const D3D_FEATURE_LEVEL featureLevel, const INT commandQueuePriority, const DWORD fenceTimeout)
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 sub-system.");
		auto createdDirect3D12SubSystem = std::make_unique<Direct3D12SubSystem>(*this, featureLevel, commandQueuePriority, fenceTimeout);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 sub-system created.");

		return createdDirect3D12SubSystem;
	}
}

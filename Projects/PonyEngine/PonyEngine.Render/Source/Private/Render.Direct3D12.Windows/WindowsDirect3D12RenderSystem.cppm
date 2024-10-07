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

export module PonyEngine.Render.Direct3D12.Windows.Implementation:WindowsDirect3D12RenderSystem;

import <cstdint>;
import <memory>;
import <optional>;
import <stdexcept>;
import <type_traits>;

import PonyBase.Math;
import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Window.Windows;

import PonyEngine.Render.Direct3D12.Windows.Factory;

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

		~WindowsDirect3D12RenderSystem() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyBase::Math::RGBA<float> ClearColor() const noexcept override;
		virtual void ClearColor(const PonyBase::Math::RGBA<float>& color) noexcept override;

		virtual RenderObjectHandle CreateRenderObject(const PonyBase::Geometry::Mesh& mesh) override;
		virtual void DestroyRenderObject(RenderObjectHandle renderObjectHandle) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsDirect3D12RenderSystem& operator =(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem& operator =(WindowsDirect3D12RenderSystem&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystem"; ///< Class name.

	private:
		[[nodiscard("Pure function")]]
		std::unique_ptr<DXGISubSystem> CreateDXGISubSystem();
		[[nodiscard("Pure function")]]
		std::unique_ptr<Direct3D12SubSystem> CreateDirect3D12SubSystem(D3D_FEATURE_LEVEL featureLevel, INT commandQueuePriority, DWORD fenceTimeout);

		static constexpr UINT BufferCount = 2u; ///< Buffer count.
		static constexpr DXGI_FORMAT RtvFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

		std::optional<PonyBase::Math::Vector2<UINT>> resolution;

		Core::IEngine* engine; ///< Engine.

		std::unique_ptr<DXGISubSystem> dxgiSubSystem; ///< DXGI sub-system.
		std::unique_ptr<Direct3D12SubSystem> direct3D12SubSystem; ///< Direct3D 12 sub-system.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystem::WindowsDirect3D12RenderSystem(Core::IEngine& engine, const WindowsDirect3D12RenderParams& params) :
		resolution(params.resolution),
		engine{&engine},
		dxgiSubSystem(CreateDXGISubSystem()),
		direct3D12SubSystem(CreateDirect3D12SubSystem(params.featureLevel, params.commandQueuePriority, params.fenceTimeout))
	{
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
		PonyBase::Math::Vector2<UINT> renderResolution;

		if (const auto windowSystem = engine->SystemManager().FindSystem<Window::IWindowsWindowSystem>()) [[likely]]
		{
			const HWND windowHandle = windowSystem->WindowHandle();
			renderResolution = resolution.has_value() ? resolution.value() : static_cast<PonyBase::Math::Vector2<UINT>>(Window::GetWindowClientSize(windowHandle));

			if (resolution.has_value())
			{
				renderResolution = resolution.value();
				PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Use custom resolution.");
			}
			else
			{
				renderResolution = static_cast<PonyBase::Math::Vector2<UINT>>(Window::GetWindowClientSize(windowHandle));
				PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Use window resolution.");
			}

			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Initialize DXGI sub-system.");
			dxgiSubSystem->Initialize(direct3D12SubSystem->GetCommandQueue(), windowHandle, renderResolution, RtvFormat, BufferCount);
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system initialized.");
		}
		else [[unlikely]]
		{
			throw std::runtime_error("Failed to find Windows window system.");
		}

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Get swap chain buffers.");
		Microsoft::WRL::ComPtr<ID3D12Resource2> backBuffers[BufferCount];
		for (UINT i = 0u; i < BufferCount; ++i)
		{
			if (const HRESULT result = dxgiSubSystem->GetBuffer(i, backBuffers[i].GetAddressOf()); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get swap chain buffer at index '{}' with '0x{:X}' result.", i, static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
			PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Buffer at index '{}' gotten at '0x{:X}'.", i, reinterpret_cast<std::uintptr_t>(backBuffers[i].Get()));
		}
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Swap chain buffers gotten.");

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Initialize Direct3D 12 sub-system.");
		direct3D12SubSystem->Initialize(renderResolution, RtvFormat, backBuffers);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 sub-system initialized.");
	}

	void WindowsDirect3D12RenderSystem::End()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Wait for end of frame.");
		direct3D12SubSystem->WaitForEndOfFrame();
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "End of frame waited for.");
	}

	void WindowsDirect3D12RenderSystem::Tick()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Wait for end of previous frame.");
		direct3D12SubSystem->WaitForEndOfFrame();

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Populate commands.");
		direct3D12SubSystem->PopulateCommands(dxgiSubSystem->GetCurrentBackBufferIndex());
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Execute.");
		direct3D12SubSystem->Execute();

		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Verbose, "Present.");
		dxgiSubSystem->Present();
	}

	PonyDebug::Log::ILogger& WindowsDirect3D12RenderSystem::Logger() const noexcept
	{
		return engine->Logger();
	}

	PonyBase::Math::RGBA<float> WindowsDirect3D12RenderSystem::ClearColor() const noexcept
	{
		return static_cast<PonyBase::Math::RGBA<float>>(direct3D12SubSystem->ClearColor());
	}

	void WindowsDirect3D12RenderSystem::ClearColor(const PonyBase::Math::RGBA<float>& color) noexcept
	{
		direct3D12SubSystem->ClearColor() = static_cast<PonyBase::Math::RGBA<FLOAT>>(color);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Clear color set to '{}'.", direct3D12SubSystem->ClearColor().ToString());
	}

	RenderObjectHandle WindowsDirect3D12RenderSystem::CreateRenderObject(const PonyBase::Geometry::Mesh& mesh)
	{
		return direct3D12SubSystem->CreateRenderObject(mesh);
	}

	void WindowsDirect3D12RenderSystem::DestroyRenderObject(const RenderObjectHandle renderObjectHandle) noexcept
	{
		direct3D12SubSystem->DestroyRenderObject(renderObjectHandle);
	}

	const char* WindowsDirect3D12RenderSystem::Name() const noexcept
	{
		return StaticName;
	}

	std::unique_ptr<DXGISubSystem> WindowsDirect3D12RenderSystem::CreateDXGISubSystem()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create DXGI sub-system.");
		const auto createdDxgiSubSystem = new DXGISubSystem(*this);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system created.");

		return std::unique_ptr<DXGISubSystem>(createdDxgiSubSystem);
	}

	std::unique_ptr<Direct3D12SubSystem> WindowsDirect3D12RenderSystem::CreateDirect3D12SubSystem(const D3D_FEATURE_LEVEL featureLevel, const INT commandQueuePriority, const DWORD fenceTimeout)
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 sub-system.");
		const auto createdDirect3D12SubSystem = new Direct3D12SubSystem(*this, featureLevel, commandQueuePriority, fenceTimeout);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 sub-system created.");

		return std::unique_ptr<Direct3D12SubSystem>(createdDirect3D12SubSystem);
	}
}

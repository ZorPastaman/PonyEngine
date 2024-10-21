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
import <type_traits>;

import PonyBase.StringUtility;

import PonyMath.Core;
import PonyMath.Geometry;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Screen;
import PonyEngine.Window.Windows;

import PonyEngine.Render.Direct3D12.Windows.Factory;

import PonyEngine.Render.Core;
import PonyEngine.Render.Direct3D12.Implementation;

import :WindowsDirect3D12DXGISubSystem;

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
		WindowsDirect3D12RenderSystem(Core::IEngine& engine, const WindowsDirect3D12RenderSystemParams& params);
		WindowsDirect3D12RenderSystem(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem(WindowsDirect3D12RenderSystem&&) = delete;

		~WindowsDirect3D12RenderSystem() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::RGBA<float> ClearColor() const noexcept override;
		virtual void ClearColor(const PonyMath::Core::RGBA<float>& color) noexcept override;

		[[nodiscard("Pure function")]]
		virtual CameraParams CameraParameters() const noexcept override;
		virtual void CameraParameters(const CameraParams& cameraParams) noexcept override;
		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> CameraTrsMatrix() const noexcept override;
		virtual void CameraTrsMatrix(const PonyMath::Core::Matrix4x4<float>& trs) noexcept override;

		virtual RenderObjectHandle CreateRenderObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& trs) override;
		virtual void DestroyRenderObject(RenderObjectHandle renderObjectHandle) noexcept override;
		virtual void UpdateRenderObjectTrs(RenderObjectHandle handle, const PonyMath::Core::Matrix4x4<float>& trs) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsDirect3D12RenderSystem& operator =(const WindowsDirect3D12RenderSystem&) = delete;
		WindowsDirect3D12RenderSystem& operator =(WindowsDirect3D12RenderSystem&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Render::WindowsDirect3D12RenderSystem"; ///< Class name.

	private:
		[[nodiscard("Pure function")]]
		std::unique_ptr<WindowsDirect3D12DXGISubSystem> CreateDXGISubSystem();
		[[nodiscard("Pure function")]]
		std::unique_ptr<Direct3D12SubSystem> CreateDirect3D12SubSystem(D3D_FEATURE_LEVEL featureLevel, INT commandQueuePriority, DWORD fenceTimeout);

		static constexpr UINT BufferCount = 2u; ///< Buffer count.
		static constexpr DXGI_FORMAT RtvFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

		Direct3D12CameraParams cameraParams;
		std::optional<Screen::Resolution<UINT>> resolution;

		Core::IEngine* engine; ///< Engine.

		std::unique_ptr<WindowsDirect3D12DXGISubSystem> dxgiSubSystem; ///< DXGI sub-system.
		std::unique_ptr<Direct3D12SubSystem> direct3D12SubSystem; ///< Direct3D 12 sub-system.
	};
}

namespace PonyEngine::Render
{
	WindowsDirect3D12RenderSystem::WindowsDirect3D12RenderSystem(Core::IEngine& engine, const WindowsDirect3D12RenderSystemParams& params) :
		cameraParams{.fov = static_cast<FLOAT>(params.cameraParams.fov), .nearPlane = static_cast<FLOAT>(params.cameraParams.nearPlane), .farPlane = static_cast<FLOAT>(params.cameraParams.farPlane)},
		resolution(params.resolution.has_value() ? std::optional<Screen::Resolution<UINT>>(static_cast<Screen::Resolution<UINT>>(params.resolution.value())) : std::nullopt),
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
		Screen::Resolution<UINT> renderResolution;

		if (const auto windowSystem = engine->SystemManager().FindSystem<Window::IWindowsWindowSystem>()) [[likely]]
		{
			const HWND windowHandle = windowSystem->WindowHandle();

			if (resolution.has_value())
			{
				renderResolution = resolution.value();
				PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Use custom resolution.");
			}
			else
			{
				renderResolution = static_cast<Screen::Resolution<UINT>>(windowSystem->Resolution());
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
		std::array<Microsoft::WRL::ComPtr<ID3D12Resource2>, BufferCount> backBuffers;
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
		std::array<ID3D12Resource2*, BufferCount> rawBackBuffers;
		for (std::size_t i = 0; i < BufferCount; ++i)
		{
			rawBackBuffers[i] = backBuffers[i].Get();
		}
		direct3D12SubSystem->Initialize(cameraParams, renderResolution, rawBackBuffers, RtvFormat);
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

	PonyMath::Core::RGBA<float> WindowsDirect3D12RenderSystem::ClearColor() const noexcept
	{
		return static_cast<PonyMath::Core::RGBA<float>>(direct3D12SubSystem->ClearColor());
	}

	void WindowsDirect3D12RenderSystem::ClearColor(const PonyMath::Core::RGBA<float>& color) noexcept
	{
		direct3D12SubSystem->ClearColor() = static_cast<PonyMath::Core::RGBA<FLOAT>>(color);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Debug, "Clear color set to '{}'.", direct3D12SubSystem->ClearColor().ToString());
	}

	CameraParams WindowsDirect3D12RenderSystem::CameraParameters() const noexcept
	{
		const Direct3D12CameraParams& params = direct3D12SubSystem->CameraParams();

		return CameraParams{.fov = static_cast<float>(params.fov), .nearPlane = static_cast<float>(params.nearPlane), .farPlane = static_cast<float>(params.farPlane)};
	}

	void WindowsDirect3D12RenderSystem::CameraParameters(const CameraParams& cameraParams) noexcept
	{
		const auto params = Direct3D12CameraParams{.fov = static_cast<FLOAT>(cameraParams.fov), .nearPlane = static_cast<FLOAT>(cameraParams.nearPlane), .farPlane = static_cast<FLOAT>(cameraParams.farPlane)};
		direct3D12SubSystem->CameraParams(params);
	}

	PonyMath::Core::Matrix4x4<float> WindowsDirect3D12RenderSystem::CameraTrsMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(direct3D12SubSystem->CameraTrsMatrix());
	}

	void WindowsDirect3D12RenderSystem::CameraTrsMatrix(const PonyMath::Core::Matrix4x4<float>& trs) noexcept
	{
		direct3D12SubSystem->CameraTrsMatrix() = trs;
	}

	RenderObjectHandle WindowsDirect3D12RenderSystem::CreateRenderObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& trs)
	{
		return direct3D12SubSystem->CreateRenderObject(mesh, static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(trs));
	}

	void WindowsDirect3D12RenderSystem::DestroyRenderObject(const RenderObjectHandle renderObjectHandle) noexcept
	{
		direct3D12SubSystem->DestroyRenderObject(renderObjectHandle);
	}

	void WindowsDirect3D12RenderSystem::UpdateRenderObjectTrs(const RenderObjectHandle handle, const PonyMath::Core::Matrix4x4<float>& trs) const noexcept
	{
		direct3D12SubSystem->UpdateRenderObjectTrs(handle, static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(trs));
	}

	const char* WindowsDirect3D12RenderSystem::Name() const noexcept
	{
		return StaticName;
	}

	std::unique_ptr<WindowsDirect3D12DXGISubSystem> WindowsDirect3D12RenderSystem::CreateDXGISubSystem()
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create DXGI sub-system.");
		const auto createdDxgiSubSystem = new WindowsDirect3D12DXGISubSystem(*this);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "DXGI sub-system created.");

		return std::unique_ptr<WindowsDirect3D12DXGISubSystem>(createdDxgiSubSystem);
	}

	std::unique_ptr<Direct3D12SubSystem> WindowsDirect3D12RenderSystem::CreateDirect3D12SubSystem(const D3D_FEATURE_LEVEL featureLevel, const INT commandQueuePriority, const DWORD fenceTimeout)
	{
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 sub-system.");
		const auto createdDirect3D12SubSystem = new Direct3D12SubSystem(*this, featureLevel, commandQueuePriority, fenceTimeout);
		PONY_LOG(engine->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 sub-system created.");

		return std::unique_ptr<Direct3D12SubSystem>(createdDirect3D12SubSystem);
	}
}

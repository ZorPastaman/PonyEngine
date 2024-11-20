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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12SubSystem;

import <cstdint>;
import <memory>;
import <span>;
import <stdexcept>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Geometry;
import PonyMath.Core;
import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Core;

import PonyEngine.Render.Detail;
import PonyEngine.Render.Direct3D12;

import :Direct3D12GraphicsPipeline;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 sys-system.
	class Direct3D12SubSystem final
	{
	public:
		[[nodiscard("Pure function")]]
		Direct3D12SubSystem(IRenderContext& renderer, const Direct3D12RenderSystemParams& params, DXGI_FORMAT rtvFormat);
		Direct3D12SubSystem(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem(Direct3D12SubSystem&&) = delete;

		~Direct3D12SubSystem() noexcept;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue* GetCommandQueue() const;

		[[nodiscard("Pure function")]]
		IDirect3D12RenderTarget* RenderTarget() const noexcept;
		[[nodiscard("Pure function")]]
		IDirect3D12RenderView* RenderView() const noexcept;
		[[nodiscard("Pure function")]]
		IDirect3D12RenderObjectManager* RenderObjectManager() const noexcept;

		void Initialize(const PonyMath::Utility::Resolution<UINT>& resolution, std::span<ID3D12Resource2*> buffers);

		void PopulateCommands(UINT bufferIndex) const;
		void Execute() const;
		void WaitForEndOfFrame() const;

		Direct3D12SubSystem& operator =(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem& operator =(Direct3D12SubSystem&&) = delete;

	private:
		DXGI_FORMAT rtvFormat;

		IRenderContext* renderer;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> debug;
#endif
		Microsoft::WRL::ComPtr<ID3D12Device10> device;

		std::unique_ptr<Direct3D12RenderTarget> renderTarget;
		std::unique_ptr<Direct3D12RenderView> renderView;
		std::unique_ptr<Direct3D12MaterialManager> materialManager;
		std::unique_ptr<Direct3D12MeshManager> meshManager;
		std::unique_ptr<Direct3D12RenderObjectManager> renderObjectManager;
		std::unique_ptr<Direct3D12GraphicsPipeline> graphicsPipeline;
		std::unique_ptr<Direct3D12Waiter> waiter;
	};
}

namespace PonyEngine::Render
{
	Direct3D12SubSystem::Direct3D12SubSystem(IRenderContext& renderer, const Direct3D12RenderSystemParams& params, const DXGI_FORMAT rtvFormat) :
		rtvFormat{rtvFormat},
		renderer{&renderer}
	{
#ifdef _DEBUG
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 debug interface.");
		if (const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get Direct3D 12 debug interface with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 debug interface acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(debug.Get()));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Debug, "Enable Direct3D 12 debug layer.");
		debug->EnableDebugLayer();
#endif

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 device. Feature level: '0x{:X}.'", static_cast<unsigned int>(params.featureLevel));
		if (const HRESULT result = D3D12CreateDevice(nullptr, params.featureLevel, IID_PPV_ARGS(device.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 device with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 device acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(device.Get()));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 material manager.");
		materialManager = std::make_unique<Direct3D12MaterialManager>(*this->renderer, device.Get(), rtvFormat);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 material manager created.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 mesh manager.");
		meshManager = std::make_unique<Direct3D12MeshManager>(*this->renderer, device.Get());
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 mesh manager created.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render object manager.");
		renderObjectManager = std::make_unique<Direct3D12RenderObjectManager>(*this->renderer, *materialManager, *meshManager, device.Get());
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render object manager created.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render view.");
		renderView = std::make_unique<Direct3D12RenderView>(params.renderViewParams.viewMatrix, params.renderViewParams.projectionMatrix, PonyMath::Utility::Resolution<UINT>(0u, 0u));
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render view created.");
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render target.");
		renderTarget = std::make_unique<Direct3D12RenderTarget>(params.renderTargetParams.clearColor);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render target created.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 graphics pipeline.");
		graphicsPipeline = std::make_unique<Direct3D12GraphicsPipeline>(*this->renderer, device.Get(), params, renderTarget.get(), renderView.get(), materialManager.get(), meshManager.get(), renderObjectManager.get());
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 graphics pipeline created.'");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 waiter. Wait timeout: {}.", params.renderTimeout);
		waiter = std::make_unique<Direct3D12Waiter>(*this->renderer, graphicsPipeline->GetCommandQueue(), params.renderTimeout);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 wait created.");
	}

	Direct3D12SubSystem::~Direct3D12SubSystem() noexcept
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 waiter.");
		waiter.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 waiter destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 graphics pipeline.'");
		graphicsPipeline.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 graphics pipeline destroyed.'");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 render object manager.");
		renderObjectManager.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render object manager destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 mesh manager.");
		meshManager.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 mesh manager destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 material.");
		materialManager.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 material destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 render view.");
		renderView.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render target view.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 render target.");
		renderTarget.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render target destroyed.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 device.");
		device.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 device released.");

#ifdef _DEBUG
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 debug interface.");
		debug.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 debug interface released.");
#endif
	}

	ID3D12CommandQueue* Direct3D12SubSystem::GetCommandQueue() const
	{
		return graphicsPipeline->GetCommandQueue();
	}

	IDirect3D12RenderTarget* Direct3D12SubSystem::RenderTarget() const noexcept
	{
		return renderTarget.get();
	}

	IDirect3D12RenderView* Direct3D12SubSystem::RenderView() const noexcept
	{
		return renderView.get();
	}

	IDirect3D12RenderObjectManager* Direct3D12SubSystem::RenderObjectManager() const noexcept
	{
		return renderObjectManager.get();
	}

	void Direct3D12SubSystem::Initialize(const PonyMath::Utility::Resolution<UINT>& resolution, const std::span<ID3D12Resource2*> buffers)
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Set render view resolution to '{}'.", resolution.ToString());
		renderView->ResolutionD3D12(resolution);
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Initialize Direct3D 12 render target.");
		renderTarget->Initialize(device.Get(), buffers, rtvFormat);
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render target initialized.");
	}

	void Direct3D12SubSystem::PopulateCommands(const UINT bufferIndex) const
	{
		graphicsPipeline->PopulateCommands(bufferIndex);
	}

	void Direct3D12SubSystem::Execute() const
	{
		graphicsPipeline->Execute();
	}

	void Direct3D12SubSystem::WaitForEndOfFrame() const
	{
		waiter->Wait();
	}
}

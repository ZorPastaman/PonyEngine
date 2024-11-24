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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12System;

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
import :Direct3D12SystemParams;
import :IDirect3D12RenderSystemContext;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 system.
	class Direct3D12System final : private IDirect3D12SystemContext
	{
	public:
		[[nodiscard("Pure function")]]
		Direct3D12System(IDirect3D12RenderSystemContext& renderer, const Direct3D12SystemParams& params);
		Direct3D12System(const Direct3D12System&) = delete;
		Direct3D12System(Direct3D12System&&) = delete;

		~Direct3D12System() noexcept;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderTargetPrivate& RenderTarget() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderTargetPrivate& RenderTarget() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderView& RenderView() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderView& RenderView() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderObjectManagerPrivate& RenderObjectManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderObjectManagerPrivate& RenderObjectManager() const noexcept override;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue* GraphicsCommandQueue() const;

		void CreateRenderTarget(const Direct3D12RenderTargetParams& params);

		void PopulateCommands(UINT bufferIndex) const;
		void Execute() const;
		void WaitForEndOfFrame() const;

		Direct3D12System& operator =(const Direct3D12System&) = delete;
		Direct3D12System& operator =(Direct3D12System&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ID3D12Device10& Device() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Device10& Device() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12DepthStencilPrivate& DepthStencil() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12DepthStencilPrivate& DepthStencil() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RootSignatureManagerPrivate& RootSignatureManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RootSignatureManagerPrivate& RootSignatureManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12MaterialManagerPrivate& MaterialManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12MaterialManagerPrivate& MaterialManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12MeshManagerPrivate& MeshManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12MeshManagerPrivate& MeshManager() const noexcept override;

		IRenderSystemContext* renderer;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> debug;
#endif
		Microsoft::WRL::ComPtr<ID3D12Device10> device;

		std::unique_ptr<Direct3D12RenderTarget> renderTarget;
		std::unique_ptr<Direct3D12DepthStencil> depthStencil;
		std::unique_ptr<Direct3D12RenderView> renderView;
		std::unique_ptr<Direct3D12RootSignatureManager> rootSignatureManager;
		std::unique_ptr<Direct3D12MaterialManager> materialManager;
		std::unique_ptr<Direct3D12MeshManager> meshManager;
		std::unique_ptr<Direct3D12RenderObjectManager> renderObjectManager;

		std::unique_ptr<Direct3D12GraphicsPipeline> graphicsPipeline;
		std::unique_ptr<Direct3D12Waiter> waiter;
	};
}

namespace PonyEngine::Render
{
	Direct3D12System::Direct3D12System(IDirect3D12RenderSystemContext& renderer, const Direct3D12SystemParams& params) :
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

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render view.");
		renderView = std::make_unique<Direct3D12RenderView>(params.renderViewParams.viewMatrix, params.renderViewParams.projectionMatrix);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render view created.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 graphics pipeline.");
		graphicsPipeline = std::make_unique<Direct3D12GraphicsPipeline>(*static_cast<IDirect3D12SystemContext*>(this), params.commandQueuePriority);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 graphics pipeline created.'");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 waiter. Wait timeout: {}.", params.renderTimeout);
		waiter = std::make_unique<Direct3D12Waiter>(*static_cast<IDirect3D12SystemContext*>(this), *GraphicsCommandQueue(), params.renderTimeout);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 wait created.");
	}

	Direct3D12System::~Direct3D12System() noexcept
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

	ID3D12CommandQueue* Direct3D12System::GraphicsCommandQueue() const
	{
		return &graphicsPipeline->CommandQueue();
	}

	PonyDebug::Log::ILogger& Direct3D12System::Logger() noexcept
	{
		return renderer->Logger();
	}

	const PonyDebug::Log::ILogger& Direct3D12System::Logger() const noexcept
	{
		return renderer->Logger();
	}

	ID3D12Device10& Direct3D12System::Device() noexcept
	{
		return *device.Get();
	}

	const ID3D12Device10& Direct3D12System::Device() const noexcept
	{
		return *device.Get();
	}

	IDirect3D12RenderTargetPrivate& Direct3D12System::RenderTarget() noexcept
	{
		return *renderTarget;
	}

	const IDirect3D12RenderTargetPrivate& Direct3D12System::RenderTarget() const noexcept
	{
		return *renderTarget;
	}

	IDirect3D12DepthStencilPrivate& Direct3D12System::DepthStencil() noexcept
	{
		return *depthStencil;
	}

	const IDirect3D12DepthStencilPrivate& Direct3D12System::DepthStencil() const noexcept
	{
		return *depthStencil;
	}

	IDirect3D12RootSignatureManagerPrivate& Direct3D12System::RootSignatureManager() noexcept
	{
		return *rootSignatureManager;
	}

	const IDirect3D12RootSignatureManagerPrivate& Direct3D12System::RootSignatureManager() const noexcept
	{
		return *rootSignatureManager;
	}

	IDirect3D12MaterialManagerPrivate& Direct3D12System::MaterialManager() noexcept
	{
		return *materialManager;
	}

	const IDirect3D12MaterialManagerPrivate& Direct3D12System::MaterialManager() const noexcept
	{
		return *materialManager;
	}

	IDirect3D12MeshManagerPrivate& Direct3D12System::MeshManager() noexcept
	{
		return *meshManager;
	}

	const IDirect3D12MeshManagerPrivate& Direct3D12System::MeshManager() const noexcept
	{
		return *meshManager;
	}

	IDirect3D12RenderView& Direct3D12System::RenderView() noexcept
	{
		return *renderView;
	}

	const IDirect3D12RenderView& Direct3D12System::RenderView() const noexcept
	{
		return *renderView;
	}

	IDirect3D12RenderObjectManagerPrivate& Direct3D12System::RenderObjectManager() noexcept
	{
		return *renderObjectManager;
	}

	const IDirect3D12RenderObjectManagerPrivate& Direct3D12System::RenderObjectManager() const noexcept
	{
		return *renderObjectManager;
	}

	void Direct3D12System::CreateRenderTarget(const Direct3D12RenderTargetParams& params)
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render target.");
		renderTarget = std::make_unique<Direct3D12RenderTarget>(*static_cast<IDirect3D12SystemContext*>(this), params);
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render target created.");

		depthStencil = std::make_unique<Direct3D12DepthStencil>(*static_cast<IDirect3D12SystemContext*>(this), params);

		rootSignatureManager = std::make_unique<Direct3D12RootSignatureManager>(*static_cast<IDirect3D12SystemContext*>(this));

		materialManager = std::make_unique<Direct3D12MaterialManager>(*static_cast<IDirect3D12SystemContext*>(this), params.rtvFormat);

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 mesh manager.");
		meshManager = std::make_unique<Direct3D12MeshManager>(*static_cast<IDirect3D12SystemContext*>(this));
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 mesh manager created.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render object manager.");
		renderObjectManager = std::make_unique<Direct3D12RenderObjectManager>(*static_cast<IDirect3D12SystemContext*>(this));
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render object manager created.");
	}

	void Direct3D12System::PopulateCommands(const UINT bufferIndex) const
	{
		graphicsPipeline->PopulateCommands(bufferIndex);
	}

	void Direct3D12System::Execute() const
	{
		graphicsPipeline->Execute();
	}

	void Direct3D12System::WaitForEndOfFrame() const
	{
		waiter->Wait();
	}
}

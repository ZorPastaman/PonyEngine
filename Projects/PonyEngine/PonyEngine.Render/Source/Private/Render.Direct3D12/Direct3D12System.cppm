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
import <stdexcept>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Render.Direct3D12;

import :Direct3D12BackBuffer;
import :Direct3D12BackBufferParams;
import :Direct3D12CopyPipeline;
import :Direct3D12CpuWaiter;
import :Direct3D12DepthStencil;
import :Direct3D12GpuWaiter;
import :Direct3D12GraphicsPipeline;
import :Direct3D12MaterialManager;
import :Direct3D12MeshManager;
import :Direct3D12RenderObjectManager;
import :Direct3D12RenderTarget;
import :Direct3D12RenderTargetParams;
import :Direct3D12RenderView;
import :Direct3D12RenderViewParams;
import :Direct3D12RootSignatureManager;
import :Direct3D12SystemParams;
import :Direct3D12Utility;
import :IDirect3D12CopyPipeline;
import :IDirect3D12DepthStencilPrivate;
import :IDirect3D12GraphicsPipeline;
import :IDirect3D12MaterialManagerPrivate;
import :IDirect3D12MeshManagerPrivate;
import :IDirect3D12RenderObjectManagerPrivate;
import :IDirect3D12RenderTargetPrivate;
import :IDirect3D12RenderViewPrivate;
import :IDirect3D12RenderSystemContext;
import :IDirect3D12RootSignatureManagerPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 system.
	class Direct3D12System final : private IDirect3D12SystemContext
	{
	public:
		/// @brief Creates a @p Direct3D12System.
		/// @param renderSystem Render system context.
		/// @param params Direct3D12 system parameters.
		[[nodiscard("Pure constructor")]]
		Direct3D12System(IDirect3D12RenderSystemContext& renderSystem, const Direct3D12SystemParams& params);
		Direct3D12System(const Direct3D12System&) = delete;
		Direct3D12System(Direct3D12System&&) = delete;

		~Direct3D12System() noexcept;

		/// @brief Gets the render target.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render target.
		[[nodiscard("Pure function")]]
		IDirect3D12RenderTarget* RenderTarget() noexcept;
		/// @brief Gets the render target.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render target.
		[[nodiscard("Pure function")]]
		const IDirect3D12RenderTarget* RenderTarget() const noexcept;

		/// @brief Gets the render view.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render view.
		[[nodiscard("Pure function")]]
		IDirect3D12RenderView* RenderView() noexcept;
		/// @brief Gets the render view.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render view.
		[[nodiscard("Pure function")]]
		const IDirect3D12RenderView* RenderView() const noexcept;

		/// @brief Gets the render object manager.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		IDirect3D12RenderObjectManager* RenderObjectManager() noexcept;
		/// @brief Gets the render object manager.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		const IDirect3D12RenderObjectManager* RenderObjectManager() const noexcept;

		/// @brief Gets the graphics command queue.
		/// @return Graphics command queue.
		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& GraphicsCommandQueue() noexcept;
		/// @brief Gets the graphics command queue.
		/// @return Graphics command queue.
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& GraphicsCommandQueue() const noexcept;

		/// @brief Creates a render system.
		/// @param backBufferParams Back buffer parameters.
		/// @param renderTargetParams Render target parameters.
		/// @param renderViewParams Render view parameters.
		void CreateRenderSystem(const Direct3D12BackBufferParams& backBufferParams, const Direct3D12RenderTargetParams& renderTargetParams, const Direct3D12RenderViewParams& renderViewParams);

		/// @brief Begins a new frame.
		void BeginFrame();
		/// @brief Renders to the back buffer at the @p bufferIndex.
		/// @param bufferIndex Current back buffer index.
		void Render(UINT bufferIndex);
		/// @brief Ends a current frame.
		void EndFrame();

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
		virtual IDirect3D12BackBufferPrivate& BackBufferPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12BackBufferPrivate& BackBufferPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderTargetPrivate& RenderTargetPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderTargetPrivate& RenderTargetPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12DepthStencilPrivate& DepthStencilPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12DepthStencilPrivate& DepthStencilPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderViewPrivate& RenderViewPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderViewPrivate& RenderViewPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12MeshManagerPrivate& MeshManagerPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12MeshManagerPrivate& MeshManagerPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RootSignatureManagerPrivate& RootSignatureManagerPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RootSignatureManagerPrivate& RootSignatureManagerPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12MaterialManagerPrivate& MaterialManagerPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12MaterialManagerPrivate& MaterialManagerPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12RenderObjectManagerPrivate& RenderObjectManagerPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12RenderObjectManagerPrivate& RenderObjectManagerPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12CopyPipeline& CopyPipeline() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12CopyPipeline& CopyPipeline() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDirect3D12GraphicsPipeline& GraphicsPipeline() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDirect3D12GraphicsPipeline& GraphicsPipeline() const noexcept override;

		IRenderSystemContext* renderSystem; ///< Render system context.

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> debug; ///< Debug interface.
#endif
		Microsoft::WRL::ComPtr<ID3D12Device10> device; ///< Render device.

		std::unique_ptr<Direct3D12BackBuffer> backBuffer; ///< Back buffer.
		std::unique_ptr<Direct3D12RenderTarget> renderTarget; ///< Render target.
		std::unique_ptr<Direct3D12DepthStencil> depthStencil; ///< Depth stencil.
		std::unique_ptr<Direct3D12RenderView> renderView; ///< Render view.

		std::unique_ptr<Direct3D12MeshManager> meshManager; ///< Mesh manager.
		std::unique_ptr<Direct3D12RootSignatureManager> rootSignatureManager; ///< Root signature manager.
		std::unique_ptr<Direct3D12MaterialManager> materialManager; ///< Material manager.
		std::unique_ptr<Direct3D12RenderObjectManager> renderObjectManager; ///< Render object manager.

		std::unique_ptr<Direct3D12CopyPipeline> copyPipeline; ///< Copy pipeline.
		std::unique_ptr<Direct3D12GraphicsPipeline> graphicsPipeline; ///< Graphics pipeline.

		std::unique_ptr<Direct3D12GpuWaiter> copyWaiter; ///< Copy pipeline waiter.
		std::unique_ptr<Direct3D12CpuWaiter> graphicsWaiter; ///< Graphics pipeline waiter.
	};
}

namespace PonyEngine::Render
{
	Direct3D12System::Direct3D12System(IDirect3D12RenderSystemContext& renderSystem, const Direct3D12SystemParams& params) :
		renderSystem{&renderSystem}
	{
#ifdef _DEBUG
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Acquire debug interface.");
		if (const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire debug interface with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Debug interface acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(debug.Get()));

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Debug, "Enable debug layer.");
		debug->EnableDebugLayer();
#endif

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Acquire device. Feature level: '0x{:X}.'", static_cast<unsigned int>(params.featureLevel));
		if (const HRESULT result = D3D12CreateDevice(nullptr, params.featureLevel, IID_PPV_ARGS(device.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire device with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		SetName(*device.Get(), "RenderDevice");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Device acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(device.Get()));

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create copy pipeline.");
		copyPipeline = std::make_unique<Direct3D12CopyPipeline>(*static_cast<IDirect3D12SystemContext*>(this), params.commandQueuePriority);
		copyPipeline->Name("CopyPipeline");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(copyPipeline.get()));

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create graphics pipeline.");
		graphicsPipeline = std::make_unique<Direct3D12GraphicsPipeline>(*static_cast<IDirect3D12SystemContext*>(this), params.commandQueuePriority);
		graphicsPipeline->Name("GraphicsPipeline");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline created at '0x{:X}'.'", reinterpret_cast<std::uintptr_t>(graphicsPipeline.get()));

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create copy pipeline waiter.");
		copyWaiter = std::make_unique<Direct3D12GpuWaiter>(*static_cast<IDirect3D12SystemContext*>(this), copyPipeline->CommandQueue(), graphicsPipeline->CommandQueue());
		copyWaiter->Name("CopyToGraphicsWaiter");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline waiter created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(copyWaiter.get()));

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create graphics pipeline waiter. Wait timeout: {}.", params.renderTimeout);
		graphicsWaiter = std::make_unique<Direct3D12CpuWaiter>(*static_cast<IDirect3D12SystemContext*>(this), graphicsPipeline->CommandQueue(), params.renderTimeout);
		graphicsWaiter->Name("GraphicsEndWaiter");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline waiter created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(graphicsWaiter.get()));
	}

	Direct3D12System::~Direct3D12System() noexcept
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy graphics pipeline waiter.");
		graphicsWaiter.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline waiter destroyed.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy copy pipeline waiter.'");
		copyWaiter.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline waiter destroyed.'");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy graphics pipeline.'");
		graphicsPipeline.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline destroyed.'");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy copy pipeline.'");
		copyPipeline.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline destroyed.'");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy render object manager.");
		renderObjectManager.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render object manager destroyed.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy material manager.");
		materialManager.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Material manager destroyed.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy root signature manager.");
		rootSignatureManager.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Root signature manager destroyed.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy mesh manager.");
		meshManager.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Mesh manager destroyed.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy render view.");
		renderView.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render target view.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy render target.");
		renderTarget.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render target destroyed.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy back buffer.");
		backBuffer.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Back buffer destroyed.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Release device.");
		device.Reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Device released.");

#ifdef _DEBUG
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Release debug interface.");
		debug.Reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Debug interface released.");
#endif
	}

	IDirect3D12RenderTarget* Direct3D12System::RenderTarget() noexcept
	{
		return renderTarget.get();
	}

	const IDirect3D12RenderTarget* Direct3D12System::RenderTarget() const noexcept
	{
		return renderTarget.get();
	}

	IDirect3D12RenderView* Direct3D12System::RenderView() noexcept
	{
		return renderView.get();
	}

	const IDirect3D12RenderView* Direct3D12System::RenderView() const noexcept
	{
		return renderView.get();
	}

	IDirect3D12RenderObjectManager* Direct3D12System::RenderObjectManager() noexcept
	{
		return renderObjectManager.get();
	}

	const IDirect3D12RenderObjectManager* Direct3D12System::RenderObjectManager() const noexcept
	{
		return renderObjectManager.get();
	}

	ID3D12CommandQueue& Direct3D12System::GraphicsCommandQueue() noexcept
	{
		return graphicsPipeline->CommandQueue();
	}

	const ID3D12CommandQueue& Direct3D12System::GraphicsCommandQueue() const noexcept
	{
		return graphicsPipeline->CommandQueue();
	}

	void Direct3D12System::CreateRenderSystem(const Direct3D12BackBufferParams& backBufferParams, const Direct3D12RenderTargetParams& renderTargetParams, const Direct3D12RenderViewParams& renderViewParams)
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create back buffer.");
		backBuffer = std::make_unique<Direct3D12BackBuffer>(*static_cast<IDirect3D12SystemContext*>(this), backBufferParams);
		backBuffer->Name("BackBuffer");
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Back buffer created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(backBuffer.get()));

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create render target.");
		renderTarget = std::make_unique<Direct3D12RenderTarget>(*static_cast<IDirect3D12SystemContext*>(this), renderTargetParams);
		renderTarget->Name("RenderTarget");
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render target created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderTarget.get()));

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create render view.");
		renderView = std::make_unique<Direct3D12RenderView>(renderViewParams);
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render view created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderView.get()));

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create depth stencil.");
		depthStencil = std::make_unique<Direct3D12DepthStencil>(*static_cast<IDirect3D12SystemContext*>(this));
		depthStencil->Name("DepthStencil");
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(depthStencil.get()));

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create mesh manager.");
		meshManager = std::make_unique<Direct3D12MeshManager>(*static_cast<IDirect3D12SystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Mesh manager created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(meshManager.get()));

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create root signature manager.");
		rootSignatureManager = std::make_unique<Direct3D12RootSignatureManager>(*static_cast<IDirect3D12SystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Root signature manager created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(rootSignatureManager.get()));

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create material manager.");
		materialManager = std::make_unique<Direct3D12MaterialManager>(*static_cast<IDirect3D12SystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Material manager created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(materialManager.get()));

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create render object manager.");
		renderObjectManager = std::make_unique<Direct3D12RenderObjectManager>(*static_cast<IDirect3D12SystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render object manager created.");
	}

	void Direct3D12System::BeginFrame()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clean render object manager.");
		renderObjectManager->Clean();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clean mesh manager.");
		meshManager->Clean();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clean material manager.");
		materialManager->Clean();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clean root signature manager.");
		rootSignatureManager->Clean();
	}

	void Direct3D12System::Render(const UINT bufferIndex)
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Populate copy pipeline commands.");
		copyPipeline->PopulateCommands();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Execute copy pipeline.");
		copyPipeline->Execute();

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Set back buffer index to '{}'.", bufferIndex);
		backBuffer->CurrentBackBufferIndex(bufferIndex);
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Add render tasks.");
		renderObjectManager->AddRenderTasks();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Populate graphics pipeline commands.");
		graphicsPipeline->PopulateCommands();

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Wait for copy pipeline to finish.");
		copyWaiter->Wait();

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Execute graphics pipeline.");
		graphicsPipeline->Execute();
	}

	void Direct3D12System::EndFrame()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Wait for graphics pipeline to finish.");
		graphicsWaiter->Wait();

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clear copy pipeline.");
		copyPipeline->Clear();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clear graphics pipeline.");
		graphicsPipeline->Clear();
	}

	PonyDebug::Log::ILogger& Direct3D12System::Logger() noexcept
	{
		return renderSystem->Logger();
	}

	const PonyDebug::Log::ILogger& Direct3D12System::Logger() const noexcept
	{
		return renderSystem->Logger();
	}

	ID3D12Device10& Direct3D12System::Device() noexcept
	{
		return *device.Get();
	}

	const ID3D12Device10& Direct3D12System::Device() const noexcept
	{
		return *device.Get();
	}

	IDirect3D12BackBufferPrivate& Direct3D12System::BackBufferPrivate() noexcept
	{
		return *backBuffer;
	}

	const IDirect3D12BackBufferPrivate& Direct3D12System::BackBufferPrivate() const noexcept
	{
		return *backBuffer;
	}

	IDirect3D12RenderTargetPrivate& Direct3D12System::RenderTargetPrivate() noexcept
	{
		return *renderTarget;
	}

	const IDirect3D12RenderTargetPrivate& Direct3D12System::RenderTargetPrivate() const noexcept
	{
		return *renderTarget;
	}

	IDirect3D12DepthStencilPrivate& Direct3D12System::DepthStencilPrivate() noexcept
	{
		return *depthStencil;
	}

	const IDirect3D12DepthStencilPrivate& Direct3D12System::DepthStencilPrivate() const noexcept
	{
		return *depthStencil;
	}

	IDirect3D12MeshManagerPrivate& Direct3D12System::MeshManagerPrivate() noexcept
	{
		return *meshManager;
	}

	const IDirect3D12MeshManagerPrivate& Direct3D12System::MeshManagerPrivate() const noexcept
	{
		return *meshManager;
	}

	IDirect3D12RootSignatureManagerPrivate& Direct3D12System::RootSignatureManagerPrivate() noexcept
	{
		return *rootSignatureManager;
	}

	const IDirect3D12RootSignatureManagerPrivate& Direct3D12System::RootSignatureManagerPrivate() const noexcept
	{
		return *rootSignatureManager;
	}

	IDirect3D12MaterialManagerPrivate& Direct3D12System::MaterialManagerPrivate() noexcept
	{
		return *materialManager;
	}

	const IDirect3D12MaterialManagerPrivate& Direct3D12System::MaterialManagerPrivate() const noexcept
	{
		return *materialManager;
	}

	IDirect3D12RenderViewPrivate& Direct3D12System::RenderViewPrivate() noexcept
	{
		return *renderView;
	}

	const IDirect3D12RenderViewPrivate& Direct3D12System::RenderViewPrivate() const noexcept
	{
		return *renderView;
	}

	IDirect3D12RenderObjectManagerPrivate& Direct3D12System::RenderObjectManagerPrivate() noexcept
	{
		return *renderObjectManager;
	}

	const IDirect3D12RenderObjectManagerPrivate& Direct3D12System::RenderObjectManagerPrivate() const noexcept
	{
		return *renderObjectManager;
	}

	IDirect3D12CopyPipeline& Direct3D12System::CopyPipeline() noexcept
	{
		return *copyPipeline;
	}

	const IDirect3D12CopyPipeline& Direct3D12System::CopyPipeline() const noexcept
	{
		return *copyPipeline;
	}

	IDirect3D12GraphicsPipeline& Direct3D12System::GraphicsPipeline() noexcept
	{
		return *graphicsPipeline;
	}

	const IDirect3D12GraphicsPipeline& Direct3D12System::GraphicsPipeline() const noexcept
	{
		return *graphicsPipeline;
	}
}

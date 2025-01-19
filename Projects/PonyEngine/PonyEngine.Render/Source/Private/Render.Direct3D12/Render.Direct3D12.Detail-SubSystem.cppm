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

export module PonyEngine.Render.Direct3D12.Detail:SubSystem;

import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;

import PonyBase.Utility;

import PonyDebug.Log;

import PonyEngine.Render.Direct3D12;

import :BackManager;
import :BackParams;
import :CopyPipeline;
import :CpuWaiter;
import :DepthStencil;
import :DescriptorHeapManager;
import :GpuWaiter;
import :GraphicsPipeline;
import :ICopyPipeline;
import :IDepthStencilPrivate;
import :IDescriptorHeapManager;
import :IGraphicsPipeline;
import :IMaterialManagerPrivate;
import :IMeshManagerPrivate;
import :IRenderObjectManagerPrivate;
import :IRenderTargetPrivate;
import :IRenderViewPrivate;
import :IRenderSystemContext;
import :IRootSignatureManagerPrivate;
import :ISubSystemContext;
import :MaterialManager;
import :MeshManager;
import :ObjectUtility;
import :RenderObjectManager;
import :RenderTarget;
import :RenderTargetParams;
import :RenderView;
import :RenderViewParams;
import :ResourceManager;
import :RootSignatureManager;
import :SubSystemParams;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D 12 system.
	class SubSystem final : private ISubSystemContext
	{
	public:
		/// @brief Creates a @p System.
		/// @param renderSystem Render system context.
		/// @param params Direct3D12 system parameters.
		[[nodiscard("Pure constructor")]]
		SubSystem(IRenderSystemContext& renderSystem, const SubSystemParams& params);
		SubSystem(const SubSystem&) = delete;
		SubSystem(SubSystem&&) = delete;

		~SubSystem() noexcept;

		/// @brief Gets the render target.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render target.
		[[nodiscard("Pure function")]]
		IRenderTarget* RenderTarget() noexcept;
		/// @brief Gets the render target.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render target.
		[[nodiscard("Pure function")]]
		const IRenderTarget* RenderTarget() const noexcept;

		/// @brief Gets the render view.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render view.
		[[nodiscard("Pure function")]]
		IRenderView* RenderView() noexcept;
		/// @brief Gets the render view.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render view.
		[[nodiscard("Pure function")]]
		const IRenderView* RenderView() const noexcept;

		/// @brief Gets the render object manager.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		IRenderObjectManager* RenderObjectManager() noexcept;
		/// @brief Gets the render object manager.
		/// @note It's created in @p CreateRenderSystem().
		/// @return Render object manager.
		[[nodiscard("Pure function")]]
		const IRenderObjectManager* RenderObjectManager() const noexcept;

		/// @brief Gets the graphics command queue.
		/// @return Graphics command queue.
		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& GraphicsCommandQueue() noexcept;
		/// @brief Gets the graphics command queue.
		/// @return Graphics command queue.
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& GraphicsCommandQueue() const noexcept;

		/// @brief Creates a render system.
		/// @param backParams Back parameters.
		/// @param renderTargetParams Render target parameters.
		/// @param renderViewParams Render view parameters.
		void CreateRenderSystem(const BackParams& backParams, const RenderTargetParams& renderTargetParams, const RenderViewParams& renderViewParams);

		/// @brief Begins a new frame.
		void BeginFrame();
		/// @brief Renders to the back buffer at the @p bufferIndex.
		/// @param backBufferIndex Current back buffer index.
		void Render(UINT backBufferIndex);
		/// @brief Ends a current frame.
		void EndFrame();

		SubSystem& operator =(const SubSystem&) = delete;
		SubSystem& operator =(SubSystem&&) = delete;

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
		virtual IBackManager& BackPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IBackManager& BackPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IRenderTargetPrivate& RenderTargetPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IRenderTargetPrivate& RenderTargetPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDepthStencilPrivate& DepthStencilPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDepthStencilPrivate& DepthStencilPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IRenderViewPrivate& RenderViewPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IRenderViewPrivate& RenderViewPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IMeshManager& MeshManagerPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IMeshManager& MeshManagerPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IRootSignatureManagerPrivate& RootSignatureManagerPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IRootSignatureManagerPrivate& RootSignatureManagerPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IMaterialManagerPrivate& MaterialManagerPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IMaterialManagerPrivate& MaterialManagerPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IResourceManager& ResourceManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IResourceManager& ResourceManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDescriptorHeapManager& DescriptorHeapManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDescriptorHeapManager& DescriptorHeapManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IRenderObjectManagerPrivate& RenderObjectManagerPrivate() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IRenderObjectManagerPrivate& RenderObjectManagerPrivate() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ICopyPipeline& CopyPipeline() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ICopyPipeline& CopyPipeline() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IGraphicsPipeline& GraphicsPipeline() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IGraphicsPipeline& GraphicsPipeline() const noexcept override;

		IRenderSystemContext* renderSystem; ///< Render system context.

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> debug; ///< Debug interface.
#endif
		Microsoft::WRL::ComPtr<ID3D12Device10> device; ///< Render device.

		std::unique_ptr<BackManager> back; ///< Back.
		std::unique_ptr<class RenderTarget> renderTarget; ///< Render target.
		std::unique_ptr<DepthStencil> depthStencil; ///< Depth stencil.
		std::unique_ptr<class RenderView> renderView; ///< Render view.

		std::unique_ptr<MeshManager> meshManager; ///< Mesh manager.
		std::unique_ptr<RootSignatureManager> rootSignatureManager; ///< Root signature manager.
		std::unique_ptr<MaterialManager> materialManager; ///< Material manager.
		std::unique_ptr<class ResourceManager> resourceManager;
		std::unique_ptr<class DescriptorHeapManager> heapManager;
		std::unique_ptr<Direct3D12RenderObjectManager> renderObjectManager; ///< Render object manager.

		std::unique_ptr<class CopyPipeline> copyPipeline; ///< Copy pipeline.
		std::unique_ptr<class GraphicsPipeline> graphicsPipeline; ///< Graphics pipeline.

		std::unique_ptr<GpuWaiter> copyWaiter; ///< Copy pipeline waiter.
		std::unique_ptr<CpuWaiter> graphicsWaiter; ///< Graphics pipeline waiter.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	SubSystem::SubSystem(IRenderSystemContext& renderSystem, const SubSystemParams& params) :
		renderSystem{&renderSystem}
	{
#ifdef _DEBUG
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Acquire debug interface.");
		if (const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire debug interface with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Debug interface acquired.");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Debug, "Enable debug layer.");
		debug->EnableDebugLayer();
#endif

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Acquire device. Feature level: '0x{:X}.'", static_cast<unsigned int>(params.featureLevel));
		if (const HRESULT result = D3D12CreateDevice(nullptr, params.featureLevel, IID_PPV_ARGS(device.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire device with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		SetName(*device.Get(), "RenderDevice");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Device acquired.");

		resourceManager = std::make_unique<class ResourceManager>(*static_cast<ISubSystemContext*>(this));

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create descriptor heap manager.");
		heapManager = std::make_unique<class DescriptorHeapManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Descriptor heap manager created.");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create copy pipeline.");
		copyPipeline = std::make_unique<class CopyPipeline>(*static_cast<ISubSystemContext*>(this), params.commandQueuePriority);
		copyPipeline->Name("CopyPipeline");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline created.");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create graphics pipeline.");
		graphicsPipeline = std::make_unique<class GraphicsPipeline>(*static_cast<ISubSystemContext*>(this), params.commandQueuePriority);
		graphicsPipeline->Name("GraphicsPipeline");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline created.'");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create copy pipeline waiter.");
		copyWaiter = std::make_unique<GpuWaiter>(*static_cast<ISubSystemContext*>(this), copyPipeline->CommandQueue(), graphicsPipeline->CommandQueue());
		copyWaiter->Name("CopyToGraphicsWaiter");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline waiter created.");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create graphics pipeline waiter. Wait timeout: {}.", params.renderTimeout);
		graphicsWaiter = std::make_unique<CpuWaiter>(*static_cast<ISubSystemContext*>(this), graphicsPipeline->CommandQueue(), params.renderTimeout);
		graphicsWaiter->Name("GraphicsEndWaiter");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline waiter created.");
	}

	SubSystem::~SubSystem() noexcept
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

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy back.");
		back.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Back destroyed.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Release device.");
		device.Reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Device released.");

#ifdef _DEBUG
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Release debug interface.");
		debug.Reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Debug interface released.");
#endif
	}

	IRenderTarget* SubSystem::RenderTarget() noexcept
	{
		return renderTarget.get();
	}

	const IRenderTarget* SubSystem::RenderTarget() const noexcept
	{
		return renderTarget.get();
	}

	IRenderView* SubSystem::RenderView() noexcept
	{
		return renderView.get();
	}

	const IRenderView* SubSystem::RenderView() const noexcept
	{
		return renderView.get();
	}

	IRenderObjectManager* SubSystem::RenderObjectManager() noexcept
	{
		return renderObjectManager.get();
	}

	const IRenderObjectManager* SubSystem::RenderObjectManager() const noexcept
	{
		return renderObjectManager.get();
	}

	ID3D12CommandQueue& SubSystem::GraphicsCommandQueue() noexcept
	{
		return graphicsPipeline->CommandQueue();
	}

	const ID3D12CommandQueue& SubSystem::GraphicsCommandQueue() const noexcept
	{
		return graphicsPipeline->CommandQueue();
	}

	void SubSystem::CreateRenderSystem(const BackParams& backParams, const RenderTargetParams& renderTargetParams, const RenderViewParams& renderViewParams)
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create back.");
		back = std::make_unique<BackManager>(*static_cast<ISubSystemContext*>(this), backParams);
		back->Name("Back");
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Back created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create render target.");
		renderTarget = std::make_unique<class RenderTarget>(*static_cast<ISubSystemContext*>(this), renderTargetParams);
		renderTarget->Name("RenderTarget");
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render target created.");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create render view.");
		renderView = std::make_unique<class RenderView>(renderViewParams);
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render view created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create depth stencil.");
		depthStencil = std::make_unique<DepthStencil>(*static_cast<ISubSystemContext*>(this));
		depthStencil->Name("DepthStencil");
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create mesh manager.");
		meshManager = std::make_unique<MeshManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Mesh manager created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create root signature manager.");
		rootSignatureManager = std::make_unique<RootSignatureManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Root signature manager created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create material manager.");
		materialManager = std::make_unique<MaterialManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Material manager created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create render object manager.");
		renderObjectManager = std::make_unique<Direct3D12RenderObjectManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render object manager created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create srgb output quad.");
		graphicsPipeline->CreateSrgbOutputQuad();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Srgb output quad created.");
	}

	void SubSystem::BeginFrame()
	{
		renderObjectManager->Clean();
		meshManager->Clean();
		materialManager->Clean();
		rootSignatureManager->Clean();

		meshManager->Tick();
	}

	void SubSystem::Render(const UINT backBufferIndex)
	{
		renderObjectManager->AddRenderTasks();
		graphicsPipeline->Prepare();

		copyPipeline->PopulateCommands();
		copyPipeline->Execute();

		back->CurrentBackBufferIndex(backBufferIndex);
		graphicsPipeline->PopulateCommands();

		copyWaiter->Wait();
		graphicsPipeline->Execute();
	}

	void SubSystem::EndFrame()
	{
		graphicsWaiter->Wait();

		copyPipeline->Clear();
		graphicsPipeline->Clear();
	}

	PonyDebug::Log::ILogger& SubSystem::Logger() noexcept
	{
		return renderSystem->Logger();
	}

	const PonyDebug::Log::ILogger& SubSystem::Logger() const noexcept
	{
		return renderSystem->Logger();
	}

	ID3D12Device10& SubSystem::Device() noexcept
	{
		return *device.Get();
	}

	const ID3D12Device10& SubSystem::Device() const noexcept
	{
		return *device.Get();
	}

	IBackManager& SubSystem::BackPrivate() noexcept
	{
		return *back;
	}

	const IBackManager& SubSystem::BackPrivate() const noexcept
	{
		return *back;
	}

	IRenderTargetPrivate& SubSystem::RenderTargetPrivate() noexcept
	{
		return *renderTarget;
	}

	const IRenderTargetPrivate& SubSystem::RenderTargetPrivate() const noexcept
	{
		return *renderTarget;
	}

	IDepthStencilPrivate& SubSystem::DepthStencilPrivate() noexcept
	{
		return *depthStencil;
	}

	const IDepthStencilPrivate& SubSystem::DepthStencilPrivate() const noexcept
	{
		return *depthStencil;
	}

	IMeshManager& SubSystem::MeshManagerPrivate() noexcept
	{
		return *meshManager;
	}

	const IMeshManager& SubSystem::MeshManagerPrivate() const noexcept
	{
		return *meshManager;
	}

	IRootSignatureManagerPrivate& SubSystem::RootSignatureManagerPrivate() noexcept
	{
		return *rootSignatureManager;
	}

	const IRootSignatureManagerPrivate& SubSystem::RootSignatureManagerPrivate() const noexcept
	{
		return *rootSignatureManager;
	}

	IMaterialManagerPrivate& SubSystem::MaterialManagerPrivate() noexcept
	{
		return *materialManager;
	}

	const IMaterialManagerPrivate& SubSystem::MaterialManagerPrivate() const noexcept
	{
		return *materialManager;
	}

	IResourceManager& SubSystem::ResourceManager() noexcept
	{
		return *resourceManager;
	}

	const IResourceManager& SubSystem::ResourceManager() const noexcept
	{
		return *resourceManager;
	}

	IDescriptorHeapManager& SubSystem::DescriptorHeapManager() noexcept
	{
		return *heapManager;
	}

	const IDescriptorHeapManager& SubSystem::DescriptorHeapManager() const noexcept
	{
		return *heapManager;
	}

	IRenderViewPrivate& SubSystem::RenderViewPrivate() noexcept
	{
		return *renderView;
	}

	const IRenderViewPrivate& SubSystem::RenderViewPrivate() const noexcept
	{
		return *renderView;
	}

	IRenderObjectManagerPrivate& SubSystem::RenderObjectManagerPrivate() noexcept
	{
		return *renderObjectManager;
	}

	const IRenderObjectManagerPrivate& SubSystem::RenderObjectManagerPrivate() const noexcept
	{
		return *renderObjectManager;
	}

	ICopyPipeline& SubSystem::CopyPipeline() noexcept
	{
		return *copyPipeline;
	}

	const ICopyPipeline& SubSystem::CopyPipeline() const noexcept
	{
		return *copyPipeline;
	}

	IGraphicsPipeline& SubSystem::GraphicsPipeline() noexcept
	{
		return *graphicsPipeline;
	}

	const IGraphicsPipeline& SubSystem::GraphicsPipeline() const noexcept
	{
		return *graphicsPipeline;
	}
}

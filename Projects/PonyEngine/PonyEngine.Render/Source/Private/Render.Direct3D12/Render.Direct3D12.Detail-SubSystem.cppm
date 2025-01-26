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
import :CameraManager;
import :CopyPipeline;
import :CpuWaiter;
import :DescriptorHeapManager;
import :FrameManager;
import :GpuWaiter;
import :GraphicsPipeline;
import :ICopyPipeline;
import :IDescriptorHeapManager;
import :IFrameManager;
import :IGraphicsPipeline;
import :IMaterialManager;
import :IMeshManager;
import :IRenderSystemContext;
import :IRootSignatureManager;
import :ISubSystemContext;
import :MaterialManager;
import :MeshManager;
import :ObjectUtility;
import :RenderObjectManager;
import :RenderTargetParams;
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
		[[nodiscard("Pure constructor")]]
		SubSystem(IRenderSystemContext& renderSystem, const SubSystemParams& subSystemParams);
		SubSystem(const SubSystem&) = delete;
		SubSystem(SubSystem&&) = delete;

		~SubSystem() noexcept;

		[[nodiscard("Pure function")]]
		ICameraManager* CameraManager() noexcept;
		[[nodiscard("Pure function")]]
		const ICameraManager* CameraManager() const noexcept;
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
		/// @param frameParams Render target parameters.
		void CreateRenderSystem(const BackParams& backParams, const FrameParams& frameParams);

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
		virtual IBackManager& BackManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IBackManager& BackManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IFrameManager& FrameManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IFrameManager& FrameManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IMeshManager& MeshManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IMeshManager& MeshManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IRootSignatureManager& RootSignatureManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IRootSignatureManager& RootSignatureManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IMaterialManager& MaterialManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IMaterialManager& MaterialManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IResourceManager& ResourceManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IResourceManager& ResourceManager() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual IDescriptorHeapManager& DescriptorHeapManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IDescriptorHeapManager& DescriptorHeapManager() const noexcept override;

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

		std::unique_ptr<class BackManager> back; ///< Back.
		std::unique_ptr<class FrameManager> frameManager; ///< Frame manager.

		std::unique_ptr<class ResourceManager> resourceManager;
		std::unique_ptr<class DescriptorHeapManager> heapManager;
		std::unique_ptr<class MeshManager> meshManager; ///< Mesh manager.
		std::unique_ptr<class RootSignatureManager> rootSignatureManager; ///< Root signature manager.
		std::unique_ptr<class MaterialManager> materialManager; ///< Material manager.

		std::unique_ptr<class CameraManager> cameraManager;
		std::unique_ptr<class RenderObjectManager> renderObjectManager; ///< Render object manager.

		std::unique_ptr<class CopyPipeline> copyPipeline; ///< Copy pipeline.
		std::unique_ptr<class GraphicsPipeline> graphicsPipeline; ///< Graphics pipeline.

		std::unique_ptr<GpuWaiter> copyWaiter; ///< Copy pipeline waiter.
		std::unique_ptr<CpuWaiter> graphicsWaiter; ///< Graphics pipeline waiter.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	SubSystem::SubSystem(IRenderSystemContext& renderSystem, const SubSystemParams& subSystemParams) :
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

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Acquire device.'");
		if (const HRESULT result = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_2, IID_PPV_ARGS(device.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire device with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		SetName(*device.Get(), "RenderDevice");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Device acquired.");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create copy pipeline.");
		copyPipeline = std::make_unique<class CopyPipeline>(*static_cast<ISubSystemContext*>(this), subSystemParams.commandQueuePriority);
		copyPipeline->Name("CopyPipeline");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline created.");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create graphics pipeline.");
		graphicsPipeline = std::make_unique<class GraphicsPipeline>(*static_cast<ISubSystemContext*>(this), subSystemParams.commandQueuePriority);
		graphicsPipeline->Name("GraphicsPipeline");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline created.'");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create copy pipeline waiter.");
		copyWaiter = std::make_unique<GpuWaiter>(*static_cast<ISubSystemContext*>(this), copyPipeline->CommandQueue(), graphicsPipeline->CommandQueue());
		copyWaiter->Name("CopyToGraphicsWaiter");
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Copy pipeline waiter created.");

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create graphics pipeline waiter. Wait timeout: {}.", subSystemParams.renderTimeout);
		graphicsWaiter = std::make_unique<CpuWaiter>(*static_cast<ISubSystemContext*>(this), graphicsPipeline->CommandQueue(), subSystemParams.renderTimeout);
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

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Destroy frame manager.");
		frameManager.reset();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Frame manager destroyed.");

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

	ICameraManager* SubSystem::CameraManager() noexcept
	{
		return cameraManager.get();
	}

	const ICameraManager* SubSystem::CameraManager() const noexcept
	{
		return cameraManager.get();
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

	void SubSystem::CreateRenderSystem(const BackParams& backParams, const FrameParams& frameParams)
	{
		resourceManager = std::make_unique<class ResourceManager>(*static_cast<ISubSystemContext*>(this));

		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create descriptor heap manager.");
		heapManager = std::make_unique<class DescriptorHeapManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(this->renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Descriptor heap manager created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create back.");
		back = std::make_unique<class BackManager>(*static_cast<ISubSystemContext*>(this), backParams);
		back->Name("Back");
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Back created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create frame manager.");
		frameManager = std::make_unique<class FrameManager>(*static_cast<ISubSystemContext*>(this), frameParams);
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Frame manager created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create mesh manager.");
		meshManager = std::make_unique<class MeshManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Mesh manager created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create root signature manager.");
		rootSignatureManager = std::make_unique<class RootSignatureManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Root signature manager created.");

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create material manager.");
		materialManager = std::make_unique<class MaterialManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Material manager created.");

		cameraManager = std::make_unique<class CameraManager>(*static_cast<ISubSystemContext*>(this));

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Create render object manager.");
		renderObjectManager = std::make_unique<class RenderObjectManager>(*static_cast<ISubSystemContext*>(this));
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Render object manager created.");

		graphicsPipeline->CreateFrame();
	}

	void SubSystem::BeginFrame()
	{
		renderObjectManager->Clean();
		meshManager->Clean();
		materialManager->Clean();
		rootSignatureManager->Clean();
		frameManager->Clean();
		heapManager->Clean();
		resourceManager->Clean();
		cameraManager->Clean();
	}

	void SubSystem::Render(const UINT backBufferIndex)
	{
		cameraManager->Tick();
		meshManager->Tick();
		renderObjectManager->Tick();
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

		graphicsPipeline->Clear();
		copyPipeline->Clear();
		meshManager->Clear();
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

	IBackManager& SubSystem::BackManager() noexcept
	{
		return *back;
	}

	const IBackManager& SubSystem::BackManager() const noexcept
	{
		return *back;
	}

	IFrameManager& SubSystem::FrameManager() noexcept
	{
		return *frameManager;
	}

	const IFrameManager& SubSystem::FrameManager() const noexcept
	{
		return *frameManager;
	}

	IMeshManager& SubSystem::MeshManager() noexcept
	{
		return *meshManager;
	}

	const IMeshManager& SubSystem::MeshManager() const noexcept
	{
		return *meshManager;
	}

	IRootSignatureManager& SubSystem::RootSignatureManager() noexcept
	{
		return *rootSignatureManager;
	}

	const IRootSignatureManager& SubSystem::RootSignatureManager() const noexcept
	{
		return *rootSignatureManager;
	}

	IMaterialManager& SubSystem::MaterialManager() noexcept
	{
		return *materialManager;
	}

	const IMaterialManager& SubSystem::MaterialManager() const noexcept
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

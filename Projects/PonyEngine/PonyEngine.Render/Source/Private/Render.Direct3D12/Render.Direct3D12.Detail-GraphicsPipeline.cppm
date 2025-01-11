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

export module PonyEngine.Render.Direct3D12.Detail:GraphicsPipeline;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <memory>;
import <optional>;
import <set>;
import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;
import <vector>;

import PonyBase.Utility.COM;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Utility;

import :IDepthStencilPrivate;
import :IGraphicsPipeline;
import :IRenderTargetPrivate;
import :IRenderViewPrivate;
import :ISubSystemContext;
import :Material;
import :Mesh;
import :ObjectUtility;
import :RootSignature;
import :RenderObject;
import :SrgbOutputQuad;
import :Transform;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 graphics pipeline.
	class GraphicsPipeline final : public IGraphicsPipeline
	{
	public:
		/// @brief Creates a @p GraphicsPipeline.
		/// @param d3d12System Direct3D12 system context.
		/// @param commandQueuePriority Command queue priority.
		[[nodiscard("Pure constructor")]]
		GraphicsPipeline(ISubSystemContext& d3d12System, INT commandQueuePriority);
		GraphicsPipeline(const GraphicsPipeline&) = delete;
		GraphicsPipeline(GraphicsPipeline&&) = delete;

		~GraphicsPipeline() noexcept;

		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& CommandQueue() noexcept;
		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& CommandQueue() const noexcept;

		virtual void AddRenderTask(const std::shared_ptr<RenderObject>& renderObject) override;

		/// @brief Creates an srgb output quad.
		/// @remark Must be called after other d3d12 system components are created but before a first render.
		void CreateSrgbOutputQuad();

		/// @brief Sets the name to the graphics pipeline components.
		/// @param name Name.
		void Name(std::string_view name);

		/// @brief Populates commands. All the system components must be ready.
		void PopulateCommands();
		/// @brief Executes populated commands.
		void Execute();
		/// @brief Clears the tasks. Must be called only after finishing execution.
		void Clear() noexcept;

		GraphicsPipeline& operator =(const GraphicsPipeline&) = delete;
		GraphicsPipeline& operator =(GraphicsPipeline&&) = delete;

	private:
		/// @brief Direct3D12 render object entry. It's used in the cache.
		struct Direct3D12RenderObjectEntry final
		{
			std::shared_ptr<RenderObject> renderObject; ///< Render object.
			Transform transform; ///< Transform.
		};

		/// @brief Resets command lists.
		void ResetLists();
		/// @brief Closes command lists.
		void CloseLists();

		/// @brief Updates render object meshes cache.
		void UpdateMeshes();
		/// @brief Populates begin to render barriers in an msaa context.
		/// @param renderTargetBuffer Render target buffer.
		/// @param depthStencilBuffer Depth stencil buffer.
		void PopulateBeginToRenderBarriers(ID3D12Resource2& renderTargetBuffer, ID3D12Resource2& depthStencilBuffer);
		/// @brief Populates a render target.
		/// @param resolution Render resolution.
		/// @param clearColor Clear color.
		/// @param rtvHandle Rtv handle.
		/// @param dsvHandle Dsv handle.
		void PopulateRenderTarget(const PonyMath::Utility::Resolution<UINT>& resolution, const PonyMath::Color::RGBA<FLOAT>& clearColor, D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle, D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);
		/// @brief Populates render objects.
		void PopulateRenderObjects();
		/// @brief Populate output.
		/// @param renderTargetHeap Render target heap.
		/// @param renderTargetHandle Render target handle.
		/// @param backViewHandle Back view handle.
		void PopulateOutput(ID3D12DescriptorHeap& renderTargetHeap, D3D12_GPU_DESCRIPTOR_HANDLE renderTargetHandle, D3D12_CPU_DESCRIPTOR_HANDLE backViewHandle);
		/// @brief Populates output to end barriers.
		/// @param renderTargetBuffer Render target buffer.
		/// @param backBuffer 
		void PopulateOutputToEndBarriers(ID3D12Resource2& renderTargetBuffer, ID3D12Resource2& backBuffer);

		/// @brief Populates render to output barriers.
		/// @param renderTargetBuffer Render target buffer.
		/// @param backBuffer Back buffer.
		/// @param depthStencilBuffer Depth stencil buffer.
		void PopulateRenderToOutputBarriers(ID3D12Resource2& renderTargetBuffer, ID3D12Resource2& backBuffer, ID3D12Resource2& depthStencilBuffer);

		/// @brief Populates render to resolve barriers.
		/// @param resolveSourceBuffer Resolve source buffer.
		/// @param resolveDestinationBuffer Resolve destination buffer.
		/// @param depthStencilBuffer Depth stencil buffer.
		void PopulateRenderToResolveBarriers(ID3D12Resource2& resolveSourceBuffer, ID3D12Resource2& resolveDestinationBuffer, ID3D12Resource2& depthStencilBuffer);
		/// @brief Populates resolve.
		/// @param resolveSourceBuffer Resolve source buffer.
		/// @param resolveDestinationBuffer Resolve destination buffer.
		/// @param format Resource format.
		void PopulateResolve(ID3D12Resource2& resolveSourceBuffer, ID3D12Resource2& resolveDestinationBuffer, DXGI_FORMAT format);
		/// @brief Populates resolve to output barriers.
		/// @param resolveSourceBuffer Resolve source buffer.
		/// @param resolveDestinationBuffer Resolve destination buffer.
		/// @param backBuffer Back buffer.
		void PopulateResolveToOutputBarriers(ID3D12Resource2& resolveSourceBuffer, ID3D12Resource2& resolveDestinationBuffer, ID3D12Resource2& backBuffer);

		/// @brief Populates barrier groups.
		void PopulateBarrierGroups();

		GUID guid; ///< Graphics pipeline guid.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Graphics command queue.
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator; ///< Graphics command allocator.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList; ///< Graphics command list.

		std::vector<Direct3D12RenderObjectEntry> renderObjects; ///< Render objects.
		std::set<Mesh*> meshes; ///< Render object meshes cache.

		std::vector<D3D12_BUFFER_BARRIER> bufferBarriers; ///< Buffer barriers cache.
		std::vector<D3D12_TEXTURE_BARRIER> textureBarriers; ///< Buffer barriers cache.

		std::unique_ptr<SrgbOutputQuad> outputQuad; ///< Srgb output quad.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	GraphicsPipeline::GraphicsPipeline(ISubSystemContext& d3d12System, const INT commandQueuePriority) :
		guid{PonyBase::Utility::COM::AcquireGuid()},
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline guid: '{}'.", PonyBase::Utility::COM::ToString(guid));

		constexpr D3D12_COMMAND_LIST_TYPE commandListType = D3D12_COMMAND_LIST_TYPE_DIRECT;

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire direct command queue. Priority: '{}'.", commandQueuePriority);
		const auto commandQueueDescription = D3D12_COMMAND_QUEUE_DESC
		{
			.Type = commandListType,
			.Priority = commandQueuePriority,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			.NodeMask = 0u
		};
		ID3D12Device10& device = this->d3d12System->Device();
		if (const HRESULT result = device.CreateCommandQueue1(&commandQueueDescription, guid, IID_PPV_ARGS(commandQueue.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire direct command queue with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command queue acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire direct command allocator.");
		if (const HRESULT result = device.CreateCommandAllocator(commandListType, IID_PPV_ARGS(commandAllocator.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire direct command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command allocator acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire direct command list.");
		if (const HRESULT result = device.CreateCommandList1(0, commandListType, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(commandList.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire direct command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command list acquired.");
	}

	GraphicsPipeline::~GraphicsPipeline() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy srgb output quad.");
		outputQuad.reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output quad destroyed.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release direct command list.");
		commandList.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command list released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release direct command allocator.");
		commandAllocator.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command allocator released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release direct command queue.");
		commandQueue.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command queue released.");
	}

	ID3D12CommandQueue& GraphicsPipeline::CommandQueue() noexcept
	{
		return *commandQueue.Get();
	}

	const ID3D12CommandQueue& GraphicsPipeline::CommandQueue() const noexcept
	{
		return *commandQueue.Get();
	}

	void GraphicsPipeline::AddRenderTask(const std::shared_ptr<RenderObject>& renderObject)
	{
		renderObjects.push_back(Direct3D12RenderObjectEntry{.renderObject = renderObject});
	}

	void GraphicsPipeline::CreateSrgbOutputQuad()
	{
		outputQuad = std::make_unique<SrgbOutputQuad>(*d3d12System);
		outputQuad->Name("OutputQuad");
	}

	void GraphicsPipeline::Name(const std::string_view name)
	{
		constexpr std::string_view commandQueueName = " - CommandQueue";
		constexpr std::string_view commandAllocatorName = " - CommandAllocator";
		constexpr std::string_view commandListName = " - CommandList";

		auto componentName = std::string();
		componentName.reserve(name.size() + commandAllocatorName.size());

		componentName.append(name).append(commandQueueName);
		SetName(*commandQueue.Get(), componentName);

		componentName.clear();
		componentName.append(name).append(commandAllocatorName);
		SetName(*commandAllocator.Get(), componentName);

		componentName.clear();
		componentName.append(name).append(commandListName);
		SetName(*commandList.Get(), componentName);
	}

	void GraphicsPipeline::PopulateCommands()
	{
		IRenderTargetPrivate& renderTarget = d3d12System->RenderTargetPrivate();
		IDepthStencilPrivate& depthStencil = d3d12System->DepthStencilPrivate();
		IBackPrivate& back = d3d12System->BackPrivate();

		ID3D12Resource2& renderTargetBuffer = renderTarget.RenderTargetBuffer();
		ID3D12Resource2* const msaaRenderTargetBuffer = renderTarget.RenderTargetBufferMsaa();
		ID3D12Resource2& depthStencilBuffer = depthStencil.DepthStencilBuffer();
		ID3D12Resource2& backBuffer = back.CurrentBackBuffer();

		ID3D12Resource2& mainRenderTargetBuffer = msaaRenderTargetBuffer ? *msaaRenderTargetBuffer : renderTargetBuffer;
		const D3D12_CPU_DESCRIPTOR_HANDLE mainRenderTargetHandle = msaaRenderTargetBuffer ? renderTarget.RtvHandleMsaa() : renderTarget.RtvHandle();

		ResetLists();
		UpdateMeshes();
		PopulateBeginToRenderBarriers(mainRenderTargetBuffer, depthStencilBuffer);
		PopulateRenderTarget(renderTarget.ResolutionD3D12(), renderTarget.ClearColorD3D12(), mainRenderTargetHandle, depthStencil.DsvHandle());
		PopulateRenderObjects();
		if (msaaRenderTargetBuffer)
		{
			PopulateRenderToResolveBarriers(mainRenderTargetBuffer, renderTargetBuffer, depthStencilBuffer);
			PopulateResolve(mainRenderTargetBuffer, renderTargetBuffer, renderTarget.Format());
			PopulateResolveToOutputBarriers(mainRenderTargetBuffer, renderTargetBuffer, backBuffer);
		}
		else
		{
			PopulateRenderToOutputBarriers(mainRenderTargetBuffer, backBuffer, depthStencilBuffer);
		}
		PopulateOutput(renderTarget.SrvHeap(), renderTarget.SrvHandle(), back.CurrentBackViewHandle());
		PopulateOutputToEndBarriers(renderTargetBuffer, backBuffer);
		CloseLists();
	}

	void GraphicsPipeline::Execute()
	{
		const auto commandLists = std::array<ID3D12CommandList*, 1> { commandList.Get() };
		commandQueue->ExecuteCommandLists(static_cast<UINT>(commandLists.size()), commandLists.data());
	}

	void GraphicsPipeline::Clear() noexcept
	{
		renderObjects.clear();
	}

	void GraphicsPipeline::ResetLists()
	{
		if (const HRESULT result = commandAllocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = commandList->Reset(commandAllocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void GraphicsPipeline::CloseLists()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void GraphicsPipeline::UpdateMeshes()
	{
		meshes.clear();
		for (const Direct3D12RenderObjectEntry& renderObjectEntry : renderObjects)
		{
			meshes.insert(&renderObjectEntry.renderObject->Mesh());
		}
	}

	void GraphicsPipeline::PopulateBeginToRenderBarriers(ID3D12Resource2& renderTargetBuffer, ID3D12Resource2& depthStencilBuffer)
	{
		bufferBarriers.clear();
		for (Mesh* const mesh : meshes)
		{
			for (const std::string& dataType : mesh->DataTypes())
			{
				const std::size_t bufferCount = mesh->BufferCount(dataType).value();
				for (std::size_t i = 0; i < bufferCount; ++i)
				{
					const auto bufferBarrier = D3D12_BUFFER_BARRIER
					{
						.SyncBefore = D3D12_BARRIER_SYNC_NONE,
						.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
						.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
						.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
						.pResource = mesh->FindBuffer(dataType, i),
						.Offset = 0UL,
						.Size = UINT64_MAX
					};
					bufferBarriers.push_back(bufferBarrier);
				}
			}
		}

		textureBarriers.clear();
		textureBarriers.reserve(2);
		const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.pResource = &renderTargetBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(renderTargetBarrier);
		const auto depthStencilBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE,
			.pResource = &depthStencilBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(depthStencilBarrier);

		PopulateBarrierGroups();
	}

	void GraphicsPipeline::PopulateRenderTarget(const PonyMath::Utility::Resolution<UINT>& resolution, const PonyMath::Color::RGBA<FLOAT>& clearColor, const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle, const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
	{
		const auto viewport = D3D12_VIEWPORT{.TopLeftX = 0.f, .TopLeftY = 0.f, .Width = static_cast<FLOAT>(resolution.Width()), .Height = static_cast<FLOAT>(resolution.Height()), .MinDepth = D3D12_MIN_DEPTH, .MaxDepth = D3D12_MAX_DEPTH};
		commandList->RSSetViewports(1u, &viewport);
		const auto rect = D3D12_RECT{.left = 0L, .top = 0L, .right = static_cast<LONG>(resolution.Width()), .bottom = static_cast<LONG>(resolution.Height())};
		commandList->RSSetScissorRects(1u, &rect);

		commandList->OMSetRenderTargets(1u, &rtvHandle, false, &dsvHandle);
		commandList->ClearRenderTargetView(rtvHandle, clearColor.Span().data(), 0u, nullptr);
		commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, D3D12_MAX_DEPTH, 0u, 0u, nullptr);
	}

	void GraphicsPipeline::PopulateRenderObjects()
	{
		const IRenderViewPrivate& renderView = d3d12System->RenderViewPrivate();
		const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix = renderView.ViewMatrixD3D12();
		const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix = renderView.ProjectionMatrixD3D12();
		for (Direct3D12RenderObjectEntry& renderObject : renderObjects)
		{
			renderObject.transform = Transform(renderObject.renderObject->ModelMatrixD3D12(), viewMatrix, projectionMatrix);
		}

		std::ranges::sort(renderObjects, [](const Direct3D12RenderObjectEntry& left, const Direct3D12RenderObjectEntry& right)
		{
			const Material* const leftMaterial = &left.renderObject->Material();
			const Material* const rightMaterial = &right.renderObject->Material();
			const bool isLeftTransparent = leftMaterial->IsTransparent();
			const bool isRightTransparent = rightMaterial->IsTransparent();

			if (isLeftTransparent != isRightTransparent)
			{
				return isLeftTransparent < isRightTransparent;
			}

			if (isLeftTransparent)
			{
				return PonyMath::Core::ExtractTranslation(left.transform.MvpMatrix()).Z() > PonyMath::Core::ExtractTranslation(right.transform.MvpMatrix()).Z();
			}

			if (const RootSignature* const leftRootSignature = &leftMaterial->RootSignature(), * const rightRootSignature = &rightMaterial->RootSignature(); leftRootSignature != rightRootSignature)
			{
				return reinterpret_cast<std::uintptr_t>(leftRootSignature) < reinterpret_cast<std::uintptr_t>(rightRootSignature);
			}
			if (leftMaterial != rightMaterial)
			{
				return reinterpret_cast<std::uintptr_t>(leftMaterial) < reinterpret_cast<std::uintptr_t>(rightMaterial);
			}

			if (const Mesh* const leftMesh = &left.renderObject->Mesh(), * const rightMesh = &right.renderObject->Mesh(); leftMesh != rightMesh)
			{
				return reinterpret_cast<std::uintptr_t>(leftMesh) < reinterpret_cast<std::uintptr_t>(rightMesh);
			}

			return PonyMath::Core::ExtractTranslation(left.transform.MvpMatrix()).Z() < PonyMath::Core::ExtractTranslation(right.transform.MvpMatrix()).Z();
		});

		const RootSignature* prevRootSignature = nullptr;
		const Material* prevMaterial = nullptr;
		const Mesh* prevMesh = nullptr;
		for (const Direct3D12RenderObjectEntry& renderObject : renderObjects)
		{
			Material* const material = &renderObject.renderObject->Material();
			RootSignature* const rootSignature = &material->RootSignature();
			if (rootSignature != prevRootSignature)
			{
				commandList->SetGraphicsRootSignature(&rootSignature->ControlledRootSignature());
			}
			if (material != prevMaterial)
			{
				commandList->SetPipelineState(&material->PipelineState());
			}

			Mesh* const mesh = &renderObject.renderObject->Mesh();
			if (mesh != prevMesh)
			{
				ID3D12DescriptorHeap* const heap = &mesh->Heap();
				commandList->SetDescriptorHeaps(1u, &heap);
			}

			if (mesh != prevMesh || rootSignature != prevRootSignature)
			{
				for (const std::string& dataType : mesh->DataTypes())
				{
					if (const std::optional<UINT> slot = rootSignature->FindDataSlot(dataType))
					{
						commandList->SetGraphicsRootDescriptorTable(slot.value(), mesh->FindHandle(dataType).value());
					}
				}
			}

			if (const std::optional<UINT> slot = rootSignature->FindDataSlot(PonyTransform))
			{
				commandList->SetGraphicsRoot32BitConstants(slot.value(), PonyMath::Core::Matrix4x4<FLOAT>::ComponentCount, renderObject.transform.MvpMatrix().Span().data(), 0);
			}

			const std::span<const UINT, 3> threadGroupCounts = mesh->ThreadGroupCounts();
			commandList->DispatchMesh(threadGroupCounts[0], threadGroupCounts[1], threadGroupCounts[2]);

			prevRootSignature = rootSignature;
			prevMaterial = material;
			prevMesh = mesh;
		}
	}

	void GraphicsPipeline::PopulateOutput(ID3D12DescriptorHeap& renderTargetHeap, const D3D12_GPU_DESCRIPTOR_HANDLE renderTargetHandle, const D3D12_CPU_DESCRIPTOR_HANDLE backViewHandle)
	{
		commandList->OMSetRenderTargets(1u, &backViewHandle, false, nullptr);

		commandList->SetGraphicsRootSignature(&outputQuad->RootSignature());
		commandList->SetPipelineState(&outputQuad->PipelineState());

		ID3D12DescriptorHeap* const heap = &renderTargetHeap;
		commandList->SetDescriptorHeaps(1u, &heap);
		commandList->SetGraphicsRootDescriptorTable(outputQuad->RenderTargetSlot, renderTargetHandle);

		commandList->DispatchMesh(outputQuad->ThreadGroupXCount, outputQuad->ThreadGroupYCount, outputQuad->ThreadGroupZCount);
	}

	void GraphicsPipeline::PopulateOutputToEndBarriers(ID3D12Resource2& renderTargetBuffer, ID3D12Resource2& backBuffer)
	{
		bufferBarriers.clear();

		textureBarriers.clear();
		textureBarriers.reserve(2);
		const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
			.pResource = &renderTargetBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(renderTargetBarrier);
		const auto backBufferBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_PRESENT,
			.pResource = &backBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(backBufferBarrier);

		PopulateBarrierGroups();
	}

	void GraphicsPipeline::PopulateRenderToOutputBarriers(ID3D12Resource2& renderTargetBuffer, ID3D12Resource2& backBuffer, ID3D12Resource2& depthStencilBuffer)
	{
		bufferBarriers.clear();
		for (Mesh* const mesh : meshes)
		{
			for (const std::string& dataType : mesh->DataTypes())
			{
				const std::size_t bufferCount = mesh->BufferCount(dataType).value();
				for (std::size_t i = 0; i < bufferCount; ++i)
				{
					const auto bufferBarrier = D3D12_BUFFER_BARRIER
					{
						.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
						.SyncAfter = D3D12_BARRIER_SYNC_NONE,
						.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
						.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
						.pResource = mesh->FindBuffer(dataType, i),
						.Offset = 0UL,
						.Size = UINT64_MAX
					};
					bufferBarriers.push_back(bufferBarrier);
				}
			}
		}

		textureBarriers.clear();
		textureBarriers.reserve(3);
		const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
			.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE,
			.pResource = &renderTargetBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(renderTargetBarrier);
		const auto backBufferBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_PRESENT,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.pResource = &backBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(backBufferBarrier);
		const auto depthStencilBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ,
			.pResource = &depthStencilBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(depthStencilBarrier);

		PopulateBarrierGroups();
	}

	void GraphicsPipeline::PopulateRenderToResolveBarriers(ID3D12Resource2& resolveSourceBuffer, ID3D12Resource2& resolveDestinationBuffer, ID3D12Resource2& depthStencilBuffer)
	{
		bufferBarriers.clear();
		for (Mesh* const mesh : meshes)
		{
			for (const std::string& dataType : mesh->DataTypes())
			{
				const std::size_t bufferCount = mesh->BufferCount(dataType).value();
				for (std::size_t i = 0; i < bufferCount; ++i)
				{
					const auto bufferBarrier = D3D12_BUFFER_BARRIER
					{
						.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
						.SyncAfter = D3D12_BARRIER_SYNC_NONE,
						.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
						.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
						.pResource = mesh->FindBuffer(dataType, i),
						.Offset = 0UL,
						.Size = UINT64_MAX
					};
					bufferBarriers.push_back(bufferBarrier);
				}
			}
		}

		textureBarriers.clear();
		textureBarriers.reserve(3);
		const auto resolveSourceBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.SyncAfter = D3D12_BARRIER_SYNC_RESOLVE,
			.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.AccessAfter = D3D12_BARRIER_ACCESS_RESOLVE_SOURCE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE,
			.pResource = &resolveSourceBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(resolveSourceBarrier);
		const auto resolveDestinationBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_RESOLVE,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_RESOLVE_DEST,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RESOLVE_DEST,
			.pResource = &resolveDestinationBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(resolveDestinationBarrier);
		const auto depthStencilBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ,
			.pResource = &depthStencilBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(depthStencilBarrier);

		PopulateBarrierGroups();
	}

	void GraphicsPipeline::PopulateResolve(ID3D12Resource2& resolveSourceBuffer, ID3D12Resource2& resolveDestinationBuffer, const DXGI_FORMAT format)
	{
		commandList->ResolveSubresource(&resolveDestinationBuffer, 0u, &resolveSourceBuffer, 0u, format);
	}

	void GraphicsPipeline::PopulateResolveToOutputBarriers(ID3D12Resource2& resolveSourceBuffer, ID3D12Resource2& resolveDestinationBuffer, ID3D12Resource2& backBuffer)
	{
		bufferBarriers.clear();

		textureBarriers.clear();
		textureBarriers.reserve(3);
		const auto resolveSourceBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RESOLVE,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_RESOLVE_SOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
			.pResource = &resolveSourceBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(resolveSourceBarrier);
		const auto resolveDestinationBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RESOLVE,
			.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
			.AccessBefore = D3D12_BARRIER_ACCESS_RESOLVE_DEST,
			.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RESOLVE_DEST,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE,
			.pResource = &resolveDestinationBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(resolveDestinationBarrier);
		const auto backBufferBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_PRESENT,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.pResource = &backBuffer,
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(backBufferBarrier);

		PopulateBarrierGroups();
	}

	void GraphicsPipeline::PopulateBarrierGroups()
	{
		auto barrierGroups = std::array<D3D12_BARRIER_GROUP, 2>();
		UINT32 count = 0u;
		if (bufferBarriers.size() > 0)
		{
			barrierGroups[count++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_BUFFER,
				.NumBarriers = static_cast<UINT32>(bufferBarriers.size()),
				.pBufferBarriers = bufferBarriers.data()
			};
		}
		if (textureBarriers.size() > 0)
		{
			barrierGroups[count++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_TEXTURE,
				.NumBarriers = static_cast<UINT32>(textureBarriers.size()),
				.pTextureBarriers = textureBarriers.data()
			};
		}

		if (count > 0u)
		{
			commandList->Barrier(count, barrierGroups.data());
		}
	}
}

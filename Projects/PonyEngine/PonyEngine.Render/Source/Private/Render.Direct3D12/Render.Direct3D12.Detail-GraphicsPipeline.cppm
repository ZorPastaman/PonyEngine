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
import <unordered_map>;
import <vector>;

import PonyBase.Utility.COM;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Utility;

import :DescriptorHeap;
import :IDescriptorHeapManager;
import :IFrameManager;
import :IGraphicsPipeline;
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

		void CreateFrame();

		virtual void AddCamera(const std::shared_ptr<Camera>& camera) override;
		virtual void AddRenderObject(const std::shared_ptr<RenderObject>& renderObject) override;

		/// @brief Sets the name to the graphics pipeline components.
		/// @param name Name.
		void Name(std::string_view name);

		void Prepare();
		/// @brief Populates commands. All the system components must be ready.
		void PopulateCommands();
		/// @brief Executes populated commands.
		void Execute();
		/// @brief Clears the tasks. Must be called only after finishing execution.
		void Clear() noexcept;

		GraphicsPipeline& operator =(const GraphicsPipeline&) = delete;
		GraphicsPipeline& operator =(GraphicsPipeline&&) = delete;

	private:
		std::size_t TransformIndex(std::size_t cameraIndex, std::size_t renderObjectIndex);

		void CreateTransforms();
		void UpdateTransforms();

		/// @brief Resets command lists.
		void ResetLists();
		/// @brief Closes command lists.
		void CloseLists();

		void UpdateMeshSet();
		/// @brief Populates begin to render barriers in an msaa context.
		void PopulateBeginToRenderBarriers();
		/// @brief Populates a render target.
		/// @param resolution Render resolution.
		/// @param clearColor Clear color.
		/// @param rtvHandle Rtv handle.
		/// @param dsvHandle Dsv handle.
		void PopulateRenderTarget();
		void PopulateCamera(std::size_t cameraIndex);
		/// @brief Merges heaps.
		void UpdateTransformHeap();
		void MergeHeaps();
		void UpdateCameraIndices();
		void UpdateRenderObjectIndices();
		void SortCameras();
		/// @brief Sorts render objects.
		void SortRenderObjects(std::size_t cameraIndex);
		/// @brief Populates render objects.
		void PopulateRenderObjects(std::size_t cameraIndex);
		/// @brief Populate output.
		/// @param renderTargetHeap Render target heap.
		/// @param renderTargetHandle Render target handle.
		/// @param backViewHandle Back view handle.
		void PopulateOutput();
		/// @brief Populates output to end barriers.
		/// @param renderTargetBuffer Render target buffer.
		/// @param backBuffer 
		void PopulateOutputToEndBarriers();

		/// @brief Populates render to output barriers.
		/// @param renderTargetBuffer Render target buffer.
		/// @param backBuffer Back buffer.
		/// @param depthStencilTexture Depth stencil buffer.
		void PopulateRenderToOutputBarriers();

		/// @brief Populates render to resolve barriers.
		/// @param resolveSourceBuffer Resolve source buffer.
		/// @param resolveDestinationBuffer Resolve destination buffer.
		/// @param depthStencilTexture Depth stencil buffer.
		void PopulateRenderToResolveBarriers();
		/// @brief Populates resolve.
		/// @param resolveSourceBuffer Resolve source buffer.
		/// @param resolveDestinationBuffer Resolve destination buffer.
		/// @param format Resource format.
		void PopulateResolve();
		/// @brief Populates resolve to output barriers.
		/// @param resolveSourceBuffer Resolve source buffer.
		/// @param resolveDestinationBuffer Resolve destination buffer.
		/// @param backBuffer Back buffer.
		void PopulateResolveToOutputBarriers();

		/// @brief Populates barrier groups.
		void PopulateBarrierGroups();

		GUID guid; ///< Graphics pipeline guid.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Graphics command queue.
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator; ///< Graphics command allocator.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList; ///< Graphics command list.

		std::vector<std::size_t> cameraIndices;
		std::vector<std::shared_ptr<Camera>> cameras;

		std::vector<std::size_t> renderObjectIndices;
		std::vector<std::shared_ptr<RenderObject>> renderObjects; ///< Render objects.
		std::set<Mesh*> meshes; ///< Render object meshes cache.

		std::vector<Transform> transforms;
		std::vector<std::shared_ptr<Buffer>> uploadTransforms;
		std::vector<std::shared_ptr<Buffer>> gpuTransforms;
		std::shared_ptr<DescriptorHeap> transformHeap;

		std::vector<D3D12_BUFFER_BARRIER> bufferBarriers; ///< Buffer barriers cache.
		std::vector<D3D12_TEXTURE_BARRIER> textureBarriers; ///< Buffer barriers cache.

		std::shared_ptr<DescriptorHeap> dataHeap; ///< Data descriptor heap.
		std::unordered_map<const ID3D12DescriptorHeap*, UINT> originalHeapOffsets; ///< Original heap to merged heap offset map.

		std::shared_ptr<Frame> frame;
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

	void GraphicsPipeline::CreateFrame()
	{
		frame = this->d3d12System->FrameManager().CreateFrame();

		outputQuad = std::make_unique<SrgbOutputQuad>(*this->d3d12System);
		outputQuad->Name("OutputQuad");
	}

	void GraphicsPipeline::AddCamera(const std::shared_ptr<Camera>& camera)
	{
		cameras.push_back(camera);
	}

	void GraphicsPipeline::AddRenderObject(const std::shared_ptr<RenderObject>& renderObject)
	{
		renderObjects.push_back(renderObject);
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

	void GraphicsPipeline::Prepare()
	{
		CreateTransforms();
		UpdateTransforms();
	}

	void GraphicsPipeline::PopulateCommands()
	{
		UpdateMeshSet();
		UpdateTransformHeap();
		MergeHeaps();
		UpdateCameraIndices();
		UpdateRenderObjectIndices();

		ResetLists();
		PopulateBeginToRenderBarriers();
		PopulateRenderTarget();
		SortCameras();
		for (const std::size_t cameraIndex : cameraIndices)
		{
			PopulateCamera(cameraIndex);
			SortRenderObjects(cameraIndex);
			PopulateRenderObjects(cameraIndex);
		}
		if (frame->ResolveTarget())
		{
			PopulateRenderToResolveBarriers();
			PopulateResolve();
			PopulateResolveToOutputBarriers();
		}
		else
		{
			PopulateRenderToOutputBarriers();
		}
		PopulateOutput();
		PopulateOutputToEndBarriers();
		CloseLists();
	}

	void GraphicsPipeline::Execute()
	{
		const auto commandLists = std::array<ID3D12CommandList*, 1> { commandList.Get() };
		commandQueue->ExecuteCommandLists(static_cast<UINT>(commandLists.size()), commandLists.data());
	}

	void GraphicsPipeline::Clear() noexcept
	{
		cameras.clear();
		renderObjects.clear();
	}

	std::size_t GraphicsPipeline::TransformIndex(const std::size_t cameraIndex, const std::size_t renderObjectIndex)
	{
		return cameraIndex * renderObjects.size() + renderObjectIndex;
	}

	void GraphicsPipeline::CreateTransforms()
	{
		const std::size_t transformCount = cameras.size() * renderObjects.size();
		transforms.resize(transformCount);

		if (uploadTransforms.size() > transformCount)
		{
			uploadTransforms.erase(uploadTransforms.cbegin() + transformCount, uploadTransforms.cend());
			gpuTransforms.erase(gpuTransforms.cbegin() + transformCount, gpuTransforms.cend());
		}

		for (std::size_t i = uploadTransforms.size(); i < transformCount; ++i)
		{
			uploadTransforms.push_back(d3d12System->ResourceManager().CreateBuffer(static_cast<UINT64>(sizeof(Transform)), HeapType::Upload));
			gpuTransforms.push_back(d3d12System->ResourceManager().CreateBuffer(static_cast<UINT64>(sizeof(Transform)), HeapType::Default));
		}
	}

	void GraphicsPipeline::UpdateTransforms()
	{
		for (std::size_t cameraIndex = 0; cameraIndex < cameras.size(); ++cameraIndex)
		{
			for (std::size_t renderObjectIndex = 0; renderObjectIndex < renderObjects.size(); ++renderObjectIndex)
			{
				const Camera& camera = *cameras[cameraIndex];
				const RenderObject& renderObject = *renderObjects[renderObjectIndex];
				const std::size_t transformIndex = TransformIndex(cameraIndex, renderObjectIndex);

				transforms[transformIndex] = Transform(renderObject.ModelMatrixD3D12(), camera.ViewMatrixD3D12(), camera.ProjectionMatrixD3D12());
			}
		}

		for (std::size_t i = 0; i < transforms.size(); ++i)
		{
			uploadTransforms[i]->SetData(transforms[i].Data(), sizeof(Transform));
		}

		for (std::size_t i = 0; i < uploadTransforms.size(); ++i)
		{
			d3d12System->CopyPipeline().AddCopyTask(uploadTransforms[i], gpuTransforms[i]);
		}
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

	void GraphicsPipeline::UpdateMeshSet()
	{
		meshes.clear();
		for (const std::shared_ptr<RenderObject>& renderObject : renderObjects)
		{
			meshes.insert(&renderObject->Mesh());
		}
	}

	void GraphicsPipeline::PopulateBeginToRenderBarriers()
	{
		bufferBarriers.clear();
		for (const std::shared_ptr<Buffer>& transform : gpuTransforms)
		{
			const auto transformBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
				.pResource = &transform->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			bufferBarriers.push_back(transformBarrier);
		}
		for (Mesh* const mesh : meshes)
		{
			for (const std::string& dataType : mesh->DataTypes())
			{
				const std::size_t bufferCount = mesh->FindBufferCount(dataType).value();
				for (std::size_t i = 0; i < bufferCount; ++i)
				{
					const auto bufferBarrier = D3D12_BUFFER_BARRIER
					{
						.SyncBefore = D3D12_BARRIER_SYNC_NONE,
						.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
						.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
						.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
						.pResource = &mesh->FindBuffer(dataType, i)->get()->Data(),
						.Offset = 0UL,
						.Size = UINT64_MAX
					};
					bufferBarriers.push_back(bufferBarrier);
				}
			}
		}

		textureBarriers.clear();
		const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.pResource = &frame->RenderTarget().Data(),
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
			.pResource = &frame->DepthStencil().Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(depthStencilBarrier);

		PopulateBarrierGroups();
	}

	void GraphicsPipeline::PopulateRenderTarget()
	{
		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = frame->RenderTargetHandle();
		const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = frame->DepthStencilHandle();
		commandList->OMSetRenderTargets(1u, &rtvHandle, false, &dsvHandle);
	}

	void GraphicsPipeline::PopulateCamera(const std::size_t cameraIndex)
	{
		const Camera& camera = *cameras[cameraIndex];
		const PonyMath::Shape::Rect<FLOAT> viewportRect = camera.ViewportRectD3D12();
		const PonyMath::Utility::Resolution<UINT>& resolution = d3d12System->FrameManager().Resolution();

		const auto viewport = D3D12_VIEWPORT
		{
			.TopLeftX = viewportRect.MinX() * resolution.Width(),
			.TopLeftY = viewportRect.MinY() * resolution.Height(),
			.Width = viewportRect.Width() * resolution.Width(),
			.Height = viewportRect.Height() * resolution.Height(),
			.MinDepth = D3D12_MIN_DEPTH,
			.MaxDepth = D3D12_MAX_DEPTH
		};
		commandList->RSSetViewports(1u, &viewport);

		const auto rect = D3D12_RECT
		{
			.left = static_cast<LONG>(viewport.TopLeftX),
			.top = static_cast<LONG>(viewport.TopLeftY),
			.right = static_cast<LONG>(viewport.TopLeftX + viewport.Width),
			.bottom = static_cast<LONG>(viewport.TopLeftY + viewport.Height)
		};
		commandList->RSSetScissorRects(1u, &rect);

		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = frame->RenderTargetHandle();
		const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = frame->DepthStencilHandle();
		commandList->ClearRenderTargetView(rtvHandle, camera.ClearColorD3D12().Span().data(), 1u, &rect);
		commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, D3D12_MAX_DEPTH, 0u, 1u, &rect);
	}

	void GraphicsPipeline::UpdateTransformHeap()
	{
		if (transformHeap && transformHeap->Heap().GetDesc().NumDescriptors == gpuTransforms.size())
		{
			return;
		}

		transformHeap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, static_cast<UINT>(gpuTransforms.size()), false);

		for (std::size_t i = 0; i < gpuTransforms.size(); ++i)
		{
			const auto cbvDesc = D3D12_CONSTANT_BUFFER_VIEW_DESC
			{
				.BufferLocation = gpuTransforms[i]->Data().GetGPUVirtualAddress(),
				.SizeInBytes = sizeof(Transform)
			};
			d3d12System->Device().CreateConstantBufferView(&cbvDesc, transformHeap->CpuHandle(static_cast<UINT>(i)));
		}
	}

	void GraphicsPipeline::MergeHeaps()
	{
		UINT descriptorCount = transformHeap->Heap().GetDesc().NumDescriptors;
		for (Mesh* const mesh : meshes)
		{
			descriptorCount += mesh->Heap().Heap().GetDesc().NumDescriptors;
		}
		if (!dataHeap || dataHeap->HandleCount() != descriptorCount)
		{
			dataHeap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, descriptorCount, true);
		}

		originalHeapOffsets.clear();
		descriptorCount = 0u;
		originalHeapOffsets[&transformHeap->Heap()] = descriptorCount;
		d3d12System->Device().CopyDescriptorsSimple(transformHeap->Heap().GetDesc().NumDescriptors, dataHeap->CpuHandle(descriptorCount), transformHeap->Heap().GetCPUDescriptorHandleForHeapStart(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		descriptorCount += transformHeap->Heap().GetDesc().NumDescriptors;

		for (Mesh* const mesh : meshes)
		{
			originalHeapOffsets[&mesh->Heap().Heap()] = descriptorCount;
			d3d12System->Device().CopyDescriptorsSimple(mesh->Heap().Heap().GetDesc().NumDescriptors, dataHeap->CpuHandle(descriptorCount), mesh->Heap().Heap().GetCPUDescriptorHandleForHeapStart(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			descriptorCount += mesh->Heap().Heap().GetDesc().NumDescriptors;
		}
	}

	void GraphicsPipeline::UpdateCameraIndices()
	{
		cameraIndices.resize(cameras.size());

		for (std::size_t i = 0; i < cameraIndices.size(); ++i)
		{
			cameraIndices[i] = i;
		}
	}

	void GraphicsPipeline::UpdateRenderObjectIndices()
	{
		renderObjectIndices.resize(renderObjects.size());

		for (std::size_t i = 0; i < renderObjectIndices.size(); ++i)
		{
			renderObjectIndices[i] = i;
		}
	}

	void GraphicsPipeline::SortCameras()
	{
		std::ranges::sort(cameraIndices, [&](const std::size_t& leftIndex, const std::size_t& rightIndex)
		{
			return cameras[leftIndex]->SortingOrder() < cameras[rightIndex]->SortingOrder();
		});
	}

	void GraphicsPipeline::SortRenderObjects(const std::size_t cameraIndex)
	{
		std::ranges::sort(renderObjectIndices, [&](const std::size_t& leftIndex, const std::size_t& rightIndex)
		{
			const RenderObject* const left = renderObjects[leftIndex].get();
			const RenderObject* const right = renderObjects[rightIndex].get();
			const Material* const leftMaterial = &left->Material();
			const Material* const rightMaterial = &right->Material();
			const bool isLeftTransparent = leftMaterial->IsTransparent();
			const bool isRightTransparent = rightMaterial->IsTransparent();

			if (isLeftTransparent != isRightTransparent)
			{
				return isLeftTransparent < isRightTransparent;
			}

			const Transform& leftTransform = transforms[TransformIndex(cameraIndex, leftIndex)];
			const Transform& rightTransform = transforms[TransformIndex(cameraIndex, rightIndex)];

			if (isLeftTransparent)
			{
				return PonyMath::Core::ExtractTranslation(leftTransform.MvpMatrix()).Z() > PonyMath::Core::ExtractTranslation(rightTransform.MvpMatrix()).Z();
			}

			if (const RootSignature* const leftRootSignature = &leftMaterial->RootSignature(), * const rightRootSignature = &rightMaterial->RootSignature(); leftRootSignature != rightRootSignature)
			{
				return reinterpret_cast<std::uintptr_t>(leftRootSignature) < reinterpret_cast<std::uintptr_t>(rightRootSignature);
			}
			if (leftMaterial != rightMaterial)
			{
				return reinterpret_cast<std::uintptr_t>(leftMaterial) < reinterpret_cast<std::uintptr_t>(rightMaterial);
			}

			if (const Mesh* const leftMesh = &left->Mesh(), * const rightMesh = &right->Mesh(); leftMesh != rightMesh)
			{
				return reinterpret_cast<std::uintptr_t>(leftMesh) < reinterpret_cast<std::uintptr_t>(rightMesh);
			}

			return PonyMath::Core::ExtractTranslation(leftTransform.MvpMatrix()).Z() < PonyMath::Core::ExtractTranslation(rightTransform.MvpMatrix()).Z();
		});
	}

	void GraphicsPipeline::PopulateRenderObjects(const std::size_t cameraIndex)
	{
		ID3D12DescriptorHeap* const heap = &dataHeap->Heap();
		commandList->SetDescriptorHeaps(1u, &heap);

		const RootSignature* prevRootSignature = nullptr;
		const Material* prevMaterial = nullptr;
		const Mesh* prevMesh = nullptr;
		for (const std::size_t renderObjectIndex : renderObjectIndices)
		{
			RenderObject* const renderObject = renderObjects[renderObjectIndex].get();

			Material* const material = &renderObject->Material();
			RootSignature* const rootSignature = &material->RootSignature();
			if (rootSignature != prevRootSignature)
			{
				commandList->SetGraphicsRootSignature(&rootSignature->ControlledRootSignature());
			}
			if (material != prevMaterial)
			{
				commandList->SetPipelineState(&material->PipelineState());
			}

			Mesh* const mesh = &renderObject->Mesh();
			if (mesh != prevMesh || rootSignature != prevRootSignature)
			{
				for (const std::string& dataType : mesh->DataTypes())
				{
					if (const std::optional<UINT> slot = rootSignature->FindDataSlot(dataType))
					{
						commandList->SetGraphicsRootDescriptorTable(slot.value(), dataHeap->GpuHandle(originalHeapOffsets[&mesh->Heap().Heap()] + mesh->FindHandleIndex(dataType).value()));
					}
				}
			}

			if (const std::optional<UINT> slot = rootSignature->FindDataSlot(PonyTransformDataType))
			{
				commandList->SetGraphicsRootDescriptorTable(slot.value(), dataHeap->GpuHandle(originalHeapOffsets[&transformHeap->Heap()] + TransformIndex(cameraIndex, renderObjectIndex)));
			}

			const std::span<const UINT, 3> threadGroupCounts = mesh->ThreadGroupCounts();
			commandList->DispatchMesh(threadGroupCounts[0], threadGroupCounts[1], threadGroupCounts[2]);

			prevRootSignature = rootSignature;
			prevMaterial = material;
			prevMesh = mesh;
		}
	}

	void GraphicsPipeline::PopulateOutput()
	{
		const D3D12_CPU_DESCRIPTOR_HANDLE backViewHandle = d3d12System->BackManager().CurrentBackHandle();
		commandList->OMSetRenderTargets(1u, &backViewHandle, false, nullptr);

		commandList->SetGraphicsRootSignature(&outputQuad->RootSignature());
		commandList->SetPipelineState(&outputQuad->PipelineState());

		ID3D12DescriptorHeap* const heap = &frame->RenderTargetShaderHeap().Heap();
		commandList->SetDescriptorHeaps(1u, &heap);
		commandList->SetGraphicsRootDescriptorTable(outputQuad->RenderTargetSlot, frame->RenderTargetShaderHandle());

		commandList->DispatchMesh(outputQuad->ThreadGroupXCount, outputQuad->ThreadGroupYCount, outputQuad->ThreadGroupZCount);
	}

	void GraphicsPipeline::PopulateOutputToEndBarriers()
	{
		bufferBarriers.clear();

		textureBarriers.clear();
		const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
			.pResource = frame->ResolveTarget() ? &frame->ResolveTarget()->Data() : &frame->RenderTarget().Data(),
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
			.pResource = &d3d12System->BackManager().CurrentBackBuffer(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(backBufferBarrier);

		PopulateBarrierGroups();
	}

	void GraphicsPipeline::PopulateRenderToOutputBarriers()
	{
		bufferBarriers.clear();
		for (const std::shared_ptr<Buffer>& transform : gpuTransforms)
		{
			const auto transformBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.pResource = &transform->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			bufferBarriers.push_back(transformBarrier);
		}
		for (Mesh* const mesh : meshes)
		{
			for (const std::string& dataType : mesh->DataTypes())
			{
				const std::size_t bufferCount = mesh->FindBufferCount(dataType).value();
				for (std::size_t i = 0; i < bufferCount; ++i)
				{
					const auto bufferBarrier = D3D12_BUFFER_BARRIER
					{
						.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
						.SyncAfter = D3D12_BARRIER_SYNC_NONE,
						.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
						.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
						.pResource = &mesh->FindBuffer(dataType, i)->get()->Data(),
						.Offset = 0UL,
						.Size = UINT64_MAX
					};
					bufferBarriers.push_back(bufferBarrier);
				}
			}
		}

		textureBarriers.clear();
		const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
			.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE,
			.pResource = &frame->RenderTarget().Data(),
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
			.pResource = &d3d12System->BackManager().CurrentBackBuffer(),
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
			.pResource = &frame->DepthStencil().Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(depthStencilBarrier);

		PopulateBarrierGroups();
	}

	void GraphicsPipeline::PopulateRenderToResolveBarriers()
	{
		bufferBarriers.clear();
		for (const std::shared_ptr<Buffer>& transform : gpuTransforms)
		{
			const auto transformBarrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.pResource = &transform->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			bufferBarriers.push_back(transformBarrier);
		}
		for (Mesh* const mesh : meshes)
		{
			for (const std::string& dataType : mesh->DataTypes())
			{
				const std::size_t bufferCount = mesh->FindBufferCount(dataType).value();
				for (std::size_t i = 0; i < bufferCount; ++i)
				{
					const auto bufferBarrier = D3D12_BUFFER_BARRIER
					{
						.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
						.SyncAfter = D3D12_BARRIER_SYNC_NONE,
						.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
						.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
						.pResource = &mesh->FindBuffer(dataType, i)->get()->Data(),
						.Offset = 0UL,
						.Size = UINT64_MAX
					};
					bufferBarriers.push_back(bufferBarrier);
				}
			}
		}

		textureBarriers.clear();
		const auto resolveSourceBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.SyncAfter = D3D12_BARRIER_SYNC_RESOLVE,
			.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.AccessAfter = D3D12_BARRIER_ACCESS_RESOLVE_SOURCE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE,
			.pResource = &frame->RenderTarget().Data(),
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
			.pResource = &frame->ResolveTarget()->Data(),
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
			.pResource = &frame->DepthStencil().Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(depthStencilBarrier);

		PopulateBarrierGroups();
	}

	void GraphicsPipeline::PopulateResolve()
	{
		commandList->ResolveSubresource(&frame->ResolveTarget()->Data(), 0u, &frame->RenderTarget().Data(), 0u, frame->ResolveTarget()->Data().GetDesc1().Format);
	}

	void GraphicsPipeline::PopulateResolveToOutputBarriers()
	{
		bufferBarriers.clear();

		textureBarriers.clear();
		const auto resolveSourceBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RESOLVE,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_RESOLVE_SOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
			.pResource = &frame->RenderTarget().Data(),
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
			.pResource = &frame->ResolveTarget()->Data(),
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
			.pResource = &d3d12System->BackManager().CurrentBackBuffer(),
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

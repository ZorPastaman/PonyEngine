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
import <numeric>;
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
import :Pipeline;
import :RootSignature;
import :RenderObject;
import :SrgbOutputQuad;
import :Transform;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 graphics pipeline.
	class GraphicsPipeline final : public Pipeline, public IGraphicsPipeline
	{
	public:
		/// @brief Creates a @p GraphicsPipeline.
		/// @param d3d12System Direct3D12 system context.
		/// @param commandQueuePriority Command queue priority.
		[[nodiscard("Pure constructor")]]
		GraphicsPipeline(ISubSystemContext& d3d12System, INT commandQueuePriority);
		GraphicsPipeline(const GraphicsPipeline&) = delete;
		GraphicsPipeline(GraphicsPipeline&&) = delete;

		virtual ~GraphicsPipeline() noexcept override = default;

		void CreateFrame();

		virtual void AddCamera(Camera& camera) override;
		virtual void AddRenderObject(RenderObject& renderObject) override;

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
		[[nodiscard("Pure function")]]
		std::size_t TransformIndex(std::size_t cameraIndex, std::size_t renderObjectIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t TransformCount() const noexcept;

		void SyncTransformCount();
		void SyncTransformCount(std::vector<std::shared_ptr<Buffer>>& transformBuffers, HeapType heapType, std::size_t transformCount) const;
		void UpdateTransforms();

		void UpdateData();
		void UpdateCameraIndices();
		void UpdateRenderObjectIndices();
		void UpdateMeshes();
		void UpdateTransformHeap();
		void MergeHeaps();

		void PushBeginToRenderBarriers();
		void PushRenderToResolveBarriers();
		void PushResolveToOutputBarriers();
		void PushRenderToOutputBarriers();
		void PushOutputToEndBarriers();

		void PushRenderBeginBarriers();
		void PushRenderEndBarriers();
		void PopulateRender();
		void PopulateRenderTarget();
		void SortCameras();
		void PopulateCamera(std::size_t cameraIndex);
		/// @brief Sorts render objects.
		void SortRenderObjects(std::size_t cameraIndex);
		/// @brief Populates render objects.
		void PopulateRenderObjects(std::size_t cameraIndex);

		void PopulateResolve();

		void PushOutputBeginBarriers();
		void PushOutputEndBarriers();
		void PopulateOutput();

		std::vector<std::size_t> cameraIndices;
		std::vector<Camera*> cameras;

		std::vector<std::size_t> renderObjectIndices;
		std::vector<RenderObject*> renderObjects; ///< Render objects.
		std::set<Mesh*> meshes; ///< Render object meshes cache.

		std::vector<Transform> transforms;
		std::vector<std::shared_ptr<Buffer>> uploadTransforms;
		std::vector<std::shared_ptr<Buffer>> gpuTransforms;
		std::shared_ptr<DescriptorHeap> transformHeap;

		std::shared_ptr<DescriptorHeap> dataHeap; ///< Data descriptor heap.
		std::unordered_map<const ID3D12DescriptorHeap*, UINT> originalHeapOffsets; ///< Original heap to merged heap offset map.

		std::shared_ptr<Frame> frame;
		std::unique_ptr<SrgbOutputQuad> outputQuad; ///< Srgb output quad.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	GraphicsPipeline::GraphicsPipeline(ISubSystemContext& d3d12System, const INT commandQueuePriority) :
		Pipeline(d3d12System, commandQueuePriority, D3D12_COMMAND_LIST_TYPE_DIRECT)
	{
	}

	void GraphicsPipeline::CreateFrame()
	{
		frame = D3D12System().FrameManager().CreateFrame();
		frame->Name("MainFrame");

		outputQuad = std::make_unique<SrgbOutputQuad>(D3D12System());
		outputQuad->Name("OutputQuad");
	}

	void GraphicsPipeline::AddCamera(Camera& camera)
	{
		cameras.push_back(&camera);
	}

	void GraphicsPipeline::AddRenderObject(RenderObject& renderObject)
	{
		renderObjects.push_back(&renderObject);
	}

	void GraphicsPipeline::Prepare()
	{
		SyncTransformCount();
		UpdateTransforms();
	}

	void GraphicsPipeline::PopulateCommands()
	{
		UpdateData();

		ResetLists();
		PushBeginToRenderBarriers();
		PushRenderBeginBarriers();
		PopulateBarriers();
		PopulateRender();
		PushRenderEndBarriers();
		if (frame->ResolveTarget())
		{
			PushRenderToResolveBarriers();
			PopulateBarriers();
			PopulateResolve();
			PushResolveToOutputBarriers();
		}
		else
		{
			PushRenderToOutputBarriers();
		}
		PushOutputBeginBarriers();
		PopulateBarriers();
		PopulateOutput();
		PushOutputEndBarriers();
		PushOutputToEndBarriers();
		PopulateBarriers();
		CloseLists();
	}

	void GraphicsPipeline::Execute()
	{
		ID3D12CommandList* const graphicsList = &CommandList();
		CommandQueue().ExecuteCommandLists(1u, &graphicsList);
	}

	void GraphicsPipeline::Clear() noexcept
	{
		cameras.clear();
		renderObjects.clear();
	}

	std::size_t GraphicsPipeline::TransformIndex(const std::size_t cameraIndex, const std::size_t renderObjectIndex) const noexcept
	{
		return cameraIndex * renderObjects.size() + renderObjectIndex;
	}

	std::size_t GraphicsPipeline::TransformCount() const noexcept
	{
		return cameras.size() * renderObjects.size();
	}

	void GraphicsPipeline::SyncTransformCount()
	{
		const std::size_t transformCount = TransformCount();
		transforms.resize(transformCount);
		SyncTransformCount(uploadTransforms, HeapType::Upload, transformCount);
		SyncTransformCount(gpuTransforms, HeapType::Default, transformCount);
	}

	void GraphicsPipeline::SyncTransformCount(std::vector<std::shared_ptr<Buffer>>& transformBuffers, const HeapType heapType, const std::size_t transformCount) const
	{
		if (transformBuffers.size() > transformCount)
		{
			transformBuffers.erase(transformBuffers.cbegin() + transformCount, transformBuffers.cend());
		}
		else
		{
			for (std::size_t i = transformBuffers.size(); i < transformCount; ++i)
			{
				const std::shared_ptr<Buffer> transform = D3D12System().ResourceManager().CreateBuffer(static_cast<UINT64>(sizeof(Transform)), heapType);
				transform->Name("Transform");
				transformBuffers.push_back(transform);
			}
		}
	}

	void GraphicsPipeline::UpdateTransforms()
	{
		for (std::size_t cameraIndex = 0; cameraIndex < cameras.size(); ++cameraIndex)
		{
			for (std::size_t renderObjectIndex = 0; renderObjectIndex < renderObjects.size(); ++renderObjectIndex)
			{
				const std::size_t transformIndex = TransformIndex(cameraIndex, renderObjectIndex);
				transforms[transformIndex] = Transform(renderObjects[renderObjectIndex]->ModelMatrixD3D12(), cameras[cameraIndex]->ViewMatrixD3D12(), cameras[cameraIndex]->ProjectionMatrixD3D12());
			}
		}

		for (std::size_t i = 0; i < uploadTransforms.size(); ++i)
		{
			uploadTransforms[i]->SetData(&transforms[i], sizeof(Transform));
		}

		for (std::size_t i = 0; i < uploadTransforms.size(); ++i)
		{
			D3D12System().CopyPipeline().AddCopyTask(*uploadTransforms[i], *gpuTransforms[i]);
		}
	}

	void GraphicsPipeline::UpdateData()
	{
		UpdateCameraIndices();
		UpdateRenderObjectIndices();

		UpdateMeshes();

		UpdateTransformHeap();
		MergeHeaps();
	}

	void GraphicsPipeline::UpdateCameraIndices()
	{
		cameraIndices.resize(cameras.size());
		std::iota(cameraIndices.begin(), cameraIndices.end(), std::size_t{0});
	}

	void GraphicsPipeline::UpdateRenderObjectIndices()
	{
		renderObjectIndices.resize(renderObjects.size());
		std::iota(renderObjectIndices.begin(), renderObjectIndices.end(), std::size_t{0});
	}

	void GraphicsPipeline::UpdateMeshes()
	{
		meshes.clear();
		for (RenderObject* const renderObject : renderObjects)
		{
			meshes.insert(&renderObject->Mesh());
		}
	}

	void GraphicsPipeline::UpdateTransformHeap()
	{
		if (transformHeap && transformHeap->HandleCount() == gpuTransforms.size())
		{
			return;
		}

		transformHeap = D3D12System().DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, static_cast<UINT>(gpuTransforms.size()), false);
		transformHeap->Name("Transform");

		for (UINT i = 0; i < gpuTransforms.size(); ++i)
		{
			const auto cbvDesc = D3D12_CONSTANT_BUFFER_VIEW_DESC
			{
				.BufferLocation = gpuTransforms[i]->Data().GetGPUVirtualAddress(),
				.SizeInBytes = sizeof(Transform)
			};
			D3D12System().Device().CreateConstantBufferView(&cbvDesc, transformHeap->CpuHandle(i));
		}
	}

	void GraphicsPipeline::MergeHeaps()
	{
		UINT descriptorCount = transformHeap->HandleCount();
		for (Mesh* const mesh : meshes)
		{
			descriptorCount += mesh->Heap().HandleCount();
		}

		if (!dataHeap || dataHeap->HandleCount() != descriptorCount)
		{
			dataHeap = D3D12System().DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, descriptorCount, true);
			dataHeap->Name("MergedData");
		}

		originalHeapOffsets.clear();
		descriptorCount = 0u;

		originalHeapOffsets[&transformHeap->Heap()] = descriptorCount;
		D3D12System().Device().CopyDescriptorsSimple(transformHeap->HandleCount(), dataHeap->CpuHandle(descriptorCount), transformHeap->CpuHandle(0u), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		descriptorCount += transformHeap->HandleCount();

		for (Mesh* const mesh : meshes)
		{
			originalHeapOffsets[&mesh->Heap().Heap()] = descriptorCount;
			D3D12System().Device().CopyDescriptorsSimple(mesh->Heap().HandleCount(), dataHeap->CpuHandle(descriptorCount), mesh->Heap().CpuHandle(0u), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			descriptorCount += mesh->Heap().HandleCount();
		}
	}

	void GraphicsPipeline::PushBeginToRenderBarriers()
	{
		const auto barrier = D3D12_TEXTURE_BARRIER
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
		AddBarrier(barrier);
	}

	void GraphicsPipeline::PushRenderToResolveBarriers()
	{
		const auto renderBarrier = D3D12_TEXTURE_BARRIER
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
		const auto resolveBarrier = D3D12_TEXTURE_BARRIER
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
		AddBarrier(renderBarrier);
		AddBarrier(resolveBarrier);
	}

	void GraphicsPipeline::PushResolveToOutputBarriers()
	{
		const auto renderBarrier = D3D12_TEXTURE_BARRIER
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
		const auto resolveBarrier = D3D12_TEXTURE_BARRIER
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
		AddBarrier(renderBarrier);
		AddBarrier(resolveBarrier);
	}

	void GraphicsPipeline::PushRenderToOutputBarriers()
	{
		const auto barrier = D3D12_TEXTURE_BARRIER
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
		AddBarrier(barrier);
	}

	void GraphicsPipeline::PushOutputToEndBarriers()
	{
		const auto barrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
			.pResource = &frame->FinalTarget().Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		AddBarrier(barrier);
	}

	void GraphicsPipeline::PushRenderBeginBarriers()
	{
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
			AddBarrier(transformBarrier);
		}
		for (Mesh* const mesh : meshes)
		{
			for (std::size_t i = 0; i < mesh->BufferCount(); ++i)
			{
				const auto bufferBarrier = D3D12_BUFFER_BARRIER
				{
					.SyncBefore = D3D12_BARRIER_SYNC_NONE,
					.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
					.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
					.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
					.pResource = &mesh->Buffer(i).Data(),
					.Offset = 0UL,
					.Size = UINT64_MAX
				};
				AddBarrier(bufferBarrier);
			}
		}

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
		AddBarrier(depthStencilBarrier);
	}

	void GraphicsPipeline::PushRenderEndBarriers()
	{
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
			AddBarrier(transformBarrier);
		}
		for (Mesh* const mesh : meshes)
		{
			for (std::size_t i = 0; i < mesh->BufferCount(); ++i)
			{
				const auto bufferBarrier = D3D12_BUFFER_BARRIER
				{
					.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
					.SyncAfter = D3D12_BARRIER_SYNC_NONE,
					.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
					.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
					.pResource = &mesh->Buffer(i).Data(),
					.Offset = 0UL,
					.Size = UINT64_MAX
				};
				AddBarrier(bufferBarrier);
			}
		}

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
		AddBarrier(depthStencilBarrier);
	}

	void GraphicsPipeline::PopulateRender()
	{
		PopulateRenderTarget();
		SortCameras();
		for (const std::size_t cameraIndex : cameraIndices)
		{
			PopulateCamera(cameraIndex);
			SortRenderObjects(cameraIndex);
			PopulateRenderObjects(cameraIndex);
		}
	}

	void GraphicsPipeline::PopulateRenderTarget()
	{
		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = frame->RtvHandle();
		const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = frame->DsvHandle();
		CommandList().OMSetRenderTargets(1u, &rtvHandle, false, &dsvHandle);
	}

	void GraphicsPipeline::SortCameras()
	{
		std::ranges::sort(cameraIndices, [&](const std::size_t& leftIndex, const std::size_t& rightIndex)
		{
			return cameras[leftIndex]->SortingOrder() < cameras[rightIndex]->SortingOrder();
		});
	}

	void GraphicsPipeline::PopulateCamera(const std::size_t cameraIndex)
	{
		const PonyMath::Shape::Rect<FLOAT>& viewportRect = cameras[cameraIndex]->ViewportRectD3D12();
		const PonyMath::Utility::Resolution<UINT>& resolution = D3D12System().FrameManager().Resolution();

		const auto viewport = D3D12_VIEWPORT
		{
			.TopLeftX = viewportRect.MinX() * resolution.Width(),
			.TopLeftY = viewportRect.MinY() * resolution.Height(),
			.Width = viewportRect.Width() * resolution.Width(),
			.Height = viewportRect.Height() * resolution.Height(),
			.MinDepth = D3D12_MIN_DEPTH,
			.MaxDepth = D3D12_MAX_DEPTH
		};
		CommandList().RSSetViewports(1u, &viewport);

		const auto rect = D3D12_RECT
		{
			.left = static_cast<LONG>(viewport.TopLeftX),
			.top = static_cast<LONG>(viewport.TopLeftY),
			.right = static_cast<LONG>(viewport.TopLeftX + viewport.Width),
			.bottom = static_cast<LONG>(viewport.TopLeftY + viewport.Height)
		};
		CommandList().RSSetScissorRects(1u, &rect);

		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = frame->RtvHandle();
		const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = frame->DsvHandle();
		CommandList().ClearRenderTargetView(rtvHandle, cameras[cameraIndex]->ClearColorD3D12().Span().data(), 1u, &rect);
		CommandList().ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, D3D12_MAX_DEPTH, 0u, 1u, &rect);
	}

	void GraphicsPipeline::SortRenderObjects(const std::size_t cameraIndex)
	{
		std::ranges::sort(renderObjectIndices, [&](const std::size_t& leftIndex, const std::size_t& rightIndex)
		{
			const RenderObject* const leftRenderObject = renderObjects[leftIndex];
			const RenderObject* const rightRenderObject = renderObjects[rightIndex];
			const Material* const leftMaterial = &leftRenderObject->Material();
			const Material* const rightMaterial = &rightRenderObject->Material();

			if (leftMaterial->IsTransparent() != rightMaterial->IsTransparent())
			{
				return leftMaterial->IsTransparent() < rightMaterial->IsTransparent();
			}

			const Transform& leftTransform = transforms[TransformIndex(cameraIndex, leftIndex)];
			const Transform& rightTransform = transforms[TransformIndex(cameraIndex, rightIndex)];

			if (leftMaterial->IsTransparent())
			{
				return PonyMath::Core::ExtractTranslation(leftTransform.MvpMatrix()).Z() > PonyMath::Core::ExtractTranslation(rightTransform.MvpMatrix()).Z();
			}

			if (&leftMaterial->RootSignature() != &rightMaterial->RootSignature())
			{
				return reinterpret_cast<std::uintptr_t>(&leftMaterial->RootSignature()) < reinterpret_cast<std::uintptr_t>(&rightMaterial->RootSignature());
			}
			if (leftMaterial != rightMaterial)
			{
				return reinterpret_cast<std::uintptr_t>(leftMaterial) < reinterpret_cast<std::uintptr_t>(rightMaterial);
			}

			if (&leftRenderObject->Mesh() != &rightRenderObject->Mesh())
			{
				return reinterpret_cast<std::uintptr_t>(&leftRenderObject->Mesh()) < reinterpret_cast<std::uintptr_t>(&rightRenderObject->Mesh());
			}

			return PonyMath::Core::ExtractTranslation(leftTransform.MvpMatrix()).Z() < PonyMath::Core::ExtractTranslation(rightTransform.MvpMatrix()).Z();
		});
	}

	void GraphicsPipeline::PopulateRenderObjects(const std::size_t cameraIndex)
	{
		ID3D12DescriptorHeap* const heap = &dataHeap->Heap();
		CommandList().SetDescriptorHeaps(1u, &heap);

		const RootSignature* prevRootSignature = nullptr;
		const Material* prevMaterial = nullptr;
		const Mesh* prevMesh = nullptr;
		for (const std::size_t renderObjectIndex : renderObjectIndices)
		{
			RenderObject* const renderObject = renderObjects[renderObjectIndex];

			Material* const material = &renderObject->Material();
			RootSignature* const rootSignature = &material->RootSignature();
			if (rootSignature != prevRootSignature)
			{
				CommandList().SetGraphicsRootSignature(&rootSignature->ControlledRootSignature());
			}
			if (material != prevMaterial)
			{
				CommandList().SetPipelineState(&material->PipelineState());
			}

			Mesh* const mesh = &renderObject->Mesh();
			if (mesh != prevMesh || rootSignature != prevRootSignature)
			{
				for (const std::string& dataType : mesh->DataTypes())
				{
					if (const std::optional<UINT> slot = rootSignature->FindDataSlot(dataType)) // TODO: Make it root signature major.
					{
						CommandList().SetGraphicsRootDescriptorTable(slot.value(), dataHeap->GpuHandle(originalHeapOffsets[&mesh->Heap().Heap()] + mesh->BufferOffset(mesh->FindDataIndex(dataType).value())));
					}
				}
			}

			if (const std::optional<UINT> slot = rootSignature->FindDataSlot(EngineDataTypes::PonyTransform))
			{
				CommandList().SetGraphicsRootDescriptorTable(slot.value(), dataHeap->GpuHandle(originalHeapOffsets[&transformHeap->Heap()] + TransformIndex(cameraIndex, renderObjectIndex)));
			}

			const std::span<const UINT, 3> threadGroupCounts = mesh->ThreadGroupCounts();
			CommandList().DispatchMesh(threadGroupCounts[0], threadGroupCounts[1], threadGroupCounts[2]); // TODO: Support amplification shader with custom thread group counts

			prevRootSignature = rootSignature;
			prevMaterial = material;
			prevMesh = mesh;
		}
	}

	void GraphicsPipeline::PopulateResolve()
	{
		CommandList().ResolveSubresource(&frame->ResolveTarget()->Data(), 0u, &frame->RenderTarget().Data(), 0u, frame->ResolveTarget()->Data().GetDesc1().Format);
	}

	void GraphicsPipeline::PushOutputBeginBarriers()
	{
		const auto barrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_PRESENT,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.pResource = &D3D12System().BackManager().CurrentBackBuffer(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		AddBarrier(barrier);
	}

	void GraphicsPipeline::PushOutputEndBarriers()
	{
		const auto barrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_PRESENT,
			.pResource = &D3D12System().BackManager().CurrentBackBuffer(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		AddBarrier(barrier);
	}

	void GraphicsPipeline::PopulateOutput()
	{
		const D3D12_CPU_DESCRIPTOR_HANDLE backViewHandle = D3D12System().BackManager().CurrentRtvHandle();
		CommandList().OMSetRenderTargets(1u, &backViewHandle, false, nullptr);

		CommandList().SetGraphicsRootSignature(&outputQuad->RootSignature());
		CommandList().SetPipelineState(&outputQuad->PipelineState());

		ID3D12DescriptorHeap* const heap = &frame->SrvHeap().Heap();
		CommandList().SetDescriptorHeaps(1u, &heap);
		CommandList().SetGraphicsRootDescriptorTable(outputQuad->RenderTargetSlot, frame->SrvHandle());

		CommandList().DispatchMesh(outputQuad->ThreadGroupXCount, outputQuad->ThreadGroupYCount, outputQuad->ThreadGroupZCount);
	}
}

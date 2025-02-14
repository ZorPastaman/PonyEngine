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

import PonyShader.Core;
import PonyShader.Space;

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
		template<typename T>
		struct RenderObjectData
		{
			std::vector<T> data;
			std::vector<std::shared_ptr<Buffer>> uploadBuffers;
			std::vector<std::shared_ptr<Buffer>> gpuBuffers;
			std::shared_ptr<DescriptorHeap> heap;
		};

		struct RenderObjectTask final
		{
			std::uint32_t renderObjectIndex;
			std::uint32_t dataIndex;
		};

		struct CameraTask final 
		{
			std::vector<RenderObjectTask> renderObjectTasks;
		};

		std::uint32_t MergedHeapMeshIndex(const Mesh& mesh, std::uint32_t bufferIndex);
		template<typename T>
		std::uint32_t MergedHeapDataIndex(const RenderObjectData<T>& data, std::uint32_t index);

		void SortCameras();
		void SyncCameraTaskCount();
		void UpdateCameraTasks();
		[[nodiscard("Pure function")]]
		bool Cull(const ICuller& culler, const RenderObject& renderObject);
		void AddData(const Camera& camera, RenderObject& renderObject);
		void AddMesh(RenderObject& renderObject);
		void AddContext(const RenderObject& renderObject);
		void AddTransform(const Camera& camera, const RenderObject& renderObject);
		void SyncDataCounts();
		template<typename T>
		void SyncDataCounts(RenderObjectData<T>& data, std::string_view name);
		void SyncDataCounts(std::vector<std::shared_ptr<Buffer>>& buffers, std::uint64_t bufferSize, std::uint32_t bufferCount, HeapType heapType, std::string_view name) const;
		void UpdateData();
		template<typename T>
		void UpdateData(RenderObjectData<T>& data);

		void UpdateHeaps();
		template<typename T>
		void UpdateHeap(RenderObjectData<T>& data, std::string_view name);
		void MergeHeaps();
		[[nodiscard("Pure function")]]
		std::uint32_t MeshDescriptorCount() const;
		std::uint32_t CopyMeshDescriptors(std::uint32_t destOffset);
		template<typename T>
		std::uint32_t CopyDataDescriptors(RenderObjectData<T>& data, std::uint32_t destOffset);

		void PushBeginToRenderBarriers();
		void PushRenderToResolveBarriers();
		void PushResolveToOutputBarriers();
		void PushRenderToOutputBarriers();
		void PushOutputToEndBarriers();

		void PushMeshBeginBarriers();
		void PushMeshEndBarriers();
		template<typename T>
		void PushRenderDataBeginBarriers(RenderObjectData<T>& data);
		template<typename T>
		void PushRenderDataEndBarriers(RenderObjectData<T>& data);
		void PushDepthStencilBeginBarriers();
		void PushDepthStencilEndBarriers();

		void PushRenderBeginBarriers();
		void PushRenderEndBarriers();
		void PopulateRender();
		void PopulateRenderTarget();
		void PopulateCamera(std::uint32_t cameraIndex);
		/// @brief Sorts render objects.
		void SortRenderObjects(std::uint32_t cameraIndex);
		/// @brief Populates render objects.
		void PopulateRenderObjects(std::uint32_t cameraIndex);
		void PopulateMaterial(const RootSignature* prevRootSignature, const Material* prevMaterial, RootSignature* rootSignature, Material* material);
		void PopulateMesh(const RootSignature* prevRootSignature, const Mesh* prevMesh, const RootSignature* rootSignature, const Mesh* mesh);
		void PopulateEngineData(const RootSignature* rootSignature, std::uint32_t dataIndex);

		void PopulateResolve();

		void PushOutputBeginBarriers();
		void PushOutputEndBarriers();
		void PopulateOutput();

		std::vector<Camera*> cameras;
		std::vector<RenderObject*> renderObjects; ///< Render objects.

		std::set<Mesh*> meshes; ///< Render object meshes cache.

		std::vector<CameraTask> cameraTasks;
		RenderObjectData<PonyShader::Core::Context> contexts;
		RenderObjectData<PonyShader::Space::Transform> transforms;

		std::shared_ptr<DescriptorHeap> dataHeap; ///< Data descriptor heap.
		std::unordered_map<const ID3D12DescriptorHeap*, std::uint32_t> originalHeapOffsets; ///< Original heap to merged heap offset map.

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
		SortCameras();
		SyncCameraTaskCount();
		UpdateCameraTasks();

		SyncDataCounts();
		UpdateData();
	}

	void GraphicsPipeline::PopulateCommands()
	{
		UpdateHeaps();
		MergeHeaps();

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

		meshes.clear();

		contexts.data.clear();
		transforms.data.clear();
	}

	template<typename T>
	std::uint32_t GraphicsPipeline::MergedHeapDataIndex(const RenderObjectData<T>& data, const std::uint32_t index)
	{
		return originalHeapOffsets[&data.heap->Heap()] + index;
	}

	std::uint32_t GraphicsPipeline::MergedHeapMeshIndex(const Mesh& mesh, const std::uint32_t bufferIndex)
	{
		return originalHeapOffsets[&mesh.Heap()->Heap()] + bufferIndex;
	}

	void GraphicsPipeline::SortCameras()
	{
		std::ranges::sort(cameras, [](const Camera* const left, const Camera* const right)
		{
			return left->SortingOrder() < right->SortingOrder();
		});
	}

	void GraphicsPipeline::SyncCameraTaskCount()
	{
		if (cameraTasks.size() < static_cast<std::uint32_t>(cameras.size()))
		{
			cameraTasks.resize(static_cast<std::uint32_t>(cameras.size()));
		}
	}

	void GraphicsPipeline::UpdateCameraTasks()
	{
		for (std::uint32_t cameraIndex = 0u, dataIndex = 0u; cameraIndex < static_cast<std::uint32_t>(cameras.size()); ++cameraIndex)
		{
			const Camera& camera = *cameras[cameraIndex];
			const ICuller& culler = camera.Culler();
			CameraTask& cameraTask = cameraTasks[cameraIndex];
			cameraTask.renderObjectTasks.clear();

			for (std::uint32_t renderObjectIndex = 0u; renderObjectIndex < static_cast<std::uint32_t>(renderObjects.size()); ++renderObjectIndex)
			{
				RenderObject& renderObject = *renderObjects[renderObjectIndex];

				if (Cull(culler, renderObject))
				{
					continue;
				}

				AddData(camera, renderObject);
				cameraTask.renderObjectTasks.push_back(RenderObjectTask{.renderObjectIndex = renderObjectIndex, .dataIndex = dataIndex});
				++dataIndex;
			}
		}
	}

	bool GraphicsPipeline::Cull(const ICuller& culler, const RenderObject& renderObject)
	{
		return !culler.IsVisible(PonyMath::Core::TransformPoint(renderObject.ModelMatrix(), PonyMath::Core::Vector3<float>::Predefined::Zero));
	}

	void GraphicsPipeline::AddData(const Camera& camera, RenderObject& renderObject)
	{
		AddMesh(renderObject);
		AddContext(renderObject);
		AddTransform(camera, renderObject);
	}

	void GraphicsPipeline::AddMesh(RenderObject& renderObject)
	{
		meshes.insert(&renderObject.Mesh());
	}

	void GraphicsPipeline::AddContext(const RenderObject& renderObject)
	{
		const ThreadGroupCounts& materialGroups = renderObject.Material().ThreadGroupCounts();
		const PonyShader::Core::ThreadGroupCounts& meshGroups = renderObject.Mesh().ThreadGroupCounts();
		const auto context = PonyShader::Core::Context
		{
			.dispatchThreadGroupCounts = CreateDispatchThreadGroupCounts(materialGroups, meshGroups),
			.materialThreadGroupCounts = materialGroups.threadGroupCounts,
			.meshThreadGroupCounts = meshGroups
		};
		contexts.data.push_back(context);
	}

	void GraphicsPipeline::AddTransform(const Camera& camera, const RenderObject& renderObject)
	{
		const auto transform = PonyShader::Space::Transform(renderObject.ModelMatrix(), camera.ViewMatrix(), camera.ProjectionMatrix());
		transforms.data.push_back(transform);
	}

	void GraphicsPipeline::SyncDataCounts()
	{
		SyncDataCounts<PonyShader::Core::Context>(contexts, "Context");
		SyncDataCounts(transforms, "Transform");
	}

	template<typename T>
	void GraphicsPipeline::SyncDataCounts(RenderObjectData<T>& data, const std::string_view name)
	{
		const std::uint64_t bufferSize = PonyMath::Core::Align(static_cast<std::uint64_t>(sizeof(T)), 256ULL);
		const std::uint32_t count = static_cast<std::uint32_t>(data.data.size());
		SyncDataCounts(data.uploadBuffers, bufferSize, count, HeapType::Upload, name);
		SyncDataCounts(data.gpuBuffers, bufferSize, count, HeapType::Default, name);
	}

	void GraphicsPipeline::SyncDataCounts(std::vector<std::shared_ptr<Buffer>>& buffers, const std::uint64_t bufferSize, const std::uint32_t bufferCount, const HeapType heapType, const std::string_view name) const
	{
		for (std::size_t i = buffers.size(); i < bufferCount; ++i)
		{
			const std::shared_ptr<Buffer> buffer = D3D12System().ResourceManager().CreateBuffer(bufferSize, heapType);
			buffer->Name(name);
			buffers.push_back(buffer);
		}
	}

	void GraphicsPipeline::UpdateData()
	{
		UpdateData(contexts);
		UpdateData(transforms);
	}

	template<typename T>
	void GraphicsPipeline::UpdateData(RenderObjectData<T>& data)
	{
		for (std::uint32_t i = 0u; i < static_cast<std::uint32_t>(data.data.size()); ++i)
		{
			data.uploadBuffers[i]->SetData(&data.data[i], sizeof(T));
			D3D12System().CopyPipeline().AddCopyTask(*data.uploadBuffers[i], *data.gpuBuffers[i]);
		}
	}

	void GraphicsPipeline::UpdateHeaps()
	{
		UpdateHeap(contexts, "Context");
		UpdateHeap(transforms, "Transform");
	}

	template<typename T>
	void GraphicsPipeline::UpdateHeap(RenderObjectData<T>& data, const std::string_view name)
	{
		if (data.heap && data.heap->HandleCount() >= data.gpuBuffers.size())
		{
			return;
		}

		data.heap = D3D12System().DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, static_cast<std::uint32_t>(data.gpuBuffers.size()), false);
		data.heap->Name(name);

		for (std::uint32_t i = 0u; i < static_cast<std::uint32_t>(data.gpuBuffers.size()); ++i)
		{
			const auto cbvDesc = D3D12_CONSTANT_BUFFER_VIEW_DESC
			{
				.BufferLocation = data.gpuBuffers[i]->Data().GetGPUVirtualAddress(),
				.SizeInBytes = PonyMath::Core::Align(static_cast<std::uint32_t>(sizeof(T)), 256u)
			};
			D3D12System().Device().CreateConstantBufferView(&cbvDesc, data.heap->CpuHandle(i));
		}
	}

	void GraphicsPipeline::MergeHeaps()
	{
		std::uint32_t descriptorCount = MeshDescriptorCount() +
			static_cast<std::uint32_t>(contexts.data.size()) +
			static_cast<std::uint32_t>(transforms.data.size());
		if (!dataHeap || dataHeap->HandleCount() < descriptorCount)
		{
			dataHeap = D3D12System().DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, descriptorCount, true);
			dataHeap->Name("MergedData");
		}

		originalHeapOffsets.clear();

		descriptorCount = CopyMeshDescriptors(0u);
		descriptorCount += CopyDataDescriptors(contexts, descriptorCount);
		CopyDataDescriptors(transforms, descriptorCount);
	}

	std::uint32_t GraphicsPipeline::MeshDescriptorCount() const
	{
		std::uint32_t descriptorCount = 0u;
		for (Mesh* const mesh : meshes)
		{
			descriptorCount += mesh->Heap()->HandleCount();
		}

		return descriptorCount;
	}

	std::uint32_t GraphicsPipeline::CopyMeshDescriptors(const std::uint32_t destOffset)
	{
		std::uint32_t descriptorCount = 0u;

		for (Mesh* const mesh : meshes)
		{
			const DescriptorHeap* const heap = mesh->Heap();
			const std::uint32_t handleCount = heap->HandleCount();
			const std::uint32_t destIndex = destOffset + descriptorCount;

			originalHeapOffsets[&heap->Heap()] = destIndex;
			D3D12System().Device().CopyDescriptorsSimple(handleCount, dataHeap->CpuHandle(destIndex), 
				mesh->Heap()->CpuHandle(0u), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

			descriptorCount += handleCount;
		}

		return descriptorCount;
	}

	template<typename T>
	std::uint32_t GraphicsPipeline::CopyDataDescriptors(RenderObjectData<T>& data, std::uint32_t destOffset)
	{
		const std::uint32_t descriptorCount = static_cast<std::uint32_t>(data.data.size());

		originalHeapOffsets[&data.heap->Heap()] = destOffset;
		if (descriptorCount > 0u) // TODO: Check other lines for zero count guard.
		{
			D3D12System().Device().CopyDescriptorsSimple(descriptorCount, dataHeap->CpuHandle(destOffset), 
				data.heap->CpuHandle(0u), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		}

		return descriptorCount;
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

	void GraphicsPipeline::PushMeshBeginBarriers()
	{
		for (Mesh* const mesh : meshes)
		{
			for (std::uint32_t i = 0u; i < mesh->BufferCount(); ++i)
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
	}

	void GraphicsPipeline::PushMeshEndBarriers()
	{
		for (Mesh* const mesh : meshes)
		{
			for (std::uint32_t i = 0u; i < mesh->BufferCount(); ++i)
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
	}

	template<typename T>
	void GraphicsPipeline::PushRenderDataBeginBarriers(RenderObjectData<T>& data)
	{
		for (const std::shared_ptr<Buffer>& buffer : data.gpuBuffers)
		{
			const auto barrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
				.pResource = &buffer->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			AddBarrier(barrier);
		}
	}

	template<typename T>
	void GraphicsPipeline::PushRenderDataEndBarriers(RenderObjectData<T>& data)
	{
		for (const std::shared_ptr<Buffer>& buffer : data.gpuBuffers)
		{
			const auto barrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.pResource = &buffer->Data(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			AddBarrier(barrier);
		}
	}

	void GraphicsPipeline::PushDepthStencilBeginBarriers()
	{
		const auto barrier = D3D12_TEXTURE_BARRIER
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
		AddBarrier(barrier);
	}

	void GraphicsPipeline::PushDepthStencilEndBarriers()
	{
		const auto barrier = D3D12_TEXTURE_BARRIER
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
		AddBarrier(barrier);
	}

	void GraphicsPipeline::PushRenderBeginBarriers()
	{
		PushMeshBeginBarriers();
		PushRenderDataBeginBarriers(contexts);
		PushRenderDataBeginBarriers(transforms);
		PushDepthStencilBeginBarriers();
	}

	void GraphicsPipeline::PushRenderEndBarriers()
	{
		PushMeshEndBarriers();
		PushRenderDataEndBarriers(contexts);
		PushRenderDataEndBarriers(transforms);
		PushDepthStencilEndBarriers();
	}

	void GraphicsPipeline::PopulateRender()
	{
		PopulateRenderTarget();
		for (std::uint32_t i = 0u; i < cameras.size(); ++i)
		{
			PopulateCamera(i);
			SortRenderObjects(i);
			PopulateRenderObjects(i);
		}
	}

	void GraphicsPipeline::PopulateRenderTarget()
	{
		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = frame->RtvHandle();
		const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = frame->DsvHandle();
		CommandList().OMSetRenderTargets(1u, &rtvHandle, false, &dsvHandle);
	}

	void GraphicsPipeline::PopulateCamera(const std::uint32_t cameraIndex)
	{
		const Camera& camera = *cameras[cameraIndex];
		const PonyMath::Shape::Rect<float>& viewportRect = camera.ViewportRect();
		const PonyMath::Utility::Resolution<std::uint32_t>& resolution = D3D12System().FrameManager().Resolution();

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
		CommandList().ClearRenderTargetView(rtvHandle, camera.ClearColor().Span().data(), 1u, &rect);
		CommandList().ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, D3D12_MAX_DEPTH, 0u, 1u, &rect);
	}

	void GraphicsPipeline::SortRenderObjects(const std::uint32_t cameraIndex)
	{
		std::ranges::sort(cameraTasks[cameraIndex].renderObjectTasks, [&](const RenderObjectTask& left, const RenderObjectTask& right)
		{
			const RenderObject* const leftRenderObject = renderObjects[left.renderObjectIndex];
			const RenderObject* const rightRenderObject = renderObjects[right.renderObjectIndex];
			const Material* const leftMaterial = &leftRenderObject->Material();
			const Material* const rightMaterial = &rightRenderObject->Material();

			if (leftMaterial->IsTransparent() != rightMaterial->IsTransparent())
			{
				return leftMaterial->IsTransparent() < rightMaterial->IsTransparent();
			}

			const PonyShader::Space::Transform& leftTransform = transforms.data[left.dataIndex];
			const PonyShader::Space::Transform& rightTransform = transforms.data[right.dataIndex];

			if (leftMaterial->IsTransparent())
			{
				return PonyMath::Core::ExtractTranslation(leftTransform.MvpMatrix()).Z() > PonyMath::Core::ExtractTranslation(rightTransform.MvpMatrix()).Z();
			}

			if (leftMaterial->RootSignature() != rightMaterial->RootSignature())
			{
				return reinterpret_cast<std::uintptr_t>(leftMaterial->RootSignature()) < reinterpret_cast<std::uintptr_t>(rightMaterial->RootSignature());
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

	void GraphicsPipeline::PopulateRenderObjects(const std::uint32_t cameraIndex)
	{
		ID3D12DescriptorHeap* const heap = &dataHeap->Heap();
		CommandList().SetDescriptorHeaps(1u, &heap);

		const RootSignature* prevRootSignature = nullptr;
		const Material* prevMaterial = nullptr;
		const Mesh* prevMesh = nullptr;
		for (const RenderObjectTask& renderObjectTask : cameraTasks[cameraIndex].renderObjectTasks)
		{
			RenderObject* const renderObject = renderObjects[renderObjectTask.renderObjectIndex];
			Material* const material = &renderObject->Material();
			RootSignature* const rootSignature = material->RootSignature();
			const Mesh* const mesh = &renderObject->Mesh();

			PopulateMaterial(prevRootSignature, prevMaterial, rootSignature, material);
			PopulateMesh(prevRootSignature, prevMesh, rootSignature, mesh);
			PopulateEngineData(rootSignature, renderObjectTask.dataIndex);

			const auto groupCounts = contexts.data[renderObjectTask.dataIndex].dispatchThreadGroupCounts;
			CommandList().DispatchMesh(groupCounts.ThreadGroupCountX(), groupCounts.ThreadGroupCountY(), groupCounts.ThreadGroupCountZ());

			prevRootSignature = rootSignature;
			prevMaterial = material;
			prevMesh = mesh;
		}
	}

	void GraphicsPipeline::PopulateMaterial(const RootSignature* const prevRootSignature, const Material* const prevMaterial, RootSignature* const rootSignature, Material* const material)
	{
		if (rootSignature != prevRootSignature)
		{
			CommandList().SetGraphicsRootSignature(&rootSignature->RootSig());
		}
		if (material != prevMaterial)
		{
			CommandList().SetPipelineState(material->PipelineState());
		}
	}

	void GraphicsPipeline::PopulateMesh(const RootSignature* const prevRootSignature, const Mesh* const prevMesh, const RootSignature* const rootSignature, const Mesh* const mesh)
	{
		if (mesh != prevMesh || rootSignature != prevRootSignature)
		{
			for (const auto& [dataType, dataSlot] : rootSignature->DataSlots())
			{
				if (const std::optional<std::uint32_t> meshDataIndex = mesh->DataIndex(dataType))
				{
					CommandList().SetGraphicsRootDescriptorTable(dataSlot, dataHeap->GpuHandle(originalHeapOffsets[&mesh->Heap()->Heap()] + mesh->BufferOffset(meshDataIndex.value())));
				}
			}
		}
	}

	void GraphicsPipeline::PopulateEngineData(const RootSignature* const rootSignature, const std::uint32_t dataIndex)
	{
		if (const std::optional<std::uint32_t> slot = rootSignature->DataSlot(EngineDataTypes::Context))
		{
			CommandList().SetGraphicsRootDescriptorTable(slot.value(), dataHeap->GpuHandle(MergedHeapDataIndex(contexts, dataIndex)));
		}

		if (const std::optional<std::uint32_t> slot = rootSignature->DataSlot(EngineDataTypes::Transform))
		{
			CommandList().SetGraphicsRootDescriptorTable(slot.value(), dataHeap->GpuHandle(MergedHeapDataIndex(transforms, dataIndex)));
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

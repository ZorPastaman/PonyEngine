/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

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
import <string>;
import <string_view>;
import <type_traits>;
import <unordered_map>;
import <vector>;

import PonyBase.Utility.COM;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Shape;
import PonyMath.Utility;

import PonyShader.Core;
import PonyShader.Space;

import PonyEngine.Render.Detail;

import :Attachment;
import :Buffer;
import :Camera;
import :DescriptorHeap;
import :Frame;
import :FrameParams;
import :IBackManager;
import :ICopyPipeline;
import :IDescriptorHeapManager;
import :IFrameManager;
import :IGraphicsPipeline;
import :ISubSystemContext;
import :PipelineState;
import :Mesh;
import :ObjectUtility;
import :Pipeline;
import :RenderObject;
import :RootSignature;
import :SrgbOutputQuad;
import :Texture;
import :View;

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

		[[nodiscard("Pure function")]]
		virtual const FrameParams& MainFrameParams() const noexcept override;

		virtual void AddCamera(Camera& camera) override;
		virtual void RemoveCamera(Camera& camera) override;

		virtual void AddRenderObject(RenderObject& renderObject) override;
		virtual void RemoveRenderObject(RenderObject& renderObject) override;

		/// @brief Creates a main frame.
		/// @param frameParams Frame parameters.
		void CreateMainFrame(const Render::FrameParams& frameParams);

		/// @brief Prepares data before populating commands.
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
		/// @brief Render object data.
		struct RenderObjectData
		{
			static constexpr std::uint32_t DataTypeCount = 2u; ///< Data type count.
			static constexpr std::uint32_t DataIndex = 0u; ///< Common data index.
			static constexpr std::uint32_t ContextIndex = 0u; ///< Context data index.
			static constexpr std::uint32_t TransformIndex = 1u; ///< Transform data index.
			/// @brief Data sizes for each type.
			static constexpr std::array<std::uint32_t, DataTypeCount> DataSizes { sizeof(PonyShader::Core::Context), sizeof(PonyShader::Space::Transform) };

			PonyShader::Core::Context context; ///< Context.
			PonyShader::Space::Transform transform; ///< Transform
		};

		/// @brief Render object task.
		struct RenderObjectTask final
		{
			std::uint32_t renderObjectIndex; ///< Render object index.
			std::uint32_t dataIndex; ///< Data index.
		};

		/// @brief Camera task.
		struct CameraTask final 
		{
			std::vector<RenderObjectTask> renderObjectTasks; ///< Render object tasks.
		};

		/// @brief Gets the data buffer size.
		/// @return Data buffer size.
		[[nodiscard("Pure function")]]
		std::uint64_t DataBufferSize() const noexcept;
		/// @brief Gets the data descriptor count.
		/// @return Data descriptor count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataDescriptorCount() const noexcept;
		/// @brief Calculates a required data descriptor count.
		/// @param dataCount Data count.
		/// @return Data descriptor count.
		[[nodiscard("Pure function")]]
		static std::size_t DataDescriptorCount(std::size_t dataCount) noexcept;
		/// @brief Gets a sum of mesh descriptors.
		/// @return Mesh descriptor count.
		[[nodiscard("Pure function")]]
		std::uint32_t MeshDescriptorCount() const noexcept;

		/// @brief Calculates an index in the merged heap.
		/// @tparam T Value type.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @return Index the merged heap.
		std::uint32_t MergedHeapDataIndex(std::uint32_t dataIndex, std::uint32_t elementIndex) noexcept;
		/// @brief Calculates an index in the merged heap by the original data.
		/// @param mesh Mesh.
		/// @param dataIndex Mesh data index.
		/// @return Index in the merged heap.
		std::uint32_t MergedHeapMeshIndex(const Mesh& mesh, std::uint32_t dataIndex) noexcept;

		/// @brief Sorts cameras.
		void SortCameras() noexcept;
		/// @brief Allocates camera task vectors.
		void AllocateCameraTasks();
		/// @brief Updates camera tasks.
		void UpdateCameraTasks();
		/// @brief Checks if the object must be culled.
		/// @param camera Camera.
		/// @param renderObject Render object.
		/// @return @a True if it must be culled; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool Cull(const Camera& camera, const RenderObject& renderObject) noexcept;
		/// @brief Adds a render object data.
		/// @param camera Camera.
		/// @param renderObject Render object.
		void AddRenderObjectData(const Camera& camera, RenderObject& renderObject);
		/// @brief Syncs render object buffers.
		void SyncRenderObjectData();
		/// @brief Syncs render object data heap.
		void SyncRenderObjectDataHeap();

		/// @brief Merges heaps.
		void MergeHeaps();
		/// @brief Copies data descriptors into the merged heap.
		/// @param destOffset Destination offset.
		/// @return How many descriptors were copied.
		std::uint32_t CopyDataDescriptors(std::uint32_t destOffset);
		/// @brief Copies mesh descriptors into the merged heap.
		/// @param destOffset Destination offset.
		/// @return How many descriptors were copied.
		std::uint32_t CopyMeshDescriptors(std::uint32_t destOffset);

		/// @brief Adds begin to render barriers.
		void AddBeginToRenderBarriers();
		/// @brief Adds render to resolve barriers.
		void AddRenderToResolveBarriers();
		/// @brief Adds resolver to output barriers.
		void AddResolveToOutputBarriers();
		/// @brief Adds render to output barriers.
		void AddRenderToOutputBarriers();
		/// @brief Adds output to end barriers.
		void AddOutputToEndBarriers();

		/// @brief Adds depth stencil begin barriers.
		void AddDepthStencilBeginBarriers();
		/// @brief Adds depth stencil end barriers.
		void AddDepthStencilEndBarriers();
		/// @brief Adds back begin barriers.
		void AddBackBeginBarriers();
		/// @brief Adds back end barriers.
		void AddBackEndBarriers();

		/// @brief Adds render begin barriers.
		void AddRenderBeginBarriers();
		/// @brief Adds render end barriers.
		void AddRenderEndBarriers();
		/// @brief Adds render data begin barriers.
		void AddRenderDataBeginBarriers();
		/// @brief Adds render data end barriers.
		void AddRenderDataEndBarriers();
		/// @brief Adds mesh begin barriers.
		void AddMeshBeginBarriers();
		/// @brief Adds mesh end barriers.
		void AddMeshEndBarriers();

		/// @brief Populates main render phase.
		void PopulateRender();
		/// @brief Populates a render target.
		void PopulateRenderTarget();
		/// @brief Populates a camera.
		/// @param cameraIndex Camera index.
		void PopulateCamera(std::uint32_t cameraIndex);
		/// @brief Sorts render objects.
		void SortRenderObjects(std::uint32_t cameraIndex);
		/// @brief Populates render objects.
		void PopulateRenderObjects(std::uint32_t cameraIndex);
		/// @brief Populates a pipeline state. If the pipeline state is the same as a previous one, does nothing.
		/// @param prevRootSignature Previous root signature.
		/// @param prevPipelineState Previous pipeline state.
		/// @param rootSignature New root signature.
		/// @param pipelineState New pipeline state.
		void PopulatePipelineState(const RootSignature* prevRootSignature, const PipelineState* prevPipelineState, RootSignature* rootSignature, PipelineState* pipelineState);
		/// @brief Populates a mesh. If the mesh is the same as a previous one, does nothing.
		/// @param prevRootSignature Previous root signature.
		/// @param prevMesh Previous mesh.
		/// @param rootSignature New root signature.
		/// @param mesh New mesh.
		void PopulateMesh(const RootSignature* prevRootSignature, const Mesh* prevMesh, const RootSignature* rootSignature, const Mesh* mesh);
		/// @brief Populates engine data.
		/// @param rootSignature Root signature.
		/// @param dataIndex Data index.
		void PopulateEngineData(const RootSignature* rootSignature, std::uint32_t dataIndex);
		/// @brief Populates engine data.
		/// @param rootSignature Root signature.
		/// @param dataType Engine data type.
		/// @param dataIndex Data index.
		/// @param elementIndex Data element index.
		/// @return @a True if the root signature has a needed slot and the data was actually populated; @a false otherwise.
		bool PopulateEngineData(const RootSignature* rootSignature, std::string_view dataType, std::uint32_t dataIndex, std::uint32_t elementIndex);

		/// @brief Populates resolve.
		void PopulateResolve();
		/// @brief Populates sRGB output.
		void PopulateOutput();

		std::vector<Camera*> cameras; ///< Cameras.
		std::vector<RenderObject*> renderObjects; ///< Render objects.

		std::vector<RenderObjectData> renderObjectData; ///< Render object data.
		std::shared_ptr<Buffer> renderObjectUploadData; ///< Render object data upload buffer.
		std::shared_ptr<Buffer> renderObjectGpuData; ///< Render object data gpu buffer.
		std::shared_ptr<DescriptorHeap> renderObjectDataHeap; ///< Render object data heap.

		std::set<Mesh*> meshes; ///< Render object meshes cache.

		std::vector<CameraTask> cameraTasks; ///< Camera tasks.

		std::shared_ptr<DescriptorHeap> mergedDataHeap; ///< Merged data descriptor heap.
		std::unordered_map<const ID3D12DescriptorHeap*, std::uint32_t> originalHeapOffsets; ///< Original heap to merged heap offset map.

		FrameParams frameParams; ///< Main frame parameters.
		std::shared_ptr<Frame> frame; ///< Main frame.
		std::unique_ptr<SrgbOutputQuad> outputQuad; ///< Srgb output quad.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	GraphicsPipeline::GraphicsPipeline(ISubSystemContext& d3d12System, const INT commandQueuePriority) :
		Pipeline(d3d12System, commandQueuePriority, D3D12_COMMAND_LIST_TYPE_DIRECT),
		frameParams{}
	{
		cameras.reserve(8);
		renderObjects.reserve(64);
		renderObjectData.reserve(8 * 64);
		cameraTasks.reserve(8);
		originalHeapOffsets.reserve(128);
	}

	const FrameParams& GraphicsPipeline::MainFrameParams() const noexcept
	{
		return frameParams;
	}

	void GraphicsPipeline::AddCamera(Camera& camera)
	{
		assert(std::ranges::find(cameras, &camera) == cameras.cend() && "The camera is already added.");
		cameras.push_back(&camera);
	}

	void GraphicsPipeline::RemoveCamera(Camera& camera)
	{
		if (const auto position = std::ranges::find(cameras, &camera); position != cameras.cend()) [[likely]]
		{
			cameras.erase(position);
		}
		else
		{
			PONY_LOG(D3D12System().Logger(), PonyDebug::Log::LogType::Warning, "Tried to remove a non-added camera.");
		}
	}

	void GraphicsPipeline::AddRenderObject(RenderObject& renderObject)
	{
		assert(std::ranges::find(renderObjects, &renderObject) == renderObjects.cend() && "The render object is already added.");
		renderObjects.push_back(&renderObject);
	}

	void GraphicsPipeline::RemoveRenderObject(RenderObject& renderObject)
	{
		if (const auto position = std::ranges::find(renderObjects, &renderObject); position != renderObjects.cend()) [[likely]]
		{
			renderObjects.erase(position);
		}
		else
		{
			PONY_LOG(D3D12System().Logger(), PonyDebug::Log::LogType::Warning, "Tried to remove a non-added render object.");
		}
	}

	void GraphicsPipeline::CreateMainFrame(const Render::FrameParams& frameParams)
	{
		PONY_LOG(D3D12System().Logger(), PonyDebug::Log::LogType::Info, "Create frame.");
		this->frameParams = D3D12System().FrameManager().ConvertFrameParams(frameParams);
		frame = D3D12System().FrameManager().CreateFrame(this->frameParams);
		frame->Name("MainFrame");
		PONY_LOG(D3D12System().Logger(), PonyDebug::Log::LogType::Info, "Frame created.");

		PONY_LOG(D3D12System().Logger(), PonyDebug::Log::LogType::Info, "Create output quad.");
		outputQuad = std::make_unique<SrgbOutputQuad>(D3D12System());
		outputQuad->Name("OutputQuad");
		PONY_LOG(D3D12System().Logger(), PonyDebug::Log::LogType::Info, "Output quad created.");
	}

	void GraphicsPipeline::Prepare()
	{
		SortCameras();
		AllocateCameraTasks();
		UpdateCameraTasks();

		SyncRenderObjectData();
	}

	void GraphicsPipeline::PopulateCommands()
	{
		SyncRenderObjectDataHeap();
		MergeHeaps();

		ResetLists();
		AddBeginToRenderBarriers();
		PopulateBarriers();
		PopulateRender();
		if (frame->FindTexture(Attachment::Resolve))
		{
			AddRenderToResolveBarriers();
			PopulateBarriers();
			PopulateResolve();
			AddResolveToOutputBarriers();
		}
		else
		{
			AddRenderToOutputBarriers();
		}
		PopulateBarriers();
		PopulateOutput();
		AddOutputToEndBarriers();
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
		meshes.clear();
		renderObjectData.clear();
	}

	std::uint64_t GraphicsPipeline::DataBufferSize() const noexcept
	{
		return static_cast<std::uint64_t>(renderObjectData.size() * sizeof(RenderObjectData));
	}

	std::uint32_t GraphicsPipeline::DataDescriptorCount() const noexcept
	{
		return static_cast<std::uint32_t>(DataDescriptorCount(renderObjectData.size()));
	}

	std::size_t GraphicsPipeline::DataDescriptorCount(const std::size_t dataCount) noexcept
	{
		return dataCount * RenderObjectData::DataTypeCount;
	}

	std::uint32_t GraphicsPipeline::MeshDescriptorCount() const noexcept
	{
		std::uint32_t descriptorCount = 0u;
		for (Mesh* const mesh : meshes)
		{
			descriptorCount += mesh->Heap()->HandleCount();
		}

		return descriptorCount;
	}

	std::uint32_t GraphicsPipeline::MergedHeapDataIndex(const std::uint32_t dataIndex, const std::uint32_t elementIndex) noexcept
	{
		return originalHeapOffsets[&renderObjectDataHeap->Heap()] + static_cast<std::uint32_t>(DataDescriptorCount(dataIndex)) + elementIndex;
	}

	std::uint32_t GraphicsPipeline::MergedHeapMeshIndex(const Mesh& mesh, const std::uint32_t dataIndex) noexcept
	{
		return originalHeapOffsets[&mesh.Heap()->Heap()] + mesh.BufferOffset(dataIndex);
	}

	void GraphicsPipeline::SortCameras() noexcept
	{
		std::ranges::sort(cameras, [](const Camera* const left, const Camera* const right)
		{
			return left->SortingOrder() < right->SortingOrder();
		});
	}

	void GraphicsPipeline::AllocateCameraTasks()
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
			CameraTask& cameraTask = cameraTasks[cameraIndex];
			cameraTask.renderObjectTasks.clear();

			for (std::uint32_t renderObjectIndex = 0u; renderObjectIndex < static_cast<std::uint32_t>(renderObjects.size()); ++renderObjectIndex)
			{
				RenderObject& renderObject = *renderObjects[renderObjectIndex];

				if (Cull(camera, renderObject))
				{
					continue;
				}

				AddRenderObjectData(camera, renderObject);
				cameraTask.renderObjectTasks.push_back(RenderObjectTask{.renderObjectIndex = renderObjectIndex, .dataIndex = dataIndex});
				++dataIndex;
			}
		}
	}

	bool GraphicsPipeline::Cull(const Camera& camera, const RenderObject& renderObject) noexcept
	{
		if (!renderObject.PipelineState().CameraCulling())
		{
			return false;
		}
		const Mesh* const mesh = renderObject.Mesh();
		if (!mesh)
		{
			return false;
		}
		const std::optional<PonyMath::Shape::AABB<float>>& boundingBox = mesh->BoundingBox();
		if (!boundingBox)
		{
			return false;
		}

		return !camera.Culler().IsVisible(PonyMath::Shape::OBB<float>(boundingBox.value(), camera.ViewMatrix() * renderObject.ModelMatrix()));
	}

	void GraphicsPipeline::AddRenderObjectData(const Camera& camera, RenderObject& renderObject)
	{
		if (DataDescriptorCount(renderObjectData.size() + 1) >= std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::runtime_error("Max render object count is exceeded.");
		}

		Mesh* const mesh = renderObject.Mesh();
		if (mesh)
		{
			meshes.insert(mesh);
		}

		const auto transform = PonyShader::Space::Transform(renderObject.ModelMatrix(), camera.ViewMatrix(), camera.ProjectionMatrix());

		const ThreadGroupCounts& pipelineStateCounts = renderObject.PipelineState().ThreadGroupCounts();
		const PonyShader::Core::ThreadGroupCounts meshGroups = mesh ? mesh->ThreadGroupCounts() : PonyShader::Core::ThreadGroupCounts();
		const auto context = PonyShader::Core::Context
		{
			.dispatchThreadGroupCounts = CreateDispatchThreadGroupCounts(pipelineStateCounts, meshGroups),
			.pipelineStateThreadGroupCounts = pipelineStateCounts.threadGroupCounts,
			.meshThreadGroupCounts = meshGroups,
			.renderQueue = renderObject.PipelineState().RenderQueue(),
			.isTransparent = renderObject.PipelineState().IsTransparent(),
			.isFlipped = transform.MvpMatrix().Determinant() < 0.f
		};

		renderObjectData.push_back(RenderObjectData
		{
			.context = context,
			.transform = transform
		});
	}

	void GraphicsPipeline::SyncRenderObjectData()
	{
		const std::uint64_t bufferSize = std::max(DataBufferSize(), 1ULL);

		if (!renderObjectUploadData || renderObjectUploadData->Data().GetDesc1().Width < bufferSize)
		{
			renderObjectUploadData = D3D12System().ResourceManager().CreateBuffer(bufferSize, HeapType::Upload);
			renderObjectUploadData->Name(DataTypes::Data);
		}
		if (!renderObjectGpuData || renderObjectGpuData->Data().GetDesc1().Width < bufferSize)
		{
			renderObjectGpuData = D3D12System().ResourceManager().CreateBuffer(bufferSize, HeapType::Default);
			renderObjectGpuData->Name(DataTypes::Data);
		}

		renderObjectUploadData->SetData(renderObjectData.data(), bufferSize);
		D3D12System().CopyPipeline().AddCopyTask(*renderObjectUploadData, *renderObjectGpuData);
	}

	void GraphicsPipeline::SyncRenderObjectDataHeap()
	{
		const std::uint32_t descriptorCount = DataDescriptorCount();

		if (renderObjectDataHeap && renderObjectDataHeap->HandleCount() >= descriptorCount)
		{
			return;
		}

		renderObjectDataHeap = D3D12System().DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, descriptorCount, false);
		renderObjectDataHeap->Name(DataTypes::Data);

		std::uint64_t gpuAddress = renderObjectGpuData->Data().GetGPUVirtualAddress();
		std::uint32_t heapIndex = 0u;
		for (std::size_t dataIndex = 0u; dataIndex < renderObjectData.size(); ++dataIndex)
		{
			for (std::size_t elementIndex = 0; elementIndex < RenderObjectData::DataTypeCount; ++elementIndex, ++heapIndex)
			{
				const std::uint32_t elementSize = RenderObjectData::DataSizes[elementIndex];

				const auto cbvDesc = D3D12_CONSTANT_BUFFER_VIEW_DESC
				{
					.BufferLocation = gpuAddress,
					.SizeInBytes = elementSize
				};
				D3D12System().Device().CreateConstantBufferView(&cbvDesc, renderObjectDataHeap->CpuHandle(heapIndex));

				gpuAddress += elementSize;
			}
		}
	}

	void GraphicsPipeline::MergeHeaps()
	{
		std::uint32_t descriptorCount = DataDescriptorCount() + MeshDescriptorCount();
		if (!mergedDataHeap || mergedDataHeap->HandleCount() < descriptorCount)
		{
			mergedDataHeap = D3D12System().DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, descriptorCount, true);
			mergedDataHeap->Name("MergedData");
		}

		originalHeapOffsets.clear();

		descriptorCount = CopyDataDescriptors(0u);
		descriptorCount += CopyMeshDescriptors(descriptorCount);

		for (std::uint32_t i = descriptorCount; i < mergedDataHeap->HandleCount(); ++i)
		{
			D3D12System().Device().CreateConstantBufferView(nullptr, mergedDataHeap->CpuHandle(i));
		}
	}

	std::uint32_t GraphicsPipeline::CopyDataDescriptors(const std::uint32_t destOffset)
	{
		const std::uint32_t descriptorCount = DataDescriptorCount();

		originalHeapOffsets[&renderObjectDataHeap->Heap()] = destOffset;
		if (descriptorCount > 0u)
		{
			D3D12System().Device().CopyDescriptorsSimple(descriptorCount, mergedDataHeap->CpuHandle(destOffset),
				renderObjectDataHeap->CpuHandle(0u), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
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
			if (handleCount > 0u)
			{
				D3D12System().Device().CopyDescriptorsSimple(handleCount, mergedDataHeap->CpuHandle(destIndex), 
					mesh->Heap()->CpuHandle(0u), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			}

			descriptorCount += handleCount;
		}

		return descriptorCount;
	}

	void GraphicsPipeline::AddBeginToRenderBarriers()
	{
		if (Texture* const renderTarget = frame->FindTexture(Attachment::RenderTarget))
		{
			const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_RENDER_TARGET,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_RENDER_TARGET,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
				.pResource = &renderTarget->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(renderTargetBarrier);
		}

		AddDepthStencilBeginBarriers();
		AddRenderBeginBarriers();
	}

	void GraphicsPipeline::AddRenderToResolveBarriers()
	{
		Texture* const renderTarget = frame->FindTexture(Attachment::RenderTarget);
		Texture* const resolve = frame->FindTexture(Attachment::Resolve);
		assert(renderTarget && resolve && "The graphics pipeline took a resolve path though render target or resolve are nullptr.");
		const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.SyncAfter = D3D12_BARRIER_SYNC_RESOLVE,
			.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.AccessAfter = D3D12_BARRIER_ACCESS_RESOLVE_SOURCE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE,
			.pResource = &renderTarget->Data(),
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
			.pResource = &resolve->Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		AddBarrier(renderTargetBarrier);
		AddBarrier(resolveBarrier);

		AddDepthStencilEndBarriers();
		AddRenderEndBarriers();
	}

	void GraphicsPipeline::AddResolveToOutputBarriers()
	{
		Texture* const renderTarget = frame->FindTexture(Attachment::RenderTarget);
		Texture* const resolve = frame->FindTexture(Attachment::Resolve);
		assert(renderTarget && resolve && "The graphics pipeline took a resolve path though render target or resolve are nullptr.");
		const auto renderBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_RESOLVE,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_RESOLVE_SOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
			.pResource = &renderTarget->Data(),
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
			.pResource = &resolve->Data(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		AddBarrier(renderBarrier);
		AddBarrier(resolveBarrier);

		AddBackBeginBarriers();
	}

	void GraphicsPipeline::AddRenderToOutputBarriers()
	{
		if (Texture* const renderTarget = frame->FindTexture(Attachment::RenderTarget))
		{
			const auto barrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
				.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
				.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
				.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE,
				.pResource = &renderTarget->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(barrier);
		}

		AddDepthStencilEndBarriers();
		AddBackBeginBarriers();
		AddRenderEndBarriers();
	}

	void GraphicsPipeline::AddOutputToEndBarriers()
	{
		if (Texture* const resolve = frame->FindTexture(Attachment::Resolve); Texture* const output = resolve ? resolve : frame->FindTexture(Attachment::RenderTarget))
		{
			const auto barrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_SHADER_RESOURCE,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
				.pResource = &output->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(barrier);
		}

		AddBackEndBarriers();
	}

	void GraphicsPipeline::AddDepthStencilBeginBarriers()
	{
		if (Texture* const depthStencil = frame->FindTexture(Attachment::DepthStencil))
		{
			const auto depthStencilBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE,
				.pResource = &depthStencil->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(depthStencilBarrier);
		}
	}

	void GraphicsPipeline::AddDepthStencilEndBarriers()
	{
		if (Texture* const depthStencil = frame->FindTexture(Attachment::DepthStencil))
		{
			const auto depthStencilBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ,
				.pResource = &depthStencil->Data(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(depthStencilBarrier);
		}
	}

	void GraphicsPipeline::AddBackBeginBarriers()
	{
		if (ID3D12Resource* const backBuffer = D3D12System().BackManager().CurrentBackBuffer())
		{
			const auto barrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_RENDER_TARGET,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_RENDER_TARGET,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_PRESENT,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
				.pResource = backBuffer,
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(barrier);
		}
	}

	void GraphicsPipeline::AddBackEndBarriers()
	{
		if (ID3D12Resource* const backBuffer = D3D12System().BackManager().CurrentBackBuffer())
		{
			const auto barrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_PRESENT,
				.pResource = backBuffer,
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			AddBarrier(barrier);
		}
	}

	void GraphicsPipeline::AddRenderBeginBarriers()
	{
		AddRenderDataBeginBarriers();
		AddMeshBeginBarriers();
	}

	void GraphicsPipeline::AddRenderEndBarriers()
	{
		AddRenderDataEndBarriers();
		AddMeshEndBarriers();
	}

	void GraphicsPipeline::AddRenderDataBeginBarriers()
	{
		const auto barrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
			.pResource = &renderObjectGpuData->Data(),
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		AddBarrier(barrier);
	}

	void GraphicsPipeline::AddRenderDataEndBarriers()
	{
		const auto barrier = D3D12_BUFFER_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_DRAW,
			.SyncAfter = D3D12_BARRIER_SYNC_NONE,
			.AccessBefore = D3D12_BARRIER_ACCESS_SHADER_RESOURCE,
			.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.pResource = &renderObjectGpuData->Data(),
			.Offset = 0UL,
			.Size = UINT64_MAX
		};
		AddBarrier(barrier);
	}

	void GraphicsPipeline::AddMeshBeginBarriers()
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

	void GraphicsPipeline::AddMeshEndBarriers()
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

	void GraphicsPipeline::PopulateRender()
	{
		PopulateRenderTarget();

		if (!frame->FindTexture(Attachment::RenderTarget) && !frame->FindTexture(Attachment::DepthStencil))
		{
			return;
		}

		for (std::uint32_t i = 0u; i < cameras.size(); ++i)
		{
			PopulateCamera(i);
			SortRenderObjects(i);
			PopulateRenderObjects(i);
		}
	}

	void GraphicsPipeline::PopulateRenderTarget()
	{
		const std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandle = frame->FindCpuHandle(View::RenderTarget);
		const std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> dsvHandle = frame->FindCpuHandle(View::DepthStencil);

		std::uint32_t count = 0u;
		std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 1> rtvs;
		if (rtvHandle)
		{
			rtvs[count++] = rtvHandle.value();
		}

		CommandList().OMSetRenderTargets(count, rtvs.data(), true, dsvHandle.has_value() ? &dsvHandle.value() : nullptr);
	}

	void GraphicsPipeline::PopulateCamera(const std::uint32_t cameraIndex)
	{
		const Camera& camera = *cameras[cameraIndex];
		const PonyMath::Shape::Rect<float>& viewportRect = camera.ViewportRect();
		const PonyMath::Utility::Resolution<std::uint32_t>& resolution = frameParams.resolution;

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

		const struct Clear& clear = camera.Clear();

		const std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> rtv = frame->FindCpuHandle(View::RenderTarget);
		if (rtv && clear.renderTargetColor)
		{
			CommandList().ClearRenderTargetView(rtv.value(), clear.renderTargetColor.value().Span().data(), 1u, &rect);
		}

		const std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> dsv = frame->FindCpuHandle(View::DepthStencil);
		if (const D3D12_CLEAR_FLAGS dsvClearFlags =
			(clear.depth.has_value() ? D3D12_CLEAR_FLAG_DEPTH : static_cast<D3D12_CLEAR_FLAGS>(0)) |
			(clear.stencil.has_value() ? D3D12_CLEAR_FLAG_STENCIL : static_cast<D3D12_CLEAR_FLAGS>(0));
			dsv && dsvClearFlags != static_cast<D3D12_CLEAR_FLAGS>(0))
		{
			CommandList().ClearDepthStencilView(dsv.value(), dsvClearFlags, clear.depth.value_or(D3D12_MAX_DEPTH), clear.stencil.value_or(std::uint8_t{0u}), 1u, &rect);
		}
	}

	void GraphicsPipeline::SortRenderObjects(const std::uint32_t cameraIndex)
	{
		std::vector<RenderObjectTask>& tasks = cameraTasks[cameraIndex].renderObjectTasks;

		// Basic sorting - by render queue, by transparency, by distance (opaque - front to back, transparent - back to front)
		std::ranges::sort(tasks, [&](const RenderObjectTask& left, const RenderObjectTask& right)
		{
			const RenderObject* const leftRenderObject = renderObjects[left.renderObjectIndex];
			const RenderObject* const rightRenderObject = renderObjects[right.renderObjectIndex];
			const PipelineState* const leftPipelineState = &leftRenderObject->PipelineState();
			const PipelineState* const rightPipelineState = &rightRenderObject->PipelineState();

			if (leftPipelineState->RenderQueue() != rightPipelineState->RenderQueue())
			{
				return leftPipelineState->RenderQueue() < rightPipelineState->RenderQueue();
			}

			if (leftPipelineState->IsTransparent() != rightPipelineState->IsTransparent())
			{
				return leftPipelineState->IsTransparent() < rightPipelineState->IsTransparent();
			}

			const Mesh* const leftMesh = leftRenderObject->Mesh();
			const Mesh* const rightMesh = rightRenderObject->Mesh();
			const PonyMath::Core::Vector3<float>& leftCentralPoint = leftMesh && leftMesh->BoundingBox()
				? leftMesh->BoundingBox().value().Center()
				: PonyMath::Core::Vector3<float>::Predefined::Zero;
			const PonyMath::Core::Vector3<float>& rightCentralPoint = rightMesh && rightMesh->BoundingBox()
				? rightMesh->BoundingBox().value().Center()
				: PonyMath::Core::Vector3<float>::Predefined::Zero;

			const PonyMath::Core::Matrix4x4<float>& leftMvp = renderObjectData[left.dataIndex].transform.MvpMatrix();
			const PonyMath::Core::Matrix4x4<float>& rightMvp = renderObjectData[right.dataIndex].transform.MvpMatrix();

			const float leftDistance = PonyMath::Core::TransformPoint(leftMvp, leftCentralPoint).Z();
			const float rightDistance = PonyMath::Core::TransformPoint(rightMvp, rightCentralPoint).Z();

			return leftPipelineState->IsTransparent()
				? leftDistance > rightDistance
				: leftDistance < rightDistance;
		});

		if (tasks.size() < 3)
		{
			return;
		}

		// Group opaque objects with the same root signature together.
		for (std::size_t baseIndex = 0; baseIndex < tasks.size() - 2; ++baseIndex)
		{
			const RenderObjectTask& baseTask = tasks[baseIndex];
			const RenderObject* const baseRenderObject = renderObjects[baseTask.renderObjectIndex];
			const PipelineState& basePipelineState = baseRenderObject->PipelineState();
			if (basePipelineState.IsTransparent())
			{
				continue;
			}
			const RootSignature* const baseRootSignature = basePipelineState.RootSignature();

			for (std::size_t targetIndex = baseIndex + 1; targetIndex < tasks.size(); ++targetIndex)
			{
				const RenderObjectTask& targetTask = tasks[targetIndex];
				const RenderObject* const targetRenderObject = renderObjects[targetTask.renderObjectIndex];
				const PipelineState& targetPipelineState = targetRenderObject->PipelineState();
				if (targetPipelineState.IsTransparent() || targetPipelineState.RenderQueue() != basePipelineState.RenderQueue())
				{
					break;
				}

				if (targetPipelineState.RootSignature() == baseRootSignature)
				{
					PonyBase::Utility::Move(tasks, targetIndex, baseIndex + 1);
					break;
				}
			}
		}

		// Group opaque objects with the same pipeline state together.
		for (std::size_t baseIndex = 0; baseIndex < tasks.size() - 2; ++baseIndex)
		{
			const RenderObjectTask& baseTask = tasks[baseIndex];
			const RenderObject* const baseRenderObject = renderObjects[baseTask.renderObjectIndex];
			const PipelineState& basePipelineState = baseRenderObject->PipelineState();
			if (basePipelineState.IsTransparent())
			{
				continue;
			}
			const RootSignature* const baseRootSignature = basePipelineState.RootSignature();

			for (std::size_t targetIndex = baseIndex + 1; targetIndex < tasks.size(); ++targetIndex)
			{
				const RenderObjectTask& targetTask = tasks[targetIndex];
				const RenderObject* const targetRenderObject = renderObjects[targetTask.renderObjectIndex];
				const PipelineState& targetPipelineState = targetRenderObject->PipelineState();
				if (targetPipelineState.IsTransparent() || targetPipelineState.RenderQueue() != basePipelineState.RenderQueue() || targetPipelineState.RootSignature() != baseRootSignature)
				{
					break;
				}

				if (&targetPipelineState == &basePipelineState)
				{
					PonyBase::Utility::Move(tasks, targetIndex, baseIndex + 1);
					break;
				}
			}
		}

		// Group opaque objects with the same mesh together.
		for (std::size_t baseIndex = 0; baseIndex < tasks.size() - 2; ++baseIndex)
		{
			const RenderObjectTask& baseTask = tasks[baseIndex];
			const RenderObject* const baseRenderObject = renderObjects[baseTask.renderObjectIndex];
			const PipelineState& basePipelineState = baseRenderObject->PipelineState();
			if (basePipelineState.IsTransparent())
			{
				continue;
			}
			const Mesh* const baseMesh = baseRenderObject->Mesh();

			for (std::size_t targetIndex = baseIndex + 1; targetIndex < tasks.size(); ++targetIndex)
			{
				const RenderObjectTask& targetTask = tasks[targetIndex];
				const RenderObject* const targetRenderObject = renderObjects[targetTask.renderObjectIndex];
				const PipelineState& targetPipelineState = targetRenderObject->PipelineState();
				if (targetPipelineState.IsTransparent() || targetPipelineState.RenderQueue() != basePipelineState.RenderQueue() || &targetPipelineState != &basePipelineState)
				{
					break;
				}

				if (targetRenderObject->Mesh() == baseMesh)
				{
					PonyBase::Utility::Move(tasks, targetIndex, baseIndex + 1);
					break;
				}
			}
		}
	}

	void GraphicsPipeline::PopulateRenderObjects(const std::uint32_t cameraIndex)
	{
		ID3D12DescriptorHeap* const heap = &mergedDataHeap->Heap();
		CommandList().SetDescriptorHeaps(1u, &heap);

		const RootSignature* prevRootSignature = nullptr;
		const PipelineState* prevPipelineState = nullptr;
		const Mesh* prevMesh = nullptr;
		for (const RenderObjectTask& renderObjectTask : cameraTasks[cameraIndex].renderObjectTasks)
		{
			RenderObject* const renderObject = renderObjects[renderObjectTask.renderObjectIndex];
			PipelineState* const pipelineState = &renderObject->PipelineState();
			RootSignature* const rootSignature = pipelineState->RootSignature();
			const Mesh* const mesh = renderObject->Mesh();

			PopulatePipelineState(prevRootSignature, prevPipelineState, rootSignature, pipelineState);
			PopulateMesh(prevRootSignature, prevMesh, rootSignature, mesh);
			PopulateEngineData(rootSignature, renderObjectTask.dataIndex);

			const auto groupCounts = renderObjectData[renderObjectTask.dataIndex].context.dispatchThreadGroupCounts;
			CommandList().DispatchMesh(groupCounts.ThreadGroupCountX(), groupCounts.ThreadGroupCountY(), groupCounts.ThreadGroupCountZ());

			prevRootSignature = rootSignature;
			prevPipelineState = pipelineState;
			prevMesh = mesh;
		}
	}

	void GraphicsPipeline::PopulatePipelineState(const RootSignature* const prevRootSignature, const PipelineState* const prevPipelineState, RootSignature* const rootSignature, PipelineState* const pipelineState)
	{
		if (rootSignature != prevRootSignature)
		{
			CommandList().SetGraphicsRootSignature(&rootSignature->RootSig());
		}
		if (pipelineState != prevPipelineState)
		{
			CommandList().SetPipelineState(pipelineState->State());
		}
	}

	void GraphicsPipeline::PopulateMesh(const RootSignature* const prevRootSignature, const Mesh* const prevMesh, const RootSignature* const rootSignature, const Mesh* const mesh)
	{
		if (mesh && (mesh != prevMesh || rootSignature != prevRootSignature))
		{
			for (const auto& [dataType, dataSlot] : rootSignature->DataSlots())
			{
				if (const std::optional<std::uint32_t> meshDataIndex = mesh->DataIndex(dataType))
				{
					CommandList().SetGraphicsRootDescriptorTable(dataSlot, mergedDataHeap->GpuHandle(MergedHeapMeshIndex(*mesh, meshDataIndex.value())));
				}
			}
		}
	}

	void GraphicsPipeline::PopulateEngineData(const RootSignature* const rootSignature, const std::uint32_t dataIndex)
	{
		if (PopulateEngineData(rootSignature, DataTypes::Data, dataIndex, RenderObjectData::DataIndex))
		{
			return;
		}

		PopulateEngineData(rootSignature, DataTypes::Context, dataIndex, RenderObjectData::ContextIndex);
		PopulateEngineData(rootSignature, DataTypes::Transform, dataIndex, RenderObjectData::TransformIndex);
	}

	bool GraphicsPipeline::PopulateEngineData(const RootSignature* const rootSignature, const std::string_view dataType, const std::uint32_t dataIndex, const std::uint32_t elementIndex)
	{
		if (const std::optional<std::uint32_t> slot = rootSignature->DataSlot(dataType))
		{
			CommandList().SetGraphicsRootDescriptorTable(slot.value(), mergedDataHeap->GpuHandle(MergedHeapDataIndex(dataIndex, elementIndex)));

			return true;
		}

		return false;
	}

	void GraphicsPipeline::PopulateResolve()
	{
		Texture* const renderTarget = frame->FindTexture(Attachment::RenderTarget);
		Texture* const resolve = frame->FindTexture(Attachment::Resolve);
		assert(renderTarget && resolve && "The graphics pipeline tried to resolve nullptr textures.");

		CommandList().ResolveSubresource(&resolve->Data(), 0u, &renderTarget->Data(), 0u, frameParams.rtvFormat);
	}

	void GraphicsPipeline::PopulateOutput()
	{
		DescriptorHeap* const outputHeap = frame->FindHeap(View::Output);
		const std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> output = frame->FindGpuHandle(View::Output);
		const std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> backViewHandle = D3D12System().BackManager().CurrentRtvHandle();
		if (!outputHeap || !output || !backViewHandle)
		{
			return;
		}

		CommandList().OMSetRenderTargets(1u, &backViewHandle.value(), true, nullptr);

		CommandList().SetGraphicsRootSignature(&outputQuad->RootSignature());
		CommandList().SetPipelineState(&outputQuad->PipelineState());

		ID3D12DescriptorHeap* const outputHeapData = &outputHeap->Heap();
		CommandList().SetDescriptorHeaps(1u, &outputHeapData);
		CommandList().SetGraphicsRootDescriptorTable(outputQuad->RenderTargetSlot, output.value());

		CommandList().DispatchMesh(outputQuad->ThreadGroupXCount, outputQuad->ThreadGroupYCount, outputQuad->ThreadGroupZCount);
	}
}

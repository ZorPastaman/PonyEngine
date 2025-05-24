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

export module PonyEngine.Render.Core:Pipeline;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <functional>;
import <optional>;
import <limits>;
import <unordered_set>;
import <utility>;
import <vector>;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Shape;
import PonyMath.Utility;

import PonyShader.Core;
import PonyShader.Space;

import :ConstantData;
import :IPipeline;
import :IRenderSystemContext;

export namespace PonyEngine::Render
{
	/// @brief Pipeline.
	class Pipeline final : public IPipeline
	{
	public:
		/// @brief Creates a pipeline.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constructor")]]
		explicit Pipeline(IRenderSystemContext& renderSystem) noexcept;
		Pipeline(const Pipeline&) = delete;
		Pipeline(Pipeline&&) = delete;

		~Pipeline() noexcept = default;

		virtual void Submit(const IRenderObject& renderObject) override;
		virtual void Submit(const ICamera& camera) override;
		virtual void Submit(const IFrame& frame) override;
		virtual void SetMainFrame(const IFrame& mainFrame) override;

		/// @brief Ticks the pipeline.
		void Tick();

		Pipeline& operator =(const Pipeline&) = delete;
		Pipeline& operator =(Pipeline&&) = delete;

	private:
		/// @brief Render object data.
		struct RenderObjectData
		{
			static constexpr std::uint32_t DataTypeCount = 2u; ///< Data type count.
			static constexpr std::uint32_t ContextIndex = 0u; ///< Context data index.
			static constexpr std::uint32_t TransformIndex = 1u; ///< Transform data index.
			/// @brief Data sizes for each type.
			static constexpr std::array<std::uint32_t, DataTypeCount> DataSizes{ sizeof(PonyShader::Core::Context), sizeof(PonyShader::Space::Transform) };

			PonyShader::Core::Context context; ///< Context.
			PonyShader::Space::Transform transform; ///< Transform
		};

		static constexpr std::size_t DataCount = 1u; ///< Data count.
		static constexpr std::size_t RenderObjectDataIndex = 0u; ///< Render object data index in a global constant buffer.

		/// @brief Render object task.
		struct RenderObjectTask final
		{
			std::size_t renderObjectIndex; ///< Render object index.
			std::size_t dataIndex; ///< Data index.
			float distance; ///< Distance to the camera.
		};

		/// @brief Camera task.
		struct CameraTask final
		{
			std::vector<RenderObjectTask> renderObjectTasks; ///< Render object tasks.
		};

		/// @brief Begins a tick.
		void BeginTick();
		/// @brief Ends a tick.
		void EndTick();

		/// @brief Begins a rendering step.
		void BeginRender();
		/// @brief Ends a render rendering step.
		void EndRender();

		/// @brief Begins a frame.
		/// @param cameraIndex Index of the camera that will be used.
		void BeginTarget(std::size_t cameraIndex);
		/// @brief Ends a frame.
		/// @param cameraIndex Index of the camera that was used.
		void EndTarget(std::size_t cameraIndex);

		/// @brief Prepares a render.
		void Prepare();
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
		static bool Cull(const ICamera& camera, const IRenderObject& renderObject) noexcept;
		/// @brief Adds a render object data.
		/// @param camera Camera.
		/// @param renderObject Render object.
		void AddRenderObjectData(const ICamera& camera, const IRenderObject& renderObject);
		/// @brief Updates resource caches.
		void UpdateResources() noexcept;
		/// @brief Sets the input data.
		void SetResources();
		/// @brief Uploads data to GPU.
		void Upload();

		/// @brief Renders.
		void Render();
		/// @brief Clears all the submitted frames.
		void ClearFrames();
		/// @brief Executes camera tasks.
		/// @param cameraIndex Camera index.
		void Render(std::size_t cameraIndex);
		/// @brief Calculates distances to the camera.
		/// @param cameraIndex Camera index.
		void CalculateDistances(std::size_t cameraIndex) noexcept;
		/// @brief Sorts render objects.
		/// @param cameraIndex Camera index.
		void SortRenderObjects(std::size_t cameraIndex) noexcept;
		/// @brief Renders objects.
		/// @param cameraIndex Camera index.
		void RenderObjects(std::size_t cameraIndex);

		/// @brief Finalizes the render.
		void Finalize();
		/// @brief Resolves the frame.
		/// @param frame Frame to resolve.
		void Resolve(const IFrame* frame);
		/// @brief Outputs the frame.
		/// @param frame Frame to output.
		void Output(const IFrame* frame);

		/// @brief Clears the submitted objects.
		void Clear() noexcept;

		/// @brief Gets targets from the frame.
		/// @param frame Frame
		/// @return <Render target, Depth stencil>.
		[[nodiscard("Pure function")]]
		static std::tuple<const IAttachment*, const IAttachment*> GetTargets(const IFrame* frame) noexcept;
		/// @brief Gets the resolve resources.
		/// @param frame Frame.
		/// @return <Resolve source, Resolve destination>.
		[[nodiscard("Pure function")]]
		static std::pair<const IAttachment*, const IAttachment*> GetResolveResources(const IFrame* frame) noexcept;
		/// @brief Gets a final attachment: a render target or a resolve.
		/// @param frame Frame.
		/// @return Final attachment.
		[[nodiscard("Pure function")]]
		static const IAttachment* GetFinalAttachment(const IFrame* frame) noexcept;

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<const IRenderObject*> renderObjects; ///< Render objects.
		std::vector<const ICamera*> cameras; ///< Cameras.
		std::vector<const IFrame*> frames; ///< Frames used this frame.
		const IFrame* mainFrame; ///< Main frame.

		std::vector<RenderObjectData> renderObjectData; ///< Render object data.
		std::vector<CameraTask> cameraTasks; ///< Camera tasks.

		std::unordered_set<const IMaterial*> materials; ///< Materials used this frame.
		std::unordered_set<const IMesh*> meshes; ///< Meshes used this frame.

		std::vector<std::reference_wrapper<const IBuffer>> buffers; ///< Buffers used this frame.
		std::vector<std::reference_wrapper<const ITexture>> textures; ///< Textures used this frame.
		std::vector<std::reference_wrapper<const IAttachment>> attachments; /// < Attachments used this frame.

		std::unordered_set<const IAttachment*> outdatedAttachments; ///< Outdated attachments.
	};
}

namespace PonyEngine::Render
{
	Pipeline::Pipeline(IRenderSystemContext& renderSystem) noexcept :
		renderSystem{&renderSystem},
		mainFrame{nullptr}
	{
	}

	void Pipeline::Submit(const IRenderObject& renderObject)
	{
		assert(std::ranges::find(renderObjects, &renderObject) == renderObjects.cend() && "The render object was submitted twice.");
		renderObjects.push_back(&renderObject);
	}

	void Pipeline::Submit(const ICamera& camera)
	{
		assert(std::ranges::find(cameras, &camera) == cameras.cend() && "The camera was submitted twice.");
		cameras.push_back(&camera);
	}

	void Pipeline::Submit(const IFrame& frame)
	{
		assert(std::ranges::find(frames, &frame) == frames.cend() && "The frame was submitted twice.");
		frames.push_back(&frame);
	}

	void Pipeline::SetMainFrame(const IFrame& mainFrame)
	{
		assert(std::ranges::find(frames, &mainFrame) != frames.cend() && "The main frame wasn't added.");
		this->mainFrame = &mainFrame;
	}

	void Pipeline::Tick()
	{
		BeginTick();
		Prepare();
		BeginRender();
		Render();
		EndRender();
		Finalize();
		EndTick();
		Clear();
	}

	void Pipeline::BeginTick()
	{
		renderSystem->RenderAgent().PipelineAgent().BeginTick();
	}

	void Pipeline::EndTick()
	{
		renderSystem->RenderAgent().PipelineAgent().EndTick();
	}

	void Pipeline::BeginRender()
	{
		renderSystem->RenderAgent().PipelineAgent().BeginRender();
	}

	void Pipeline::EndRender()
	{
		renderSystem->RenderAgent().PipelineAgent().EndRender();
	}

	void Pipeline::BeginTarget(const std::size_t cameraIndex)
	{
		const ICamera* const camera = cameras[cameraIndex];

		// TODO: Take a frame from the camera.
		const IFrame* const frame = mainFrame;

		auto [renderTarget, depthStencil] = GetTargets(frame);
		renderSystem->RenderAgent().PipelineAgent().BeginTarget(renderTarget, depthStencil);

		const PonyMath::Shape::Rect<float>& cameraViewport = camera->ViewportRect();
		const PonyMath::Utility::Resolution<std::uint32_t>& frameResolution = frame->Resolution();
		const PonyMath::Shape::Rect<float> viewportRect = PonyMath::Shape::Rect<float>(0.f, 0.f, frameResolution.Width(), frameResolution.Height()).Unnormalize(cameraViewport);
		renderSystem->RenderAgent().PipelineAgent().SetViewport(viewportRect);

		const ClearValue& clear = camera->ClearValue();
		if (renderTarget && clear.color)
		{
			renderSystem->RenderAgent().PipelineAgent().ClearColor(*renderTarget, clear.color.value(), viewportRect);
		}
		if (depthStencil && (clear.depth || clear.stencil))
		{
			if (clear.depth && clear.stencil)
			{
				renderSystem->RenderAgent().PipelineAgent().ClearDepthStencil(*depthStencil, clear.depth.value(), clear.stencil.value(), viewportRect);
			}
			else if (clear.depth)
			{
				renderSystem->RenderAgent().PipelineAgent().ClearDepthStencil(*depthStencil, clear.depth.value(), viewportRect);
			}
			else
			{
				renderSystem->RenderAgent().PipelineAgent().ClearDepthStencil(*depthStencil, clear.stencil.value(), viewportRect);
			}
		}
	}

	void Pipeline::EndTarget(const std::size_t cameraIndex)
	{
		// TODO: Take a frame from the camera.
		const IFrame* const frame = mainFrame;

		auto [renderTarget, depthStencil] = GetTargets(frame);
		renderSystem->RenderAgent().PipelineAgent().EndTarget(renderTarget, depthStencil);

		if (const std::optional<std::uint32_t> renderTargetIndex = frame->FindAttachmentIndex(AttachmentType::Resolve))
		{
			outdatedAttachments.insert(&frame->Attachment(renderTargetIndex.value()));
		}
	}

	void Pipeline::Prepare()
	{
		SortCameras();
		AllocateCameraTasks();
		UpdateCameraTasks();
		UpdateResources();
		SetResources();
		Upload();
	}

	void Pipeline::SortCameras() noexcept
	{
		std::ranges::sort(cameras, [](const ICamera* const left, const ICamera* const right)
		{
			return left->SortingOrder() < right->SortingOrder();
		});
	}

	void Pipeline::AllocateCameraTasks()
	{
		cameraTasks.reserve(cameras.size());
		for (std::size_t i = cameraTasks.size(); i < cameras.size(); ++i)
		{
			cameraTasks.emplace_back();
		}
	}

	void Pipeline::UpdateCameraTasks()
	{
		for (std::size_t cameraIndex = 0, dataIndex = 0; cameraIndex < cameras.size(); ++cameraIndex)
		{
			const ICamera& camera = *cameras[cameraIndex];
			CameraTask& cameraTask = cameraTasks[cameraIndex];
			cameraTask.renderObjectTasks.clear();

			for (std::size_t renderObjectIndex = 0; renderObjectIndex < renderObjects.size(); ++renderObjectIndex)
			{
				const IRenderObject& renderObject = *renderObjects[renderObjectIndex];

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

	bool Pipeline::Cull(const ICamera& camera, const IRenderObject& renderObject) noexcept
	{
		if (!renderObject.Material()->PipelineState()->CameraCulling())
		{
			return false;
		}
		const IMesh* const mesh = renderObject.Mesh().get();
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

	void Pipeline::AddRenderObjectData(const ICamera& camera, const IRenderObject& renderObject)
	{
		const IMaterial& material = *renderObject.Material();
		materials.insert(&material);
		const IMesh* const mesh = renderObject.Mesh().get();
		if (mesh)
		{
			meshes.insert(mesh);
		}

		const auto transform = PonyShader::Space::Transform
		{
			.model = renderObject.ModelMatrix(),
			.view = camera.ViewMatrix(),
			.projection = camera.ProjectionMatrix(),
			.mv = camera.ViewMatrix() * renderObject.ModelMatrix(),
			.vp = camera.ViewProjectionMatrix(),
			.mvp = camera.ViewProjectionMatrix() * renderObject.ModelMatrix(),
			.modelInv = renderObject.ModelInverseMatrix(),
			.viewInv = camera.ViewInverseMatrix(),
			.projectionInv = camera.ProjectionInverseMatrix(),
			.mvInv = renderObject.ModelInverseMatrix() * camera.ViewInverseMatrix(),
			.vpInv = camera.ViewProjectionInverseMatrix(),
			.mvpInv = renderObject.ModelInverseMatrix() * camera.ViewProjectionInverseMatrix()
		};
		const IPipelineState& pipelineState = *material.PipelineState();
		const ThreadGroupCounts& pipelineStateCounts = pipelineState.ThreadGroupCounts();
		const PonyShader::Core::ThreadGroupCounts meshGroups = mesh ? mesh->ThreadGroupCounts() : PonyShader::Core::ThreadGroupCounts();
		const auto context = PonyShader::Core::Context
		{
			.dispatchThreadGroupCounts = CreateDispatchThreadGroupCounts(pipelineStateCounts, meshGroups),
			.pipelineStateThreadGroupCounts = pipelineStateCounts.threadGroupCounts,
			.meshThreadGroupCounts = meshGroups,
			.renderQueue = pipelineState.RenderQueue(),
			.isTransparent = pipelineState.Blend().renderTargetBlend.index() != 0,
			.isFlipped = transform.mvp.Determinant() < 0.f
		};
		renderObjectData.push_back(RenderObjectData
		{
			.context = context,
			.transform = transform
		});
	}

	void Pipeline::UpdateResources() noexcept
	{
		for (const IMaterial* material : materials)
		{
			buffers.push_back(material->Buffer());

			for (std::uint32_t textureTypeIndex = 0u; textureTypeIndex < material->TextureTypeCount(); ++textureTypeIndex)
			{
				if (const ITexture* const texture = material->Texture(textureTypeIndex).get()) // TODO: Add default texture. Default buffers are needed as well.
				{
					if (std::ranges::find_if(textures, [&](const std::reference_wrapper<const ITexture>& t) { return &t.get() == texture; }) == textures.cend())
					{
						textures.push_back(*texture);
					}
				}
			}
		}

		for (const IMesh* mesh : meshes)
		{
			buffers.push_back(mesh->Buffer());
		}

		for (const IFrame* frame : frames)
		{
			for (std::uint32_t attachmentIndex = 0; attachmentIndex < frame->AttachmentCount(); ++attachmentIndex)
			{
				attachments.push_back(frame->Attachment(attachmentIndex));
			}
		}
	}

	void Pipeline::SetResources()
	{
		const auto data = std::array<ConstantData, DataCount>
		{
			ConstantData
			{
				.data = std::span(reinterpret_cast<const std::byte*>(renderObjectData.data()), renderObjectData.size() * sizeof(RenderObjectData)),
				.scheme = RenderObjectData::DataSizes
			}
		};
		renderSystem->RenderAgent().PipelineAgent().SetResources(data, buffers, textures, attachments);
	}

	void Pipeline::Upload()
	{
		renderSystem->RenderAgent().PipelineAgent().Upload();
	}

	void Pipeline::Render()
	{
		ClearFrames();

		for (std::size_t cameraIndex = 0; cameraIndex < cameras.size(); ++cameraIndex)
		{
			Render(cameraIndex);
		}
	}

	void Pipeline::ClearFrames()
	{
		for (const IFrame* frame : frames)
		{
			const ClearValue& clearValue = frame->ClearValue();

			if (clearValue.color)
			{
				if (const std::optional<std::uint32_t> renderTargetIndex = frame->FindAttachmentIndex(AttachmentType::RenderTarget))
				{
					const IAttachment& renderTarget = frame->Attachment(renderTargetIndex.value());
					renderSystem->RenderAgent().PipelineAgent().ClearColor(renderTarget, clearValue.color.value());

					if (const std::optional<std::uint32_t> resolveIndex = frame->FindAttachmentIndex(AttachmentType::Resolve))
					{
						outdatedAttachments.insert(&frame->Attachment(resolveIndex.value()));
					}
				}
			}
			if (clearValue.depth || clearValue.stencil)
			{
				if (const std::optional<std::uint32_t> depthStencilIndex = frame->FindAttachmentIndex(AttachmentType::DepthStencil))
				{
					const IAttachment& depthStencil = frame->Attachment(depthStencilIndex.value());

					if (clearValue.depth && clearValue.stencil)
					{
						renderSystem->RenderAgent().PipelineAgent().ClearDepthStencil(depthStencil, clearValue.depth.value(), clearValue.stencil.value());
					}
					else if (clearValue.depth)
					{
						renderSystem->RenderAgent().PipelineAgent().ClearDepthStencil(depthStencil, clearValue.depth.value());
					}
					else
					{
						renderSystem->RenderAgent().PipelineAgent().ClearDepthStencil(depthStencil, clearValue.stencil.value());
					}
				}
			}
		}
	}

	void Pipeline::Render(const std::size_t cameraIndex)
	{
		if (cameraTasks[cameraIndex].renderObjectTasks.empty())
		{
			return;
		}

		BeginTarget(cameraIndex);
		CalculateDistances(cameraIndex);
		SortRenderObjects(cameraIndex);
		RenderObjects(cameraIndex);
		EndTarget(cameraIndex);
	}

	void Pipeline::CalculateDistances(const std::size_t cameraIndex) noexcept
	{
		for (RenderObjectTask& task : cameraTasks[cameraIndex].renderObjectTasks)
		{
			task.distance = 0.f;

			const IMesh* const mesh = renderObjects[task.renderObjectIndex]->Mesh().get();
			if (!mesh)
			{
				continue;
			}
			const std::optional<PonyMath::Shape::AABB<float>>& boundingBox = mesh->BoundingBox();
			if (!boundingBox)
			{
				continue;
			}

			task.distance = PonyMath::Core::ProjectPoint(renderObjectData[task.dataIndex].transform.mvp, boundingBox.value().Center()).Z();
		}
	}

	void Pipeline::SortRenderObjects(const std::size_t cameraIndex) noexcept
	{
		std::vector<RenderObjectTask>& tasks = cameraTasks[cameraIndex].renderObjectTasks;
		std::ranges::sort(tasks, [&](const RenderObjectTask& left, const RenderObjectTask& right)
		{
			const RenderObjectData& leftData = renderObjectData[left.dataIndex];
			const RenderObjectData& rightData = renderObjectData[right.dataIndex];

			if (leftData.context.renderQueue != rightData.context.renderQueue)
			{
				return leftData.context.renderQueue < rightData.context.renderQueue;
			}

			if (leftData.context.isTransparent != rightData.context.isTransparent)
			{
				return leftData.context.isTransparent < rightData.context.isTransparent;
			}

			const IRenderObject& leftRenderObject = *renderObjects[left.renderObjectIndex];
			const IRenderObject& rightRenderObject = *renderObjects[right.renderObjectIndex];

			const IMesh* const leftMesh = leftRenderObject.Mesh().get();
			const IMesh* const rightMesh = rightRenderObject.Mesh().get();

			if (!leftMesh || !rightMesh)
			{
				return rightMesh == nullptr;
			}
			if (!leftMesh->BoundingBox() || !rightMesh->BoundingBox())
			{
				return !rightMesh->BoundingBox().has_value();
			}

			return leftData.context.isTransparent
				? left.distance > right.distance
				: left.distance < right.distance;
		});

		// TODO: Add grouping. But it needs a bin size.
	}

	void Pipeline::RenderObjects(const std::size_t cameraIndex)
	{
		for (const RenderObjectTask& renderObjectTask : cameraTasks[cameraIndex].renderObjectTasks)
		{
			const IRenderObject& renderObject = *renderObjects[renderObjectTask.renderObjectIndex];
			const IMesh* const mesh = renderObject.Mesh().get();
			const IMaterial& material = *renderObject.Material();
			const IPipelineState& pipelineState = *material.PipelineState();
			const IRootSignature& rootSignature = *pipelineState.RootSignature();

			renderSystem->RenderAgent().PipelineAgent().SetPipelineState(pipelineState);

			for (std::uint32_t i = 0; i < rootSignature.SlotCount(); ++i) // TODO: Bind defaults if not found.
			{
				const std::string_view slotName = rootSignature.SlotName(i);

				// TODO: Add slot info to root signature.
				if (slotName == DataTypes::Data)
				{
					renderSystem->RenderAgent().PipelineAgent().BindData(renderObjectData.data(), 
						static_cast<std::uint32_t>(renderObjectTask.dataIndex), i);
					continue;
				}
				if (slotName == DataTypes::Context)
				{
					renderSystem->RenderAgent().PipelineAgent().BindData(renderObjectData.data(), 
						static_cast<std::uint32_t>(renderObjectTask.dataIndex) + RenderObjectData::ContextIndex, i);
					continue;
				}
				if (slotName == DataTypes::Transform)
				{
					renderSystem->RenderAgent().PipelineAgent().BindData(renderObjectData.data(),
						static_cast<std::uint32_t>(renderObjectTask.dataIndex) + RenderObjectData::TransformIndex, i);
					continue;
				}

				if (const std::optional<std::uint32_t> typeIndex = material.FindDataTypeIndex(slotName))
				{
					renderSystem->RenderAgent().PipelineAgent().BindBuffer(material.Buffer(), typeIndex.value(), i);
					continue;
				}
				if (const std::optional<std::uint32_t> typeIndex = material.FindTextureTypeIndex(slotName))
				{
					renderSystem->RenderAgent().PipelineAgent().BindTexture(*material.Texture(typeIndex.value()), i); // TODO: Check for nullptr or default texture.
					continue;
				}

				if (mesh)
				{
					if (const std::optional<std::uint32_t> typeIndex = mesh->FindDataTypeIndex(slotName))
					{
						renderSystem->RenderAgent().PipelineAgent().BindBuffer(mesh->Buffer(), typeIndex.value(), i);
						continue;
					}
				}
			}

			const auto groupCounts = renderObjectData[renderObjectTask.dataIndex].context.dispatchThreadGroupCounts;
			renderSystem->RenderAgent().PipelineAgent().Dispatch(groupCounts.ThreadGroupCountX(), groupCounts.ThreadGroupCountY(), groupCounts.ThreadGroupCountZ());
		}
	}

	void Pipeline::Finalize()
	{
		Resolve(mainFrame);
		Output(mainFrame);
	}

	void Pipeline::Resolve(const IFrame* frame)
	{
		auto [source, destination] = GetResolveResources(frame);
		if (!source || !destination)
		{
			return;
		}

		if (outdatedAttachments.contains(destination))
		{
			renderSystem->RenderAgent().PipelineAgent().Resolve(*source, *destination);
			outdatedAttachments.erase(destination);
		}
	}

	void Pipeline::Output(const IFrame* frame)
	{
		const IAttachment* const finalAttachment = GetFinalAttachment(frame);
		if (!finalAttachment)
		{
			return;
		}

		renderSystem->RenderAgent().PipelineAgent().Output(*finalAttachment);
	}

	void Pipeline::Clear() noexcept
	{
		renderObjects.clear();
		cameras.clear();
		mainFrame = nullptr;

		renderObjectData.clear();
		for (CameraTask& cameraTask : cameraTasks)
		{
			cameraTask.renderObjectTasks.clear();
		}

		materials.clear();
		meshes.clear();
		frames.clear();

		outdatedAttachments.clear();

		buffers.clear();
		textures.clear();
		attachments.clear();

		renderSystem->RenderAgent().PipelineAgent().Clear();
	}

	std::tuple<const IAttachment*, const IAttachment*> Pipeline::GetTargets(const IFrame* const frame) noexcept
	{
		const std::optional<std::uint32_t> renderTargetIndex = frame->FindAttachmentIndex(AttachmentType::RenderTarget);
		const IAttachment* const renderTarget = renderTargetIndex ? &frame->Attachment(renderTargetIndex.value()) : nullptr;
		const std::optional<std::uint32_t> depthStencilIndex = frame->FindAttachmentIndex(AttachmentType::DepthStencil);
		const IAttachment* const depthStencil = depthStencilIndex ? &frame->Attachment(depthStencilIndex.value()) : nullptr;

		return std::tuple(renderTarget, depthStencil);
	}

	std::pair<const IAttachment*, const IAttachment*> Pipeline::GetResolveResources(const IFrame* frame) noexcept
	{
		const std::optional<std::uint32_t> renderTargetIndex = frame->FindAttachmentIndex(AttachmentType::RenderTarget);
		const IAttachment* const renderTarget = renderTargetIndex ? &frame->Attachment(renderTargetIndex.value()) : nullptr;
		const std::optional<std::uint32_t> resolveIndex = frame->FindAttachmentIndex(AttachmentType::Resolve);
		const IAttachment* const resolve = resolveIndex ? &frame->Attachment(resolveIndex.value()) : nullptr;

		return std::pair(renderTarget, resolve);
	}

	const IAttachment* Pipeline::GetFinalAttachment(const IFrame* frame) noexcept
	{
		if (const std::optional<std::uint32_t> resolveIndex = frame->FindAttachmentIndex(AttachmentType::Resolve))
		{
			return &frame->Attachment(resolveIndex.value());
		}

		if (const std::optional<std::uint32_t> renderTargetIndex = frame->FindAttachmentIndex(AttachmentType::RenderTarget))
		{
			return &frame->Attachment(renderTargetIndex.value());
		}

		return nullptr;
	}
}

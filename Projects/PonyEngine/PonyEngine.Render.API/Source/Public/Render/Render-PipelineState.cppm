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

export module PonyEngine.Render:PipelineState;

import <algorithm>;
import <cstdint>;
import <optional>;
import <string>;
import <string_view>;
import <unordered_map>;
import <utility>;
import <vector>;

import :Blend;
import :DepthStencil;
import :IPipelineStateObserver;
import :PipelineStateParams;
import :Rasterizer;
import :ThreadGroupCounts;

export namespace PonyEngine::Render
{
	/// @brief Graphics pipeline state.
	class PipelineState final
	{
	public:
		/// @brief Creates an empty pipeline state.
		[[nodiscard("Pure constructor")]]
		PipelineState() noexcept = default;
		/// @brief Creates a pipeline state.
		/// @param params Pipeline state parameters.
		[[nodiscard("Pure constructor")]]
		explicit PipelineState(const PipelineStateParams& params);
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		PipelineState(const PipelineState& other);
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		PipelineState(PipelineState&& other) noexcept;

		~PipelineState() noexcept = default;

		/// @brief Gets the root signature shader.
		/// @return Root signature shader. Relative path to a shader file without extension.
		[[nodiscard("Pure function")]]
		std::string_view RootSignatureShader() const noexcept;
		/// @brief Sets the root signature shader.
		/// @param shader Root signature shader. Relative path to a shader file without extension.
		void RootSignatureShader(std::string_view shader);
		/// @brief Gets the amplification shader.
		/// @return Amplification shader. Relative path to a shader file without extension.
		[[nodiscard("Pure function")]]
		std::string_view AmplificationShader() const noexcept;
		/// @brief Sets the amplification shader.
		/// @param shader Amplification shader. Relative path to a shader file without extension.
		void AmplificationShader(std::string_view shader);
		/// @brief Gets the mesh shader.
		/// @return Mesh shader. Relative path to a shader file without extension.
		[[nodiscard("Pure function")]]
		std::string_view MeshShader() const noexcept;
		/// @brief Sets the mesh shader.
		/// @param shader Mesh shader. Relative path to a shader file without extension.
		void MeshShader(std::string_view shader);
		/// @brief Gets the pixel shader.
		/// @return Pixel shader. Relative path to a shader file without extension.
		[[nodiscard("Pure function")]]
		std::string_view PixelShader() const noexcept;
		/// @brief Sets the pixel shader.
		/// @param shader Pixel shader. Relative path to a shader file without extension.
		void PixelShader(std::string_view shader);

		/// @brief Gets the blend parameters.
		/// @return Blend parameters.
		[[nodiscard("Pure function")]]
		const struct Blend& Blend() const noexcept;
		/// @brief Sets the blend parameters.
		/// @param blend Blend parameters.
		void Blend(const struct Blend& blend) noexcept;
		/// @brief Gets the rasterizer parameters.
		/// @return Rasterizer parameters.
		[[nodiscard("Pure function")]]
		const struct Rasterizer& Rasterizer() const noexcept;
		/// @brief Sets the rasterizer parameters.
		/// @param rasterizer Rasterizer parameters.
		void Rasterizer(const struct Rasterizer& rasterizer) noexcept;
		/// @brief Gets the depth stencil parameters.
		/// @return Depth stencil parameters.
		[[nodiscard("Pure function")]]
		const struct DepthStencil& DepthStencil() const noexcept;
		/// @brief Sets the depth stencil parameters.
		/// @param depthStencil Depth stencil parameters.
		void DepthStencil(const struct DepthStencil& depthStencil) noexcept;

		/// @brief Tries to find a data slot by the @p dataType type.
		/// @param dataType Data type.
		/// @return Data slot; std::nullopt if the @p dataType isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataSlot(std::string_view dataType) const noexcept;
		/// @brief Maps the @p dataType to the @p dataSlot.
		/// @param dataType Data type.
		/// @param dataSlot Data slot.
		void DataSlot(std::string_view dataType, std::uint32_t dataSlot);
		/// @brief Gets the data slots.
		/// @return Data slots.
		[[nodiscard("Pure function")]]
		const std::unordered_map<std::string, std::uint32_t>& DataSlots() const noexcept;
		/// @brief Sets the data slots.
		/// @param data Data slots.
		void DataSlots(const std::unordered_map<std::string, std::uint32_t>& data);

		/// @brief Gets the thread group counts.
		/// @return Thread group counts.
		[[nodiscard("Pure function")]]
		const struct ThreadGroupCounts& ThreadGroupCounts() const noexcept;
		/// @brief Sets the thread group counts.
		/// @param threadGroupCounts Thread group counts to set.
		void ThreadGroupCounts(const struct ThreadGroupCounts& threadGroupCounts) noexcept;

		/// @brief Gets the render queue.
		/// @return Render queue.
		[[nodiscard("Pure function")]]
		std::int32_t RenderQueue() const noexcept;
		/// @brief Sets the render queue.
		/// @param renderQueue Render queue to set.
		void RenderQueue(std::int32_t renderQueue) noexcept;

		/// @brief Gets the camera culling.
		/// @return Camera culling.
		[[nodiscard("Pure function")]]
		bool CameraCulling() const noexcept;
		/// @brief Sets the camera culling.
		/// @param culling Camera culling to set.
		void CameraCulling(bool culling) noexcept;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		/// @brief Adds a pipeline state observer.
		/// @param observer Pipeline state observer to add. It must be unique. It must live longer than the pipeline state.
		void AddObserver(IPipelineStateObserver& observer) const;
		/// @brief Removes a pipeline state observer.
		/// @param observer Pipeline state observer to remove.
		void RemoveObserver(IPipelineStateObserver& observer) const noexcept;

		PipelineState& operator =(const PipelineState& other);
		PipelineState& operator =(PipelineState&& other) noexcept;

	private:
		/// @brief Calls @p OnRootSignatureShaderChanged() on each observer.
		void OnRootSignatureShaderChanged() const noexcept;
		/// @brief Calls @p OnAmplificationShaderChanged() on each observer.
		void OnAmplificationShaderChanged() const noexcept;
		/// @brief Calls @p OnMeshShaderChanged() on each observer.
		void OnMeshShaderChanged() const noexcept;
		/// @brief Calls @p OnPixelShaderChanged() on each observer.
		void OnPixelShaderChanged() const noexcept;

		/// @brief Calls @p OnBlendChanged() on each observer.
		void OnBlendChanged() const noexcept;
		/// @brief Calls @p OnRasterizerChanged() on each observer.
		void OnRasterizerChanged() const noexcept;
		/// @brief Calls @p OnDepthStencilChanged() on each observer.
		void OnDepthStencilChanged() const noexcept;

		/// @brief Calls @p OnDataSlotsChanged() on each observer.
		void OnDataSlotsChanged() const noexcept;

		/// @brief Calls @p OnThreadGroupCountsChanged() on each observer.
		void OnThreadGroupCountsChanged() const noexcept;
		/// @brief Calls @p OnRenderQueueChanged() on each observer.
		void OnRenderQueueChanged() const noexcept;
		/// @brief Calls @p OnCameraCullingChanged() on each observer.
		void OnCameraCullingChanged() const noexcept;

		/// @brief Calls @p OnNameChanged() on each observer.
		void OnNameChanged() const noexcept;

		std::string rootSignatureShader; ///< Root signature shader path.
		std::string amplificationShader; ///< Amplification shader path.
		std::string meshShader; ///< Mesh shader path.
		std::string pixelShader; ///< Pixel shader path.

		struct Blend blend; ///< Blend parameters.
		struct Rasterizer rasterizer; ///< Rasterizer parameters.
		struct DepthStencil depthStencil; ///< Depth stencil parameters.

		std::unordered_map<std::string, std::uint32_t> dataSlots; ///< Data slots mapping.

		struct ThreadGroupCounts threadGroupCounts; ///< Thread group counts.
		std::int32_t renderQueue; ///< Render queue.
		bool cameraCulling; ///< Is camera culling enabled?

		std::string name; ///< Name.

		mutable std::vector<IPipelineStateObserver*> pipelineStateObservers; ///< Observers.
	};
}

namespace PonyEngine::Render
{
	PipelineState::PipelineState(const PipelineStateParams& params) :
		rootSignatureShader(params.rootSignatureShader),
		amplificationShader(params.amplificationShader),
		meshShader(params.meshShader),
		pixelShader(params.pixelShader),
		blend(params.blend),
		rasterizer(params.rasterizer),
		depthStencil(params.depthStencil),
		dataSlots(params.dataSlots),
		threadGroupCounts(params.threadGroupCounts),
		renderQueue{params.renderQueue},
		cameraCulling{params.cameraCulling},
		name(params.name)
	{
	}

	PipelineState::PipelineState(const PipelineState& other) :
		rootSignatureShader(other.rootSignatureShader),
		amplificationShader(other.amplificationShader),
		meshShader(other.meshShader),
		pixelShader(other.pixelShader),
		blend(other.blend),
		rasterizer(other.rasterizer),
		depthStencil(other.depthStencil),
		dataSlots(other.dataSlots),
		threadGroupCounts(other.threadGroupCounts),
		renderQueue{other.renderQueue},
		cameraCulling{other.cameraCulling},
		name(other.name)
	{
	}

	PipelineState::PipelineState(PipelineState&& other) noexcept :
		rootSignatureShader(std::move(other.rootSignatureShader)),
		amplificationShader(std::move(other.amplificationShader)),
		meshShader(std::move(other.meshShader)),
		pixelShader(std::move(other.pixelShader)),
		blend(std::move(other.blend)),
		rasterizer(std::move(other.rasterizer)),
		depthStencil(std::move(other.depthStencil)),
		dataSlots(std::move(other.dataSlots)),
		threadGroupCounts(std::move(other.threadGroupCounts)),
		renderQueue{other.renderQueue},
		cameraCulling{other.cameraCulling},
		name(std::move(other.name))
	{
	}

	std::string_view PipelineState::RootSignatureShader() const noexcept
	{
		return rootSignatureShader;
	}

	void PipelineState::RootSignatureShader(const std::string_view shader)
	{
		if (rootSignatureShader == shader)
		{
			return;
		}

		rootSignatureShader = shader;
		OnRootSignatureShaderChanged();
	}

	std::string_view PipelineState::AmplificationShader() const noexcept
	{
		return amplificationShader;
	}

	void PipelineState::AmplificationShader(const std::string_view shader)
	{
		if (amplificationShader == shader)
		{
			return;
		}

		amplificationShader = shader;
		OnAmplificationShaderChanged();
	}

	std::string_view PipelineState::MeshShader() const noexcept
	{
		return meshShader;
	}

	void PipelineState::MeshShader(const std::string_view shader)
	{
		if (meshShader == shader)
		{
			return;
		}

		meshShader = shader;
		OnMeshShaderChanged();
	}

	std::string_view PipelineState::PixelShader() const noexcept
	{
		return pixelShader;
	}

	void PipelineState::PixelShader(const std::string_view shader)
	{
		if (pixelShader == shader)
		{
			return;
		}

		pixelShader = shader;
		OnPixelShaderChanged();
	}

	const struct Blend& PipelineState::Blend() const noexcept
	{
		return blend;
	}

	void PipelineState::Blend(const struct Blend& blend) noexcept
	{
		if (this->blend == blend)
		{
			return;
		}

		this->blend = blend;
		OnBlendChanged();
	}

	const struct Rasterizer& PipelineState::Rasterizer() const noexcept
	{
		return rasterizer;
	}

	void PipelineState::Rasterizer(const struct Rasterizer& rasterizer) noexcept
	{
		if (this->rasterizer == rasterizer)
		{
			return;
		}

		this->rasterizer = rasterizer;
		OnRasterizerChanged();
	}

	const struct DepthStencil& PipelineState::DepthStencil() const noexcept
	{
		return depthStencil;
	}

	void PipelineState::DepthStencil(const struct DepthStencil& depthStencil) noexcept
	{
		if (this->depthStencil == depthStencil)
		{
			return;
		}

		this->depthStencil = depthStencil;
		OnDepthStencilChanged();
	}

	std::optional<std::uint32_t> PipelineState::DataSlot(const std::string_view dataType) const noexcept
	{
		for (const auto& [type, slot] : dataSlots)
		{
			if (type == dataType)
			{
				return slot;
			}
		}

		return std::nullopt;
	}

	void PipelineState::DataSlot(const std::string_view dataType, const std::uint32_t dataSlot)
	{
		for (const auto& [type, slot] : dataSlots)
		{
			if (type == dataType)
			{
				if (slot != dataSlot)
				{
					dataSlots[type] = dataSlot;
					OnRootSignatureShaderChanged();
				}

				return;
			}
		}

		dataSlots[std::string(dataType)] = dataSlot;
		OnDataSlotsChanged();
	}

	const std::unordered_map<std::string, std::uint32_t>& PipelineState::DataSlots() const noexcept
	{
		return dataSlots;
	}

	void PipelineState::DataSlots(const std::unordered_map<std::string, std::uint32_t>& data)
	{
		if (dataSlots == data)
		{
			return;
		}

		dataSlots = data;
		OnDataSlotsChanged();
	}

	const struct ThreadGroupCounts& PipelineState::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void PipelineState::ThreadGroupCounts(const struct ThreadGroupCounts& threadGroupCounts) noexcept
	{
		if (this->threadGroupCounts == threadGroupCounts)
		{
			return;
		}

		this->threadGroupCounts = threadGroupCounts;
		OnThreadGroupCountsChanged();
	}

	std::int32_t PipelineState::RenderQueue() const noexcept
	{
		return renderQueue;
	}

	void PipelineState::RenderQueue(const std::int32_t renderQueue) noexcept
	{
		if (this->renderQueue == renderQueue)
		{
			return;
		}

		this->renderQueue = renderQueue;
		OnRenderQueueChanged();
	}

	bool PipelineState::CameraCulling() const noexcept
	{
		return cameraCulling;
	}

	void PipelineState::CameraCulling(const bool culling) noexcept
	{
		if (cameraCulling == culling)
		{
			return;
		}

		cameraCulling = culling;
		OnCameraCullingChanged();
	}

	std::string_view PipelineState::Name() const noexcept
	{
		return name;
	}

	void PipelineState::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
		OnNameChanged();
	}

	void PipelineState::AddObserver(IPipelineStateObserver& observer) const
	{
		assert(std::ranges::find(pipelineStateObservers, &observer) == pipelineStateObservers.cend() && "The pipeline state observer is already added.");
		pipelineStateObservers.push_back(&observer);
	}

	void PipelineState::RemoveObserver(IPipelineStateObserver& observer) const noexcept
	{
		if (const auto position = std::ranges::find(pipelineStateObservers, &observer); position != pipelineStateObservers.cend()) [[likely]]
		{
			pipelineStateObservers.erase(position);
		}
	}

	void PipelineState::OnRootSignatureShaderChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnRootSignatureShaderChanged();
		}
	}

	void PipelineState::OnAmplificationShaderChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnAmplificationShaderChanged();
		}
	}

	void PipelineState::OnMeshShaderChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnMeshShaderChanged();
		}
	}

	void PipelineState::OnPixelShaderChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnPixelShaderChanged();
		}
	}

	void PipelineState::OnBlendChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnBlendChanged();
		}
	}

	void PipelineState::OnRasterizerChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnRasterizerChanged();
		}
	}

	void PipelineState::OnDepthStencilChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnDepthStencilChanged();
		}
	}

	void PipelineState::OnDataSlotsChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnDataSlotsChanged();
		}
	}

	void PipelineState::OnThreadGroupCountsChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnThreadGroupCountsChanged();
		}
	}

	void PipelineState::OnRenderQueueChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnRenderQueueChanged();
		}
	}

	void PipelineState::OnCameraCullingChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnCameraCullingChanged();
		}
	}

	void PipelineState::OnNameChanged() const noexcept
	{
		for (IPipelineStateObserver* const observer : pipelineStateObservers)
		{
			observer->OnNameChanged();
		}
	}

	PipelineState& PipelineState::operator =(const PipelineState& other)
	{
		std::optional<std::string> newRootSig = rootSignatureShader == other.rootSignatureShader ? std::nullopt : std::optional(other.rootSignatureShader);
		std::optional<std::string> newAmplificationShader = amplificationShader == other.amplificationShader ? std::nullopt : std::optional(other.amplificationShader);
		std::optional<std::string> newMeshShader = meshShader == other.meshShader ? std::nullopt : std::optional(other.meshShader);
		std::optional<std::string> newPixelShader = pixelShader == other.pixelShader ? std::nullopt : std::optional(other.pixelShader);
		std::optional<std::unordered_map<std::string, std::uint32_t>> newDataSlots = dataSlots == other.dataSlots ? std::nullopt : std::optional(other.dataSlots);
		std::optional<std::string> newName = name == other.name ? std::nullopt : std::optional(other.name);

		if (newRootSig)
		{
			rootSignatureShader = std::move(newRootSig.value());
			OnRootSignatureShaderChanged();
		}
		if (newAmplificationShader)
		{
			amplificationShader = std::move(newAmplificationShader.value());
			OnAmplificationShaderChanged();
		}
		if (newMeshShader)
		{
			meshShader = std::move(newMeshShader.value());
			OnMeshShaderChanged();
		}
		if (newPixelShader)
		{
			pixelShader = std::move(newPixelShader.value());
			OnPixelShaderChanged();
		}
		Blend(other.blend);
		Rasterizer(other.rasterizer);
		DepthStencil(other.depthStencil);

		if (newDataSlots)
		{
			dataSlots = std::move(newDataSlots.value());
			OnDataSlotsChanged();
		}

		ThreadGroupCounts(other.threadGroupCounts);
		RenderQueue(other.renderQueue);
		CameraCulling(other.cameraCulling);

		if (newName)
		{
			name = std::move(newName.value());
			OnNameChanged();
		}

		return *this;
	}

	PipelineState& PipelineState::operator =(PipelineState&& other) noexcept
	{
		RootSignatureShader(std::move(other.rootSignatureShader));
		AmplificationShader(std::move(other.amplificationShader));
		MeshShader(std::move(other.meshShader));
		PixelShader(std::move(other.pixelShader));
		Blend(std::move(other.blend));
		Rasterizer(std::move(other.rasterizer));
		DepthStencil(std::move(other.depthStencil));

		DataSlots(std::move(other.dataSlots));

		ThreadGroupCounts(std::move(other.threadGroupCounts));
		RenderQueue(other.renderQueue);
		CameraCulling(other.cameraCulling);

		Name(std::move(other.name));

		return *this;
	}
}

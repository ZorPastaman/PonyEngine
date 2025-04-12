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

export module PonyEngine.Render:Material;

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
import :IMaterialObserver;
import :MaterialParams;
import :Rasterizer;
import :ThreadGroupCounts;

export namespace PonyEngine::Render
{
	/// @brief Render material.
	class Material final
	{
	public:
		/// @brief Creates an empty material.
		[[nodiscard("Pure constructor")]]
		Material() noexcept = default;
		/// @brief Creates a material.
		/// @param params Material parameters.
		[[nodiscard("Pure constructor")]]
		explicit Material(const MaterialParams& params);
		/// @brief Creates a material.
		/// @param params Material parameters.
		[[nodiscard("Pure constructor")]]
		explicit Material(MaterialParams&& params);
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		Material(const Material& other);
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		Material(Material&& other) noexcept;

		~Material() noexcept = default;

		/// @brief Gets the root signature shader.
		/// @return Root signature shader. Relative path to a shader file without extension.
		[[nodiscard("Pure function")]]
		std::string_view RootSignatureShader() const noexcept;
		/// @brief Sets the root signature shader.
		/// @param shader Root signature shader. Relative path to a shader file without extension.
		void RootSignatureShader(std::string_view shader);
		/// @brief Sets the root signature shader.
		/// @param shader Root signature shader. Relative path to a shader file without extension.
		void RootSignatureShader(std::string&& shader);
		/// @brief Gets the amplification shader.
		/// @return Amplification shader. Relative path to a shader file without extension.
		[[nodiscard("Pure function")]]
		std::string_view AmplificationShader() const noexcept;
		/// @brief Sets the amplification shader.
		/// @param shader Amplification shader. Relative path to a shader file without extension.
		void AmplificationShader(std::string_view shader);
		/// @brief Sets the amplification shader.
		/// @param shader Amplification shader. Relative path to a shader file without extension.
		void AmplificationShader(std::string&& shader);
		/// @brief Gets the mesh shader.
		/// @return Mesh shader. Relative path to a shader file without extension.
		[[nodiscard("Pure function")]]
		std::string_view MeshShader() const noexcept;
		/// @brief Sets the mesh shader.
		/// @param shader Mesh shader. Relative path to a shader file without extension.
		void MeshShader(std::string_view shader);
		/// @brief Sets the mesh shader.
		/// @param shader Mesh shader. Relative path to a shader file without extension.
		void MeshShader(std::string&& shader);
		/// @brief Gets the pixel shader.
		/// @return Pixel shader. Relative path to a shader file without extension.
		[[nodiscard("Pure function")]]
		std::string_view PixelShader() const noexcept;
		/// @brief Sets the pixel shader.
		/// @param shader Pixel shader. Relative path to a shader file without extension.
		void PixelShader(std::string_view shader);
		/// @brief Sets the pixel shader.
		/// @param shader Pixel shader. Relative path to a shader file without extension.
		void PixelShader(std::string&& shader);

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
		/// @brief Sets the data slots.
		/// @param data Data slots.
		void DataSlots(std::unordered_map<std::string, std::uint32_t>&& data);

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
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string&& name);

		/// @brief Adds a material observer.
		/// @param observer Material observer to add. It must be unique. It must live longer than the material.
		void AddObserver(IMaterialObserver& observer) const;
		/// @brief Removes a material observer.
		/// @param observer Material observer to remove.
		void RemoveObserver(IMaterialObserver& observer) const noexcept;

		Material& operator =(const Material& other);
		Material& operator =(Material&& other) noexcept;

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

		mutable std::vector<IMaterialObserver*> materialObservers; ///< Observers.
	};
}

namespace PonyEngine::Render
{
	Material::Material(const MaterialParams& params) :
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

	Material::Material(MaterialParams&& params) :
		rootSignatureShader(std::move(params.rootSignatureShader)),
		amplificationShader(std::move(params.amplificationShader)),
		meshShader(std::move(params.meshShader)),
		pixelShader(std::move(params.pixelShader)),
		blend(std::move(params.blend)),
		rasterizer(std::move(params.rasterizer)),
		depthStencil(std::move(params.depthStencil)),
		dataSlots(std::move(params.dataSlots)),
		threadGroupCounts(std::move(params.threadGroupCounts)),
		renderQueue{params.renderQueue},
		cameraCulling{params.cameraCulling},
		name(std::move(params.name))
	{
	}

	Material::Material(const Material& other) :
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

	Material::Material(Material&& other) noexcept :
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

	std::string_view Material::RootSignatureShader() const noexcept
	{
		return rootSignatureShader;
	}

	void Material::RootSignatureShader(const std::string_view shader)
	{
		if (rootSignatureShader == shader)
		{
			return;
		}

		rootSignatureShader = shader;
		OnRootSignatureShaderChanged();
	}

	void Material::RootSignatureShader(std::string&& shader)
	{
		if (rootSignatureShader == shader)
		{
			return;
		}

		rootSignatureShader = std::move(shader);
		OnRootSignatureShaderChanged();
	}

	std::string_view Material::AmplificationShader() const noexcept
	{
		return amplificationShader;
	}

	void Material::AmplificationShader(const std::string_view shader)
	{
		if (amplificationShader == shader)
		{
			return;
		}

		amplificationShader = shader;
		OnAmplificationShaderChanged();
	}

	void Material::AmplificationShader(std::string&& shader)
	{
		if (amplificationShader == shader)
		{
			return;
		}

		amplificationShader = std::move(shader);
		OnAmplificationShaderChanged();
	}

	std::string_view Material::MeshShader() const noexcept
	{
		return meshShader;
	}

	void Material::MeshShader(const std::string_view shader)
	{
		if (meshShader == shader)
		{
			return;
		}

		meshShader = shader;
		OnMeshShaderChanged();
	}

	void Material::MeshShader(std::string&& shader)
	{
		if (meshShader == shader)
		{
			return;
		}

		meshShader = std::move(shader);
		OnMeshShaderChanged();
	}

	std::string_view Material::PixelShader() const noexcept
	{
		return pixelShader;
	}

	void Material::PixelShader(const std::string_view shader)
	{
		if (pixelShader == shader)
		{
			return;
		}

		pixelShader = shader;
		OnPixelShaderChanged();
	}

	void Material::PixelShader(std::string&& shader)
	{
		if (pixelShader == shader)
		{
			return;
		}

		pixelShader = std::move(shader);
		OnPixelShaderChanged();
	}

	const struct Blend& Material::Blend() const noexcept
	{
		return blend;
	}

	void Material::Blend(const struct Blend& blend) noexcept
	{
		if (this->blend == blend)
		{
			return;
		}

		this->blend = blend;
		OnBlendChanged();
	}

	const struct Rasterizer& Material::Rasterizer() const noexcept
	{
		return rasterizer;
	}

	void Material::Rasterizer(const struct Rasterizer& rasterizer) noexcept
	{
		if (this->rasterizer == rasterizer)
		{
			return;
		}

		this->rasterizer = rasterizer;
		OnRasterizerChanged();
	}

	const struct DepthStencil& Material::DepthStencil() const noexcept
	{
		return depthStencil;
	}

	void Material::DepthStencil(const struct DepthStencil& depthStencil) noexcept
	{
		if (this->depthStencil == depthStencil)
		{
			return;
		}

		this->depthStencil = depthStencil;
		OnDepthStencilChanged();
	}

	std::optional<std::uint32_t> Material::DataSlot(const std::string_view dataType) const noexcept
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

	void Material::DataSlot(const std::string_view dataType, const std::uint32_t dataSlot)
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

	const std::unordered_map<std::string, std::uint32_t>& Material::DataSlots() const noexcept
	{
		return dataSlots;
	}

	void Material::DataSlots(const std::unordered_map<std::string, std::uint32_t>& data)
	{
		if (dataSlots == data)
		{
			return;
		}

		dataSlots = data;
		OnDataSlotsChanged();
	}

	void Material::DataSlots(std::unordered_map<std::string, std::uint32_t>&& data)
	{
		if (dataSlots == data)
		{
			return;
		}

		dataSlots = std::move(data);
		OnDataSlotsChanged();
	}

	const struct ThreadGroupCounts& Material::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Material::ThreadGroupCounts(const struct ThreadGroupCounts& threadGroupCounts) noexcept
	{
		if (this->threadGroupCounts == threadGroupCounts)
		{
			return;
		}

		this->threadGroupCounts = threadGroupCounts;
		OnThreadGroupCountsChanged();
	}

	std::int32_t Material::RenderQueue() const noexcept
	{
		return renderQueue;
	}

	void Material::RenderQueue(const std::int32_t renderQueue) noexcept
	{
		if (this->renderQueue == renderQueue)
		{
			return;
		}

		this->renderQueue = renderQueue;
		OnRenderQueueChanged();
	}

	bool Material::CameraCulling() const noexcept
	{
		return cameraCulling;
	}

	void Material::CameraCulling(const bool culling) noexcept
	{
		if (cameraCulling == culling)
		{
			return;
		}

		cameraCulling = culling;
		OnCameraCullingChanged();
	}

	std::string_view Material::Name() const noexcept
	{
		return name;
	}

	void Material::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
		OnNameChanged();
	}

	void Material::Name(std::string&& name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = std::move(name);
		OnNameChanged();
	}

	void Material::AddObserver(IMaterialObserver& observer) const
	{
		assert(std::ranges::find(materialObservers, &observer) == materialObservers.cend() && "The material observer is already added.");
		materialObservers.push_back(&observer);
	}

	void Material::RemoveObserver(IMaterialObserver& observer) const noexcept
	{
		if (const auto position = std::ranges::find(materialObservers, &observer); position != materialObservers.cend()) [[likely]]
		{
			materialObservers.erase(position);
		}
	}

	void Material::OnRootSignatureShaderChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnRootSignatureShaderChanged();
		}
	}

	void Material::OnAmplificationShaderChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnAmplificationShaderChanged();
		}
	}

	void Material::OnMeshShaderChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnMeshShaderChanged();
		}
	}

	void Material::OnPixelShaderChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnPixelShaderChanged();
		}
	}

	void Material::OnBlendChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnBlendChanged();
		}
	}

	void Material::OnRasterizerChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnRasterizerChanged();
		}
	}

	void Material::OnDepthStencilChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnDepthStencilChanged();
		}
	}

	void Material::OnDataSlotsChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnDataSlotsChanged();
		}
	}

	void Material::OnThreadGroupCountsChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnThreadGroupCountsChanged();
		}
	}

	void Material::OnRenderQueueChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnRenderQueueChanged();
		}
	}

	void Material::OnCameraCullingChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnCameraCullingChanged();
		}
	}

	void Material::OnNameChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnNameChanged();
		}
	}

	Material& Material::operator =(const Material& other)
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

	Material& Material::operator =(Material&& other) noexcept
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

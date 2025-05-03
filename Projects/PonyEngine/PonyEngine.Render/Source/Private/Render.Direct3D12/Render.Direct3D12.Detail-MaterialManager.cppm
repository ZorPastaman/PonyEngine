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

export module PonyEngine.Render.Direct3D12.Detail:MaterialManager;

import <memory>;
import <set>;
import <utility>;
import <vector>;

import PonyEngine.Render;

import :Buffer;
import :FormatUtility;
import :IMaterialManager;
import :IResourceManager;
import :ISubSystemContext;
import :ITextureManager;
import :Material;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 material manager.
	class MaterialManager final : public IMaterialManager
	{
	public:
		/// @brief Creates a material manager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit MaterialManager(ISubSystemContext& d3d12System) noexcept;
		MaterialManager(const MaterialManager&) = delete;
		MaterialManager(MaterialManager&&) = delete;

		~MaterialManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Material> CreateMaterial(const std::shared_ptr<const Render::Material>& material) override;

		/// @brief Ticks the material manager.
		void Tick();

		/// @brief Cleans out of dead materials.
		void Clean() noexcept;

		MaterialManager& operator =(const MaterialManager&) = delete;
		MaterialManager& operator =(MaterialManager&&) = delete;

	private:
		/// @brief Material observer.
		class MaterialObserver final : public IMaterialObserver
		{
		public:
			/// @brief Creates a material observer with all fields true.
			[[nodiscard("Pure constructor")]]
			MaterialObserver() noexcept;
			MaterialObserver(const MaterialObserver&) = delete;
			MaterialObserver(MaterialObserver&&) = delete;

			virtual void OnPipelineStateChanged() noexcept override;
			virtual void OnDataChanged() noexcept override;
			virtual void OnDataChanged(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) noexcept override;
			virtual void OnTextureChanged() noexcept override;
			virtual void OnTextureChanged(std::uint32_t textureTypeIndex, std::uint32_t textureIndex) noexcept override;
			virtual void OnNameChanged() noexcept override;

			/// @brief Gets the changed data.
			/// @return Changed data. It's empty if the @p DataChanged() is @a true.
			[[nodiscard("Pure function")]]
			const std::set<std::pair<std::uint32_t, std::uint32_t>>& ChangedData() const noexcept;
			/// @brief Gets the changed textures.
			/// @return Changed textures. It's empty if the @p TextureChanged() is @a true.
			[[nodiscard("Pure function")]]
			const std::set<std::pair<std::uint32_t, std::uint32_t>>& ChangedTextures() const noexcept;
			/// @brief Is the data structure changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool DataChanged() const noexcept;
			/// @brief Is the texture structure changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool TextureChanged() const noexcept;
			/// @brief Is the pipeline state changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool PipelineStateChanged() const noexcept;
			/// @brief Is the name changed?
			/// @return @a True if it's changed; @a false otherwise.
			[[nodiscard("Pure function")]]
			bool NameChanged() const noexcept;

			/// @brief Sets all the fields to false.
			void Reset() noexcept;

			MaterialObserver& operator =(const MaterialObserver&) = delete;
			MaterialObserver& operator =(MaterialObserver&&) = delete;

		private:
			std::set<std::pair<std::uint32_t, std::uint32_t>> changedData; ///< Changed data indices.
			std::set<std::pair<std::uint32_t, std::uint32_t>> changedTextures; ///< Changed texture indices.
			bool dataChanged; ///< Is data structure changed?
			bool textureChanged; ///< Is texture structure changed?
			bool pipelineStateChanged; ///< Is pipeline state changed?
			bool nameChanged; ///< Is name changed?
		};

		/// @brief Buffer info. Used to sort material data buffers.
		struct BufferInfo final
		{
			const PonyBase::Container::Buffer* buffer; ///< Material buffer.
			std::uint64_t offset; ///< Offset in element indices.
			std::uint32_t dataTypeIndex; ///< Data type index.
			std::uint32_t bufferIndex; ///< Buffer index.
		};

		/// @brief Calculates a buffer order.
		///	@param source Material.
		/// @return Buffer infos in the order they must appear in a render buffer.
		[[nodiscard("Pure function")]]
		static std::vector<BufferInfo> CalculateBufferOrder(const Render::Material& source);
		/// @brief Calculates a buffer size by the buffer infos.
		/// @param bufferInfos Buffer infos.
		/// @return Required size.
		[[nodiscard("Pure function")]]
		static std::uint64_t CalculateBufferSize(std::span<const BufferInfo> bufferInfos) noexcept;

		[[nodiscard("Pure function")]]
		static D3D12_SHADER_RESOURCE_VIEW_DESC GetSRV(const Render::Texture& texture);

		/// @brief Updates the material.
		/// @param material Material
		/// @param source Material source.
		/// @param observer Material observer.
		void UpdateMaterial(Material& material, const Render::Material& source, const MaterialObserver& observer) const;
		/// @brief Update the material pipeline state.
		/// @param material Material.
		/// @param source Material source.
		/// @param observer Material observer.
		void UpdatePipelineState(Material& material, const Render::Material& source, const MaterialObserver& observer) const;
		/// @brief Updates the material data.
		/// @param material Material
		/// @param source Material source.
		/// @param observer Material observer.
		void UpdateData(Material& material, const Render::Material& source, const MaterialObserver& observer) const;
		/// @brief Updates the material data.
		/// @param material Material.
		/// @param source Material source.
		void UpdateData(Material& material, const Render::Material& source) const;
		/// @brief Updates the material data.
		/// @param material Material.
		/// @param source Material source.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		void UpdateData(Material& material, const Render::Material& source, std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const;
		void UpdateTextures(Material& material, const Render::Material& source, const MaterialObserver& observer);
		/// @brief Updates the material name.
		/// @param material Material.
		/// @param source Material source.
		/// @param observer Material observer.
		static void UpdateName(Material& material, const Render::Material& source, const MaterialObserver& observer);

		/// @brief Adds a new material.
		/// @param material Material.
		/// @param source Material source.
		void Add(const std::shared_ptr<Material>& material, const std::shared_ptr<const Render::Material>& source);
		/// @brief Removes a material.
		/// @param index Material index.
		void Remove(std::size_t index) noexcept;

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Material>> materials; ///< Materials.
		std::vector<std::shared_ptr<const Render::Material>> sources; ///< Material sources.
		std::vector<std::unique_ptr<MaterialObserver>> observers; ///< Material observers.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	MaterialManager::MaterialObserver::MaterialObserver() noexcept :
		dataChanged{true},
		textureChanged{true},
		pipelineStateChanged{true},
		nameChanged{true}
	{
	}

	void MaterialManager::MaterialObserver::OnPipelineStateChanged() noexcept
	{
		pipelineStateChanged = true;
	}

	void MaterialManager::MaterialObserver::OnDataChanged() noexcept
	{
		changedData.clear();
		dataChanged = true;
	}

	void MaterialManager::MaterialObserver::OnDataChanged(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) noexcept
	{
		if (!dataChanged)
		{
			changedData.insert(std::pair(dataTypeIndex, dataIndex));
		}
	}

	void MaterialManager::MaterialObserver::OnTextureChanged() noexcept
	{
		changedTextures.clear();
		textureChanged = true;
	}

	void MaterialManager::MaterialObserver::OnTextureChanged(const std::uint32_t textureTypeIndex, const std::uint32_t textureIndex) noexcept
	{
		if (!textureChanged)
		{
			changedTextures.insert(std::pair(textureTypeIndex, textureIndex));
		}
	}

	void MaterialManager::MaterialObserver::OnNameChanged() noexcept
	{
		nameChanged = true;
	}

	const std::set<std::pair<std::uint32_t, std::uint32_t>>& MaterialManager::MaterialObserver::ChangedData() const noexcept
	{
		return changedData;
	}

	const std::set<std::pair<std::uint32_t, std::uint32_t>>& MaterialManager::MaterialObserver::ChangedTextures() const noexcept
	{
		return changedTextures;
	}

	bool MaterialManager::MaterialObserver::DataChanged() const noexcept
	{
		return dataChanged;
	}

	bool MaterialManager::MaterialObserver::TextureChanged() const noexcept
	{
		return textureChanged;
	}

	bool MaterialManager::MaterialObserver::PipelineStateChanged() const noexcept
	{
		return pipelineStateChanged;
	}

	bool MaterialManager::MaterialObserver::NameChanged() const noexcept
	{
		return nameChanged;
	}

	void MaterialManager::MaterialObserver::Reset() noexcept
	{
		changedData.clear();
		changedTextures.clear();
		dataChanged = false;
		textureChanged = false;
		pipelineStateChanged = false;
		nameChanged = false;
	}

	MaterialManager::MaterialManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System(&d3d12System)
	{
	}

	std::shared_ptr<Material> MaterialManager::CreateMaterial(const std::shared_ptr<const Render::Material>& material)
	{
		if (!material) [[unlikely]]
		{
			throw std::invalid_argument("Material is nullptr.");
		}

		for (std::size_t i = 0; i < sources.size(); ++i)
		{
			if (sources[i].get() == material.get())
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material reused at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(materials[i].get()));
				return materials[i];
			}
		}

		const auto renderMaterial = std::make_shared<Material>();
		Add(renderMaterial, material);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderMaterial.get()));

		return renderMaterial;
	}

	void MaterialManager::Tick()
	{
		for (std::size_t i = 0; i < materials.size(); ++i)
		{
			Material& material = *materials[i];
			const Render::Material& source = *sources[i];
			MaterialObserver& observer = *observers[i];

			UpdateMaterial(material, source, observer);
			UpdatePipelineState(material, source, observer);
			UpdateData(material, source, observer);
			UpdateName(material, source, observer);

			observer.Reset();
		}
	}

	void MaterialManager::Clean() noexcept
	{
		for (std::size_t i = materials.size(); i-- > 0; )
		{
			if (const std::shared_ptr<Material>& material = materials[i]; material.use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy material at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(material.get()));
				Remove(i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material destroyed.");
			}
		}
	}

	std::vector<MaterialManager::BufferInfo> MaterialManager::CalculateBufferOrder(const Render::Material& source)
	{
		std::vector<BufferInfo> answer;
		answer.reserve(source.DataCount());
		for (std::uint32_t dataTypeIndex = 0u; dataTypeIndex < source.DataTypeCount(); ++dataTypeIndex)
		{
			for (std::uint32_t bufferIndex = 0u; bufferIndex < source.DataCount(dataTypeIndex); ++bufferIndex)
			{
				answer.push_back(BufferInfo{.buffer = &source.Data(dataTypeIndex, bufferIndex), .offset = 0ULL, .dataTypeIndex = dataTypeIndex, .bufferIndex = bufferIndex});
			}
		}

		std::ranges::sort(answer, [](const BufferInfo& left, const BufferInfo& right) { return left.buffer->Stride() > right.buffer->Stride(); });

		for (std::size_t i = 1; i < answer.size(); ++i)
		{
			const BufferInfo& prev = answer[i - 1];
			const std::uint64_t prevEnd = prev.offset * prev.buffer->Stride() + static_cast<std::uint64_t>(prev.buffer->Size());
			answer[i].offset = PonyMath::Core::DivideCeil(prevEnd, static_cast<std::uint64_t>(answer[i].buffer->Stride()));
		}

		return answer;
	}

	std::uint64_t MaterialManager::CalculateBufferSize(const std::span<const BufferInfo> bufferInfos) noexcept
	{
		if (bufferInfos.size() == 0)
		{
			return 1ULL;
		}

		const BufferInfo& last = bufferInfos[bufferInfos.size() - 1];

		return last.offset * last.buffer->Stride() + last.buffer->Size();
	}

	D3D12_SHADER_RESOURCE_VIEW_DESC MaterialManager::GetSRV(const Render::Texture& texture)
	{
		switch (texture.Dimension())
		{
		case TextureDimension::Texture1D:
			return D3D12_SHADER_RESOURCE_VIEW_DESC
			{
				.Format = GetD3D12Format(texture.Format()),
				.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1D,
				.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
				.Texture1D = D3D12_TEX1D_SRV
				{
					.MostDetailedMip = 0u,
					.MipLevels = 1u,
					.ResourceMinLODClamp = 0.f
				}
			};
		case TextureDimension::Texture2D:
			return D3D12_SHADER_RESOURCE_VIEW_DESC
			{
				.Format = GetD3D12Format(texture.Format()),
				.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D,
				.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
				.Texture2D = D3D12_TEX2D_SRV
				{
					.MostDetailedMip = 0u,
					.MipLevels = 1u,
					.PlaneSlice = 0u,
					.ResourceMinLODClamp = 0.f
				}
			};
		case TextureDimension::Texture3D:
			return D3D12_SHADER_RESOURCE_VIEW_DESC
			{
				.Format = GetD3D12Format(texture.Format()),
				.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D,
				.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
				.Texture3D = D3D12_TEX3D_SRV
				{
					.MostDetailedMip = 0u,
					.MipLevels = 1u,
					.ResourceMinLODClamp = 0.f
				}
			};
		default: [[unlikely]]
			throw std::invalid_argument("Unsupported texture dimension.");
		}
	}

	void MaterialManager::UpdateMaterial(Material& material, const Render::Material& source, const MaterialObserver& observer) const
	{
		if (!observer.DataChanged() && !observer.TextureChanged()) [[likely]]
		{
			return;
		}

		const std::uint32_t dataCount = source.DataCount();
		const std::uint32_t textureCount = source.TextureCount();
		const std::uint32_t heapSize = dataCount + textureCount;

		const std::vector<BufferInfo> bufferInfos = CalculateBufferOrder(source);
		std::shared_ptr<Buffer> buffer = d3d12System->ResourceManager().CreateBuffer(CalculateBufferSize(bufferInfos), HeapType::Default);

		std::vector<std::vector<std::shared_ptr<Texture>>> textures;
		textures.reserve(source.TextureTypeCount());
		for (std::uint32_t textureTypeIndex = 0; textureTypeIndex < source.TextureTypeCount(); ++textureTypeIndex)
		{
			std::vector<std::shared_ptr<Texture>>& createdTextures = textures[textureTypeIndex];
			createdTextures.reserve(source.TextureCount(textureTypeIndex));

			for (std::uint32_t textureIndex = 0; textureIndex < source.TextureCount(textureTypeIndex); ++textureIndex)
			{
				createdTextures.push_back(d3d12System->TextureManager().CreateTexture(source.Texture(textureTypeIndex, textureIndex)));
			}
		}

		std::shared_ptr<DescriptorHeap> heap = d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, heapSize, false);

		std::vector<std::vector<std::uint64_t>> bufferOffsets;
		bufferOffsets.reserve(source.DataTypeCount());
		for (std::uint32_t i = 0u; i < source.DataTypeCount(); ++i)
		{
			bufferOffsets.push_back(std::vector<std::uint64_t>(source.DataCount(i)));
		}
		for (const BufferInfo& bufferInfo : bufferInfos)
		{
			bufferOffsets[bufferInfo.dataTypeIndex][bufferInfo.bufferIndex] = bufferInfo.offset;
		}

		std::vector<std::string> types;
		std::vector<std::uint32_t> heapIndices;
		types.reserve(heapSize);
		heapIndices.reserve(heapSize);

		std::uint32_t heapIndex = 0u;

		for (std::uint32_t dataTypeIndex = 0u; dataTypeIndex < source.DataTypeCount(); ++dataTypeIndex)
		{
			types.push_back(std::string(source.DataType(dataTypeIndex)));
			heapIndices.push_back(heapIndex);

			for (std::uint32_t dataIndex = 0u; dataIndex < source.DataCount(dataTypeIndex); ++dataIndex, ++heapIndex)
			{
				const PonyBase::Container::Buffer& sourceBuffer = source.Data(dataTypeIndex, dataIndex);
				const auto srvDesc = D3D12_SHADER_RESOURCE_VIEW_DESC
				{
					.Format = DXGI_FORMAT_UNKNOWN,
					.ViewDimension = D3D12_SRV_DIMENSION_BUFFER,
					.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
					.Buffer = D3D12_BUFFER_SRV
					{
						.FirstElement = bufferOffsets[dataTypeIndex][dataIndex],
						.NumElements = static_cast<UINT>(sourceBuffer.Count()),
						.StructureByteStride = static_cast<UINT>(sourceBuffer.Stride()),
						.Flags = D3D12_BUFFER_SRV_FLAG_NONE
					}
				};
				d3d12System->Device().CreateShaderResourceView(&buffer->Data(), &srvDesc, heap->CpuHandle(heapIndex));
			}
		}
		for (const BufferInfo& bufferInfo : bufferInfos)
		{
			bufferOffsets[bufferInfo.dataTypeIndex][bufferInfo.bufferIndex] = bufferInfo.offset * bufferInfo.buffer->Stride();
		}

		for (std::uint32_t textureTypeIndex = 0u; textureTypeIndex < source.TextureTypeCount(); ++textureTypeIndex)
		{
			types.push_back(std::string(source.TextureType(textureTypeIndex)));
			heapIndices.push_back(heapIndex);

			for (std::uint32_t textureIndex = 0u; textureIndex < source.TextureCount(textureTypeIndex); ++textureIndex, ++heapIndex)
			{
				Texture& texture = *textures[textureTypeIndex][textureIndex];
				const Render::Texture& sourceTexture = *source.Texture(textureTypeIndex, textureIndex);
				const auto srvDesc = GetSRV(sourceTexture);
				d3d12System->Device().CreateShaderResourceView(&texture.Data(), &srvDesc, heap->CpuHandle(heapIndex));
			}
		}

		material = Material(nullptr, std::move(buffer), std::move(bufferOffsets), std::move(textures), std::move(heap), std::move(types), std::move(heapIndices));
	}

	void MaterialManager::UpdatePipelineState(Material& material, const Render::Material& source, const MaterialObserver& observer) const
	{
		if (!observer.PipelineStateChanged()) [[likely]]
		{
			return;
		}

		material.PipelineState(d3d12System->PipelineStateManager().CreatePipelineState(source.PipelineState()));
	}

	void MaterialManager::UpdateData(Material& material, const Render::Material& source, const MaterialObserver& observer) const
	{
		if (observer.DataChanged()) [[unlikely]]
		{
			UpdateData(material, source);
		}
		else [[likely]]
		{
			for (const auto [dataTypeIndex, bufferIndex] : observer.ChangedData())
			{
				UpdateData(material, source, dataTypeIndex, bufferIndex);
			}
		}
	}

	void MaterialManager::UpdateData(Material& material, const Render::Material& source) const
	{
		Buffer& gpuBuffer = *material.Buffer();
		const std::uint64_t size = gpuBuffer.Data().GetDesc1().Width;
		const std::shared_ptr<Buffer> uploadBuffer = d3d12System->ResourceManager().CreateBuffer(size, HeapType::Upload);

		for (std::uint32_t dataTypeIndex = 0u; dataTypeIndex < material.TypeCount(); ++dataTypeIndex)
		{
			for (std::uint32_t dataIndex = 0u; dataIndex < material.DataCount(dataTypeIndex); ++dataIndex)
			{
				const PonyBase::Container::Buffer& buffer = source.Data(dataTypeIndex, dataIndex);
				uploadBuffer->SetData(buffer.Data(), buffer.Size(), material.BufferOffset(dataTypeIndex, dataIndex));
			}
		}

		d3d12System->CopyPipeline().AddCopyTask(*uploadBuffer, gpuBuffer);
	}

	void MaterialManager::UpdateData(Material& material, const Render::Material& source, const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const
	{
		const PonyBase::Container::Buffer& sourceBuffer = source.Data(dataTypeIndex, dataIndex);
		const std::shared_ptr<Buffer> uploadBuffer = d3d12System->ResourceManager().CreateBuffer(sourceBuffer.Size(), HeapType::Upload);
		uploadBuffer->SetData(sourceBuffer);

		Buffer& gpuBuffer = *material.Buffer();
		d3d12System->CopyPipeline().AddCopyTask(*uploadBuffer, gpuBuffer, 0ULL, material.BufferOffset(dataTypeIndex, dataIndex), sourceBuffer.Size());
	}

	void MaterialManager::UpdateTextures(Material& material, const Render::Material& source, const MaterialObserver& observer)
	{
		for (const auto [textureTypeIndex, textureIndex] : observer.ChangedTextures())
		{
			material.Texture(textureTypeIndex, textureIndex, d3d12System->TextureManager().CreateTexture(source.Texture(textureTypeIndex, textureIndex)));
		}
	}

	void MaterialManager::UpdateName(Material& material, const Render::Material& source, const MaterialObserver& observer)
	{
		if (!observer.NameChanged()) [[likely]]
		{
			return;
		}

		material.Name(source.Name());
	}

	void MaterialManager::Add(const std::shared_ptr<Material>& material, const std::shared_ptr<const Render::Material>& source)
	{
		const std::size_t currentSize = materials.size();

		try
		{
			materials.push_back(material);
			sources.push_back(source);
			observers.push_back(std::make_unique<MaterialObserver>());
			source->AddObserver(*observers.back());
		}
		catch (...)
		{
			materials.resize(currentSize);
			sources.resize(currentSize);
			observers.resize(currentSize);

			throw;
		}
	}

	void MaterialManager::Remove(const std::size_t index) noexcept
	{
		sources[index]->RemoveObserver(*observers[index]);

		materials.erase(materials.cbegin() + index);
		sources.erase(sources.cbegin() + index);
		observers.erase(observers.cbegin() + index);
	}
}

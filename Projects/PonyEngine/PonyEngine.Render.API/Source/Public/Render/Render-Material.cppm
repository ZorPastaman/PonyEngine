/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Material;

import <array>;
import <cstdint>;
import <optional>;
import <span>;
import <stdexcept>;
import <string>;
import <string_view>;
import <unordered_map>;
import <vector>;

import :Blend;
import :IMaterialObserver;
import :MaterialParams;

export namespace PonyEngine::Render
{
	class Material final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Material() noexcept = default;
		[[nodiscard("Pure constructor")]]
		explicit Material(const MaterialParams& params);
		[[nodiscard("Pure constructor")]]
		Material(const Material& other);
		[[nodiscard("Pure constructor")]]
		Material(Material&& other) noexcept;

		~Material() noexcept = default;

		[[nodiscard("Pure function")]]
		std::string_view RootSignatureShader() const noexcept;
		void RootSignatureShader(std::string_view shader);
		void RootSignatureShader(std::string&& shader);
		[[nodiscard("Pure function")]]
		std::string_view AmplificationShader() const noexcept;
		void AmplificationShader(std::string_view shader);
		void AmplificationShader(std::string&& shader);
		[[nodiscard("Pure function")]]
		std::string_view MeshShader() const noexcept;
		void MeshShader(std::string_view shader);
		void MeshShader(std::string&& shader);
		[[nodiscard("Pure function")]]
		std::string_view PixelShader() const noexcept;
		void PixelShader(std::string_view shader);
		void PixelShader(std::string&& shader);

		[[nodiscard("Pure function")]]
		const struct Blend& Blend() const noexcept;
		void Blend(const struct Blend& blendToSet) noexcept;
		[[nodiscard("Pure function")]]
		const struct Rasterizer& Rasterizer() const noexcept;
		void Rasterizer(const struct Rasterizer& rasterizerToSet) noexcept;

		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataSlot(std::string_view dataType) const noexcept;
		void DataSlot(std::string_view dataType, std::uint32_t dataSlot);
		[[nodiscard("Pure function")]]
		const std::unordered_map<std::string, std::uint32_t>& DataSlots() const noexcept;
		void DataSlots(const std::unordered_map<std::string, std::uint32_t>& data);
		void DataSlots(std::unordered_map<std::string, std::uint32_t>&& data);

		[[nodiscard("Pure function")]]
		const struct ThreadGroupCounts& ThreadGroupCounts() const noexcept;
		void ThreadGroupCounts(const struct ThreadGroupCounts& threadGroupCountsToSet) noexcept;

		[[nodiscard("Pure function")]]
		bool CameraCulling() const noexcept;
		void CameraCulling(bool culling) noexcept;

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		void Name(std::string_view nameToSet);
		void Name(std::string&& nameToSet);

		void AddObserver(IMaterialObserver& observer) const;
		void RemoveObserver(IMaterialObserver& observer) const noexcept;

		Material& operator =(const Material& other);
		Material& operator =(Material&& other) noexcept;

	private:
		void OnRootSignatureChanged() const noexcept;
		void OnAmplificationShaderChanged() const noexcept;
		void OnMeshShaderChanged() const noexcept;
		void OnPixelShaderChanged() const noexcept;

		void OnBlendChanged() const noexcept;
		void OnRasterizerChanged() const noexcept;

		void OnDataSlotsChanged() const noexcept;

		void OnThreadGroupCountsChanged() const noexcept;
		void OnCameraCullingChanged() const noexcept;

		void OnNameChanged() const noexcept;

		std::string rootSignatureShader;
		std::string amplificationShader;
		std::string meshShader;
		std::string pixelShader;

		struct Blend blend;
		struct Rasterizer rasterizer;

		std::unordered_map<std::string, std::uint32_t> dataSlots;

		struct ThreadGroupCounts threadGroupCounts;
		bool cameraCulling;

		std::string name;

		mutable std::vector<IMaterialObserver*> materialObservers;
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
		dataSlots(params.dataSlots),
		threadGroupCounts(params.threadGroupCounts),
		cameraCulling(params.cameraCulling),
		name(params.name)
	{
	}

	Material::Material(const Material& other) :
		rootSignatureShader(other.rootSignatureShader),
		amplificationShader(other.amplificationShader),
		meshShader(other.meshShader),
		pixelShader(other.pixelShader),
		blend(other.blend),
		rasterizer(other.rasterizer),
		dataSlots(other.dataSlots),
		threadGroupCounts(other.threadGroupCounts),
		cameraCulling(other.cameraCulling),
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
		dataSlots(std::move(other.dataSlots)),
		threadGroupCounts(std::move(other.threadGroupCounts)),
		cameraCulling(std::move(other.cameraCulling)),
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
		OnRootSignatureChanged();
	}

	void Material::RootSignatureShader(std::string&& shader)
	{
		if (rootSignatureShader == shader)
		{
			return;
		}

		rootSignatureShader = std::move(shader);
		OnRootSignatureChanged();
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

	void Material::Blend(const struct Blend& blendToSet) noexcept
	{
		blend = blendToSet;
		OnBlendChanged();
	}

	const struct Rasterizer& Material::Rasterizer() const noexcept
	{
		return rasterizer;
	}

	void Material::Rasterizer(const struct Rasterizer& rasterizerToSet) noexcept
	{
		rasterizer = rasterizerToSet;
		OnRasterizerChanged();
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
					OnRootSignatureChanged();
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
		dataSlots = data;
		OnDataSlotsChanged();
	}

	void Material::DataSlots(std::unordered_map<std::string, std::uint32_t>&& data)
	{
		dataSlots = std::move(data);
		OnDataSlotsChanged();
	}

	const struct ThreadGroupCounts& Material::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Material::ThreadGroupCounts(const struct ThreadGroupCounts& threadGroupCountsToSet) noexcept
	{
		if (threadGroupCounts == threadGroupCountsToSet)
		{
			return;
		}

		threadGroupCounts = threadGroupCountsToSet;
		OnThreadGroupCountsChanged();
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

	void Material::Name(const std::string_view nameToSet)
	{
		if (name == nameToSet)
		{
			return;
		}

		name = nameToSet;
		OnNameChanged();
	}

	void Material::Name(std::string&& nameToSet)
	{
		if (name == nameToSet)
		{
			return;
		}

		name = std::move(nameToSet);
		OnNameChanged();
	}

	void Material::AddObserver(IMaterialObserver& observer) const
	{
		materialObservers.push_back(&observer);
	}

	void Material::RemoveObserver(IMaterialObserver& observer) const noexcept
	{
		if (const auto position = std::ranges::find(materialObservers, &observer); position != materialObservers.cend()) [[likely]]
		{
			materialObservers.erase(position);
		}
	}

	void Material::OnRootSignatureChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnRootSignatureChanged();
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
		RootSignatureShader(other.rootSignatureShader);
		AmplificationShader(other.amplificationShader);
		MeshShader(other.meshShader);
		PixelShader(other.pixelShader);
		Blend(other.blend);
		Rasterizer(other.rasterizer);
		DataSlots(other.dataSlots);

		ThreadGroupCounts(other.threadGroupCounts);
		CameraCulling(other.cameraCulling);

		Name(other.name);

		return *this;
	}

	Material& Material::operator =(Material&& other) noexcept
	{
		RootSignatureShader(std::move(other.rootSignatureShader));
		AmplificationShader(std::move(other.amplificationShader));
		MeshShader(std::move(other.meshShader));
		PixelShader(std::move(other.pixelShader));
		Blend(other.blend);
		Rasterizer(other.rasterizer);
		DataSlots(std::move(other.dataSlots));

		ThreadGroupCounts(other.threadGroupCounts);
		CameraCulling(other.cameraCulling);

		Name(std::move(other.name));

		return *this;
	}
}

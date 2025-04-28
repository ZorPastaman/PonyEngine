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

import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <string>;
import <vector>;

import PonyBase.Container;
import PonyBase.Utility;

import :BufferData;
import :IMaterialObserver;
import :MaterialParams;
import :PipelineState;

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
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		Material(const Material& other);
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		Material(Material&& other) noexcept;

		~Material() noexcept = default;

		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<class PipelineState>& PipelineState() const noexcept;
		/// @brief Sets the pipeline state.
		/// @param pipelineState Pipeline state to set.
		void PipelineState(const std::shared_ptr<class PipelineState>& pipelineState) noexcept;

		/// @brief Tries to find a data type index by the @p dataType.
		/// @param dataType Data type.
		/// @return Data type index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataTypeIndex(std::string_view dataType) const noexcept;
		/// @brief Gets a data type by the @p dataTypeIndex.
		/// @param dataTypeIndex Data type index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::string_view DataType(std::uint32_t dataTypeIndex) const noexcept;
		/// @brief Gets the data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataTypeCount() const noexcept;
		/// @brief Gets the data types.
		/// @return Data types.
		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		/// @brief Gets the data count by the @p dataTypeIndex.
		/// @param dataTypeIndex Data type index.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount(std::uint32_t dataTypeIndex) const noexcept;
		/// @brief Gets the data count of all the tables.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataCount() const noexcept;

		/// @brief Gets the data.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Buffer index.
		/// @return Data.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept;

		/// @brief Creates a data table or overrides an existing one if their data types are the same.
		/// @param dataType Data type.
		/// @param dataParams Data parameters.
		/// @return Data type index.
		std::uint32_t CreateDataTable(std::string_view dataType, std::span<const PonyBase::Container::BufferParams> dataParams);
		/// @brief Destroys a data table.
		/// @param dataTypeIndex Data type index.
		void DestroyDataTable(std::uint32_t dataTypeIndex) noexcept;

		/// @brief Sets the data to a buffer.
		/// @param dataIndex Data type index.
		/// @param bufferIndex Buffer index.
		/// @param data Data.
		/// @param offset Data offset in bytes.
		void SetBuffer(std::uint32_t dataIndex, std::uint32_t bufferIndex, std::span<const std::byte> data, std::size_t offset = 0);
		/// @brief Sets a value to a buffer.
		/// @tparam T Value type.
		/// @param dataIndex Data type index.
		/// @param bufferIndex Buffer index.
		/// @param value Value.
		/// @param index Value index.
		template<typename T>
		void SetBuffer(std::uint32_t dataIndex, std::uint32_t bufferIndex, const T& value, std::size_t index = 0);
		/// @brief Sets the data to a buffer.
		/// @tparam T Value type.
		/// @param dataIndex Data type index.
		/// @param bufferIndex Buffer index.
		/// @param data Data.
		/// @param startIndex Start index.
		template<typename T>
		void SetBuffer(std::uint32_t dataIndex, std::uint32_t bufferIndex, std::span<const T> data, std::size_t startIndex = 0);

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		/// @brief Adds the observer.
		/// @param observer Observer to add. It must be unique. It must live longer than the material.
		void AddObserver(IMaterialObserver& observer) const;
		/// @brief Removes the observer.
		/// @param observer Observer to remove.
		void RemoveObserver(IMaterialObserver& observer) const noexcept;

		/// @brief Copy assignment.
		/// @param other Copy source.
		/// @return @a This.
		Material& operator =(const Material& other);
		/// @brief Move assignment.
		/// @param other Move source.
		/// @return @a This.
		Material& operator =(Material&& other) noexcept;

	private:
		/// @brief Calls @p OnPipelineStateChanged() on each observer.
		void OnPipelineStateChanged() const noexcept;
		/// @brief Calls @p OnDataChanged() on each observer.
		void OnDataChanged() const noexcept;
		/// @brief Calls @p OnDataChanged() on each observer.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		void OnDataChanged(std::uint32_t dataIndex, std::uint32_t bufferIndex) const noexcept;
		/// @brief Calls @p OnNameChanged() on each observer.
		void OnNameChanged() const noexcept;

		std::shared_ptr<class PipelineState> pipelineState; ///< Pipeline state.
		BufferData bufferData; ///< Buffer data.

		std::string name; ///< Material name.

		mutable std::vector<IMaterialObserver*> materialObservers; ///< Material observers.
	};
}

namespace PonyEngine::Render
{
	Material::Material(const MaterialParams& params) :
		pipelineState(params.pipelineState),
		bufferData(params.dataTables),
		name(params.name)
	{
	}

	Material::Material(const Material& other) :
		pipelineState(other.pipelineState),
		bufferData(other.bufferData),
		name(other.name)
	{
	}

	Material::Material(Material&& other) noexcept :
		pipelineState(std::move(other.pipelineState)),
		bufferData(std::move(other.bufferData)),
		name(std::move(other.name))
	{
	}

	const std::shared_ptr<class PipelineState>& Material::PipelineState() const noexcept
	{
		return pipelineState;
	}

	void Material::PipelineState(const std::shared_ptr<class Render::PipelineState>& pipelineState) noexcept
	{
		if (this->pipelineState == pipelineState)
		{
			return;
		}

		this->pipelineState = pipelineState;
		OnPipelineStateChanged();
	}

	std::optional<std::uint32_t> Material::DataTypeIndex(const std::string_view dataType) const noexcept
	{
		return bufferData.DataIndex(dataType);
	}

	std::string_view Material::DataType(const std::uint32_t dataTypeIndex) const noexcept
	{
		return bufferData.DataType(dataTypeIndex);
	}

	std::uint32_t Material::DataTypeCount() const noexcept
	{
		return bufferData.DataTypeCount();
	}

	std::span<const std::string> Material::DataTypes() const noexcept
	{
		return bufferData.DataTypes();
	}

	std::uint32_t Material::DataCount(const std::uint32_t dataTypeIndex) const noexcept
	{
		return bufferData.BufferCount(dataTypeIndex);
	}

	std::uint32_t Material::DataCount() const noexcept
	{
		return bufferData.BufferCount();
	}

	const PonyBase::Container::Buffer& Material::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.Buffer(dataTypeIndex, dataIndex);
	}

	std::uint32_t Material::CreateDataTable(const std::string_view dataType, const std::span<const PonyBase::Container::BufferParams> dataParams)
	{
		const std::uint32_t dataIndex = bufferData.CreateBufferTable(dataType, dataParams);
		OnDataChanged();

		return dataIndex;
	}

	void Material::DestroyDataTable(const std::uint32_t dataTypeIndex) noexcept
	{
		bufferData.DestroyBufferTable(dataTypeIndex);
		OnDataChanged();
	}

	void Material::SetBuffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex, const std::span<const std::byte> data, const std::size_t offset)
	{
		bufferData.SetData(dataIndex, bufferIndex, data, offset);
		OnDataChanged(dataIndex, bufferIndex);
	}

	template <typename T>
	void Material::SetBuffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex, const T& value, const std::size_t index)
	{
		bufferData.SetData(dataIndex, bufferIndex, value, index);
		OnDataChanged(dataIndex, bufferIndex);
	}

	template <typename T>
	void Material::SetBuffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex, const std::span<const T> data, const std::size_t startIndex)
	{
		bufferData.SetData(dataIndex, bufferIndex, data, startIndex);
		OnDataChanged(dataIndex, bufferIndex);
	}

	void Material::OnPipelineStateChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnPipelineStateChanged();
		}
	}

	void Material::OnDataChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnDataChanged();
		}
	}

	void Material::OnDataChanged(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnDataChanged(dataIndex, bufferIndex);
		}
	}

	void Material::OnNameChanged() const noexcept
	{
		for (IMaterialObserver* const observer : materialObservers)
		{
			observer->OnNameChanged();
		}
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

	void Material::AddObserver(IMaterialObserver& observer) const
	{
		assert(std::ranges::find(materialObservers, &observer) == materialObservers.cend() && "The mesh observer is already added.");
		materialObservers.push_back(&observer);
	}

	void Material::RemoveObserver(IMaterialObserver& observer) const noexcept
	{
		if (const auto position = std::ranges::find(materialObservers, &observer); position != materialObservers.cend()) [[likely]]
		{
			materialObservers.erase(position);
		}
	}

	Material& Material::operator =(const Material& other)
	{
		BufferData newBufferData = other.bufferData;
		std::optional<std::string> newName = other.name == name ? std::nullopt : std::optional(other.name);

		if (pipelineState != other.pipelineState)
		{
			pipelineState = other.pipelineState;
			OnPipelineStateChanged();
		}

		bufferData = std::move(newBufferData);
		OnDataChanged();

		if (newName)
		{
			name = std::move(newName.value());
			OnNameChanged();
		}

		return *this;
	}

	Material& Material::operator =(Material&& other) noexcept
	{
		if (pipelineState == other.pipelineState)
		{
			pipelineState = std::move(other.pipelineState);
			OnPipelineStateChanged();
		}

		bufferData = std::move(other.bufferData);
		OnDataChanged();

		if (name != other.name)
		{
			name = std::move(other.name);
			OnNameChanged();
		}

		return *this;
	}
}

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

export module PonyEngine.Render:Mesh;

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <optional>;
import <span>;
import <string>;
import <string_view>;
import <utility>;
import <vector>;

import PonyBase.Container;

import PonyMath.Shape;

import PonyShader.Core;

import :BufferData;
import :IMeshObserver;
import :MeshParams;

export namespace PonyEngine::Render
{
	/// @brief Render mesh.
	/// @details It's a map of a data type to an array of buffers.
	/// @remark All the mesh data will be transferred to shader t-buffers.
	class Mesh final
	{ 
	public:
		/// @brief Creates an empty mesh with zero thread group counts.
		[[nodiscard("Pure constructor")]]
		Mesh() noexcept = default;
		/// @brief Creates a mesh.
		/// @param params Mesh parameters
		[[nodiscard("Pure constructor")]]
		explicit Mesh(const MeshParams& params);
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other);
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept;

		~Mesh() noexcept = default;

		/// @brief Tries to find a data index by the @p dataType.
		/// @param dataType Data type.
		/// @return Data index; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataIndex(std::string_view dataType) const noexcept;
		/// @brief Gets a data type by the @p dataIndex.
		/// @param dataIndex Data index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		std::string_view DataType(std::uint32_t dataIndex) const noexcept;
		/// @brief Gets the data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		std::uint32_t DataTypeCount() const noexcept;
		/// @brief Gets the data types.
		/// @return Data types.
		[[nodiscard("Pure function")]]
		std::span<const std::string> DataTypes() const noexcept;

		/// @brief Gets the buffer count by the @p dataIndex.
		/// @param dataIndex Data index.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount(std::uint32_t dataIndex) const noexcept;
		/// @brief Gets the buffer count of all the tables.
		/// @return Buffer count.
		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount() const noexcept;

		/// @brief Gets the buffer.
		/// @param dataIndex Data type index.
		/// @param bufferIndex Buffer index.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex) const noexcept;

		/// @brief Creates a buffer table or overrides an existing one if their data types are the same.
		/// @param dataType Data type.
		/// @param bufferParams Buffer parameters.
		/// @return Data type index.
		std::uint32_t CreateBufferTable(std::string_view dataType, std::span<const PonyBase::Container::BufferParams> bufferParams);
		/// @brief Destroys a buffer table.
		/// @param dataIndex Data type index.
		void DestroyBufferTable(std::uint32_t dataIndex) noexcept;

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

		/// @brief Gets the thread group counts.
		/// @return Thread group counts.
		[[nodiscard("Pure function")]]
		const PonyShader::Core::ThreadGroupCounts& ThreadGroupCounts() const noexcept;
		/// @brief Sets the thread group counts.
		/// @param threadGroupCounts Thread group counts to set.
		void ThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& threadGroupCounts);

		/// @brief Gets the bounding box.
		/// @return Bounding box.
		[[nodiscard("Pure function")]]
		const std::optional<PonyMath::Shape::AABB<float>>& BoundingBox() const noexcept;
		/// @brief Sets the bounding box.
		/// @param boundingBox Bounding box to set.
		void BoundingBox(const std::optional<PonyMath::Shape::AABB<float>>& boundingBox) noexcept;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		/// @brief Adds the observer.
		/// @param observer Observer to add. It must be unique. It must live longer than the mesh.
		void AddObserver(IMeshObserver& observer) const;
		/// @brief Removes the observer.
		/// @param observer Observer to remove.
		void RemoveObserver(IMeshObserver& observer) const noexcept;

		/// @brief Copy assignment.
		/// @param other Copy source.
		/// @return @a This.
		Mesh& operator =(const Mesh& other);
		/// @brief Move assignment.
		/// @param other Move source.
		/// @return @a This.
		Mesh& operator =(Mesh&& other) noexcept;

	private:
		/// @brief Calls @p OnMeshChanged() on each observer.
		void OnMeshChanged() const noexcept;
		/// @brief Calls @p OnBufferChanged() on each observer.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		void OnBufferChanged(std::uint32_t dataIndex, std::uint32_t bufferIndex) const noexcept;
		/// @brief Calls @p OnThreadGroupCountsChanged() on each observer.
		void OnThreadGroupCountsChanged() const noexcept;
		/// @brief Calls @p OnBoundingBoxChanged() on each observer.
		void OnBoundingBoxChanged() const noexcept;
		/// @brief Calls @p OnNameChanged() on each observer.
		void OnNameChanged() const noexcept;

		BufferData bufferData; ///< Buffer data.

		PonyShader::Core::ThreadGroupCounts threadGroupCounts; ///< Thread group counts.
		std::optional<PonyMath::Shape::AABB<float>> boundingBox; ///< Bounding box.

		std::string name; ///< Mesh name.

		mutable std::vector<IMeshObserver*> meshObservers; ///< Mesh observers.
	};
}

namespace PonyEngine::Render
{
	Mesh::Mesh(const MeshParams& params) :
		bufferData(params.bufferTables),
		threadGroupCounts(params.threadGroupCounts),
		boundingBox(params.boundingBox),
		name(params.name)
	{
	}

	Mesh::Mesh(const Mesh& other) :
		bufferData(other.bufferData),
		threadGroupCounts(other.threadGroupCounts),
		boundingBox(other.boundingBox),
		name(other.name)
	{
	}

	Mesh::Mesh(Mesh&& other) noexcept :
		bufferData(std::move(other.bufferData)),
		threadGroupCounts(other.threadGroupCounts),
		boundingBox(other.boundingBox),
		name(std::move(other.name))
	{
	}

	std::optional<std::uint32_t> Mesh::DataIndex(const std::string_view dataType) const noexcept
	{
		return bufferData.DataIndex(dataType);
	}

	std::string_view Mesh::DataType(const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.DataType(dataIndex);
	}

	std::uint32_t Mesh::DataTypeCount() const noexcept
	{
		return bufferData.DataTypeCount();
	}

	std::span<const std::string> Mesh::DataTypes() const noexcept
	{
		return bufferData.DataTypes();
	}

	std::uint32_t Mesh::BufferCount(const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.BufferCount(dataIndex);
	}

	std::uint32_t Mesh::BufferCount() const noexcept
	{
		return bufferData.BufferCount();
	}

	const PonyBase::Container::Buffer& Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return bufferData.Buffer(dataIndex, bufferIndex);
	}

	std::uint32_t Mesh::CreateBufferTable(const std::string_view dataType, const std::span<const PonyBase::Container::BufferParams> bufferParams)
	{
		const std::uint32_t dataIndex = bufferData.CreateBufferTable(dataType, bufferParams);
		OnMeshChanged();

		return dataIndex;
	}

	void Mesh::DestroyBufferTable(const std::uint32_t dataIndex) noexcept
	{
		bufferData.DestroyBufferTable(dataIndex);
		OnMeshChanged();
	}

	void Mesh::SetBuffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex, const std::span<const std::byte> data, const std::size_t offset)
	{
		bufferData.SetData(dataIndex, bufferIndex, data, offset);
		OnBufferChanged(dataIndex, bufferIndex);
	}

	template <typename T>
	void Mesh::SetBuffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex, const T& value, const std::size_t index)
	{
		bufferData.SetData(dataIndex, bufferIndex, value, index);
		OnBufferChanged(dataIndex, bufferIndex);
	}

	template <typename T>
	void Mesh::SetBuffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex, const std::span<const T> data, const std::size_t startIndex)
	{
		bufferData.SetData(dataIndex, bufferIndex, data, startIndex);
		OnBufferChanged(dataIndex, bufferIndex);
	}

	const PonyShader::Core::ThreadGroupCounts& Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Mesh::ThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& threadGroupCounts)
	{
		if (this->threadGroupCounts == threadGroupCounts)
		{
			return;
		}

		this->threadGroupCounts = threadGroupCounts;
		OnThreadGroupCountsChanged();
	}

	const std::optional<PonyMath::Shape::AABB<float>>& Mesh::BoundingBox() const noexcept
	{
		return boundingBox;
	}

	void Mesh::BoundingBox(const std::optional<PonyMath::Shape::AABB<float>>& boundingBox) noexcept
	{
		if (this->boundingBox == boundingBox)
		{
			return;
		}

		this->boundingBox = boundingBox;
		OnBoundingBoxChanged();
	}

	std::string_view Mesh::Name() const noexcept
	{
		return name;
	}

	void Mesh::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
		OnNameChanged();
	}

	void Mesh::AddObserver(IMeshObserver& observer) const
	{
		assert(std::ranges::find(meshObservers, &observer) == meshObservers.cend() && "The mesh observer is already added.");
		meshObservers.push_back(&observer);
	}

	void Mesh::RemoveObserver(IMeshObserver& observer) const noexcept
	{
		if (const auto position = std::ranges::find(meshObservers, &observer); position != meshObservers.cend()) [[likely]]
		{
			meshObservers.erase(position);
		}
	}

	void Mesh::OnMeshChanged() const noexcept
	{
		for (IMeshObserver* const observer : meshObservers)
		{
			observer->OnMeshChanged();
		}
	}

	void Mesh::OnBufferChanged(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		for (IMeshObserver* const observer : meshObservers)
		{
			observer->OnBufferChanged(dataIndex, bufferIndex);
		}
	}

	void Mesh::OnThreadGroupCountsChanged() const noexcept
	{
		for (IMeshObserver* const observer : meshObservers)
		{
			observer->OnThreadGroupCountsChanged();
		}
	}

	void Mesh::OnBoundingBoxChanged() const noexcept
	{
		for (IMeshObserver* const observer : meshObservers)
		{
			observer->OnBoundingBoxChanged();
		}
	}

	void Mesh::OnNameChanged() const noexcept
	{
		for (IMeshObserver* const observer : meshObservers)
		{
			observer->OnNameChanged();
		}
	}

	Mesh& Mesh::operator =(const Mesh& other)
	{
		BufferData newBufferData = other.bufferData;
		std::optional<std::string> newName = name == other.name ? std::nullopt : std::optional(other.name);

		bufferData = std::move(newBufferData);
		OnMeshChanged();

		ThreadGroupCounts(other.threadGroupCounts);
		BoundingBox(other.boundingBox);

		if (newName)
		{
			name = std::move(newName.value());
			OnNameChanged();
		}

		return *this;
	}

	Mesh& Mesh::operator =(Mesh&& other) noexcept
	{
		bufferData = std::move(other.bufferData);
		OnMeshChanged();

		ThreadGroupCounts(other.threadGroupCounts);
		BoundingBox(other.boundingBox);

		if (name != other.name)
		{
			name = std::move(other.name);
			OnNameChanged();
		}

		return *this;
	}
}

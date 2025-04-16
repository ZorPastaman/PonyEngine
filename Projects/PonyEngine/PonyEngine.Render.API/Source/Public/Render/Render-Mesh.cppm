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
import <limits>;
import <optional>;
import <span>;
import <stdexcept>;
import <string>;
import <string_view>;
import <unordered_map>;
import <utility>;
import <vector>;

import PonyBase.Container;
import PonyBase.Utility;

import PonyMath.Shape;

import PonyShader.Core;

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
		class BufferTableAccess;

		/// @brief Buffer access wrapper.
		class BufferAccess final
		{
		public:
			[[nodiscard("Pure constructor")]]
			BufferAccess(const BufferAccess& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			BufferAccess(BufferAccess&& other) noexcept = default;

			~BufferAccess() noexcept = default;

			/// @brief Gets the buffer.
			/// @return Buffer.
			[[nodiscard("Pure function")]]
			const PonyBase::Container::Buffer& Buffer() const noexcept;

			/// @brief Sets the value by the index.
			/// @param index Byte index.
			/// @param value Value.
			void Set(std::size_t index, std::byte value) noexcept;
			/// @brief Sets the data.
			/// @note offset + data.size() must not exceed the target buffer size.
			/// @param offset Data destination offset.
			/// @param data Data to set.
			void Set(std::size_t offset, std::span<const std::byte> data);
			/// @brief Sets the value by the index.
			/// @tparam T Value type. Its size must be a stride of the buffer.
			/// @param index Value index.
			/// @param value Value.
			template<typename T>
			void Set(std::size_t index, const T& value) noexcept;
			/// @brief Sets the data.
			/// @note offset + data.size() must not exceed a target buffer size.
			/// @tparam T Value type.
			/// @param offset Data destination offset.
			/// @param data Data to set.
			template<typename T>
			void Set(std::size_t offset, std::span<const T> data) noexcept;

			BufferAccess& operator =(const BufferAccess& other) noexcept = default;
			BufferAccess& operator =(BufferAccess&& other) noexcept = default;

		private:
			/// @brief Creates a buffer access.
			/// @param buffer Buffer.
			/// @param mesh Mesh.
			/// @param dataIndex Data index.
			/// @param bufferIndex Buffer index.
			[[nodiscard("Pure constructor")]]
			BufferAccess(PonyBase::Container::Buffer& buffer, Mesh& mesh, std::uint32_t dataIndex, std::uint32_t bufferIndex) noexcept;

			PonyBase::Container::Buffer* buffer; ///< Buffer.
			Mesh* mesh; ///< Mesh.
			std::uint32_t dataIndex; ///< Data index.
			std::uint32_t bufferIndex; ///< Buffer index.

			friend Mesh;
			friend BufferTableAccess;
		};

		/// @brief Buffer view access wrapper.
		/// @tparam T Value type.
		template<typename T>
		class BufferViewAccess final
		{
		public:
			[[nodiscard("Pure constructor")]]
			BufferViewAccess(const BufferViewAccess& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			BufferViewAccess(BufferViewAccess&& other) noexcept = default;

			~BufferViewAccess() noexcept = default;

			/// @brief Gets the buffer view.
			/// @return Buffer view.
			[[nodiscard("Pure function")]]
			const PonyBase::Container::BufferView<T>& BufferView() const noexcept;

			/// @brief Sets the value by the index.
			/// @param index Value index.
			/// @param value Value to set.
			void Set(std::size_t index, const T& value) noexcept;
			/// @brief Sets the data.
			/// @note offset + data.size() must not exceed a target buffer size.
			/// @param offset Data destination offset.
			/// @param data Data to set.
			void Set(std::size_t offset, std::span<const T> data) noexcept;

			BufferViewAccess& operator =(const BufferViewAccess& other) noexcept = default;
			BufferViewAccess& operator =(BufferViewAccess&& other) noexcept = default;

		private:
			/// @brief Creates a buffer view access.
			/// @param bufferView Buffer view.
			/// @param mesh Mesh.
			/// @param dataIndex Data index.
			/// @param bufferIndex Buffer index.
			[[nodiscard("Pure constructor")]]
			BufferViewAccess(const PonyBase::Container::BufferView<T>& bufferView, Mesh& mesh, std::uint32_t dataIndex, std::uint32_t bufferIndex) noexcept;

			PonyBase::Container::BufferView<T> bufferView; ///< Buffer view.
			Mesh* mesh; ///< Mesh.
			std::uint32_t dataIndex; ///< Data index.
			std::uint32_t bufferIndex; ///< Buffer index.

			friend Mesh;
			friend BufferTableAccess;
		};

		/// @brief Buffer table access wrapper
		class BufferTableAccess final
		{
		public:
			[[nodiscard("Pure constructor")]]
			BufferTableAccess(const BufferTableAccess& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			BufferTableAccess(BufferTableAccess&& other) noexcept = default;

			~BufferTableAccess() noexcept = default;

			/// @brief Gets the buffer count.
			/// @return Buffer count.
			[[nodiscard("Pure function")]]
			std::size_t BufferCount() const noexcept;

			/// @brief Gets the buffer access by the index.
			/// @param index Buffer index.
			/// @return Buffer access.
			[[nodiscard("Pure function")]]
			BufferAccess Buffer(std::uint32_t index) noexcept;
			/// @brief Gets the buffer by the index.
			/// @param index Buffer index.
			/// @return Buffer.
			[[nodiscard("Pure function")]]
			const PonyBase::Container::Buffer& Buffer(std::uint32_t index) const noexcept;

			/// @brief Gets the buffer view access by the index.
			/// @param index Buffer index.
			/// @return Buffer view access.
			template<typename T> [[nodiscard("Pure function")]]
			BufferViewAccess<T> BufferView(std::uint32_t index);
			/// @brief Gets the buffer view by the index.
			/// @param index Buffer index.
			/// @return Buffer view.
			template<typename T> [[nodiscard("Pure function")]]
			PonyBase::Container::BufferView<const T> BufferView(std::uint32_t index) const;

			BufferTableAccess& operator =(const BufferTableAccess& other) noexcept = default;
			BufferTableAccess& operator =(BufferTableAccess&& other) noexcept = default;

		private:
			/// @brief Creates a buffer table access.
			/// @param buffers Buffers.
			/// @param mesh Mesh.
			/// @param dataIndex Data index.
			[[nodiscard("Pure constructor")]]
			BufferTableAccess(std::span<PonyBase::Container::Buffer> buffers, Mesh& mesh, std::uint32_t dataIndex) noexcept;

			std::span<PonyBase::Container::Buffer> buffers; ///< Buffers.
			Mesh* mesh; ///< Mesh.
			std::uint32_t dataIndex; ///< Data index.

			friend Mesh;
		};

		/// @brief Creates an empty mesh with zero thread group counts.
		[[nodiscard("Pure constructor")]]
		Mesh() noexcept = default;
		/// @brief Creates a mesh.
		/// @param params Mesh parameters
		[[nodiscard("Pure constructor")]]
		explicit Mesh(const MeshParams& params);
		/// @brief Creates a mesh.
		/// @param params Mesh parameters
		[[nodiscard("Pure constructor")]]
		explicit Mesh(MeshParams&& params);
		/// @brief Creates an empty mesh with defined thread group counts.
		/// @param threadGroupCounts Thread group counts.
		[[nodiscard("Pure constructor")]]
		explicit Mesh(const PonyShader::Core::ThreadGroupCounts& threadGroupCounts) noexcept;
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other);
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept;

		~Mesh() noexcept = default;

		/// @brief Creates a buffer table inside the mesh or replaces an existing one.
		/// @note The @p bufferParams mustn't be empty.
		/// @note The mesh buffer count mustn't exceed std::uint32_t max value.
		/// @param dataType Data type.
		/// @param bufferParams Buffer parameters. Each element describes an individual buffer in the table.
		/// @return Buffer table access to a created table. It may be invalid if the mesh structure is changed.
		BufferTableAccess CreateBufferTable(std::string_view dataType, std::span<const PonyBase::Container::BufferParams> bufferParams);
		/// @brief Destroys a buffer table by the data type.
		/// @param dataType Data type.
		void DestroyBufferTable(std::string_view dataType) noexcept;

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
		/// @brief Tries to find a buffer count by the @p dataType.
		/// @param dataType Data type.
		/// @return Buffer count; std::nullopt if such a data type isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> BufferCount(std::string_view dataType) const noexcept;
		/// @brief Gets the buffer count of all the tables.
		/// @return Buffer count.
		[[nodiscard("Pure function")]]
		std::uint32_t BufferCount() const noexcept;

		/// @brief Gets a buffer access.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		/// @return Buffer access. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		BufferAccess Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) noexcept;
		/// @brief Gets the buffer.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		/// @return Buffer. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) const noexcept;
		/// @brief Gets the buffer.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		/// @return Buffer. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& BufferConst(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) const noexcept;
		/// @brief Tries to find a buffer.
		/// @param dataType Data type.
		/// @param bufferIndex Buffer index.
		/// @return Buffer access; std::nullopt if such a data type isn't found. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		std::optional<BufferAccess> Buffer(std::string_view dataType, std::uint32_t bufferIndex = 0u) noexcept;
		/// @brief Tries to find a buffer.
		/// @param dataType Data type.
		/// @param bufferIndex Buffer index.
		/// @return Buffer; nullptr if such a data type isn't found. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer* Buffer(std::string_view dataType, std::uint32_t bufferIndex = 0u) const noexcept;
		/// @brief Tries to find a buffer.
		/// @param dataType Data type.
		/// @param bufferIndex Buffer index.
		/// @return Buffer; nullptr if such a data type isn't found. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer* BufferConst(std::string_view dataType, std::uint32_t bufferIndex = 0u) const noexcept;

		/// @brief Gets a buffer view access.
		/// @tparam T Value type.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		/// @return Buffer view access. It may be invalidated if the mesh structure is changed.
		template<typename T> [[nodiscard("Pure function")]]
		BufferViewAccess<T> Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) noexcept;
		/// @brief Gets a buffer view.
		/// @tparam T Value type.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		/// @return Buffer view. It may be invalidated if the mesh structure is changed.
		template<typename T> [[nodiscard("Pure function")]]
		PonyBase::Container::BufferView<const T> Buffer(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) const noexcept;
		/// @brief Gets a buffer view.
		/// @tparam T Value type.
		/// @param dataIndex Data index.
		/// @param bufferIndex Buffer index.
		/// @return Buffer view. It may be invalidated if the mesh structure is changed.
		template<typename T> [[nodiscard("Pure function")]]
		PonyBase::Container::BufferView<const T> BufferConst(std::uint32_t dataIndex, std::uint32_t bufferIndex = 0u) const noexcept;
		/// @brief Tries to find a buffer view access.
		/// @tparam T Value type.
		/// @param dataType Data type.
		/// @param bufferIndex Buffer index.
		/// @return Buffer view access; std::nullopt if such a data type isn't found. It may be invalidated if the mesh structure is changed.
		template<typename T> [[nodiscard("Pure function")]]
		std::optional<BufferViewAccess<T>> Buffer(std::string_view dataType, std::uint32_t bufferIndex = 0u) noexcept;
		/// @brief Tries to find a buffer view.
		/// @tparam T Value type.
		/// @param dataType Data type.
		/// @param bufferIndex Buffer index.
		/// @return Buffer view; std::nullopt if such a data type isn't found. It may be invalidated if the mesh structure is changed.
		template<typename T> [[nodiscard("Pure function")]]
		std::optional<PonyBase::Container::BufferView<const T>> Buffer(std::string_view dataType, std::uint32_t bufferIndex = 0u) const noexcept;
		/// @brief Tries to find a buffer view.
		/// @tparam T Value type.
		/// @param dataType Data type.
		/// @param bufferIndex Buffer index.
		/// @return Buffer view; std::nullopt if such a data type isn't found. It may be invalidated if the mesh structure is changed.
		template<typename T> [[nodiscard("Pure function")]]
		std::optional<PonyBase::Container::BufferView<const T>> BufferConst(std::string_view dataType, std::uint32_t bufferIndex = 0u) const noexcept;

		/// @brief Gets a buffer table access by the @p dataIndex.
		/// @param dataIndex Data index.
		/// @return Buffer table access. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		BufferTableAccess BufferTable(std::uint32_t dataIndex) noexcept;
		/// @brief Gets buffers by the @p dataIndex.
		/// @param dataIndex Data index.
		/// @return Buffers. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> BufferTable(std::uint32_t dataIndex) const noexcept;
		/// @brief Gets buffers by the @p dataIndex.
		/// @param dataIndex Data index.
		/// @return Buffers. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> BufferTableConst(std::uint32_t dataIndex) const noexcept;
		/// @brief Tries to find a buffer table access by the @p dataType.
		/// @param dataType Data type.
		/// @return Buffer table access; std::nullopt if such a data type isn't found. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		std::optional<BufferTableAccess> BufferTable(std::string_view dataType) noexcept;
		/// @brief Tries to find a buffer table by the @p dataType.
		/// @param dataType Data type.
		/// @return Buffer table; std::nullopt if such a data type isn't found. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> BufferTable(std::string_view dataType) const noexcept;
		/// @brief Tries to find a buffer table by the @p dataType.
		/// @param dataType Data type.
		/// @return Buffer table; std::nullopt if such a data type isn't found. It may be invalidated if the mesh structure is changed.
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Container::Buffer> BufferTableConst(std::string_view dataType) const noexcept;

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
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string&& name);

		/// @brief Adds the observer.
		/// @param observer Observer to add. It must be unique. It must live longer than the mesh.
		void AddObserver(IMeshObserver& observer) const;
		/// @brief Removes the observer.
		/// @param observer Observer to remove.
		void RemoveObserver(IMeshObserver& observer) const noexcept;

		Mesh& operator =(const Mesh& other);
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

		std::vector<std::string> dataTypes; ///< Data types.
		std::vector<std::vector<PonyBase::Container::Buffer>> bufferTables; ///< Buffer tables.

		PonyShader::Core::ThreadGroupCounts threadGroupCounts; ///< Thread group counts.
		std::optional<PonyMath::Shape::AABB<float>> boundingBox; ///< Bounding box.

		std::string name; ///< Mesh name.

		mutable std::vector<IMeshObserver*> meshObservers; ///< Mesh observers.
	};
}

namespace PonyEngine::Render
{
	Mesh::BufferAccess::BufferAccess(PonyBase::Container::Buffer& buffer, Mesh& mesh, const std::uint32_t dataIndex, const std::uint32_t bufferIndex) noexcept :
		buffer{&buffer},
		mesh{&mesh},
		dataIndex{dataIndex},
		bufferIndex{bufferIndex}
	{
	}

	const PonyBase::Container::Buffer& Mesh::BufferAccess::Buffer() const noexcept
	{
		return *buffer;
	}

	void Mesh::BufferAccess::Set(const std::size_t index, const std::byte value) noexcept
	{
		buffer->Data()[index] = value;
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	void Mesh::BufferAccess::Set(const std::size_t offset, std::span<const std::byte> data)
	{
		if (data.size() + offset > buffer->Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of bounds.");
		}

		std::ranges::copy(data, buffer->Data() + offset);
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	template<typename T>
	void Mesh::BufferAccess::Set(const std::size_t index, const T& value) noexcept
	{
		buffer->Get<T>(index) = value;
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	template<typename T>
	void Mesh::BufferAccess::Set(const std::size_t offset, const std::span<const T> data) noexcept
	{
		if ((data.size() + offset) * sizeof(T) > buffer->Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of bounds.");
		}

		std::ranges::copy(data, &buffer->Get<T>(offset));
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	template<typename T>
	Mesh::BufferViewAccess<T>::BufferViewAccess(const PonyBase::Container::BufferView<T>& bufferView, Mesh& mesh, const std::uint32_t dataIndex, const std::uint32_t bufferIndex) noexcept :
		bufferView(bufferView),
		mesh{&mesh},
		dataIndex{dataIndex},
		bufferIndex{bufferIndex}
	{
	}


	template<typename T>
	const PonyBase::Container::BufferView<T>& Mesh::BufferViewAccess<T>::BufferView() const noexcept
	{
		return bufferView;
	}

	template<typename T>
	void Mesh::BufferViewAccess<T>::Set(const std::size_t index, const T& value) noexcept
	{
		bufferView[index] = value;
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	template<typename T>
	void Mesh::BufferViewAccess<T>::Set(const std::size_t offset, std::span<const T> data) noexcept
	{
		if (data.size() + offset > bufferView.Span().size()) [[unlikely]]
		{
			throw std::out_of_range("Out of bounds.");
		}

		std::ranges::copy(data, bufferView.Data() + offset);
		mesh->OnBufferChanged(dataIndex, bufferIndex);
	}

	Mesh::BufferTableAccess::BufferTableAccess(const std::span<PonyBase::Container::Buffer> buffers, Mesh& mesh, const std::uint32_t dataIndex) noexcept :
		buffers(buffers),
		mesh{&mesh},
		dataIndex{dataIndex}
	{
	}

	std::size_t Mesh::BufferTableAccess::BufferCount() const noexcept
	{
		return buffers.size();
	}

	Mesh::BufferAccess Mesh::BufferTableAccess::Buffer(const std::uint32_t index) noexcept
	{
		return BufferAccess(buffers[index], *mesh, dataIndex, index);
	}

	const PonyBase::Container::Buffer& Mesh::BufferTableAccess::Buffer(const std::uint32_t index) const noexcept
	{
		return buffers[index];
	}

	template<typename T>
	Mesh::BufferViewAccess<T> Mesh::BufferTableAccess::BufferView(const std::uint32_t index)
	{
		return BufferViewAccess<T>(PonyBase::Container::BufferView<T>(&buffers[index]), *mesh, dataIndex, index);
	}

	template<typename T>
	PonyBase::Container::BufferView<const T> Mesh::BufferTableAccess::BufferView(const std::uint32_t index) const
	{
		return PonyBase::Container::BufferView<const T>(&buffers[index]);
	}

	Mesh::Mesh(const MeshParams& params) :
		threadGroupCounts(params.threadGroupCounts),
		boundingBox(params.boundingBox),
		name(params.name)
	{
		std::size_t bufferCount = 0;
		for (const auto& [dataType, bufferTable] : params.bufferTables)
		{
			if (bufferTable.size() == 0) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Data table of '{}' is empty.", dataType));
			}
			bufferCount += bufferTable.size();
		}
		if (bufferCount > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count exceeds std::uint32_t max value.");
		}

		dataTypes.reserve(params.bufferTables.size());
		bufferTables.reserve(params.bufferTables.size());

		for (const auto& [dataType, bufferTable] : params.bufferTables)
		{
			dataTypes.push_back(dataType);
			bufferTables.push_back(bufferTable);
		}
	}

	Mesh::Mesh(MeshParams&& params) :
		threadGroupCounts(std::move(params.threadGroupCounts)),
		boundingBox(std::move(params.boundingBox)),
		name(std::move(params.name))
	{
		std::size_t bufferCount = 0;
		for (const auto& [dataType, bufferTable] : params.bufferTables)
		{
			if (bufferTable.size() == 0) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Data table of '{}' is empty.", dataType));
			}
			bufferCount += bufferTable.size();
		}
		if (bufferCount > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count exceeds std::uint32_t max value.");
		}

		dataTypes.reserve(params.bufferTables.size());
		bufferTables.reserve(params.bufferTables.size());

		for (const auto& [dataType, bufferTable] : params.bufferTables)
		{
			dataTypes.push_back(std::move(dataType));
			bufferTables.push_back(std::move(bufferTable));
		}
	}

	Mesh::Mesh(const PonyShader::Core::ThreadGroupCounts& threadGroupCounts) noexcept :
		threadGroupCounts(threadGroupCounts)
	{
	}

	Mesh::Mesh(const Mesh& other) :
		dataTypes(other.dataTypes),
		bufferTables(other.bufferTables),
		threadGroupCounts(other.threadGroupCounts),
		boundingBox(other.boundingBox),
		name(other.name)
	{
	}

	Mesh::Mesh(Mesh&& other) noexcept :
		dataTypes(std::move(other.dataTypes)),
		bufferTables(std::move(other.bufferTables)),
		threadGroupCounts(std::move(other.threadGroupCounts)),
		boundingBox(std::move(other.boundingBox)),
		name(std::move(other.name))
	{
	}

	Mesh::BufferTableAccess Mesh::CreateBufferTable(const std::string_view dataType, const std::span<const PonyBase::Container::BufferParams> bufferParams)
	{
		if (bufferParams.size() == 0) [[unlikely]]
		{
			throw std::invalid_argument("Buffer params is empty.");
		}
		if (bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count exceeds std::uint32_t max value.");
		}

		auto buffers = std::vector<PonyBase::Container::Buffer>();
		buffers.reserve(bufferParams.size());
		for (const PonyBase::Container::BufferParams& bufferParam : bufferParams)
		{
			buffers.push_back(PonyBase::Container::Buffer(bufferParam));
		}

		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			if (BufferCount() - BufferCount(dataIndex.value()) + bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Buffer count will exceed std::uint32_t max value.");
			}
			bufferTables[dataIndex.value()] = std::move(buffers);

			OnMeshChanged();

			return BufferTableAccess(bufferTables[dataIndex.value()], *this, dataIndex.value());
		}

		if (BufferCount() + bufferParams.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer count will exceed std::uint32_t max value.");
		}

		const std::size_t currentSize = dataTypes.size();
		try
		{
			dataTypes.push_back(std::string(dataType));
			bufferTables.push_back(std::move(buffers));
		}
		catch (...)
		{
			dataTypes.resize(currentSize);
			bufferTables.resize(currentSize);

			throw;
		}

		OnMeshChanged();

		return BufferTableAccess(bufferTables.back(), *this, static_cast<std::uint32_t>(currentSize));
	}

	void Mesh::DestroyBufferTable(const std::string_view dataType) noexcept
	{
		if (const std::optional<std::size_t> tableIndex = DataIndex(dataType))
		{
			dataTypes.erase(dataTypes.begin() + tableIndex.value());
			bufferTables.erase(bufferTables.begin() + tableIndex.value());
			OnMeshChanged();
		}
	}

	std::optional<std::uint32_t> Mesh::DataIndex(const std::string_view dataType) const noexcept
	{
		for (std::uint32_t i = 0; i < dataTypes.size(); ++i)
		{
			if (dataTypes[i] == dataType)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	std::string_view Mesh::DataType(const std::uint32_t dataIndex) const noexcept
	{
		return dataTypes[dataIndex];
	}

	std::uint32_t Mesh::DataTypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(dataTypes.size());
	}

	std::span<const std::string> Mesh::DataTypes() const noexcept
	{
		return dataTypes;
	}

	std::uint32_t Mesh::BufferCount(const std::uint32_t dataIndex) const noexcept
	{
		return static_cast<std::uint32_t>(bufferTables[dataIndex].size());
	}

	std::optional<std::uint32_t> Mesh::BufferCount(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferCount(dataIndex.value());
		}

		return std::nullopt;
	}

	std::uint32_t Mesh::BufferCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (std::uint32_t i = 0u; i < dataTypes.size(); ++i)
		{
			count += BufferCount(i);
		}

		return count;
	}

	Mesh::BufferAccess Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) noexcept
	{
		return BufferAccess(bufferTables[dataIndex][bufferIndex], *this, dataIndex, bufferIndex);
	}

	const PonyBase::Container::Buffer& Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return bufferTables[dataIndex][bufferIndex];
	}

	const PonyBase::Container::Buffer& Mesh::BufferConst(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return Buffer(dataIndex, bufferIndex);
	}

	std::optional<Mesh::BufferAccess> Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType) && bufferIndex < BufferCount(dataIndex.value()))
		{
			return Buffer(dataIndex.value(), bufferIndex);
		}

		return std::nullopt;
	}

	const PonyBase::Container::Buffer* Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType) && bufferIndex < BufferCount(dataIndex.value()))
		{
			return &Buffer(dataIndex.value(), bufferIndex);
		}

		return nullptr;
	}

	const PonyBase::Container::Buffer* Mesh::BufferConst(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		return Buffer(dataType, bufferIndex);
	}

	template<typename T>
	Mesh::BufferViewAccess<T> Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) noexcept
	{
		return BufferViewAccess<T>(PonyBase::Container::BufferView<T>(bufferTables[dataIndex]), *this, dataIndex, bufferIndex);
	}

	template<typename T>
	PonyBase::Container::BufferView<const T> Mesh::Buffer(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return PonyBase::Container::BufferView<const T>(bufferTables[dataIndex][bufferIndex]);
	}

	template<typename T>
	PonyBase::Container::BufferView<const T> Mesh::BufferConst(const std::uint32_t dataIndex, const std::uint32_t bufferIndex) const noexcept
	{
		return Buffer<T>(dataIndex, bufferIndex);
	}

	template<typename T>
	std::optional<Mesh::BufferViewAccess<T>> Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			if (const std::vector<PonyBase::Container::Buffer>& table = bufferTables[dataIndex.value()]; bufferIndex < table.size() && table[bufferIndex].Stride() == sizeof(T))
			{
				return Buffer(dataIndex.value(), bufferIndex);
			}
		}

		return std::nullopt;
	}

	template<typename T>
	std::optional<PonyBase::Container::BufferView<const T>> Mesh::Buffer(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			if (const std::vector<PonyBase::Container::Buffer>& table = bufferTables[dataIndex.value()]; bufferIndex < table.size() && table[bufferIndex].Stride() == sizeof(T))
			{
				return Buffer(dataIndex.value(), bufferIndex);
			}
		}

		return std::nullopt;
	}

	template<typename T>
	std::optional<PonyBase::Container::BufferView<const T>> Mesh::BufferConst(const std::string_view dataType, const std::uint32_t bufferIndex) const noexcept
	{
		return Buffer<T>(dataType, bufferIndex);
	}

	Mesh::BufferTableAccess Mesh::BufferTable(const std::uint32_t dataIndex) noexcept
	{
		return BufferTableAccess(bufferTables[dataIndex], *this, dataIndex);
	}

	std::span<const PonyBase::Container::Buffer> Mesh::BufferTable(const std::uint32_t dataIndex) const noexcept
	{
		return bufferTables[dataIndex];
	}

	std::span<const PonyBase::Container::Buffer> Mesh::BufferTableConst(const std::uint32_t dataIndex) const noexcept
	{
		return bufferTables[dataIndex];
	}

	std::optional<Mesh::BufferTableAccess> Mesh::BufferTable(const std::string_view dataType) noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferTable(dataIndex.value());
		}

		return std::nullopt;
	}

	std::span<const PonyBase::Container::Buffer> Mesh::BufferTable(const std::string_view dataType) const noexcept
	{
		if (const std::optional<std::uint32_t> dataIndex = DataIndex(dataType))
		{
			return BufferTable(dataIndex.value());
		}

		return std::span<const PonyBase::Container::Buffer>();
	}

	std::span<const PonyBase::Container::Buffer> Mesh::BufferTableConst(const std::string_view dataType) const noexcept
	{
		return BufferTable(dataType);
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

	void Mesh::Name(std::string&& name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = std::move(name);
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
		std::vector<std::string> newDataTypes = other.dataTypes;
		std::vector<std::vector<PonyBase::Container::Buffer>> newBufferTables = other.bufferTables;
		std::optional<std::string> newName = name == other.name ? std::nullopt : std::optional(other.name);

		dataTypes = std::move(newDataTypes);
		bufferTables = std::move(newBufferTables);
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
		dataTypes = std::move(other.dataTypes);
		bufferTables = std::move(other.bufferTables);
		OnMeshChanged();

		ThreadGroupCounts(other.threadGroupCounts);
		BoundingBox(std::move(other.boundingBox));

		Name(std::move(other.name));

		return *this;
	}
}

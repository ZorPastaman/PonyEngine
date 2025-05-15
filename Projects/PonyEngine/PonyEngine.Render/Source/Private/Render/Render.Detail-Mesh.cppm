/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:Mesh;

import <cstddef>;
import <cstdint>;
import <optional>;
import <span>;
import <string>;
import <string_view>;

import PonyBase.Container;

import PonyMath.Shape;

import PonyShader.Core;

import PonyEngine.Render;

import :BufferData;
import :MeshDirtyFlag;

export namespace PonyEngine::Render
{
	/// @brief Mesh.
	class Mesh final : public IMesh
	{
	public:
		/// @brief Creates a mesh.
		/// @param params Mesh parameters.
		[[nodiscard("Pure constructor")]]
		explicit Mesh(const MeshParams& params);
		Mesh(const Mesh&) = delete;
		Mesh(Mesh&&) = delete;

		~Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindDataTypeIndex(std::string_view dataType) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view DataType(std::uint32_t dataTypeIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataTypeCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;
		virtual void Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::span<const std::byte> data) override;
		[[nodiscard("Pure function")]]
		virtual std::size_t DataSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataCount(std::uint32_t dataTypeIndex) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex) const noexcept override;
		virtual void Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex, std::span<const std::byte> element) override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t ElementSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t ElementCount(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;

		virtual std::uint32_t CreateData(std::string_view dataType, std::span<const PonyBase::Container::BufferParams> dataParams) override;
		virtual void DestroyData(std::uint32_t dataTypeIndex) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyShader::Core::ThreadGroupCounts& ThreadGroupCounts() const noexcept override;
		virtual void ThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& counts) override;

		[[nodiscard("Pure function")]]
		virtual const std::optional<PonyMath::Shape::AABB<float>>& BoundingBox() const noexcept override;
		virtual void BoundingBox(const std::optional<PonyMath::Shape::AABB<float>>& box) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the dirty flags.
		/// @return Dirty flags.
		[[nodiscard("Pure function")]]
		MeshDirtyFlag DirtyFlags() const noexcept;
		/// @brief Resets the dirty flags.
		void ResetDirty() noexcept;

		Mesh& operator =(const Mesh&) = delete;
		Mesh& operator =(Mesh&&) = delete;

	private:
		BufferData bufferData; ///< Buffer data.

		PonyShader::Core::ThreadGroupCounts threadGroupCounts; ///< Thread group counts.
		std::optional<PonyMath::Shape::AABB<float>> boundingBox; ///< Bounding box.

		std::string name; ///< Mesh name.

		MeshDirtyFlag dirtyFlags; ///< Dirty flags.
	};
}

namespace PonyEngine::Render
{
	Mesh::Mesh(const MeshParams& params) :
		bufferData(params.data),
		threadGroupCounts(params.threadGroupCounts),
		boundingBox(params.boundingBox),
		name(params.name),
		dirtyFlags{MeshDirtyFlag::All}
	{
	}

	std::optional<std::uint32_t> Mesh::FindDataTypeIndex(const std::string_view dataType) const noexcept
	{
		return bufferData.DataTypeIndex(dataType);
	}

	std::string_view Mesh::DataType(const std::uint32_t dataTypeIndex) const noexcept
	{
		return bufferData.DataType(dataTypeIndex);
	}

	std::uint32_t Mesh::DataTypeCount() const noexcept
	{
		return bufferData.DataTypeCount();
	}

	std::span<const std::byte> Mesh::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.GetData(dataTypeIndex, dataIndex);
	}

	void Mesh::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::span<const std::byte> data)
	{
		bufferData.SetData(dataTypeIndex, dataIndex, data);
		dirtyFlags |= MeshDirtyFlag::Data;
	}

	std::size_t Mesh::DataSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.DataSize(dataTypeIndex, dataIndex);
	}

	std::uint32_t Mesh::DataCount(const std::uint32_t dataTypeIndex) const noexcept
	{
		return bufferData.DataCount(dataTypeIndex);
	}

	std::span<const std::byte> Mesh::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex) const noexcept
	{
		return bufferData.GetData(dataTypeIndex, dataIndex, elementIndex);
	}

	void Mesh::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex, const std::span<const std::byte> element)
	{
		bufferData.SetData(dataTypeIndex, dataIndex, elementIndex, element);
		dirtyFlags |= MeshDirtyFlag::Data;
	}

	std::uint32_t Mesh::ElementSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.ElementSize(dataTypeIndex, dataIndex);
	}

	std::uint32_t Mesh::ElementCount(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.ElementCount(dataTypeIndex, dataIndex);
	}

	std::uint32_t Mesh::CreateData(const std::string_view dataType, const std::span<const PonyBase::Container::BufferParams> dataParams)
	{
		const std::uint32_t index = bufferData.Create(dataType, dataParams);
		dirtyFlags |= MeshDirtyFlag::DataStructure;

		return index;
	}

	void Mesh::DestroyData(const std::uint32_t dataTypeIndex) noexcept
	{
		bufferData.Destroy(dataTypeIndex);
		dirtyFlags |= MeshDirtyFlag::DataStructure;
	}

	const PonyShader::Core::ThreadGroupCounts& Mesh::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Mesh::ThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& counts)
	{
		threadGroupCounts = counts;
	}

	const std::optional<PonyMath::Shape::AABB<float>>& Mesh::BoundingBox() const noexcept
	{
		return boundingBox;
	}

	void Mesh::BoundingBox(const std::optional<PonyMath::Shape::AABB<float>>& box)
	{
		boundingBox = box;
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
		dirtyFlags |= MeshDirtyFlag::Name;
	}

	MeshDirtyFlag Mesh::DirtyFlags() const noexcept
	{
		return dirtyFlags;
	}

	void Mesh::ResetDirty() noexcept
	{
		dirtyFlags = MeshDirtyFlag::None;
	}
}

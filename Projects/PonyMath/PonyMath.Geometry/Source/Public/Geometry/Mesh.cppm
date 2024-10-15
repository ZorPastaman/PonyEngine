/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyMath.Geometry:Mesh;

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <limits>;
import <stdexcept>;
import <span>;
import <utility>;
import <vector>;

import PonyMath.Core;

export namespace PonyMath::Geometry
{
	/// @brief Mesh implementation.
	/// @remark Vertex colors are optional.
	class Mesh final
	{
	public:
		using VertexType = Core::Vector3<float>; ///< Vertex type.
		using TriangleType = Core::Vector3<std::uint32_t>; ///< Triangle type.
		using VertexColorType = Core::RGBA<float>; ///< Vertex color type.

		/// @brief Creates an empty mesh.
		[[nodiscard("Pure constructor")]]
		Mesh() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other) = default;
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept = default;

		~Mesh() noexcept = default;

		/// @brief Gets the vertex count.
		/// @return Vertex count.
		[[nodiscard("Pure function")]]
		std::uint32_t VertexCount() const noexcept;
		/// @brief Sets the vertex count.
		/// @param vertexCount New vertex count.
		/// @remark If the new vertex count is less than the current vertex count, the triangles will be cleared;
		/// @remark If the new vertex count is greater than the current vertex count, the triangles will remain;
		/// @remark If the mesh has vertex colors, their array will be resized appropriately.
		void VertexCount(std::uint32_t vertexCount);

		/// @brief Gets the triangle count.
		/// @return Triangle count.
		[[nodiscard("Pure function")]]
		std::size_t TriangleCount() const noexcept;
		/// @brief Sets triangle count.
		/// @note Vertex count must be set first.
		/// @note It throws if the vertex array is empty and you try to set the triangle count more than zero.
		/// @param triangleCount New triangle count.
		void TriangleCount(std::size_t triangleCount);

		/// @brief Checks if the vertex color array isn't empty.
		/// @return @a True if it's not empty; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasColors() const noexcept;
		/// @brief Creates or destroys the vertex color array.
		/// @remark The vertex color count is either empty or the same as vertex count.
		/// @param hasColors If it's @a true, the vertex color array is created; if it's @a false, the vertex color array is destroyed.
		void HasColors(bool hasColors);

		/// @brief Gets a vertex by the index.
		/// @param vertexIndex Vertex index.
		/// @return Vertex.
		[[nodiscard("Pure function")]]
		const Core::Vector3<float>& Vertex(std::uint32_t vertexIndex) const noexcept;
		/// @brief Sets a vertex by the index.
		/// @param vertexIndex Vertex index.
		/// @param vertex Vertex to set.
		void Vertex(std::uint32_t vertexIndex, const Core::Vector3<float>& vertex) noexcept;
		/// @brief Gets the vertices.
		/// @return Vertices.
		[[nodiscard("Pure function")]]
		std::span<const Core::Vector3<float>> Vertices() const noexcept;
		/// @brief Sets the vertices.
		/// @details The function resizes the vertex array to the @p verticesToSet size.
		/// @note It throws if the @p verticesToSet size exceeds uint32 max value.
		/// @params verticesToSet Vertices to set.
		void Vertices(std::span<const Core::Vector3<float>> verticesToSet);

		/// @brief Gets a triangle by the index.
		/// @param triangleIndex Triangle index.
		/// @return Triangle.
		[[nodiscard("Pure function")]]
		const Core::Vector3<std::uint32_t>& Triangle(std::size_t triangleIndex) const noexcept;
		/// @brief Sets a triangle by the index.
		/// @note The @p triangle mustn't be out of vertex bounds.
		/// @param triangleIndex Triangle index.
		/// @param triangle Triangle to set.
		void Triangle(std::size_t triangleIndex, const Core::Vector3<std::uint32_t>& triangle);
		/// @brief Gets the triangles.
		/// @return Triangles.
		[[nodiscard("Pure function")]]
		std::span<const Core::Vector3<std::uint32_t>> Triangles() const noexcept;
		/// @brief Sets the triangles.
		/// @details The function resizes the triangle array to the @p trianglesToSet size.
		/// @note The @p trianglesToSet mustn't be out of vertex bounds.
		/// @param trianglesToSet Triangles to set.
		void Triangles(std::span<const Core::Vector3<std::uint32_t>> trianglesToSet);

		/// @brief Gets a vertex color by the index.
		/// @param vertexIndex Vertex index.
		/// @return Vertex color.
		[[nodiscard("Pure function")]]
		const Core::RGBA<float>& Color(std::uint32_t vertexIndex) const noexcept;
		/// @brief Sets a vertex color by the index.
		/// @param vertexIndex Vertex index.
		/// @param color Vertex color to set.
		void Color(std::uint32_t vertexIndex, const Core::RGBA<float>& color) noexcept;
		/// @brief Gets vertex colors.
		/// @return Vertex colors.
		[[nodiscard("Pure function")]]
		std::span<const Core::RGBA<float>> Colors() const noexcept;
		/// @brief Sets vertex colors.
		/// @note The @p colorsToSet size must be either zero or the same as current vertex count.
		/// @param colorsToSet Vertex colors to set.
		void Colors(std::span<const Core::RGBA<float>> colorsToSet);

		Mesh& operator =(const Mesh& other) = default;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		std::vector<Core::Vector3<float>> vertices; ///< Vertices.
		std::vector<Core::Vector3<std::uint32_t>> triangles; ///< Triangles.

		std::vector<Core::RGBA<float>> colors; ///< Vertex colors.
	};
}

namespace PonyMath::Geometry
{
	std::uint32_t Mesh::VertexCount() const noexcept
	{
		return static_cast<std::uint32_t>(vertices.size());
	}

	void Mesh::VertexCount(const std::uint32_t vertexCount)
	{
		if (vertexCount == VertexCount())
		{
			return;
		}

		if (vertexCount < VertexCount())
		{
			vertices.resize(vertexCount);
			triangles.clear(); // Any triangle may become invalid.

			if (HasColors())
			{
				colors.resize(vertexCount);
			}

			return;
		}

		// The function doesn't resize here because any resize may throw an exception and corrupt a state of the mesh.
		auto newVertices = std::vector<Core::Vector3<float>>(vertexCount);
		std::ranges::copy(vertices, newVertices.begin());

		auto newColors = std::vector<Core::RGBA<float>>(HasColors() ? vertexCount : 0);
		std::ranges::copy(colors, newColors.begin());

		vertices = std::move(newVertices);
		// Any triangle stays valid.

		colors = std::move(newColors);
	}

	std::size_t Mesh::TriangleCount() const noexcept
	{
		return triangles.size();
	}

	void Mesh::TriangleCount(const std::size_t triangleCount)
	{
		if (triangleCount > 0 && vertices.size() < 1) [[unlikely]]
		{
			throw std::logic_error("Triangles can't exist if there's no vertex in the mesh.");
		}

		triangles.resize(triangleCount);
	}

	bool Mesh::HasColors() const noexcept
	{
		return colors.size() > 0;
	}

	void Mesh::HasColors(const bool hasColors)
	{
		colors.resize(hasColors ? VertexCount() : 0);
	}

	const Core::Vector3<float>& Mesh::Vertex(const std::uint32_t vertexIndex) const noexcept
	{
		return vertices[vertexIndex];
	}

	void Mesh::Vertex(const std::uint32_t vertexIndex, const Core::Vector3<float>& vertex) noexcept
	{
		vertices[vertexIndex] = vertex;
	}

	std::span<const Core::Vector3<float>> Mesh::Vertices() const noexcept
	{
		return vertices;
	}

	void Mesh::Vertices(std::span<const Core::Vector3<float>> verticesToSet)
	{
		if (verticesToSet.size() > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Vertex count can't exceed std::uint32_t max value.");
		}

		VertexCount(static_cast<std::uint32_t>(verticesToSet.size()));
		std::ranges::copy(verticesToSet, vertices.begin());
	}

	const Core::Vector3<std::uint32_t>& Mesh::Triangle(const std::size_t triangleIndex) const noexcept
	{
		return triangles[triangleIndex];
	}

	void Mesh::Triangle(const std::size_t triangleIndex, const Core::Vector3<std::uint32_t>& triangle)
	{
		const std::uint32_t vertexCount = VertexCount();
		for (std::size_t i = 0; i < Core::Vector3<std::uint32_t>::ComponentCount; ++i)
		{
			if (triangle[i] >= vertexCount) [[unlikely]]
			{
				throw std::invalid_argument("Triangle is out of bounds.");
			}
		}

		triangles[triangleIndex] = triangle;
	}

	std::span<const Core::Vector3<std::uint32_t>> Mesh::Triangles() const noexcept
	{
		return triangles;
	}

	void Mesh::Triangles(const std::span<const Core::Vector3<std::uint32_t>> trianglesToSet)
	{
		for (const std::uint32_t vertexCount = VertexCount(), *current = trianglesToSet.data()->Span().data(), *const end = current + trianglesToSet.size() * Core::Vector3<std::uint32_t>::ComponentCount; 
			current != end; 
			++current)
		{
			if (*current >= vertexCount) [[unlikely]]
			{
				throw std::invalid_argument("At least one triangle is out of bounds.");
			}
		}

		TriangleCount(trianglesToSet.size());
		std::ranges::copy(trianglesToSet, triangles.begin());
	}

	const Core::RGBA<float>& Mesh::Color(const std::uint32_t vertexIndex) const noexcept
	{
		return colors[vertexIndex];
	}

	void Mesh::Color(const std::uint32_t vertexIndex, const Core::RGBA<float>& color) noexcept
	{
		colors[vertexIndex] = color;
	}

	std::span<const Core::RGBA<float>> Mesh::Colors() const noexcept
	{
		return colors;
	}

	void Mesh::Colors(const std::span<const Core::RGBA<float>> colorsToSet)
	{
		if (colorsToSet.size() == 0)
		{
			colors.resize(0);

			return;
		}

		if (colorsToSet.size() != vertices.size()) [[unlikely]]
		{
			throw std::invalid_argument("Span of new colors has incorrect size.");
		}

		colors.resize(colorsToSet.size());
		std::ranges::copy(colorsToSet, colors.begin());
	}
}

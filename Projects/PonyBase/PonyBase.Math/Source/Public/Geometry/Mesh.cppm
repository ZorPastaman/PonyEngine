/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Geometry:Mesh;

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <limits>;
import <stdexcept>;
import <span>;
import <utility>;
import <vector>;

import PonyBase.Math;

export namespace PonyBase::Geometry
{
	class Mesh final // TODO: Add docs and tests
	{
	public:
		using VertexType = Math::Vector3<float>;
		using TriangleType = Math::Vector3<std::uint32_t>;
		using VertexColorType = Math::RGBA<float>;

		[[nodiscard("Pure constructor")]]
		Mesh() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other) = default;
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept = default;

		~Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		std::uint32_t VertexCount() const noexcept;
		void VertexCount(std::uint32_t vertexCount);

		[[nodiscard("Pure function")]]
		std::size_t TriangleCount() const noexcept;
		void TriangleCount(std::size_t triangleCount);

		[[nodiscard("Pure function")]]
		const Math::Vector3<float>& Vertex(std::uint32_t vertexIndex) const noexcept;
		void Vertex(std::uint32_t vertexIndex, const Math::Vector3<float>& vertex) noexcept;
		[[nodiscard("Pure function")]]
		std::span<const Math::Vector3<float>> Vertices() const noexcept;
		void Vertices(std::span<const Math::Vector3<float>> verticesToSet);

		[[nodiscard("Pure function")]]
		const Math::Vector3<std::uint32_t>& Triangle(std::size_t triangleIndex) const noexcept;
		void Triangle(std::size_t triangleIndex, const Math::Vector3<std::uint32_t>& triangle);
		[[nodiscard("Pure function")]]
		std::span<const Math::Vector3<std::uint32_t>> Triangles() const noexcept;
		void Triangles(std::span<const Math::Vector3<std::uint32_t>> trianglesToSet);

		[[nodiscard("Pure function")]]
		const Math::RGBA<float>& Color(std::uint32_t vertexIndex) const noexcept;
		void Color(std::uint32_t vertexIndex, const Math::RGBA<float>& color) noexcept;
		[[nodiscard("Pure function")]]
		std::span<const Math::RGBA<float>> Colors() const noexcept;
		void Colors(std::span<const Math::RGBA<float>> colorsToSet);

		Mesh& operator =(const Mesh& other) = default;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		std::vector<Math::Vector3<float>> vertices;
		std::vector<Math::Vector3<std::uint32_t>> triangles;

		std::vector<Math::RGBA<float>> colors;
	};
}

namespace PonyBase::Geometry
{
	std::uint32_t Mesh::VertexCount() const noexcept
	{
		return static_cast<std::uint32_t>(vertices.size());
	}

	void Mesh::VertexCount(const std::uint32_t vertexCount)
	{
		if (vertexCount == vertices.size())
		{
			return;
		}

		if (vertexCount < vertices.size())
		{
			vertices.resize(vertexCount);

			colors.resize(colors.size() > 0 ? vertexCount : colors.size());

			triangles.clear(); // Any triangle may become invalid.

			return;
		}

		// The function doesn't resize here because any resize may throw an exception and corrupt a state of a mesh.
		auto newVertices = std::vector<Math::Vector3<float>>(vertexCount);
		std::ranges::copy(vertices, newVertices.begin());

		auto newColors = std::vector<Math::RGBA<float>>(colors.size() > 0 ? vertexCount : colors.size());
		std::ranges::copy(colors, newColors.begin());

		vertices = std::move(newVertices);
		colors = std::move(newColors);
		// Any triangle stays valid.
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

	const Math::Vector3<float>& Mesh::Vertex(const std::uint32_t vertexIndex) const noexcept
	{
		return vertices[vertexIndex];
	}

	void Mesh::Vertex(const std::uint32_t vertexIndex, const Math::Vector3<float>& vertex) noexcept
	{
		vertices[vertexIndex] = vertex;
	}

	std::span<const Math::Vector3<float>> Mesh::Vertices() const noexcept
	{
		return vertices;
	}

	void Mesh::Vertices(const std::span<const Math::Vector3<float>> verticesToSet)
	{
		if (verticesToSet.size() > std::numeric_limits<std::uint32_t>::max())
		{
			throw std::invalid_argument("Vertex count mayn't exceed std::uint32_t max value.");
		}

		VertexCount(static_cast<std::uint32_t>(verticesToSet.size()));
		std::ranges::copy(verticesToSet, vertices.begin());
	}

	const Math::Vector3<std::uint32_t>& Mesh::Triangle(const std::size_t triangleIndex) const noexcept
	{
		return triangles[triangleIndex];
	}

	void Mesh::Triangle(const std::size_t triangleIndex, const Math::Vector3<std::uint32_t>& triangle)
	{
		const std::uint32_t vertexCount = static_cast<std::uint32_t>(vertices.size());
		for (std::size_t i = 0; i < Math::Vector3<std::uint32_t>::ComponentCount; ++i)
		{
			if (triangle[i] >= vertexCount) [[unlikely]]
			{
				throw std::invalid_argument("Triangle is out of bounds.");
			}
		}

		triangles[triangleIndex] = triangle;
	}

	std::span<const Math::Vector3<std::uint32_t>> Mesh::Triangles() const noexcept
	{
		return triangles;
	}

	void Mesh::Triangles(const std::span<const Math::Vector3<std::uint32_t>> trianglesToSet)
	{
		const std::uint32_t vertexCount = static_cast<std::uint32_t>(vertices.size());
		const std::uint32_t* current = trianglesToSet.data()->Span().data();
		const std::uint32_t* const end = current + trianglesToSet.size() * Math::Vector3<std::uint32_t>::ComponentCount;
		for (; current != end; ++current)
		{
			if (*current >= vertexCount) [[unlikely]]
			{
				throw std::invalid_argument("At least one triangle is out of bounds.");
			}
		}

		TriangleCount(trianglesToSet.size());
		std::ranges::copy(trianglesToSet, triangles.begin());
	}

	const Math::RGBA<float>& Mesh::Color(const std::uint32_t vertexIndex) const noexcept
	{
		return colors[vertexIndex];
	}

	void Mesh::Color(const std::uint32_t vertexIndex, const Math::RGBA<float>& color) noexcept
	{
		colors[vertexIndex] = color;
	}

	std::span<const Math::RGBA<float>> Mesh::Colors() const noexcept
	{
		return colors;
	}

	void Mesh::Colors(const std::span<const Math::RGBA<float>> colorsToSet)
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

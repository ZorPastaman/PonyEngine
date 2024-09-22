/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:Mesh;

import <algorithm>;
import <cstddef>;
import <exception>;
import <span>;
import <vector>;

import PonyBase.Math;

export namespace PonyEngine::Render
{
	class Mesh final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Mesh() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Mesh(std::size_t vertexCount, std::size_t triangleCount);
		[[nodiscard("Pure constructor")]]
		Mesh(std::span<const PonyBase::Math::Vector3<float>> verticesToSet, std::span<const PonyBase::Math::RGBA<float>> colorsToSet, std::span<const PonyBase::Math::Vector3<std::size_t>> trianglesToSet);
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other) = default;
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept = default;

		~Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Version() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t VertexCount() const noexcept;
		void VertexCount(std::size_t vertexCount);

		[[nodiscard("Pure function")]]
		std::size_t TriangleCount() const noexcept;
		void TriangleCount(std::size_t triangleCount);

		[[nodiscard("Pure function")]]
		const PonyBase::Math::Vector3<float>& Vertex(std::size_t vertexIndex) const noexcept;
		void Vertex(std::size_t vertexIndex, const PonyBase::Math::Vector3<float>& vertex) noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Math::Vector3<float>> Vertices() const noexcept;
		void Vertices(std::span<const PonyBase::Math::Vector3<float>> verticesToSet);

		[[nodiscard("Pure function")]]
		const PonyBase::Math::RGBA<float>& Color(std::size_t vertexIndex) const noexcept;
		void Color(std::size_t vertexIndex, const PonyBase::Math::RGBA<float>& color) noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Math::RGBA<float>> Colors() const noexcept;
		void Colors(std::span<const PonyBase::Math::RGBA<float>> colorsToSet);

		[[nodiscard("Pure function")]]
		const PonyBase::Math::Vector3<std::size_t>& Triangle(std::size_t triangleIndex) const noexcept;
		void Triangle(std::size_t triangleIndex, const PonyBase::Math::Vector3<std::size_t>& triangle) noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Math::Vector3<std::size_t>> Triangles() const noexcept;
		void Triangles(std::span<const PonyBase::Math::Vector3<std::size_t>> trianglesToSet);

		void ValidateTriangles() noexcept;

		Mesh& operator =(const Mesh& other) = default;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		bool IsTriangleValid(std::size_t triangleIndex) const noexcept;

		std::vector<PonyBase::Math::Vector3<float>> vertices;
		std::vector<PonyBase::Math::RGBA<float>> colors;
		std::vector<PonyBase::Math::Vector3<std::size_t>> triangles;
		std::size_t version;
	};
}

namespace PonyEngine::Render
{
	Mesh::Mesh(const std::size_t vertexCount, const std::size_t triangleCount) :
		vertices(vertexCount),
		colors(vertexCount),
		triangles(triangleCount),
		version{0}
	{
	}

	Mesh::Mesh(const std::span<const PonyBase::Math::Vector3<float>> verticesToSet, const std::span<const PonyBase::Math::RGBA<float>> colorsToSet, const std::span<const PonyBase::Math::Vector3<std::size_t>> trianglesToSet) :
		vertices(verticesToSet.begin(), verticesToSet.end()),
		colors(colorsToSet.begin(), colorsToSet.begin() + vertices.size()),
		triangles(trianglesToSet.begin(), trianglesToSet.end()),
		version{0}
	{
	}

	std::size_t Mesh::Version() const noexcept
	{
		return version;
	}

	std::size_t Mesh::VertexCount() const noexcept
	{
		return vertices.size();
	}

	void Mesh::VertexCount(const std::size_t vertexCount)
	{
		++version;

		try
		{
			vertices.resize(vertexCount);
			colors.resize(vertexCount);
		}
		catch (const std::exception&)
		{
			const std::size_t minSize = std::min(vertices.size(), colors.size());
			vertices.resize(minSize);
			colors.resize(minSize);

			throw;
		}
	}

	std::size_t Mesh::TriangleCount() const noexcept
	{
		return triangles.size();
	}

	void Mesh::TriangleCount(const std::size_t triangleCount)
	{
		++version;
		triangles.resize(triangleCount);
	}

	const PonyBase::Math::Vector3<float>& Mesh::Vertex(const std::size_t vertexIndex) const noexcept
	{
		return vertices[vertexIndex];
	}

	void Mesh::Vertex(const std::size_t vertexIndex, const PonyBase::Math::Vector3<float>& vertex) noexcept
	{
		++version;
		vertices[vertexIndex] = vertex;
	}

	std::span<const PonyBase::Math::Vector3<float>> Mesh::Vertices() const noexcept
	{
		return vertices;
	}

	void Mesh::Vertices(const std::span<const PonyBase::Math::Vector3<float>> verticesToSet)
	{
		++version;
		std::ranges::copy(verticesToSet, vertices.begin());
	}

	const PonyBase::Math::RGBA<float>& Mesh::Color(const std::size_t vertexIndex) const noexcept
	{
		return colors[vertexIndex];
	}

	void Mesh::Color(const std::size_t vertexIndex, const PonyBase::Math::RGBA<float>& color) noexcept
	{
		++version;
		colors[vertexIndex] = color;
	}

	std::span<const PonyBase::Math::RGBA<float>> Mesh::Colors() const noexcept
	{
		return colors;
	}

	void Mesh::Colors(const std::span<const PonyBase::Math::RGBA<float>> colorsToSet)
	{
		++version;
		std::ranges::copy(colorsToSet, colors.begin());
	}

	const PonyBase::Math::Vector3<std::size_t>& Mesh::Triangle(const std::size_t triangleIndex) const noexcept
	{
		return triangles[triangleIndex];
	}

	void Mesh::Triangle(const std::size_t triangleIndex, const PonyBase::Math::Vector3<std::size_t>& triangle) noexcept
	{
		++version;
		triangles[triangleIndex] = triangle;
	}

	std::span<const PonyBase::Math::Vector3<std::size_t>> Mesh::Triangles() const noexcept
	{
		return triangles;
	}

	void Mesh::Triangles(const std::span<const PonyBase::Math::Vector3<std::size_t>> trianglesToSet)
	{
		++version;
		std::ranges::copy(trianglesToSet, triangles.begin());
	}

	void Mesh::ValidateTriangles() noexcept
	{
		bool changed = false;

		for (std::size_t i = triangles.size(); i-- > 0;)
		{
			if (!IsTriangleValid(i))
			{
				changed = true;
				triangles.erase(triangles.cbegin() + i);
			}
		}

		version += changed;
	}

	bool Mesh::IsTriangleValid(const std::size_t triangleIndex) const noexcept
	{
		const PonyBase::Math::Vector3<std::size_t>& triangle = triangles[triangleIndex];
		const std::size_t vertexCount = vertices.size();

		return triangle[0] < vertexCount && triangle[1] < vertexCount && triangle[2] < vertexCount;
	}
}

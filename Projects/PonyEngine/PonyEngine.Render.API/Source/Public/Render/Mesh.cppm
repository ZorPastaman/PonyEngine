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
import <cstdint>;
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
		Mesh(std::span<const PonyBase::Math::Vector3<float>> verticesToSet, std::span<const PonyBase::Math::RGBA<float>> colorsToSet, std::span<const PonyBase::Math::Vector3<std::uint32_t>> trianglesToSet);
		[[nodiscard("Pure constructor")]]
		Mesh(const Mesh& other) = default;
		[[nodiscard("Pure constructor")]]
		Mesh(Mesh&& other) noexcept = default;

		~Mesh() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t VertexCount() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t TriangleCount() const noexcept;

		[[nodiscard("Pure function")]]
		const PonyBase::Math::Vector3<float>& Vertex(std::size_t vertexIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Math::Vector3<float>> Vertices() const noexcept;

		[[nodiscard("Pure function")]]
		const PonyBase::Math::RGBA<float>& Color(std::size_t vertexIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Math::RGBA<float>> Colors() const noexcept;

		[[nodiscard("Pure function")]]
		const PonyBase::Math::Vector3<std::uint32_t>& Triangle(std::size_t triangleIndex) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const PonyBase::Math::Vector3<std::uint32_t>> Triangles() const noexcept;

		Mesh& operator =(const Mesh& other) = default;
		Mesh& operator =(Mesh&& other) noexcept = default;

	private:
		std::vector<PonyBase::Math::Vector3<float>> vertices;
		std::vector<PonyBase::Math::RGBA<float>> colors;
		std::vector<PonyBase::Math::Vector3<std::uint32_t>> triangles;
	};
}

namespace PonyEngine::Render
{
	Mesh::Mesh(const std::span<const PonyBase::Math::Vector3<float>> verticesToSet, const std::span<const PonyBase::Math::RGBA<float>> colorsToSet, const std::span<const PonyBase::Math::Vector3<std::uint32_t>> trianglesToSet) :
		vertices(verticesToSet.begin(), verticesToSet.end()),
		colors(colorsToSet.begin(), colorsToSet.begin() + vertices.size()),
		triangles(trianglesToSet.begin(), trianglesToSet.end())
	{
	}

	std::size_t Mesh::VertexCount() const noexcept
	{
		return vertices.size();
	}

	std::size_t Mesh::TriangleCount() const noexcept
	{
		return triangles.size();
	}

	const PonyBase::Math::Vector3<float>& Mesh::Vertex(const std::size_t vertexIndex) const noexcept
	{
		return vertices[vertexIndex];
	}

	std::span<const PonyBase::Math::Vector3<float>> Mesh::Vertices() const noexcept
	{
		return vertices;
	}

	const PonyBase::Math::RGBA<float>& Mesh::Color(const std::size_t vertexIndex) const noexcept
	{
		return colors[vertexIndex];
	}

	std::span<const PonyBase::Math::RGBA<float>> Mesh::Colors() const noexcept
	{
		return colors;
	}

	const PonyBase::Math::Vector3<std::uint32_t>& Mesh::Triangle(const std::size_t triangleIndex) const noexcept
	{
		return triangles[triangleIndex];
	}

	std::span<const PonyBase::Math::Vector3<std::uint32_t>> Mesh::Triangles() const noexcept
	{
		return triangles;
	}
}

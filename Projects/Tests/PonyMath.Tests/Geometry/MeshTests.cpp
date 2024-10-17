/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <type_traits>
#include <utility>

import PonyMath.Core;
import PonyMath.Geometry;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Geometry
{
	TEST_CLASS(MeshTests)
	{
		TEST_METHOD(TypeTest)
		{
			Assert::IsTrue(std::is_same_v<PonyMath::Core::Vector3<float>, PonyMath::Geometry::Mesh::VertexType>);
			Assert::IsTrue(std::is_same_v<PonyMath::Core::Vector3<std::uint32_t>, PonyMath::Geometry::Mesh::TriangleType>);
			Assert::IsTrue(std::is_same_v<PonyMath::Core::RGBA<float>, PonyMath::Geometry::Mesh::VertexColorType>);
		}

		TEST_METHOD(ConstructorTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			Assert::AreEqual(0u, mesh.VertexCount());
			Assert::AreEqual(std::size_t{0}, mesh.TriangleCount());
			Assert::IsFalse(mesh.HasColors());

			constexpr std::array<PonyMath::Core::Vector3<float>, 3> vertices = { PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f), PonyMath::Core::Vector3<float>(-1.f, -2.f, -3.f), PonyMath::Core::Vector3<float>(-2.f, 4.f, -7.f) };
			constexpr std::array<PonyMath::Core::Vector3<std::uint32_t>, 1> triangles = { PonyMath::Core::Vector3<std::uint32_t>{0, 2, 1} };
			constexpr std::array<PonyMath::Core::RGBA<float>, 3> colors = { PonyMath::Core::RGBA<float>(0.2f, 0.5f, 0.8f, 1.f), PonyMath::Core::RGBA<float>(0.f, 1.f, 0.4f, 0.9f), PonyMath::Core::RGBA<float>(1.f, 0.f, 0.f, 0.7f) };
			mesh.Vertices(vertices);
			mesh.Triangles(triangles);
			mesh.Colors(colors);
			const PonyMath::Geometry::Mesh copiedMesh = mesh;
			Assert::AreEqual(vertices.size(), static_cast<std::size_t>(copiedMesh.VertexCount()));
			for (std::uint32_t i = 0u; i < vertices.size(); ++i)
			{
				Assert::IsTrue(vertices[i] == copiedMesh.Vertex(i));
			}
			Assert::AreEqual(triangles.size(), copiedMesh.TriangleCount());
			for (std::size_t i = 0; i < triangles.size(); ++i)
			{
				Assert::IsTrue(triangles[i] == copiedMesh.Triangle(i));
			}
			Assert::IsTrue(copiedMesh.HasColors());
			for (std::uint32_t i = 0u; i < colors.size(); ++i)
			{
				Assert::IsTrue(colors[i] == copiedMesh.Color(i));
			}

			const PonyMath::Geometry::Mesh movedMesh = std::move(mesh);
			Assert::AreEqual(vertices.size(), static_cast<std::size_t>(movedMesh.VertexCount()));
			for (std::uint32_t i = 0u; i < vertices.size(); ++i)
			{
				Assert::IsTrue(vertices[i] == movedMesh.Vertex(i));
			}
			Assert::AreEqual(triangles.size(), movedMesh.TriangleCount());
			for (std::size_t i = 0; i < triangles.size(); ++i)
			{
				Assert::IsTrue(triangles[i] == movedMesh.Triangle(i));
			}
			Assert::IsTrue(movedMesh.HasColors());
			for (std::uint32_t i = 0u; i < colors.size(); ++i)
			{
				Assert::IsTrue(colors[i] == movedMesh.Color(i));
			}
		}

		TEST_METHOD(VertexCountTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			Assert::AreEqual(0u, mesh.VertexCount());

			mesh.VertexCount(6u);
			Assert::AreEqual(6u, mesh.VertexCount());
			Assert::AreEqual(std::size_t{6}, mesh.Vertices().size());
			for (std::uint32_t i = 0u; i < 6u; ++i)
			{
				Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == mesh.Vertex(i));
			}
			Assert::AreEqual(std::size_t{0}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{0}, mesh.Triangles().size());
			Assert::IsFalse(mesh.HasColors());
			Assert::AreEqual(std::size_t{0}, mesh.Colors().size());

			constexpr std::array<PonyMath::Core::Vector3<float>, 6> vertices = 
			{
				PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f),
				PonyMath::Core::Vector3<float>(-1.f, -2.f, -3.f),
				PonyMath::Core::Vector3<float>(-2.f, 4.f, -7.f),
				PonyMath::Core::Vector3<float>(-22.f, 14.f, -17.f),
				PonyMath::Core::Vector3<float>(2.f, 4.f, 7.f),
				PonyMath::Core::Vector3<float>(2.f, 4.f, -7.f),
			};
			constexpr std::array<PonyMath::Core::Vector3<std::uint32_t>, 3> triangles =
			{
				PonyMath::Core::Vector3<std::uint32_t>(0, 1, 2),
				PonyMath::Core::Vector3<std::uint32_t>(1, 2, 3),
				PonyMath::Core::Vector3<std::uint32_t>(3, 4, 5)
			};
			mesh.Vertices(vertices);
			mesh.Triangles(triangles);
			mesh.VertexCount(6u);
			Assert::AreEqual(6u, mesh.VertexCount());
			Assert::AreEqual(std::size_t{6}, mesh.Vertices().size());
			for (std::uint32_t i = 0u; i < vertices.size(); ++i)
			{
				Assert::IsTrue(vertices[i] == mesh.Vertex(i));
			}
			Assert::AreEqual(std::size_t{3}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{3}, mesh.Triangles().size());
			for (std::size_t i = 0; i < triangles.size(); ++i)
			{
				Assert::IsTrue(triangles[i] == mesh.Triangle(i));
			}
			Assert::IsFalse(mesh.HasColors());
			Assert::AreEqual(std::size_t{0}, mesh.Colors().size());

			mesh.VertexCount(10u);
			Assert::AreEqual(10u, mesh.VertexCount());
			Assert::AreEqual(std::size_t{10}, mesh.Vertices().size());
			for (std::uint32_t i = 0u; i < vertices.size(); ++i)
			{
				Assert::IsTrue(vertices[i] == mesh.Vertex(i));
			}
			for (std::uint32_t i = static_cast<std::uint32_t>(vertices.size()); i < 10u; ++i)
			{
				Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == mesh.Vertex(i));
			}
			Assert::AreEqual(std::size_t{3}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{3}, mesh.Triangles().size());
			for (std::size_t i = 0; i < triangles.size(); ++i)
			{
				Assert::IsTrue(triangles[i] == mesh.Triangle(i));
			}
			Assert::IsFalse(mesh.HasColors());
			Assert::AreEqual(std::size_t{0}, mesh.Colors().size());

			mesh.VertexCount(4u);
			Assert::AreEqual(4u, mesh.VertexCount());
			Assert::AreEqual(std::size_t{4}, mesh.Vertices().size());
			for (std::uint32_t i = 0u; i < 4u; ++i)
			{
				Assert::IsTrue(vertices[i] == mesh.Vertex(i));
			}
			Assert::AreEqual(std::size_t{0}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{0}, mesh.Triangles().size());
			Assert::IsFalse(mesh.HasColors());
			Assert::AreEqual(std::size_t{0}, mesh.Colors().size());

			constexpr std::array<PonyMath::Core::RGBA<float>, 4> colors =
			{
				PonyMath::Core::RGBA<float>(0.1f, 0.2f, 0.3f, 0.9f),
				PonyMath::Core::RGBA<float>(0.12f, 0.22f, 0.83f, 0.9f),
				PonyMath::Core::RGBA<float>(0.13f, 0.42f, 0.93f, 0.8f),
				PonyMath::Core::RGBA<float>(0.16f, 0.62f, 0.73f, 0.95f),
			};
			mesh.Colors(std::span(colors).subspan(0, 4));
			mesh.Triangles(std::span(triangles).subspan(0, 2));
			mesh.VertexCount(4u);
			Assert::AreEqual(4u, mesh.VertexCount());
			Assert::AreEqual(std::size_t{4}, mesh.Vertices().size());
			for (std::uint32_t i = 0u; i < 4u; ++i)
			{
				Assert::IsTrue(vertices[i] == mesh.Vertex(i));
			}
			Assert::AreEqual(std::size_t{2}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{2}, mesh.Triangles().size());
			for (std::size_t i = 0; i < 2u; ++i)
			{
				Assert::IsTrue(triangles[i] == mesh.Triangle(i));
			}
			Assert::IsTrue(mesh.HasColors());
			Assert::AreEqual(std::size_t{4}, mesh.Colors().size());
			for (std::uint32_t i = 0u; i < 4u; ++i)
			{
				Assert::IsTrue(colors[i] == mesh.Color(i));
			}

			mesh.VertexCount(6u);
			Assert::AreEqual(6u, mesh.VertexCount());
			Assert::AreEqual(std::size_t{6}, mesh.Vertices().size());
			for (std::uint32_t i = 0u; i < 4u; ++i)
			{
				Assert::IsTrue(vertices[i] == mesh.Vertex(i));
			}
			for (std::uint32_t i = 4u; i < 6u; ++i)
			{
				Assert::IsTrue(PonyMath::Core::Vector3<float>::Predefined::Zero == mesh.Vertex(i));
			}
			Assert::AreEqual(std::size_t{2}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{2}, mesh.Triangles().size());
			for (std::size_t i = 0; i < 2u; ++i)
			{
				Assert::IsTrue(triangles[i] == mesh.Triangle(i));
			}
			Assert::IsTrue(mesh.HasColors());
			Assert::AreEqual(std::size_t{6}, mesh.Colors().size());
			for (std::uint32_t i = 0u; i < 4u; ++i)
			{
				Assert::IsTrue(colors[i] == mesh.Color(i));
			}
			for (std::uint32_t i = 4u; i < 6u; ++i)
			{
				Assert::IsTrue(PonyMath::Core::RGBA<float>::Predefined::Clear == mesh.Color(i));
			}

			mesh.VertexCount(3u);
			Assert::AreEqual(3u, mesh.VertexCount());
			Assert::AreEqual(std::size_t{3}, mesh.Vertices().size());
			for (std::uint32_t i = 0u; i < 3u; ++i)
			{
				Assert::IsTrue(vertices[i] == mesh.Vertex(i));
			}
			Assert::AreEqual(std::size_t{0}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{0}, mesh.Triangles().size());
			Assert::IsTrue(mesh.HasColors());
			Assert::AreEqual(std::size_t{3}, mesh.Colors().size());
			for (std::uint32_t i = 0u; i < 3u; ++i)
			{
				Assert::IsTrue(colors[i] == mesh.Color(i));
			}
		}

		TEST_METHOD(TriangleCountTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			Assert::AreEqual(std::size_t{0}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{0}, mesh.Triangles().size());
			mesh.TriangleCount(0);
			Assert::AreEqual(std::size_t{0}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{0}, mesh.Triangles().size());

			Assert::ExpectException<std::logic_error>([&] {mesh.TriangleCount(4);});

			mesh.VertexCount(4);
			mesh.TriangleCount(7);
			Assert::AreEqual(std::size_t{7}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{7}, mesh.Triangles().size());
			for (std::size_t i = 0; i < mesh.TriangleCount(); ++i)
			{
				Assert::IsTrue(PonyMath::Core::Vector3<std::uint32_t>::Predefined::Zero == mesh.Triangle(i));
			}

			mesh.TriangleCount(3);
			Assert::AreEqual(std::size_t{3}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{3}, mesh.Triangles().size());
			for (std::size_t i = 0; i < mesh.TriangleCount(); ++i)
			{
				Assert::IsTrue(PonyMath::Core::Vector3<std::uint32_t>::Predefined::Zero == mesh.Triangle(i));
			}

			mesh.TriangleCount(0);
			Assert::AreEqual(std::size_t{0}, mesh.TriangleCount());
			Assert::AreEqual(std::size_t{0}, mesh.Triangles().size());
		}

		TEST_METHOD(HasColorsTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			Assert::IsFalse(mesh.HasColors());
			Assert::AreEqual(std::size_t{0}, mesh.Colors().size());

			mesh.HasColors(true);
			Assert::IsFalse(mesh.HasColors());
			Assert::AreEqual(std::size_t{0}, mesh.Colors().size());

			mesh.VertexCount(4);
			mesh.HasColors(true);
			Assert::IsTrue(mesh.HasColors());
			Assert::AreEqual(std::size_t{4}, mesh.Colors().size());
			for (std::uint32_t i = 0u; i < mesh.VertexCount(); ++i)
			{
				Assert::IsTrue(PonyMath::Core::RGBA<float>::Predefined::Clear == mesh.Color(i));
			}

			mesh.HasColors(false);
			Assert::IsFalse(mesh.HasColors());
			Assert::AreEqual(std::size_t{0}, mesh.Colors().size());
		}

		TEST_METHOD(VertexTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			mesh.VertexCount(3u);
			constexpr std::array<PonyMath::Core::Vector3<float>, 3> vertices =
			{
				PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f),
				PonyMath::Core::Vector3<float>(-1.f, -2.f, -3.f),
				PonyMath::Core::Vector3<float>(-2.f, 4.f, -7.f)
			};

			for (std::uint32_t i = 0; i < vertices.size(); ++i)
			{
				mesh.Vertex(i, vertices[i]);
				Assert::IsTrue(vertices[i] == mesh.Vertex(i));
			}
		}

		TEST_METHOD(VerticesTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			Assert::AreEqual(std::size_t{0}, mesh.Vertices().size());
			constexpr std::array<PonyMath::Core::Vector3<float>, 3> vertices =
			{
				PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f),
				PonyMath::Core::Vector3<float>(-1.f, -2.f, -3.f),
				PonyMath::Core::Vector3<float>(-2.f, 4.f, -7.f)
			};
			mesh.Vertices(vertices);
			Assert::AreEqual(3u, mesh.VertexCount());
			for (std::uint32_t i = 0u; i < vertices.size(); ++i)
			{
				Assert::IsTrue(vertices[i] == mesh.Vertices()[i]);
			}

			mesh.Vertices(std::span(vertices).subspan(1, 2));
			Assert::AreEqual(2u, mesh.VertexCount());
			for (std::uint32_t i = 0u; i < 2u; ++i)
			{
				Assert::IsTrue(vertices[i + 1] == mesh.Vertices()[i]);
			}
		}

		TEST_METHOD(TriangleTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			constexpr std::array<PonyMath::Core::Vector3<float>, 3> vertices =
			{
				PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f),
				PonyMath::Core::Vector3<float>(-1.f, -2.f, -3.f),
				PonyMath::Core::Vector3<float>(-2.f, 4.f, -7.f)
			};
			mesh.Vertices(vertices);
			constexpr std::array<PonyMath::Core::Vector3<std::uint32_t>, 2> triangles =
			{
				PonyMath::Core::Vector3<std::uint32_t>(0, 1, 2),
				PonyMath::Core::Vector3<std::uint32_t>(1, 2, 0)
			};
			mesh.TriangleCount(2u);
			for (std::size_t i = 0; i < triangles.size(); ++i)
			{
				mesh.Triangle(i, triangles[i]);
				Assert::IsTrue(triangles[i] == mesh.Triangle(i));
			}

			Assert::ExpectException<std::invalid_argument>([&] {mesh.Triangle(0, PonyMath::Core::Vector3<std::uint32_t>(0, 0, 3));});
			Assert::ExpectException<std::invalid_argument>([&] {mesh.Triangle(0, PonyMath::Core::Vector3<std::uint32_t>(1, 3, 0));});
			Assert::ExpectException<std::invalid_argument>([&] {mesh.Triangle(0, PonyMath::Core::Vector3<std::uint32_t>(3, 1, 0));});
		}

		TEST_METHOD(TrianglesTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			Assert::AreEqual(std::size_t{0}, mesh.Triangles().size());
			constexpr std::array<PonyMath::Core::Vector3<float>, 3> vertices =
			{
				PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f),
				PonyMath::Core::Vector3<float>(-1.f, -2.f, -3.f),
				PonyMath::Core::Vector3<float>(-2.f, 4.f, -7.f)
			};
			mesh.Vertices(vertices);
			std::array<PonyMath::Core::Vector3<std::uint32_t>, 2> triangles =
			{
				PonyMath::Core::Vector3<std::uint32_t>(0, 1, 2),
				PonyMath::Core::Vector3<std::uint32_t>(1, 2, 0)
			};
			mesh.Triangles(triangles);
			Assert::AreEqual(triangles.size(), mesh.TriangleCount());
			for (std::size_t i = 0; i < triangles.size(); ++i)
			{
				mesh.Triangle(i, triangles[i]);
				Assert::IsTrue(triangles[i] == mesh.Triangles()[i]);
			}

			mesh.Triangles(std::span(triangles).subspan(0, 1));
			Assert::AreEqual(std::size_t{1}, mesh.TriangleCount());
			Assert::IsTrue(triangles[0] == mesh.Triangles()[0]);

			triangles[0][0] = 3;
			Assert::ExpectException<std::invalid_argument>([&] {mesh.Triangles(triangles);});
			triangles[0][0] = 0;
			triangles[1][2] = 4;
			Assert::ExpectException<std::invalid_argument>([&] {mesh.Triangles(triangles);});
		}

		TEST_METHOD(ColorTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			mesh.VertexCount(3u);
			mesh.HasColors(true);
			constexpr std::array<PonyMath::Core::RGBA<float>, 3> colors =
			{
				PonyMath::Core::RGBA<float>(0.1f, 0.3f, 0.4f, 0.9f),
				PonyMath::Core::RGBA<float>(0.f, 0.7f, 0.45f, 0.95f),
				PonyMath::Core::RGBA<float>(0.7f, 0.3f, 0.7f, 1.f)
			};

			for (std::uint32_t i = 0; i < colors.size(); ++i)
			{
				mesh.Color(i, colors[i]);
				Assert::IsTrue(colors[i] == mesh.Color(i));
			}
		}

		TEST_METHOD(ColorsTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			mesh.VertexCount(3u);
			mesh.HasColors(true);
			constexpr std::array<PonyMath::Core::RGBA<float>, 3> colors =
			{
				PonyMath::Core::RGBA<float>(0.1f, 0.3f, 0.4f, 0.9f),
				PonyMath::Core::RGBA<float>(0.f, 0.7f, 0.45f, 0.95f),
				PonyMath::Core::RGBA<float>(0.7f, 0.3f, 0.7f, 1.f)
			};
			mesh.Colors(colors);
			Assert::AreEqual(std::size_t{3}, mesh.Colors().size());
			for (std::uint32_t i = 0u; i < colors.size(); ++i)
			{
				Assert::IsTrue(colors[i] == mesh.Colors()[i]);
			}
		}

		TEST_METHOD(AssignmentTest)
		{
			auto mesh = PonyMath::Geometry::Mesh();
			constexpr std::array<PonyMath::Core::Vector3<float>, 3> vertices = { PonyMath::Core::Vector3<float>(1.f, 2.f, 3.f), PonyMath::Core::Vector3<float>(-1.f, -2.f, -3.f), PonyMath::Core::Vector3<float>(-2.f, 4.f, -7.f) };
			constexpr std::array<PonyMath::Core::Vector3<std::uint32_t>, 1> triangles = { PonyMath::Core::Vector3<std::uint32_t>{0, 2, 1} };
			constexpr std::array<PonyMath::Core::RGBA<float>, 3> colors = { PonyMath::Core::RGBA<float>(0.2f, 0.5f, 0.8f, 1.f), PonyMath::Core::RGBA<float>(0.f, 1.f, 0.4f, 0.9f), PonyMath::Core::RGBA<float>(1.f, 0.f, 0.f, 0.7f) };
			mesh.Vertices(vertices);
			mesh.Triangles(triangles);
			mesh.Colors(colors);
			auto copiedMesh = PonyMath::Geometry::Mesh();;
			copiedMesh = mesh;
			Assert::AreEqual(vertices.size(), static_cast<std::size_t>(copiedMesh.VertexCount()));
			for (std::uint32_t i = 0u; i < vertices.size(); ++i)
			{
				Assert::IsTrue(vertices[i] == copiedMesh.Vertex(i));
			}
			Assert::AreEqual(triangles.size(), copiedMesh.TriangleCount());
			for (std::size_t i = 0; i < triangles.size(); ++i)
			{
				Assert::IsTrue(triangles[i] == copiedMesh.Triangle(i));
			}
			Assert::IsTrue(copiedMesh.HasColors());
			for (std::uint32_t i = 0u; i < colors.size(); ++i)
			{
				Assert::IsTrue(colors[i] == copiedMesh.Color(i));
			}

			auto movedMesh = PonyMath::Geometry::Mesh();
			movedMesh = std::move(mesh);
			Assert::AreEqual(vertices.size(), static_cast<std::size_t>(movedMesh.VertexCount()));
			for (std::uint32_t i = 0u; i < vertices.size(); ++i)
			{
				Assert::IsTrue(vertices[i] == movedMesh.Vertex(i));
			}
			Assert::AreEqual(triangles.size(), movedMesh.TriangleCount());
			for (std::size_t i = 0; i < triangles.size(); ++i)
			{
				Assert::IsTrue(triangles[i] == movedMesh.Triangle(i));
			}
			Assert::IsTrue(movedMesh.HasColors());
			for (std::uint32_t i = 0u; i < colors.size(); ++i)
			{
				Assert::IsTrue(colors[i] == movedMesh.Color(i));
			}
		}
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstdint>
#include <utility>

import PonyShader.Mesh;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Mesh
{
	TEST_CLASS(MeshletTests)
	{
		TEST_METHOD(ConstructorTest)
		{
			const auto defaultMeshlet = PonyShader::Mesh::Meshlet();
			Assert::AreEqual(0u, defaultMeshlet.VertexOffset());
			Assert::AreEqual(0u, defaultMeshlet.PrimitiveOffset());
			Assert::AreEqual(std::uint8_t{0u}, defaultMeshlet.VertexCount());
			Assert::AreEqual(std::uint8_t{0u}, defaultMeshlet.PrimitiveCount());

			const auto meshlet = PonyShader::Mesh::Meshlet(4u, 5u, 2u, 5u);
			Assert::AreEqual(4u, meshlet.VertexOffset());
			Assert::AreEqual(5u, meshlet.PrimitiveOffset());
			Assert::AreEqual(std::uint8_t{2u}, meshlet.VertexCount());
			Assert::AreEqual(std::uint8_t{5u}, meshlet.PrimitiveCount());

			auto copied = meshlet;
			Assert::AreEqual(4u, copied.VertexOffset());
			Assert::AreEqual(5u, copied.PrimitiveOffset());
			Assert::AreEqual(std::uint8_t{2u}, copied.VertexCount());
			Assert::AreEqual(std::uint8_t{5u}, copied.PrimitiveCount());

			const auto moved = std::move(copied);
			Assert::AreEqual(4u, moved.VertexOffset());
			Assert::AreEqual(5u, moved.PrimitiveOffset());
			Assert::AreEqual(std::uint8_t{2u}, moved.VertexCount());
			Assert::AreEqual(std::uint8_t{5u}, moved.PrimitiveCount());
		}

		TEST_METHOD(VertexOffsetTest)
		{
			auto meshlet = PonyShader::Mesh::Meshlet(4u, 5u, 2u, 5u);
			meshlet.VertexOffset() = 6u;
			Assert::AreEqual(6u, meshlet.VertexOffset());

			const auto meshletC = meshlet;
			Assert::AreEqual(6u, meshletC.VertexOffset());
		}

		TEST_METHOD(PrimitiveOffsetTest)
		{
			auto meshlet = PonyShader::Mesh::Meshlet(4u, 5u, 2u, 5u);
			meshlet.PrimitiveOffset() = 10u;
			Assert::AreEqual(10u, meshlet.PrimitiveOffset());

			const auto meshletC = meshlet;
			Assert::AreEqual(10u, meshletC.PrimitiveOffset());
		}

		TEST_METHOD(VertexCountTest)
		{
			auto meshlet = PonyShader::Mesh::Meshlet(4u, 5u, 2u, 5u);
			meshlet.VertexCount() = 8u;
			Assert::AreEqual(std::uint8_t{8u}, meshlet.VertexCount());

			const auto meshletC = meshlet;
			Assert::AreEqual(std::uint8_t{8u}, meshletC.VertexCount());
		}

		TEST_METHOD(PrimitiveCountTest)
		{
			auto meshlet = PonyShader::Mesh::Meshlet(4u, 5u, 2u, 5u);
			meshlet.PrimitiveCount() = 6u;
			Assert::AreEqual(std::uint8_t{6u}, meshlet.PrimitiveCount());

			const auto meshletC = meshlet;
			Assert::AreEqual(std::uint8_t{6u}, meshletC.PrimitiveCount());
		}

		TEST_METHOD(AssignmentTest)
		{
			constexpr auto meshlet = PonyShader::Mesh::Meshlet(4u, 5u, 2u, 5u);
			auto copied = PonyShader::Mesh::Meshlet();
			copied = meshlet;
			Assert::IsTrue(meshlet == copied);

			auto moved = PonyShader::Mesh::Meshlet();
			moved = std::move(copied);
			Assert::IsTrue(meshlet == moved);
		}

		TEST_METHOD(EqualTest)
		{
			auto meshlet = PonyShader::Mesh::Meshlet(4u, 5u, 2u, 5u);
			const auto copied = meshlet;
			Assert::IsTrue(meshlet == copied);

			meshlet.VertexOffset() += 1u;
			Assert::IsFalse(meshlet == copied);

			meshlet.VertexOffset() = copied.VertexOffset();
			meshlet.PrimitiveOffset() += 1u;
			Assert::IsFalse(meshlet == copied);

			meshlet.PrimitiveOffset() = copied.PrimitiveOffset();
			meshlet.VertexCount() += 1u;
			Assert::IsFalse(meshlet == copied);

			meshlet.VertexCount() = copied.VertexCount();
			meshlet.PrimitiveCount() += 1u;
			Assert::IsFalse(meshlet == copied);
		}

		static constexpr PonyShader::Mesh::Meshlet MeshletConstexpr()
		{
			auto meshlet = PonyShader::Mesh::Meshlet(4u, 5u, 2u, 5u);
			auto moved = std::move(meshlet);

			moved.VertexOffset() += 3u;
			moved.PrimitiveOffset() += 2u;
			moved.VertexCount() += 1u;
			moved.PrimitiveCount() += 1u;

			auto copied = PonyShader::Mesh::Meshlet();
			copied = moved;
			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultMeshlet = PonyShader::Mesh::Meshlet();
			[[maybe_unused]] constexpr auto meshlet = PonyShader::Mesh::Meshlet(4u, 6u, 2u, 1u);
			[[maybe_unused]] constexpr auto copied = meshlet;
			[[maybe_unused]] constexpr auto moved = MeshletConstexpr();

			[[maybe_unused]] constexpr auto vertexOffset = meshlet.VertexOffset();
			[[maybe_unused]] constexpr auto primitiveOffset = meshlet.PrimitiveOffset();
			[[maybe_unused]] constexpr auto vertexCount = meshlet.VertexCount();
			[[maybe_unused]] constexpr auto primitiveCount = meshlet.PrimitiveCount();

			[[maybe_unused]] constexpr bool equal = meshlet == copied;
			[[maybe_unused]] constexpr bool notEqual = meshlet != copied;
		}
	};
}

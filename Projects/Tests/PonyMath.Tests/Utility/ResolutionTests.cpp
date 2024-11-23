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
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

import PonyMath.Core;
import PonyMath.Utility;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
	TEST_CLASS(ResolutionTests)
	{
		TEST_METHOD(TypesTest)
		{
			Assert::IsTrue(std::is_same_v<std::uint8_t, PonyMath::Utility::Resolution<std::uint8_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<std::uint16_t, PonyMath::Utility::Resolution<std::uint16_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<std::uint32_t, PonyMath::Utility::Resolution<std::uint32_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<std::uint64_t, PonyMath::Utility::Resolution<std::uint64_t>::ValueType>);
		}

		TEST_METHOD(ConstructorTest)
		{
			const auto defaultResolution = PonyMath::Utility::Resolution<std::uint32_t>();
			Assert::AreEqual(0u, defaultResolution.Width());
			Assert::AreEqual(0u, defaultResolution.Height());

			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);
			Assert::AreEqual(width, resolution.Width());
			Assert::AreEqual(height, resolution.Height());

			constexpr auto vector = PonyMath::Core::Vector2<std::uint32_t>(width, height);
			const auto vectorResolution = PonyMath::Utility::Resolution<std::uint32_t>(vector);
			Assert::AreEqual(width, vectorResolution.Width());
			Assert::AreEqual(height, vectorResolution.Height());

			const auto copiedResolution = resolution;
			Assert::AreEqual(width, copiedResolution.Width());
			Assert::AreEqual(height, copiedResolution.Height());

			const auto movedResolution = std::move(resolution);
			Assert::AreEqual(width, movedResolution.Width());
			Assert::AreEqual(height, movedResolution.Height());
		}

		TEST_METHOD(WidthTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);
			Assert::AreEqual(width, resolution.Width());

			resolution.Width() = 520u;
			Assert::AreEqual(520u, resolution.Width());

			const auto resolutionC = resolution;
			Assert::AreEqual(520u, resolutionC.Width());
		}

		TEST_METHOD(HeightTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);
			Assert::AreEqual(width, resolution.Width());

			resolution.Height() = 520u;
			Assert::AreEqual(520u, resolution.Height());

			const auto resolutionC = resolution;
			Assert::AreEqual(520u, resolutionC.Height());
		}

		TEST_METHOD(SpanTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);
			Assert::AreEqual(width, resolution.Span()[0]);
			Assert::AreEqual(height, resolution.Span()[1]);

			const auto resolutionC = resolution;
			Assert::AreEqual(width, resolutionC.Span()[0]);
			Assert::AreEqual(height, resolutionC.Span()[1]);
		}

		TEST_METHOD(VectorTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);
			Assert::AreEqual(width, resolution.Vector()[0]);
			Assert::AreEqual(height, resolution.Vector()[1]);

			const auto resolutionC = resolution;
			Assert::AreEqual(width, resolutionC.Vector()[0]);
			Assert::AreEqual(height, resolutionC.Vector()[1]);
		}

		TEST_METHOD(AspectTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);
			Assert::AreEqual(320. / 240., static_cast<double>(resolution.Aspect<float>()), 0.001);
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);
			Assert::AreEqual("320x240", resolution.ToString().c_str());

			std::ostringstream ss;
			ss << resolution;
			Assert::AreEqual("320x240", ss.str().c_str());
		}

		TEST_METHOD(CastTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);
			const auto longResolution = static_cast<PonyMath::Utility::Resolution<std::uint64_t>>(resolution);
			Assert::AreEqual(320ULL, longResolution.Width());
			Assert::AreEqual(240ULL, longResolution.Height());
		}

		TEST_METHOD(VectorCastTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);
			const auto vector = static_cast<PonyMath::Core::Vector2<std::uint32_t>>(resolution);
			Assert::AreEqual(width, vector.X());
			Assert::AreEqual(height, vector.Y());
		}

		TEST_METHOD(AssignmentTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);

			auto copiedResolution = PonyMath::Utility::Resolution<std::uint32_t>();
			copiedResolution = resolution;
			Assert::AreEqual(width, copiedResolution.Width());
			Assert::AreEqual(height, copiedResolution.Height());

			auto movedResolution = PonyMath::Utility::Resolution<std::uint32_t>();
			movedResolution = std::move(resolution);
			Assert::AreEqual(width, movedResolution.Width());
			Assert::AreEqual(height, movedResolution.Height());
		}

		TEST_METHOD(EqualTest)
		{
			constexpr std::uint32_t width = 320u;
			constexpr std::uint32_t height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(width, height);

			auto otherResolution = resolution;
			Assert::IsTrue(resolution == otherResolution);
			Assert::IsFalse(resolution != otherResolution);

			otherResolution.Width() += 1u;
			Assert::IsFalse(resolution == otherResolution);
			Assert::IsTrue(resolution != otherResolution);

			otherResolution = resolution;
			otherResolution.Height() -= 1u;
			Assert::IsFalse(resolution == otherResolution);
			Assert::IsTrue(resolution != otherResolution);
		}

		static constexpr PonyMath::Utility::Resolution<std::uint32_t> GetConstexpr()
		{
			auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(1024u, 768u);
			auto movedResolution = std::move(resolution);

			[[maybe_unused]] auto width = movedResolution.Width();
			[[maybe_unused]] auto height = movedResolution.Height();
			[[maybe_unused]] auto span = movedResolution.Span();
			[[maybe_unused]] auto vector = movedResolution.Vector();

			auto copiedResolution = PonyMath::Utility::Resolution<std::uint32_t>();
			copiedResolution = movedResolution;
			auto movedCopy = PonyMath::Utility::Resolution<std::uint32_t>();
			movedCopy = std::move(copiedResolution);

			return movedResolution;
		}

		TEST_METHOD(ConstexprTest)
		{
			[[maybe_unused]] constexpr auto defaultResolution = PonyMath::Utility::Resolution<std::uint32_t>();
			[[maybe_unused]] constexpr auto resolution = PonyMath::Utility::Resolution<std::uint32_t>(1024u, 768u);
			[[maybe_unused]] constexpr auto vectorResolution = PonyMath::Utility::Resolution<std::uint32_t>(PonyMath::Core::Vector2<std::uint32_t>(800u, 600u));
			[[maybe_unused]] constexpr auto copiedResolution = resolution;
			[[maybe_unused]] constexpr auto movedResolution = GetConstexpr();

			[[maybe_unused]] constexpr auto width = resolution.Width();
			[[maybe_unused]] constexpr auto height = resolution.Height();
			[[maybe_unused]] constexpr auto span = resolution.Span();
			[[maybe_unused]] constexpr auto vector = resolution.Vector();

			[[maybe_unused]] constexpr auto aspect = resolution.Aspect<float>();

			[[maybe_unused]] constexpr auto castResolution = static_cast<PonyMath::Utility::Resolution<std::uint64_t>>(resolution);

			[[maybe_unused]] constexpr auto resolutionVector = static_cast<PonyMath::Core::Vector2<std::uint32_t>>(resolution);

			[[maybe_unused]] constexpr bool equal = resolution == copiedResolution;
			[[maybe_unused]] constexpr bool notEqual = resolution != copiedResolution;
		}
	};
}

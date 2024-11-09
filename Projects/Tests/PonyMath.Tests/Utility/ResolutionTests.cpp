/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

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
			Assert::IsTrue(std::is_same_v<unsigned int, PonyMath::Utility::Resolution<unsigned int>::ValueType>);
			Assert::IsTrue(std::is_same_v<unsigned long, PonyMath::Utility::Resolution<unsigned long>::ValueType>);
			Assert::IsTrue(std::is_same_v<unsigned long long, PonyMath::Utility::Resolution<unsigned long long>::ValueType>);
		}

		TEST_METHOD(ConstructorTest)
		{
			const auto defaultResolution = PonyMath::Utility::Resolution<unsigned int>();
			Assert::AreEqual(0u, defaultResolution.Width());
			Assert::AreEqual(0u, defaultResolution.Height());

			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);
			Assert::AreEqual(width, resolution.Width());
			Assert::AreEqual(height, resolution.Height());

			constexpr auto vector = PonyMath::Core::Vector2<unsigned int>(width, height);
			const auto vectorResolution = PonyMath::Utility::Resolution<unsigned int>(vector);
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
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);
			Assert::AreEqual(width, resolution.Width());

			resolution.Width() = 520u;
			Assert::AreEqual(520u, resolution.Width());

			const auto resolutionC = resolution;
			Assert::AreEqual(520u, resolutionC.Width());
		}

		TEST_METHOD(HeightTest)
		{
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);
			Assert::AreEqual(width, resolution.Width());

			resolution.Height() = 520u;
			Assert::AreEqual(520u, resolution.Height());

			const auto resolutionC = resolution;
			Assert::AreEqual(520u, resolutionC.Height());
		}

		TEST_METHOD(SpanTest)
		{
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);
			Assert::AreEqual(width, resolution.Span()[0]);
			Assert::AreEqual(height, resolution.Span()[1]);

			const auto resolutionC = resolution;
			Assert::AreEqual(width, resolutionC.Span()[0]);
			Assert::AreEqual(height, resolutionC.Span()[1]);
		}

		TEST_METHOD(VectorTest)
		{
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);
			Assert::AreEqual(width, resolution.Vector()[0]);
			Assert::AreEqual(height, resolution.Vector()[1]);

			const auto resolutionC = resolution;
			Assert::AreEqual(width, resolutionC.Vector()[0]);
			Assert::AreEqual(height, resolutionC.Vector()[1]);
		}

		TEST_METHOD(AspectTest)
		{
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);
			Assert::AreEqual(320. / 240., static_cast<double>(resolution.Aspect<float>()), 0.001);
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);
			Assert::AreEqual("320x240", resolution.ToString().c_str());

			std::ostringstream ss;
			ss << resolution;
			Assert::AreEqual("320x240", ss.str().c_str());
		}

		TEST_METHOD(CastTest)
		{
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);
			const auto longResolution = static_cast<PonyMath::Utility::Resolution<unsigned long long>>(resolution);
			Assert::AreEqual(320ULL, longResolution.Width());
			Assert::AreEqual(240ULL, longResolution.Height());
		}

		TEST_METHOD(VectorCastTest)
		{
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);
			const auto vector = static_cast<PonyMath::Core::Vector2<unsigned int>>(resolution);
			Assert::AreEqual(width, vector.X());
			Assert::AreEqual(height, vector.Y());
		}

		TEST_METHOD(AssignmentTest)
		{
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);

			auto copiedResolution = PonyMath::Utility::Resolution<unsigned int>();
			copiedResolution = resolution;
			Assert::AreEqual(width, copiedResolution.Width());
			Assert::AreEqual(height, copiedResolution.Height());

			auto movedResolution = PonyMath::Utility::Resolution<unsigned int>();
			movedResolution = std::move(resolution);
			Assert::AreEqual(width, movedResolution.Width());
			Assert::AreEqual(height, movedResolution.Height());
		}

		TEST_METHOD(EqualTest)
		{
			constexpr unsigned int width = 320u;
			constexpr unsigned int height = 240u;
			constexpr auto resolution = PonyMath::Utility::Resolution<unsigned int>(width, height);

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

		static constexpr PonyMath::Utility::Resolution<unsigned int> GetConstexpr()
		{
			auto resolution = PonyMath::Utility::Resolution<unsigned int>(1024u, 768u);
			auto movedResolution = std::move(resolution);

			[[maybe_unused]] auto width = movedResolution.Width();
			[[maybe_unused]] auto height = movedResolution.Height();
			[[maybe_unused]] auto span = movedResolution.Span();
			[[maybe_unused]] auto vector = movedResolution.Vector();

			auto copiedResolution = PonyMath::Utility::Resolution<unsigned int>();
			copiedResolution = movedResolution;
			auto movedCopy = PonyMath::Utility::Resolution<unsigned int>();
			movedCopy = std::move(copiedResolution);

			return movedResolution;
		}

		TEST_METHOD(ConstexprTest)
		{
			[[maybe_unused]] constexpr auto defaultResolution = PonyMath::Utility::Resolution<unsigned int>();
			[[maybe_unused]] constexpr auto resolution = PonyMath::Utility::Resolution<unsigned int>(1024u, 768u);
			[[maybe_unused]] constexpr auto vectorResolution = PonyMath::Utility::Resolution<unsigned int>(PonyMath::Core::Vector2<unsigned int>(800u, 600u));
			[[maybe_unused]] constexpr auto copiedResolution = resolution;
			[[maybe_unused]] constexpr auto movedResolution = GetConstexpr();

			[[maybe_unused]] constexpr auto width = resolution.Width();
			[[maybe_unused]] constexpr auto height = resolution.Height();
			[[maybe_unused]] constexpr auto span = resolution.Span();
			[[maybe_unused]] constexpr auto vector = resolution.Vector();

			[[maybe_unused]] constexpr auto aspect = resolution.Aspect<float>();

			[[maybe_unused]] constexpr auto castResolution = static_cast<PonyMath::Utility::Resolution<unsigned long long>>(resolution);

			[[maybe_unused]] constexpr auto resolutionVector = static_cast<PonyMath::Core::Vector2<unsigned int>>(resolution);

			[[maybe_unused]] constexpr bool equal = resolution == copiedResolution;
			[[maybe_unused]] constexpr bool notEqual = resolution != copiedResolution;
		}
	};
}

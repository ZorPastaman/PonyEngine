/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cmath>
#include <cstdint>
#include <format>
#include <limits>
#include <string>
#include <type_traits>
#include <utility>

import PonyMath.Shape;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Shape
{
	TEST_CLASS(RectTests)
	{
		TEST_METHOD(TypeTest)
		{
			Assert::IsTrue(std::is_same_v<std::int32_t, PonyMath::Shape::Rect<std::int32_t>::ValueType>);
			Assert::IsTrue(std::is_same_v<float, PonyMath::Shape::Rect<float>::ValueType>);
		}

		TEST_METHOD(PredefinedTest)
		{
			Assert::IsTrue(PonyMath::Shape::Rect<float>(0.f, 0.f, 0.f, 0.f) == PonyMath::Shape::Rect<float>::Predefined::Zero);
			Assert::IsTrue(PonyMath::Shape::Rect<float>(0.f, 0.f, 1.f, 1.f) == PonyMath::Shape::Rect<float>::Predefined::NormalizedFull);
		}

		TEST_METHOD(ConstructorTest)
		{
			const auto defaultRect = PonyMath::Shape::Rect<float>();
			Assert::AreEqual(0.f, defaultRect.MinX());
			Assert::AreEqual(0.f, defaultRect.MinY());
			Assert::AreEqual(0.f, defaultRect.Width());
			Assert::AreEqual(0.f, defaultRect.Height());

			const auto rect = PonyMath::Shape::Rect<float>(-2.f, 3.f, 4.f, 5.f);
			Assert::AreEqual(-2.f, rect.MinX());
			Assert::AreEqual(3.f, rect.MinY());
			Assert::AreEqual(4.f, rect.Width());
			Assert::AreEqual(5.f, rect.Height());

			const auto vectorRect = PonyMath::Shape::Rect<float>(PonyMath::Core::Vector2<float>(1.f, -0.5f), PonyMath::Core::Vector2<float>(1.f, 3.f));
			Assert::AreEqual(1.f, vectorRect.MinX());
			Assert::AreEqual(-0.5f, vectorRect.MinY());
			Assert::AreEqual(1.f, vectorRect.Width());
			Assert::AreEqual(3.f, vectorRect.Height());

			auto copiedRect = rect;
			Assert::AreEqual(-2.f, copiedRect.MinX());
			Assert::AreEqual(3.f, copiedRect.MinY());
			Assert::AreEqual(4.f, copiedRect.Width());
			Assert::AreEqual(5.f, copiedRect.Height());

			const auto movedRect = std::move(copiedRect);
			Assert::AreEqual(-2.f, movedRect.MinX());
			Assert::AreEqual(3.f, movedRect.MinY());
			Assert::AreEqual(4.f, movedRect.Width());
			Assert::AreEqual(5.f, movedRect.Height());
		}

		TEST_METHOD(PositionTest)
		{
			auto rect = PonyMath::Shape::Rect<float>(-2.f, 3.f, 4.f, 5.f);
			Assert::AreEqual(-2.f, rect.Position().X());
			Assert::AreEqual(3.f, rect.Position().Y());

			constexpr auto rectC = PonyMath::Shape::Rect<float>(-2.f, 3.f, 4.f, 5.f);
			Assert::AreEqual(-2.f, rectC.Position().X());
			Assert::AreEqual(3.f, rectC.Position().Y());
		}

		TEST_METHOD(SizeTest)
		{
			auto rect = PonyMath::Shape::Rect<float>(-2.f, 3.f, 4.f, 5.f);
			Assert::AreEqual(4.f, rect.Size().X());
			Assert::AreEqual(5.f, rect.Size().Y());

			constexpr auto rectC = PonyMath::Shape::Rect<float>(-2.f, 3.f, 4.f, 5.f);
			Assert::AreEqual(4.f, rectC.Size().X());
			Assert::AreEqual(5.f, rectC.Size().Y());
		}

		TEST_METHOD(GetMinTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			Assert::AreEqual(4.f, rect.MinX());
			Assert::AreEqual(1.f, rect.MinY());
			Assert::AreEqual(4.f, rect.Min().X());
			Assert::AreEqual(1.f, rect.Min().Y());
		}

		TEST_METHOD(SetMinTest)
		{
			auto rect = PonyMath::Shape::Rect<std::int32_t>(4, 1, 2, 7);
			rect.MinX(2);
			Assert::AreEqual(2, rect.MinX());
			Assert::AreEqual(6, rect.MaxX());

			rect.MinY(3);
			Assert::AreEqual(3, rect.MinY());
			Assert::AreEqual(8, rect.MaxY());

			rect.Min(PonyMath::Core::Vector2<std::int32_t>(5, 1));
			Assert::AreEqual(5, rect.MinX());
			Assert::AreEqual(1, rect.MinY());
			Assert::AreEqual(6, rect.MaxX());
			Assert::AreEqual(8, rect.MaxY());
		}

		TEST_METHOD(GetMaxTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			Assert::AreEqual(6.f, rect.MaxX());
			Assert::AreEqual(8.f, rect.MaxY());
			Assert::AreEqual(6.f, rect.Max().X());
			Assert::AreEqual(8.f, rect.Max().Y());
		}

		TEST_METHOD(SetMaxTest)
		{
			auto rect = PonyMath::Shape::Rect<std::int32_t>(4, 1, 2, 7);
			rect.MaxX(10);
			Assert::AreEqual(4, rect.MinX());
			Assert::AreEqual(10, rect.MaxX());

			rect.MaxY(4);
			Assert::AreEqual(1, rect.MinY());
			Assert::AreEqual(4, rect.MaxY());

			rect.Max(PonyMath::Core::Vector2<std::int32_t>(5, 10));
			Assert::AreEqual(4, rect.MinX());
			Assert::AreEqual(1, rect.MinY());
			Assert::AreEqual(5, rect.MaxX());
			Assert::AreEqual(10, rect.MaxY());
		}

		TEST_METHOD(WidthTest)
		{
			auto rect = PonyMath::Shape::Rect<std::int32_t>(4, 1, 2, 7);
			Assert::AreEqual(2, rect.Width());

			rect.Width(4);
			Assert::AreEqual(4, rect.MinX());
			Assert::AreEqual(4, rect.Width());

			rect.Width<true>(2);
			Assert::AreEqual(5, rect.MinX());
			Assert::AreEqual(2, rect.Width());
		}

		TEST_METHOD(HeightTest)
		{
			auto rect = PonyMath::Shape::Rect<std::int32_t>(4, 1, 2, 7);
			Assert::AreEqual(7, rect.Height());

			rect.Height(4);
			Assert::AreEqual(1, rect.MinY());
			Assert::AreEqual(4, rect.Height());

			rect.Height<true>(6);
			Assert::AreEqual(0, rect.MinY());
			Assert::AreEqual(6, rect.Height());
		}

		TEST_METHOD(CenterTest)
		{
			auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			const auto center = rect.Center();
			Assert::AreEqual(5., static_cast<double>(center.X()), 0.001);
			Assert::AreEqual(4.5, static_cast<double>(center.Y()), 0.001);

			rect.Center(PonyMath::Core::Vector2<float>(-1.f, -2.f));
			Assert::AreEqual(-2, static_cast<double>(rect.MinX()), 0.001);
			Assert::AreEqual(-5.5, static_cast<double>(rect.MinY()), 0.001);
		}

		TEST_METHOD(PerimeterTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			Assert::AreEqual(18., static_cast<double>(rect.Perimeter()), 0.001);
		}

		TEST_METHOD(AreaTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			Assert::AreEqual(14., static_cast<double>(rect.Area()), 0.001);
		}

		TEST_METHOD(IsFiniteTest)
		{
			auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			Assert::IsTrue(rect.IsFinite());
			rect.Position().X() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(rect.IsFinite());
			rect.Position().X() = 1.f;
			rect.Position().Y() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(rect.IsFinite());
			rect.Position().Y() = 2.f;
			rect.Size().X() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(rect.IsFinite());
			rect.Size().X() = 3.f;
			rect.Size().Y() = std::numeric_limits<float>::quiet_NaN();
			Assert::IsFalse(rect.IsFinite());
		}

		TEST_METHOD(ContainsTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			Assert::IsTrue(rect.Contains(PonyMath::Core::Vector2<float>(5.f, 7.f)));
			Assert::IsFalse(rect.Contains(PonyMath::Core::Vector2<float>(8.f, 7.f)));
			Assert::IsFalse(rect.Contains(PonyMath::Core::Vector2<float>(5.f, -7.f)));
		}

		TEST_METHOD(NormalizePointTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			auto point = rect.Normalize(PonyMath::Core::Vector2<float>(4.f, 1.f));
			Assert::AreEqual(0., static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(point.Y()), 0.001);
			point = rect.Unnormalize(point);
			Assert::AreEqual(4., static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(1., static_cast<double>(point.Y()), 0.001);

			point = rect.Normalize(PonyMath::Core::Vector2<float>(6.f, 8.f));
			Assert::AreEqual(1., static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(1., static_cast<double>(point.Y()), 0.001);
			point = rect.Unnormalize(point);
			Assert::AreEqual(6., static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(8., static_cast<double>(point.Y()), 0.001);

			point = rect.Normalize(PonyMath::Core::Vector2<float>(5.f, 4.5f));
			Assert::AreEqual(0.5, static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(0.5, static_cast<double>(point.Y()), 0.001);
			point = rect.Unnormalize(point);
			Assert::AreEqual(5., static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(4.5, static_cast<double>(point.Y()), 0.001);

			point = rect.Normalize(PonyMath::Core::Vector2<float>(8.f, 15.f));
			Assert::AreEqual(2., static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(2., static_cast<double>(point.Y()), 0.001);
			point = rect.Unnormalize(point);
			Assert::AreEqual(8., static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(15., static_cast<double>(point.Y()), 0.001);

			point = rect.Normalize(PonyMath::Core::Vector2<float>(2.f, -6.f));
			Assert::AreEqual(-1., static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(point.Y()), 0.001);
			point = rect.Unnormalize(point);
			Assert::AreEqual(2., static_cast<double>(point.X()), 0.001);
			Assert::AreEqual(-6., static_cast<double>(point.Y()), 0.001);
		}

		TEST_METHOD(NormalizeRectTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			auto rectN = rect;
			rectN = rect.Normalize(rectN);
			Assert::AreEqual(0., static_cast<double>(rectN.Position().X()), 0.001);
			Assert::AreEqual(0., static_cast<double>(rectN.Position().Y()), 0.001);
			Assert::AreEqual(1., static_cast<double>(rectN.Size().X()), 0.001);
			Assert::AreEqual(1., static_cast<double>(rectN.Size().Y()), 0.001);
			rectN = rect.Unnormalize(rectN);
			Assert::AreEqual(4., static_cast<double>(rectN.MinX()), 0.001);
			Assert::AreEqual(1., static_cast<double>(rectN.MinY()), 0.001);
			Assert::AreEqual(6., static_cast<double>(rectN.MaxX()), 0.001);
			Assert::AreEqual(8., static_cast<double>(rectN.MaxY()), 0.001);

			rectN = PonyMath::Shape::Rect<float>(5.f, 4.5f, 1.f, 3.5f);
			rectN = rect.Normalize(rectN);
			Assert::AreEqual(0.5, static_cast<double>(rectN.Position().X()), 0.001);
			Assert::AreEqual(0.5, static_cast<double>(rectN.Position().Y()), 0.001);
			Assert::AreEqual(0.5, static_cast<double>(rectN.Size().X()), 0.001);
			Assert::AreEqual(0.5, static_cast<double>(rectN.Size().Y()), 0.001);
			rectN = rect.Unnormalize(rectN);
			Assert::AreEqual(5., static_cast<double>(rectN.MinX()), 0.001);
			Assert::AreEqual(4.5, static_cast<double>(rectN.MinY()), 0.001);
			Assert::AreEqual(6., static_cast<double>(rectN.MaxX()), 0.001);
			Assert::AreEqual(8., static_cast<double>(rectN.MaxY()), 0.001);

			rectN = PonyMath::Shape::Rect<float>(2.f, -6.f, 6.f, 21.f);
			rectN = rect.Normalize(rectN);
			Assert::AreEqual(-1., static_cast<double>(rectN.Position().X()), 0.001);
			Assert::AreEqual(-1., static_cast<double>(rectN.Position().Y()), 0.001);
			Assert::AreEqual(3., static_cast<double>(rectN.Size().X()), 0.001);
			Assert::AreEqual(3., static_cast<double>(rectN.Size().Y()), 0.001);
			rectN = rect.Unnormalize(rectN);
			Assert::AreEqual(2., static_cast<double>(rectN.MinX()), 0.001);
			Assert::AreEqual(-6., static_cast<double>(rectN.MinY()), 0.001);
			Assert::AreEqual(8., static_cast<double>(rectN.MaxX()), 0.001);
			Assert::AreEqual(15., static_cast<double>(rectN.MaxY()), 0.001);
		}

		TEST_METHOD(SetTest)
		{
			auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			rect.Set(1.f, -3.f, 5.f, 8.f);
			Assert::AreEqual(1.f, rect.Position().X());
			Assert::AreEqual(-3.f, rect.Position().Y());
			Assert::AreEqual(5.f, rect.Size().X());
			Assert::AreEqual(8.f, rect.Size().Y());

			rect.Set(PonyMath::Core::Vector2<float>(-2.f, 4.f), PonyMath::Core::Vector2<float>(4.f, 7.f));
			Assert::AreEqual(-2.f, rect.Position().X());
			Assert::AreEqual(4.f, rect.Position().Y());
			Assert::AreEqual(4.f, rect.Size().X());
			Assert::AreEqual(7.f, rect.Size().Y());
		}

		TEST_METHOD(ResolveNegativeTest)
		{
			auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			rect.ResolveNegativeSize();
			Assert::AreEqual(4.f, rect.Position().X());
			Assert::AreEqual(1.f, rect.Position().Y());
			Assert::AreEqual(2.f, rect.Size().X());
			Assert::AreEqual(7.f, rect.Size().Y());

			rect = PonyMath::Shape::Rect<float>(4.f, 1.f, -2.f, -7.f);
			rect.ResolveNegativeSize();
			Assert::AreEqual(2.f, rect.Position().X());
			Assert::AreEqual(-6.f, rect.Position().Y());
			Assert::AreEqual(2.f, rect.Size().X());
			Assert::AreEqual(7.f, rect.Size().Y());
		}

		TEST_METHOD(ToStringTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			const std::string str = rect.ToString();
			Assert::AreEqual("Position: (4, 1), Size: (2, 7)", str.c_str());

			std::ostringstream ss;
			ss << rect;
			Assert::AreEqual(str, ss.str());
		}

		TEST_METHOD(ConvertTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			const auto rectD = static_cast<PonyMath::Shape::Rect<double>>(rect);
			Assert::AreEqual(4., rectD.Position().X());
			Assert::AreEqual(1., rectD.Position().Y());
			Assert::AreEqual(2., rectD.Size().X());
			Assert::AreEqual(7., rectD.Size().Y());
		}

		TEST_METHOD(AssignmentTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			auto copiedRect = PonyMath::Shape::Rect<float>();
			copiedRect = rect;
			Assert::AreEqual(4.f, copiedRect.Position().X());
			Assert::AreEqual(1.f, copiedRect.Position().Y());
			Assert::AreEqual(2.f, copiedRect.Size().X());
			Assert::AreEqual(7.f, copiedRect.Size().Y());

			auto movedRect = PonyMath::Shape::Rect<float>();
			movedRect = std::move(copiedRect);
			Assert::AreEqual(4.f, movedRect.Position().X());
			Assert::AreEqual(1.f, movedRect.Position().Y());
			Assert::AreEqual(2.f, movedRect.Size().X());
			Assert::AreEqual(7.f, movedRect.Size().Y());
		}

		TEST_METHOD(EqualTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			auto copiedRect = rect;
			Assert::IsTrue(rect == copiedRect);
			Assert::IsFalse(rect != copiedRect);

			copiedRect.Position().X() = 1.f;
			Assert::IsFalse(rect == copiedRect);
			Assert::IsTrue(rect != copiedRect);

			copiedRect.Position().X() = 4.f;
			copiedRect.Position().Y() = 3.f;
			Assert::IsFalse(rect == copiedRect);
			Assert::IsTrue(rect != copiedRect);

			copiedRect.Position().Y() = 1.f;
			copiedRect.Size().X() = 1.f;
			Assert::IsFalse(rect == copiedRect);
			Assert::IsTrue(rect != copiedRect);

			copiedRect.Size().X() = 2.f;
			copiedRect.Size().Y() = 3.f;
			Assert::IsFalse(rect == copiedRect);
			Assert::IsTrue(rect != copiedRect);
		}

		TEST_METHOD(AreAlmostEqualTest)
		{
			constexpr auto rect = PonyMath::Shape::Rect<float>(4.f, 1.f, 2.f, 7.f);
			auto copiedRect = rect;
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(rect, copiedRect));

			copiedRect.Position().X() = 1.f;
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(rect, copiedRect));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(rect, copiedRect, 10.f));
			copiedRect.Position().X() = std::nextafter(4.f, 0.f);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(rect, copiedRect));

			copiedRect.Position().X() = 4.f;
			copiedRect.Position().Y() = 3.f;
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(rect, copiedRect));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(rect, copiedRect, 10.f));
			copiedRect.Position().Y() = std::nextafter(1.f, 0.f);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(rect, copiedRect));

			copiedRect.Position().Y() = 1.f;
			copiedRect.Size().X() = 1.f;
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(rect, copiedRect));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(rect, copiedRect, 10.f));
			copiedRect.Size().X() = std::nextafter(2.f, 0.f);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(rect, copiedRect));

			copiedRect.Size().X() = 2.f;
			copiedRect.Size().Y() = 3.f;
			Assert::IsFalse(PonyMath::Shape::AreAlmostEqual(rect, copiedRect));
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(rect, copiedRect, 10.f));
			copiedRect.Size().Y() = std::nextafter(7.f, 0.f);
			Assert::IsTrue(PonyMath::Shape::AreAlmostEqual(rect, copiedRect));
		}

		static constexpr PonyMath::Shape::Rect<float> RectConstexpr()
		{
			auto defaultRect = PonyMath::Shape::Rect<float>();
			auto movedRect = std::move(defaultRect);

			movedRect.Position() = PonyMath::Core::Vector2<float>(0.f, 0.f);
			movedRect.Size() = PonyMath::Core::Vector2<float>(1.f, 2.f);

			movedRect.MinX(3.f);
			movedRect.MinY(4.f);
			movedRect.Min(PonyMath::Core::Vector2<float>(-4.f, -5.f));
			movedRect.MaxX(5.f);
			movedRect.MaxY(6.f);
			movedRect.Max(PonyMath::Core::Vector2<float>(8.f, 7.f));

			movedRect.Width(4.f);
			movedRect.Width<true>(5.f);
			movedRect.Height(3.f);
			movedRect.Height<true>(6.f);

			movedRect.Center(PonyMath::Core::Vector2<float>(4.f, 7.f));

			movedRect.Set(2.f, 1.f, 7.f, 8.f);
			movedRect.Set(PonyMath::Core::Vector2<float>(2.f, 6.f), PonyMath::Core::Vector2<float>(-4.f, 5.f));

			movedRect.ResolveNegativeSize();

			PonyMath::Shape::Rect<float> copied;
			copied = movedRect;
			movedRect = std::move(copied);

			return movedRect;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultRect = PonyMath::Shape::Rect<float>();
			[[maybe_unused]] constexpr auto rect = PonyMath::Shape::Rect<float>(1.f, 5.f, 1.f, 2.f);
			[[maybe_unused]] constexpr auto vectorRect = PonyMath::Shape::Rect<float>(PonyMath::Core::Vector2<float>(2.f, 3.f), PonyMath::Core::Vector2<float>(10.f, 1.f));
			[[maybe_unused]] constexpr auto copiedRect = rect;
			[[maybe_unused]] constexpr auto movedRect = RectConstexpr();

			[[maybe_unused]] constexpr auto position = rect.Position();
			[[maybe_unused]] constexpr auto size = rect.Size();

			[[maybe_unused]] constexpr auto minX = rect.MinX();
			[[maybe_unused]] constexpr auto minY = rect.MinY();
			[[maybe_unused]] constexpr auto min = rect.Min();
			[[maybe_unused]] constexpr auto maxX = rect.MaxX();
			[[maybe_unused]] constexpr auto maxY = rect.MaxY();
			[[maybe_unused]] constexpr auto max = rect.Max();

			[[maybe_unused]] constexpr auto width = rect.Width();
			[[maybe_unused]] constexpr auto height = rect.Height();

			[[maybe_unused]] constexpr auto center = rect.Center();

			[[maybe_unused]] constexpr auto perimeter = rect.Perimeter();
			[[maybe_unused]] constexpr auto area = rect.Area();

			[[maybe_unused]] constexpr auto contains = rect.Contains(PonyMath::Core::Vector2<float>(1.f, 1.f));

			[[maybe_unused]] constexpr auto norm = rect.Normalize(PonyMath::Core::Vector2<float>(4.f, 5.f));
			[[maybe_unused]] constexpr auto unnorm = rect.Unnormalize(norm);
			[[maybe_unused]] constexpr auto normR = rect.Normalize(vectorRect);
			[[maybe_unused]] constexpr auto unnormR = rect.Unnormalize(normR);

			[[maybe_unused]] constexpr auto converted = static_cast<PonyMath::Shape::Rect<double>>(rect);

			[[maybe_unused]] constexpr auto equal = rect == vectorRect;
			[[maybe_unused]] constexpr auto notEqual = rect != vectorRect;

			[[maybe_unused]] constexpr bool areAlmostEqual = PonyMath::Shape::AreAlmostEqual(rect, vectorRect);
		}
	};
}

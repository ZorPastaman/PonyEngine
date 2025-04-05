/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstddef>
#include <cstdint>
#include <utility>

import PonyMath.Core;

import PonyShader.Space;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Space
{
	TEST_CLASS(TransformTests)
	{
		TEST_METHOD(ConstructorTest)
		{
			const auto defaultTransform = PonyShader::Space::Transform();
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Identity == defaultTransform.ModelMatrix());
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Identity == defaultTransform.ViewMatrix());
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Identity == defaultTransform.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::Matrix4x4<float>::Predefined::Identity == defaultTransform.MvpMatrix());

			const PonyMath::Core::Matrix4x4<float> model = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(4.f, -2.f, 5.f), PonyMath::Core::Vector3(1.f, 0.1f, -2.f), PonyMath::Core::Vector3(-0.5f, 2.f, 1.f));
			const PonyMath::Core::Matrix4x4<float> view = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(2.f, -7.f, -4.f), PonyMath::Core::Vector3(-1.f, -2.f, -0.4f), PonyMath::Core::Vector3(2.f, -3.f, -2.f));
			const PonyMath::Core::Matrix4x4<float> projection = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 2.f, 0.5f, 1500.f);
			const PonyMath::Core::Matrix4x4<float> mvp = projection * view * model;
			const auto transform = PonyShader::Space::Transform(model, view, projection);
			Assert::IsTrue(model == transform.ModelMatrix());
			Assert::IsTrue(view == transform.ViewMatrix());
			Assert::IsTrue(projection == transform.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(mvp, transform.MvpMatrix()));

			auto copied = transform;
			Assert::IsTrue(model == copied.ModelMatrix());
			Assert::IsTrue(view == copied.ViewMatrix());
			Assert::IsTrue(projection == copied.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(mvp, copied.MvpMatrix()));

			const auto moved = std::move(copied);
			Assert::IsTrue(model == moved.ModelMatrix());
			Assert::IsTrue(view == moved.ViewMatrix());
			Assert::IsTrue(projection == moved.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(mvp, moved.MvpMatrix()));
		}

		TEST_METHOD(ModelMatrixTest)
		{
			PonyMath::Core::Matrix4x4<float> model = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(4.f, -2.f, 5.f), PonyMath::Core::Vector3(1.f, 0.1f, -2.f), PonyMath::Core::Vector3(-0.5f, 2.f, 1.f));
			const PonyMath::Core::Matrix4x4<float> view = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(2.f, -7.f, -4.f), PonyMath::Core::Vector3(-1.f, -2.f, -0.4f), PonyMath::Core::Vector3(2.f, -3.f, -2.f));
			const PonyMath::Core::Matrix4x4<float> projection = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 2.f, 0.5f, 1500.f);
			auto transform = PonyShader::Space::Transform(model, view, projection);
			model = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(-3.f, -7.f, 10.f), PonyMath::Core::Vector3(13.f, 12.f, 20.f), PonyMath::Core::Vector3(-2.f, -2.f, 3.f));
			PonyMath::Core::Matrix4x4<float> mvp = projection * view * model;
			transform.ModelMatrix(model);
			Assert::IsTrue(model == transform.ModelMatrix());
			Assert::IsTrue(view == transform.ViewMatrix());
			Assert::IsTrue(projection == transform.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(mvp, transform.MvpMatrix()));
		}

		TEST_METHOD(ViewMatrixTest)
		{
			const PonyMath::Core::Matrix4x4<float> model = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(4.f, -2.f, 5.f), PonyMath::Core::Vector3(1.f, 0.1f, -2.f), PonyMath::Core::Vector3(-0.5f, 2.f, 1.f));
			PonyMath::Core::Matrix4x4<float> view = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(2.f, -7.f, -4.f), PonyMath::Core::Vector3(-1.f, -2.f, -0.4f), PonyMath::Core::Vector3(2.f, -3.f, -2.f));
			const PonyMath::Core::Matrix4x4<float> projection = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 2.f, 0.5f, 1500.f);
			auto transform = PonyShader::Space::Transform(model, view, projection);
			view = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(-3.f, -7.f, 10.f), PonyMath::Core::Vector3(13.f, 12.f, 20.f), PonyMath::Core::Vector3(-2.f, -2.f, 3.f));
			PonyMath::Core::Matrix4x4<float> mvp = projection * view * model;
			transform.ViewMatrix(view);
			Assert::IsTrue(model == transform.ModelMatrix());
			Assert::IsTrue(view == transform.ViewMatrix());
			Assert::IsTrue(projection == transform.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(mvp, transform.MvpMatrix()));
		}

		TEST_METHOD(ProjectionMatrixTest)
		{
			const PonyMath::Core::Matrix4x4<float> model = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(4.f, -2.f, 5.f), PonyMath::Core::Vector3(1.f, 0.1f, -2.f), PonyMath::Core::Vector3(-0.5f, 2.f, 1.f));
			const PonyMath::Core::Matrix4x4<float> view = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(2.f, -7.f, -4.f), PonyMath::Core::Vector3(-1.f, -2.f, -0.4f), PonyMath::Core::Vector3(2.f, -3.f, -2.f));
			PonyMath::Core::Matrix4x4<float> projection = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 2.f, 0.5f, 1500.f);
			auto transform = PonyShader::Space::Transform(model, view, projection);
			projection = PonyMath::Core::PerspectiveMatrix(2.f, 5.f, 10.f, 500.f);
			PonyMath::Core::Matrix4x4<float> mvp = projection * view * model;
			transform.ProjectionMatrix(projection);
			Assert::IsTrue(model == transform.ModelMatrix());
			Assert::IsTrue(view == transform.ViewMatrix());
			Assert::IsTrue(projection == transform.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(mvp, transform.MvpMatrix()));
		}

		TEST_METHOD(AssignmentTest)
		{
			const PonyMath::Core::Matrix4x4<float> model = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(4.f, -2.f, 5.f), PonyMath::Core::Vector3(1.f, 0.1f, -2.f), PonyMath::Core::Vector3(-0.5f, 2.f, 1.f));
			const PonyMath::Core::Matrix4x4<float> view = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(2.f, -7.f, -4.f), PonyMath::Core::Vector3(-1.f, -2.f, -0.4f), PonyMath::Core::Vector3(2.f, -3.f, -2.f));
			const PonyMath::Core::Matrix4x4<float> projection = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 2.f, 0.5f, 1500.f);
			const PonyMath::Core::Matrix4x4<float> mvp = projection * view * model;
			const auto transform = PonyShader::Space::Transform(model, view, projection);
			Assert::IsTrue(model == transform.ModelMatrix());
			Assert::IsTrue(view == transform.ViewMatrix());
			Assert::IsTrue(projection == transform.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(mvp, transform.MvpMatrix()));

			auto copied = PonyShader::Space::Transform();
			copied = transform;
			Assert::IsTrue(model == copied.ModelMatrix());
			Assert::IsTrue(view == copied.ViewMatrix());
			Assert::IsTrue(projection == copied.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(mvp, copied.MvpMatrix()));

			auto moved = PonyShader::Space::Transform();
			moved = std::move(copied);
			Assert::IsTrue(model == moved.ModelMatrix());
			Assert::IsTrue(view == moved.ViewMatrix());
			Assert::IsTrue(projection == moved.ProjectionMatrix());
			Assert::IsTrue(PonyMath::Core::AreAlmostEqual(mvp, moved.MvpMatrix()));
		}

		TEST_METHOD(EqualTest)
		{
			PonyMath::Core::Matrix4x4<float> model = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(4.f, -2.f, 5.f), PonyMath::Core::Vector3(1.f, 0.1f, -2.f), PonyMath::Core::Vector3(-0.5f, 2.f, 1.f));
			PonyMath::Core::Matrix4x4<float> view = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(2.f, -7.f, -4.f), PonyMath::Core::Vector3(-1.f, -2.f, -0.4f), PonyMath::Core::Vector3(2.f, -3.f, -2.f));
			PonyMath::Core::Matrix4x4<float> projection = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 2.f, 0.5f, 1500.f);
			auto transform = PonyShader::Space::Transform(model, view, projection);
			const auto copied = transform;
			Assert::IsTrue(copied == transform);

			for (std::size_t i = 0; i < 16; ++i)
			{
				const float was = model.Span()[i];
				model.Span()[i] = std::nextafter(was, 100.f);
				transform.ModelMatrix(model);
				Assert::IsFalse(copied == transform);
				model.Span()[i] += 1.f;
				transform.ModelMatrix(model);
				Assert::IsFalse(copied == transform);
				model.Span()[i] = was;
				transform.ModelMatrix(model);
			}

			for (std::size_t i = 0; i < 16; ++i)
			{
				const float was = view.Span()[i];
				view.Span()[i] = std::nextafter(was, 100.f);
				transform.ViewMatrix(view);
				Assert::IsFalse(copied == transform);
				view.Span()[i] += 1.f;
				transform.ViewMatrix(view);
				Assert::IsFalse(copied == transform);
				view.Span()[i] = was;
				transform.ViewMatrix(view);
			}

			for (std::size_t i = 0; i < 16; ++i)
			{
				const float was = projection.Span()[i];
				projection.Span()[i] = std::nextafter(was, 100.f);
				transform.ProjectionMatrix(projection);
				Assert::IsFalse(copied == transform);
				projection.Span()[i] += 1.f;
				transform.ProjectionMatrix(projection);
				Assert::IsFalse(copied == transform);
				projection.Span()[i] = was;
				transform.ProjectionMatrix(projection);
			}
		}

		TEST_METHOD(AreEqualTest)
		{
			PonyMath::Core::Matrix4x4<float> model = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(4.f, -2.f, 5.f), PonyMath::Core::Vector3(1.f, 0.1f, -2.f), PonyMath::Core::Vector3(-0.5f, 2.f, 1.f));
			PonyMath::Core::Matrix4x4<float> view = PonyMath::Core::TrsMatrix(PonyMath::Core::Vector3(2.f, -7.f, -4.f), PonyMath::Core::Vector3(-1.f, -2.f, -0.4f), PonyMath::Core::Vector3(2.f, -3.f, -2.f));
			PonyMath::Core::Matrix4x4<float> projection = PonyMath::Core::PerspectiveMatrix(60.f * PonyMath::Core::DegToRad<float>, 2.f, 0.5f, 1500.f);
			auto transform = PonyShader::Space::Transform(model, view, projection);
			const auto copied = transform;
			Assert::IsTrue(PonyShader::Space::AreAlmostEqual(copied, transform));

			for (std::size_t i = 0; i < 16; ++i)
			{
				const float was = model.Span()[i];
				model.Span()[i] = std::nextafter(was, 100.f);
				transform.ModelMatrix(model);
				Assert::IsTrue(PonyShader::Space::AreAlmostEqual(copied, transform));
				model.Span()[i] += 1.f;
				transform.ModelMatrix(model);
				Assert::IsFalse(PonyShader::Space::AreAlmostEqual(copied, transform));
				Assert::IsTrue(PonyShader::Space::AreAlmostEqual(copied, transform, 5.f));
				model.Span()[i] = was;
				transform.ModelMatrix(model);
			}

			for (std::size_t i = 0; i < 16; ++i)
			{
				const float was = view.Span()[i];
				view.Span()[i] = std::nextafter(was, 100.f);
				transform.ViewMatrix(view);
				Assert::IsTrue(PonyShader::Space::AreAlmostEqual(copied, transform));
				view.Span()[i] += 1.f;
				transform.ViewMatrix(view);
				Assert::IsFalse(PonyShader::Space::AreAlmostEqual(copied, transform));
				Assert::IsTrue(PonyShader::Space::AreAlmostEqual(copied, transform, 5.f));
				view.Span()[i] = was;
				transform.ViewMatrix(view);
			}

			for (std::size_t i = 0; i < 16; ++i)
			{
				const float was = projection.Span()[i];
				projection.Span()[i] = std::nextafter(was, 100.f);
				transform.ProjectionMatrix(projection);
				Assert::IsTrue(PonyShader::Space::AreAlmostEqual(copied, transform));
				projection.Span()[i] += 1.f;
				transform.ProjectionMatrix(projection);
				Assert::IsFalse(PonyShader::Space::AreAlmostEqual(copied, transform));
				Assert::IsTrue(PonyShader::Space::AreAlmostEqual(copied, transform, 5.f));
				projection.Span()[i] = was;
				transform.ProjectionMatrix(projection);
			}
		}

		static constexpr PonyShader::Space::Transform TransformConstexpr()
		{
			auto transform = PonyShader::Space::Transform();
			auto moved = std::move(transform);

			transform.ModelMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity);
			transform.ViewMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity);
			transform.ProjectionMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity);

			auto copied = PonyShader::Space::Transform();
			copied = moved;
			moved = std::move(copied);

			return moved;
		}

		TEST_METHOD(ConstexprCompilationTest)
		{
			[[maybe_unused]] constexpr auto defaultTransform = PonyShader::Space::Transform();
			[[maybe_unused]] constexpr auto transform = PonyShader::Space::Transform(PonyMath::Core::Matrix4x4<float>::Predefined::Identity, PonyMath::Core::Matrix4x4<float>::Predefined::Identity, PonyMath::Core::Matrix4x4<float>::Predefined::Identity);
			[[maybe_unused]] constexpr auto copied = transform;
			[[maybe_unused]] constexpr auto moved = TransformConstexpr();

			[[maybe_unused]] constexpr auto model = transform.ModelMatrix();
			[[maybe_unused]] constexpr auto view = transform.ViewMatrix();
			[[maybe_unused]] constexpr auto projection = transform.ProjectionMatrix();
			[[maybe_unused]] constexpr auto mvp = transform.MvpMatrix();

			[[maybe_unused]] constexpr bool equal = transform == copied;
			[[maybe_unused]] constexpr bool notEqual = transform != copied;
		}
	};
}

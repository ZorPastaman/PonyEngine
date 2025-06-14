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
#include <cstdint>
#include <utility>

import PonyBase.Container;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Container
{
	TEST_CLASS(BufferViewTests)
	{
		TEST_METHOD(ContrustorTest)
		{
			const auto defaultView = PonyBase::Container::BufferView<int>();
			Assert::IsNull(defaultView.Buffer());

			auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(4u);
			const auto view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&buffer), reinterpret_cast<std::uintptr_t>(view.Buffer()));

			Assert::ExpectException<std::invalid_argument>([&]
			{
				auto b = PonyBase::Container::Buffer::Create<std::int32_t>(4u);
				const auto v = PonyBase::Container::BufferView<std::uint16_t>(b);
			});

			const auto bufferC = PonyBase::Container::Buffer::Create<std::int32_t>(4u);
			const auto viewC = PonyBase::Container::BufferView<const std::uint32_t>(bufferC);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&bufferC), reinterpret_cast<std::uintptr_t>(viewC.Buffer()));

			Assert::ExpectException<std::invalid_argument>([&]
			{
				const auto b = PonyBase::Container::Buffer::Create<std::int32_t>(4u);
				const auto v = PonyBase::Container::BufferView<const std::uint16_t>(b);
			});

			auto copied = view;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&buffer), reinterpret_cast<std::uintptr_t>(copied.Buffer()));

			const auto moved = std::move(copied);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&buffer), reinterpret_cast<std::uintptr_t>(moved.Buffer()));
		}

		TEST_METHOD(StrideTest)
		{
			const auto view = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::AreEqual(static_cast<std::uint32_t>(sizeof(std::uint32_t)), view.Stride());
		}

		TEST_METHOD(CountTest)
		{
			auto view = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::AreEqual(0u, view.Count());

			auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(4u);
			view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::AreEqual(4u, view.Count());
		}

		TEST_METHOD(SizeTest)
		{
			auto view = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::AreEqual(std::size_t{0}, view.Size());

			auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(4u);
			view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::AreEqual(std::size_t{16}, view.Size());
		}

		TEST_METHOD(DataTest)
		{
			auto view = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::IsNull(view.Data());
			const auto viewC = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::IsNull(viewC.Data());

			auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(4u);
			view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(buffer.Data()), reinterpret_cast<std::uintptr_t>(view.Data()));

			const auto viewCC = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(buffer.Data()), reinterpret_cast<std::uintptr_t>(viewCC.Data()));
		}

		TEST_METHOD(BufferTest)
		{
			auto view = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::IsNull(view.Buffer());
			const auto viewC = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::IsNull(viewC.Buffer());

			auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(4u);
			view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&buffer), reinterpret_cast<std::uintptr_t>(view.Buffer()));

			const auto viewCC = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&buffer), reinterpret_cast<std::uintptr_t>(viewCC.Buffer()));
		}

		TEST_METHOD(IsEmptyTest)
		{
			auto view = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::IsTrue(view.IsEmpty());

			auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(0u);
			view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::IsTrue(view.IsEmpty());

			buffer = PonyBase::Container::Buffer::Create<std::int32_t>(4u);
			view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::IsFalse(view.IsEmpty());
		}

		TEST_METHOD(SpanTest)
		{
			auto view = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::AreEqual(std::size_t{0}, view.Span().size());
			const auto viewC = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::AreEqual(std::size_t{0}, viewC.Span().size());

			const std::array<std::uint32_t, 3> data = { 2, 8, 1 };
			auto buffer = PonyBase::Container::Buffer::Create<std::uint32_t>(data);
			view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], view.Span()[i]);
			}

			const auto viewCC = PonyBase::Container::BufferView<const std::uint32_t>(buffer);
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], viewCC.Span()[i]);
			}
		}

		TEST_METHOD(ToBoolTest)
		{
			auto view = PonyBase::Container::BufferView<std::uint32_t>();
			Assert::IsFalse(static_cast<bool>(view));

			auto buffer = PonyBase::Container::Buffer(4u, 4u);
			view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::IsTrue(static_cast<bool>(view));

			buffer = PonyBase::Container::Buffer::Create<std::int32_t>(2u);
			view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			Assert::IsTrue(static_cast<bool>(view));
		}

		TEST_METHOD(AccessTest)
		{
			const std::array<std::uint32_t, 3> data = { 2, 8, 1 };
			auto buffer = PonyBase::Container::Buffer::Create<std::uint32_t>(data);
			auto view = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], view[i]);
			}

			const auto viewC = PonyBase::Container::BufferView<std::uint32_t>(buffer);
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], viewC[i]);
			}
		}

		TEST_METHOD(AssignmentTest)
		{
			auto buffer = PonyBase::Container::Buffer(4u, 4u);
			const auto view = PonyBase::Container::BufferView<std::uint32_t>(buffer);

			auto copied = PonyBase::Container::BufferView<std::uint32_t>();
			copied = view;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&buffer), reinterpret_cast<std::uintptr_t>(copied.Buffer()));

			auto moved = PonyBase::Container::BufferView<std::uint32_t>();
			moved = std::move(copied);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&buffer), reinterpret_cast<std::uintptr_t>(moved.Buffer()));
		}
	};
}

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
#include <utility>

import PonyBase.Container;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Container
{
	TEST_CLASS(BufferTests)
	{
		TEST_METHOD(ContructorTest)
		{
			const auto defaultBuffer = PonyBase::Container::Buffer();
			Assert::AreEqual(0u, defaultBuffer.Stride());
			Assert::AreEqual(0u, defaultBuffer.Count());
			Assert::IsFalse(static_cast<bool>(defaultBuffer));

			const auto buffer = PonyBase::Container::Buffer(4u, 7u);
			Assert::AreEqual(4u, buffer.Stride());
			Assert::AreEqual(7u, buffer.Count());
			Assert::IsTrue(static_cast<bool>(buffer));

			const auto paramedBuffer = PonyBase::Container::Buffer(PonyBase::Container::BufferParams{.stride = 3u, .count = 5u});
			Assert::AreEqual(3u, paramedBuffer.Stride());
			Assert::AreEqual(5u, paramedBuffer.Count());
			Assert::IsTrue(static_cast<bool>(paramedBuffer));

			const std::array<std::int32_t, 3> data = { 4, 6, 9 };
			const auto spannedBuffer = PonyBase::Container::Buffer(sizeof(std::int32_t), std::span<const std::byte>(reinterpret_cast<const std::byte*>(data.data()), data.size() * sizeof(std::int32_t)));
			Assert::AreEqual(static_cast<std::uint32_t>(sizeof(std::int32_t)), spannedBuffer.Stride());
			Assert::AreEqual(3u, spannedBuffer.Count());
			Assert::IsTrue(static_cast<bool>(spannedBuffer));
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], spannedBuffer.Get<std::int32_t>(i));
			}

			PonyBase::Container::Buffer copied = buffer;
			Assert::AreEqual(4u, copied.Stride());
			Assert::AreEqual(7u, copied.Count());
			Assert::IsTrue(static_cast<bool>(copied));

			const PonyBase::Container::Buffer moved = std::move(copied);
			Assert::AreEqual(4u, moved.Stride());
			Assert::AreEqual(7u, moved.Count());
			Assert::IsTrue(static_cast<bool>(moved));
		}

		TEST_METHOD(CreateTest)
		{
			const auto buffer = PonyBase::Container::Buffer::Create<std::int16_t>(7u);
			Assert::AreEqual(static_cast<std::uint32_t>(sizeof(std::int16_t)), buffer.Stride());
			Assert::AreEqual(7u, buffer.Count());
			Assert::IsTrue(static_cast<bool>(buffer));

			const std::array<std::int32_t, 3> data = { 4, 6, 9 };
			const auto spannedBuffer = PonyBase::Container::Buffer::Create<std::int32_t>(data);
			Assert::AreEqual(static_cast<std::uint32_t>(sizeof(std::int32_t)), spannedBuffer.Stride());
			Assert::AreEqual(3u, spannedBuffer.Count());
			Assert::IsTrue(static_cast<bool>(spannedBuffer));
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], spannedBuffer.Get<std::int32_t>(i));
			}
		}

		TEST_METHOD(StrideTest)
		{
			const auto buffer = PonyBase::Container::Buffer(2u, 7u);
			Assert::AreEqual(2u, buffer.Stride());
		}

		TEST_METHOD(CountTest)
		{
			const auto buffer = PonyBase::Container::Buffer(2u, 5u);
			Assert::AreEqual(5u, buffer.Count());
		}

		TEST_METHOD(SizeTest)
		{
			const auto buffer = PonyBase::Container::Buffer(3u, 8u);
			Assert::AreEqual(std::size_t{3} * 8u, buffer.Size());
		}

		TEST_METHOD(DataTest)
		{
			const std::array<std::int32_t, 3> data = { 4, 6, 9 };
			auto spannedBuffer = PonyBase::Container::Buffer::Create<std::int32_t>(data);
			const auto span = std::span<const std::byte, sizeof(std::int32_t) * 3>(reinterpret_cast<const std::byte*>(data.data()), sizeof(std::int32_t) * 3);
			for (std::size_t i = 0; i < span.size(); ++i)
			{
				Assert::AreEqual(static_cast<char>(span[i]), static_cast<char>(spannedBuffer.Data()[i]));
			}

			const auto spannedBufferC = PonyBase::Container::Buffer::Create<std::int32_t>(data);
			for (std::size_t i = 0; i < span.size(); ++i)
			{
				Assert::AreEqual(static_cast<char>(span[i]), static_cast<char>(spannedBufferC.Data()[i]));
			}
		}

		TEST_METHOD(IsEmptyTest)
		{
			const auto defaultBuffer = PonyBase::Container::Buffer();
			Assert::IsTrue(defaultBuffer.IsEmpty());

			const auto buffer = PonyBase::Container::Buffer(2u, 7u);
			Assert::IsFalse(buffer.IsEmpty());

			const auto emptyBuffer = PonyBase::Container::Buffer(4u, 0u);
			Assert::IsTrue(emptyBuffer.IsEmpty());
		}

		TEST_METHOD(GetTest)
		{
			const std::array<std::int32_t, 3> data = { 4, 6, 9 };
			auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(data);
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], buffer.Get<std::int32_t>(i));
			}

			const auto bufferC = PonyBase::Container::Buffer::Create<std::int32_t>(data); 
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], bufferC.Get<std::int32_t>(i));
			}
		}

		TEST_METHOD(SpanTest)
		{
			const std::array<std::int32_t, 3> data = { 4, 6, 9 };
			auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(data);
			const auto span = buffer.Span<std::int32_t>();
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], span[i]);
			}

			const auto bufferC = PonyBase::Container::Buffer::Create<std::int32_t>(data);
			const auto spanC = bufferC.Span<std::int32_t>();
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], spanC[i]);
			}
		}

		TEST_METHOD(CopyFrom)
		{
			const std::array<std::int32_t, 3> data = { 4, 6, 9 };
			const auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(data);
			auto target = PonyBase::Container::Buffer(4u, 3u);
			target.CopyFrom(buffer);
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], target.Get<std::int32_t>(i));
			}

			auto failByStride = PonyBase::Container::Buffer(2u, 3u);
			Assert::ExpectException<std::invalid_argument>([&]{ failByStride.CopyFrom(buffer); });
			auto failByCount = PonyBase::Container::Buffer(4u, 4u);
			Assert::ExpectException<std::invalid_argument>([&]{ failByCount.CopyFrom(buffer); });
		}

		TEST_METHOD(ToBoolTest)
		{
			const auto defaultBuffer = PonyBase::Container::Buffer();
			Assert::IsFalse(static_cast<bool>(defaultBuffer));

			const auto buffer = PonyBase::Container::Buffer(1u, 3u);
			Assert::IsTrue(static_cast<bool>(buffer));
		}

		TEST_METHOD(AssignmentTest)
		{
			const std::array<std::int32_t, 3> data = { 4, 6, 9 };
			const auto buffer = PonyBase::Container::Buffer::Create<std::int32_t>(data);

			auto copiedBuffer = PonyBase::Container::Buffer();
			copiedBuffer = buffer;
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], copiedBuffer.Get<std::int32_t>(i));
			}

			auto movedBuffer = PonyBase::Container::Buffer();
			movedBuffer = std::move(copiedBuffer);
			for (std::size_t i = 0; i < data.size(); ++i)
			{
				Assert::AreEqual(data[i], movedBuffer.Get<std::int32_t>(i));
			}
		}
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <exception>

import PonyEngine.Core;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(HandledExceptionTests)
	{
		TEST_METHOD(ConstructorTest)
		{
			const auto exception = std::logic_error("Message!");

			const auto defaultHandled = PonyEngine::Core::HandledException();
			Assert::AreEqual(std::exception().what(), defaultHandled.what());
			Assert::IsFalse(static_cast<bool>(defaultHandled.Exception()));

			auto handled = PonyEngine::Core::HandledException(exception);
			Assert::AreEqual(exception.what(), handled.what());
			bool caught = false;
			try
			{
				std::rethrow_exception(handled.Exception());
			}
			catch (const std::logic_error&)
			{
				caught = true;
			}
			Assert::IsTrue(caught);

			const PonyEngine::Core::HandledException copiedHandled = handled;
			Assert::AreEqual(exception.what(), copiedHandled.what());
			Assert::IsTrue(handled.Exception() == copiedHandled.Exception());

			const PonyEngine::Core::HandledException movedHandled = std::move(handled);
			Assert::AreEqual(exception.what(), movedHandled.what());
			Assert::IsTrue(copiedHandled.Exception() == movedHandled.Exception());
		}

		TEST_METHOD(AssignmentTest)
		{
			const auto exception = std::logic_error("Message!");
			auto handled = PonyEngine::Core::HandledException(exception);

			auto copiedHandled = PonyEngine::Core::HandledException();
			copiedHandled = handled;
			Assert::AreEqual(exception.what(), copiedHandled.what());
			Assert::IsTrue(handled.Exception() == copiedHandled.Exception());

			auto movedHandled = PonyEngine::Core::HandledException();
			movedHandled = std::move(handled);
			Assert::AreEqual(exception.what(), movedHandled.what());
			Assert::IsTrue(copiedHandled.Exception() == movedHandled.Exception());
		}
	};
}

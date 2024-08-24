/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Log.Factory;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Log
{
	TEST_CLASS(LoggerDeleterTests)
	{
		class EmptySubLogger final : public PonyEngine::Log::ISubLogger
		{
		public:
			virtual void Log(const PonyEngine::Log::LogEntry&) noexcept override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		class SubLoggerDestroyer final : public PonyEngine::Log::ISubLoggerDestroyer
		{
		public:
			PonyEngine::Log::ISubLogger* lastSubLogger = nullptr;

			virtual void Destroy(PonyEngine::Log::ISubLogger* subLogger) noexcept override
			{
				lastSubLogger = subLogger;
			}
		};

		TEST_METHOD(ConstructorTest)
		{
			auto subLoggerDestroyer = SubLoggerDestroyer();
			const auto subLoggerDeleter = PonyEngine::Log::SubLoggerDeleter(subLoggerDestroyer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&subLoggerDestroyer), reinterpret_cast<std::uintptr_t>(&subLoggerDeleter.SubLoggerDestroyer()));

			PonyEngine::Log::SubLoggerDeleter copiedSubLoggerDeleter = subLoggerDeleter;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&subLoggerDestroyer), reinterpret_cast<std::uintptr_t>(&copiedSubLoggerDeleter.SubLoggerDestroyer()));

			const PonyEngine::Log::SubLoggerDeleter movedSubLoggerDeleter = std::move(copiedSubLoggerDeleter);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&subLoggerDestroyer), reinterpret_cast<std::uintptr_t>(&movedSubLoggerDeleter.SubLoggerDestroyer()));
		}

		TEST_METHOD(DeleteTest)
		{
			const auto subLogger = new EmptySubLogger();
			auto subLoggerDestroyer = SubLoggerDestroyer();
			const auto subLoggerDeleter = PonyEngine::Log::SubLoggerDeleter(subLoggerDestroyer);
			subLoggerDeleter(subLogger);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(subLogger), reinterpret_cast<std::uintptr_t>(subLoggerDestroyer.lastSubLogger));

			delete subLogger;
		}

		TEST_METHOD(AssignmentTest)
		{
			auto subLoggerDestroyer = SubLoggerDestroyer();
			auto anotherSubLoggerDestroyer = SubLoggerDestroyer();
			auto subLoggerDeleter = PonyEngine::Log::SubLoggerDeleter(subLoggerDestroyer);

			auto copiedSubLoggerDeleter = PonyEngine::Log::SubLoggerDeleter(anotherSubLoggerDestroyer);
			copiedSubLoggerDeleter = subLoggerDeleter;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&subLoggerDestroyer), reinterpret_cast<std::uintptr_t>(&copiedSubLoggerDeleter.SubLoggerDestroyer()));

			auto movedSubLoggerDeleter = PonyEngine::Log::SubLoggerDeleter(anotherSubLoggerDestroyer);
			movedSubLoggerDeleter = std::move(subLoggerDeleter);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&subLoggerDestroyer), reinterpret_cast<std::uintptr_t>(&movedSubLoggerDeleter.SubLoggerDestroyer()));
		}
	};
}

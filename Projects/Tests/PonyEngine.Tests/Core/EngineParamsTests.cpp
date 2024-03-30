/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstdint>;
import <exception>;

import PonyEngine.Core.Factories;
import PonyEngine.Debug.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(EngineParamsTests)
	{
		class EmptyLogger final : public PonyEngine::Debug::Log::ILogger
		{
		public:
			[[nodiscard("Pure function")]]
			virtual const char* GetName() const noexcept override { return ""; }

			virtual void Log(PonyEngine::Debug::Log::LogType logType, const PonyEngine::Debug::Log::LogInput& logInput) noexcept override { }
			virtual void LogException(const std::exception& exception, const PonyEngine::Debug::Log::LogInput& logInput) noexcept override { }

			virtual void AddSubLogger(PonyEngine::Debug::Log::ISubLogger* subLogger) override { }
			virtual void RemoveSubLogger(PonyEngine::Debug::Log::ISubLogger* subLogger) override { }
		};

		TEST_METHOD(ContructorTest)
		{
			EmptyLogger logger;
			PonyEngine::Core::EngineParams engineParams(logger);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(static_cast<PonyEngine::Debug::Log::ILogger*>(&logger)), reinterpret_cast<std::uintptr_t>(&engineParams.logger));
		}
	};
}

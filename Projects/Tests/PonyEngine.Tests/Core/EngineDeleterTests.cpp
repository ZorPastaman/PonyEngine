/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import PonyEngine.Core.Factory;
import PonyEngine.Log;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
	TEST_CLASS(EngineDeleterTests)
	{
		class EmptyLogger final : public PonyEngine::Log::ILogger
		{
		public:
			virtual void Log(const PonyEngine::Log::LogType, const PonyEngine::Log::LogInput&) noexcept override
			{
			}

			virtual void LogException(const std::exception&, const PonyEngine::Log::LogInput&) noexcept override
			{
			}

			virtual void AddSubLogger(PonyEngine::Log::ISubLogger&) override
			{
			}

			virtual void RemoveSubLogger(PonyEngine::Log::ISubLogger&) override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		class EmptySystemManager final : public PonyEngine::Core::ISystemManager
		{
		public:
			[[nodiscard("Pure function")]]
			virtual void* FindSystem(const std::type_info&) const noexcept override
			{
				return nullptr;
			}
		};

		class EmptyEngine final : public PonyEngine::Core::IEngine
		{
		public:
			mutable EmptyLogger logger = EmptyLogger();
			mutable EmptySystemManager systemManager = EmptySystemManager();

			[[nodiscard("Pure function")]]
			virtual std::size_t FrameCount() const noexcept override
			{
				return 0;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Log::ILogger& Logger() const noexcept override
			{
				return logger;
			}

			[[nodiscard("Pure function")]]
			virtual PonyEngine::Core::ISystemManager& SystemManager() const noexcept override
			{
				return systemManager;
			}

			[[nodiscard("Pure function")]]
			virtual bool IsRunning() const noexcept override
			{
				return true;
			}

			[[nodiscard("Pure function")]]
			virtual int ExitCode() const noexcept override
			{
				return 0;
			}

			virtual void Stop(int) noexcept override
			{
			}

			[[nodiscard("Pure function")]]
			virtual const char* Name() const noexcept override
			{
				return "";
			}
		};

		class EngineDestroyer final : public PonyEngine::Core::IEngineDestroyer
		{
		public:
			PonyEngine::Core::IEngine* lastEngine = nullptr;

			virtual void Destroy(PonyEngine::Core::IEngine* engine) noexcept override
			{
				lastEngine = engine;
			}
		};

		TEST_METHOD(ConstructorTest)
		{
			auto engineDestroyer = EngineDestroyer();
			const auto engineDeleter = PonyEngine::Core::EngineDeleter(engineDestroyer);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&engineDestroyer), reinterpret_cast<std::uintptr_t>(engineDeleter.EngineDestroyer()));

			PonyEngine::Core::EngineDeleter copiedEngineDeleter = engineDeleter;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&engineDestroyer), reinterpret_cast<std::uintptr_t>(copiedEngineDeleter.EngineDestroyer()));

			const PonyEngine::Core::EngineDeleter movedEngineDeleter = std::move(copiedEngineDeleter);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&engineDestroyer), reinterpret_cast<std::uintptr_t>(movedEngineDeleter.EngineDestroyer()));
		}

		TEST_METHOD(DeleteTest)
		{
			const auto engine = new EmptyEngine();
			auto engineDestroyer = EngineDestroyer();
			const auto engineDeleter = PonyEngine::Core::EngineDeleter(engineDestroyer);
			engineDeleter(engine);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(engine), reinterpret_cast<std::uintptr_t>(engineDestroyer.lastEngine));

			delete engine;
		}

		TEST_METHOD(AssignmentTest)
		{
			auto engineDestroyer = EngineDestroyer();
			auto anotherEngineDestroyer = EngineDestroyer();
			auto engineDeleter = PonyEngine::Core::EngineDeleter(engineDestroyer);

			auto copiedEngineDeleter = PonyEngine::Core::EngineDeleter(anotherEngineDestroyer);
			copiedEngineDeleter = engineDeleter;
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&engineDestroyer), reinterpret_cast<std::uintptr_t>(copiedEngineDeleter.EngineDestroyer()));

			auto movedEngineDeleter = PonyEngine::Core::EngineDeleter(anotherEngineDestroyer);
			movedEngineDeleter = std::move(engineDeleter);
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(&engineDestroyer), reinterpret_cast<std::uintptr_t>(movedEngineDeleter.EngineDestroyer()));
		}
	};
}

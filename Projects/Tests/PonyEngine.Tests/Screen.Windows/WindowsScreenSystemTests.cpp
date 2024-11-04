/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include "PonyBase/Core/Windows/Framework.h"

#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"

import PonyMath.Utility;

import PonyEngine.Screen.Windows.Implementation;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Screen
{
	TEST_CLASS(WindowsScreenSystemTests)
	{
		TEST_METHOD(DisplayResolutionTest)
		{
			auto logger = Core::Logger();
			auto application = Core::Application();
			application.logger = &logger;
			auto engine = Core::Engine();
			engine.application = &application;
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{});
			auto system = factory.systemFactory->Create(engine, PonyEngine::Core::EngineSystemParams{});
			std::get<0>(system.system)->Begin();
			auto screenSystem = dynamic_cast<PonyEngine::Screen::IScreenSystem*>(std::get<0>(system.system).Get());

			auto expectedResolution = PonyMath::Utility::Resolution<unsigned int>(static_cast<unsigned int>(GetSystemMetrics(SM_CXSCREEN)), static_cast<unsigned int>(GetSystemMetrics(SM_CYSCREEN)));
			Assert::IsTrue(expectedResolution == screenSystem->DisplayResolution());

			std::get<0>(system.system)->End();
		}
	};
}

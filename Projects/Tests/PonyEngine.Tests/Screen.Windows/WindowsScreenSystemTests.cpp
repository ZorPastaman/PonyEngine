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

#include <cstdint>
#include <variant>

#include "Mocks/Application.h"
#include "Mocks/Logger.h"
#include "Mocks/Engine.h"

import PonyMath.Utility;

import PonyEngine.Screen.Windows.Impl;

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
			const auto factory = PonyEngine::Screen::CreateWindowsScreenFactory(application, PonyEngine::Screen::WindowsScreenSystemFactoryParams{}, PonyEngine::Screen::WindowsScreenSystemParams{});
			auto system = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			std::get<0>(system.system)->Begin();
			auto screenSystem = dynamic_cast<PonyEngine::Screen::IScreenSystem*>(std::get<0>(system.system).get());

			auto expectedResolution = PonyMath::Utility::Resolution<std::uint32_t>(static_cast<std::uint32_t>(GetSystemMetrics(SM_CXSCREEN)), static_cast<std::uint32_t>(GetSystemMetrics(SM_CYSCREEN)));
			Assert::IsTrue(expectedResolution == screenSystem->DisplayResolution());

			std::get<0>(system.system)->End();
		}
	};
}

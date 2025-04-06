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

import Mocks;

import PonyMath.Utility;

import PonyEngine.Screen.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Screen
{
	TEST_CLASS(WindowsScreenSystemTests)
	{
		TEST_METHOD(DisplayResolutionTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			auto engine = Mocks::Engine();
			engine.application = &application;
			const auto factory = PonyEngine::Screen::Windows::CreateScreenFactory(application, PonyEngine::Screen::Windows::ScreenSystemFactoryParams{}, PonyEngine::Screen::Windows::ScreenSystemParams{});
			auto system = factory.systemFactory->Create(engine, PonyEngine::Core::SystemParams{});
			std::get<0>(system.system)->Begin();
			auto screenSystem = dynamic_cast<PonyEngine::Screen::IScreenSystem*>(std::get<0>(system.system).get());

			auto expectedResolution = PonyMath::Utility::Resolution<std::uint32_t>(static_cast<std::uint32_t>(GetSystemMetrics(SM_CXSCREEN)), static_cast<std::uint32_t>(GetSystemMetrics(SM_CYSCREEN)));
			Assert::IsTrue(expectedResolution == screenSystem->DisplayResolution());

			std::get<0>(system.system)->End();
		}
	};
}

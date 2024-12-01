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
#include <memory>

#include "Mocks/Application.h"
#include "Mocks/Logger.h"

import PonyEngine.Window.Windows.Impl;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(WindowsClassTests)
	{
		TEST_METHOD(CreateWindowsClassTest)
		{
			auto logger = Mocks::Logger();
			auto application = Mocks::Application();
			application.logger = &logger;
			const auto params = PonyEngine::Window::WindowsClassParams{.name = L"Test", .icon = nullptr, .smallIcon = nullptr, .cursor = nullptr}; // TODO: Add tests for all the fields.
			std::unique_ptr<PonyEngine::Window::WindowsClass> windowsClass = PonyEngine::Window::CreateWindowsClass(application, params).windowsClass;

			WNDCLASSEXW classParams;
			Assert::IsTrue(GetClassInfoExW(windowsClass->Instance(), params.name.c_str(), &classParams));
			Assert::IsTrue(GetClassInfoExW(windowsClass->Instance(), reinterpret_cast<LPCWSTR>(windowsClass->Class()), &classParams));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(nullptr), reinterpret_cast<std::uintptr_t>(classParams.hIcon));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(nullptr), reinterpret_cast<std::uintptr_t>(classParams.hIconSm));
			const auto classCursor = static_cast<HCURSOR>(LoadImageW(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
			Assert::AreEqual(reinterpret_cast<std::uintptr_t>(classCursor), reinterpret_cast<std::uintptr_t>(classParams.hCursor));

			const HINSTANCE hInstance = windowsClass->Instance();
			const ATOM atom = windowsClass->Class();
			windowsClass.reset();
			Assert::IsFalse(GetClassInfoExW(hInstance, reinterpret_cast<LPCWSTR>(atom), &classParams));
		}
	};
}

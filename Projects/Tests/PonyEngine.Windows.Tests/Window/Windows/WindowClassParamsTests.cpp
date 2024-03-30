/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <string>;

import PonyEngine.Window.Windows.Factories;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(WindowClassParamsTests)
	{
		TEST_METHOD(ConstructorTest)
		{
			const wchar_t* className = L"Class";
			PonyEngine::Window::WindowClassParams params(className);
			Assert::AreEqual(className, params.GetWindowClassName().c_str());

			std::wstring classNameString = className;
			PonyEngine::Window::WindowClassParams stringParams(classNameString);
			Assert::AreEqual(className, params.GetWindowClassName().c_str());

			PonyEngine::Window::WindowClassParams movedStringParams(std::move(classNameString));
			Assert::AreEqual(className, params.GetWindowClassName().c_str());
		}
	};
}

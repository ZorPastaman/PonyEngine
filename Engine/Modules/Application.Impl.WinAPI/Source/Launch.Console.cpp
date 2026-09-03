/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

import std;

import PonyEngine.Application.Impl.WinAPI;

int main(const int argc, const char* const argv[])
{
	try
	{
		return std::make_unique<PonyEngine::Application::ConsoleProcess>(PonyEngine::Application::MakeCommandLineView(argc, argv))->Run();
	}
	catch (const std::exception& e)
	{
		std::println(std::cerr, "{}:\n{}", typeid(e).name(), e.what());
		return -1;
	}
	catch (...)
	{
		std::println(std::cerr, "Unexpected exception");
		return -1;
	}
}

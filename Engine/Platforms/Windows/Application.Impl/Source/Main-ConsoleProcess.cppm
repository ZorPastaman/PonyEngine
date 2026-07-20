/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Impl.Windows:ConsoleProcess;

export namespace PonyEngine::Application::Windows
{
	class ConsoleProcess final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleProcess(int argc, const char* const argv[]);

		[[nodiscard("Must be returned from main")]]
		int Run();

	private:
	};
}

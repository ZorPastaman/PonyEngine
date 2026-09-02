/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <shellapi.h>

export module PonyEngine.Application.Impl.Windows:CommandLine;

import std;

import PonyEngine.Text.WinAPI;

export namespace PonyEngine::Application
{
	/// @brief Makes a command line view.
	/// @param argc Main argc argument.
	/// @param argv Main argv argument.
	/// @return Command line view.
	[[nodiscard("Pure function")]]
	std::vector<std::string_view> MakeCommandLineView(int argc, const char* const argv[]);

	/// @brief Makes a command line.
	/// @return Command line.
	[[nodiscard("Pure function")]]
	std::vector<std::string> MakeCommandLine();
	/// @brief Makes a command line view.
	/// @param commandLine Command line.
	/// @return Command line view.
	[[nodiscard("Pure function")]]
	std::vector<std::string_view> MakeCommandLineView(std::span<const std::string> commandLine);
}

namespace PonyEngine::Application
{
	std::vector<std::string_view> MakeCommandLineView(const int argc, const char* const argv[])
	{
		std::vector<std::string_view> commandLine;
		commandLine.reserve(argc);
		for (int i = 0; i < argc; ++i)
		{
			commandLine.push_back(argv[i]);
		}

		return commandLine;
	}

	std::vector<std::string> MakeCommandLine()
	{
		int argc;
		const auto argv = std::unique_ptr<wchar_t*, decltype(&LocalFree)>(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

		std::vector<std::string> commandLine;
		commandLine.reserve(argc);

		for (int i = 0; i < argc; ++i)
		{
			const std::wstring_view source = argv.get()[i];
			const std::size_t size = Text::GetStringSize(source);
			std::string arg;
			arg.resize(size);
			const std::size_t copied = Text::ConvertToString(source, arg);
			arg.resize(copied);
			arg.shrink_to_fit();

			commandLine.push_back(std::move(arg));
		}

		return commandLine;
	}

	std::vector<std::string_view> MakeCommandLineView(const std::span<const std::string> commandLine)
	{
		return std::vector<std::string_view>(commandLine.cbegin(), commandLine.cend());
	}
}

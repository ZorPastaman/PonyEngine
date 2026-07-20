/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

#include <shellapi.h>

export module PonyEngine.Application.Impl.Windows:GUIProcess;

import PonyEngine.Application.Impl;
import PonyEngine.Application.Windows;
import PonyEngine.Log;
import PonyEngine.Platform.Windows;

import :Console;
import :Path;
import :Process;

export namespace PonyEngine::Application::Windows
{
	class GUIProcess final : private IMainData, private IResourceProvider, private IMessagePump
	{
	public:
		[[nodiscard("Pure constructor")]]
		GUIProcess(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd);
		GUIProcess(const GUIProcess&) = delete;
		GUIProcess(GUIProcess&&) = delete;

		~GUIProcess() noexcept;

		[[nodiscard("Must be returned from main")]]
		int Run();

		GUIProcess& operator =(const GUIProcess&) = delete;
		GUIProcess& operator =(GUIProcess&&) = delete;

	private:
		[[nodiscard("Pure function")]] 
		virtual HINSTANCE Instance() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual HINSTANCE PrevInstance() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual PSTR CommandLine() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual int ShowCommand() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual HICON MainIcon() const override;

		[[nodiscard("Pure function")]] 
		virtual UINT LastMessageType() const override;
		[[nodiscard("Pure function")]] 
		virtual DWORD LastMessageRawTime() const override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTime() const override;
		[[nodiscard("Pure function")]] 
		virtual POINT LastMessagePoint() const override;

		void UpdateCommandLine();
		void AddApplicationInterfaces();
		void RemoveApplicationInterfaces();

		void Initialize();
		void Finalize();

		[[nodiscard("Pure function")]]
		int RunMainLoop();
		void TickMessagePump();
		void UpdateMessageTime(DWORD newMessageTime) noexcept;

		HINSTANCE instance;
		HINSTANCE prevInstance;
		PSTR cmdLine;
		int showCmd;

		std::vector<std::string> commandLineSource;
		std::vector<std::string_view> commandLine;

		std::chrono::time_point<std::chrono::steady_clock> lastMessageTime; ///< Time of the last message.
		DWORD lastMessageRawTime; ///< Raw time of the last message.
		UINT lastMessageType;
		POINT lastMessagePoint;

		std::unique_ptr<App> application;
	};
}

namespace PonyEngine::Application::Windows
{
	GUIProcess::GUIProcess(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd) :
		instance{hInstance},
		prevInstance{hPrevInstance},
		cmdLine{lpCmdLine},
		showCmd{nShowCmd},
		lastMessageTime(std::chrono::steady_clock::now()),
		lastMessageRawTime(GetTickCount()),
		lastMessageType{0u},
		lastMessagePoint{.x = 0l, .y = 0l}
	{
		SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
		UpdateCommandLine();

		application = std::make_unique<App>(commandLine, GetExecutablePath(), GetLocalDataDirectory(), GetUserDataDirectory(), GetTempDataDirectory());
		AddApplicationInterfaces();

#ifdef PONY_ENGINE_CREATE_CONSOLE
		CreateConsole();
		SetConsoleCodePage(CP_UTF8);
#endif
	}

	GUIProcess::~GUIProcess() noexcept
	{
#ifdef PONY_ENGINE_CREATE_CONSOLE
		try
		{
			DestroyConsole();
		}
		catch (...)
		{
			// Highly unlikely and doesn't matter.
		}
#endif

		try
		{
			RemoveApplicationInterfaces();
		}
		catch (...)
		{
			// Highly unlikely and doesn't matter.
		}
	}

	int GUIProcess::Run()
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Wrong thread.");

		Initialize();
		const int exitCode = RunMainLoop();
		Finalize();

		return exitCode;
	}

	HINSTANCE GUIProcess::Instance() const noexcept
	{
		return instance;
	}

	HINSTANCE GUIProcess::PrevInstance() const noexcept
	{
		return prevInstance;
	}

	PSTR GUIProcess::CommandLine() const noexcept
	{
		return cmdLine;
	}

	int GUIProcess::ShowCommand() const noexcept
	{
		return showCmd;
	}

	HICON GUIProcess::MainIcon() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return nullptr; // TODO: Implement
	}

	UINT GUIProcess::LastMessageType() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return lastMessageType;
	}

	DWORD GUIProcess::LastMessageRawTime() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return lastMessageRawTime;
	}

	std::chrono::time_point<std::chrono::steady_clock> GUIProcess::LastMessageTime() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return lastMessageTime;
	}

	POINT GUIProcess::LastMessagePoint() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return lastMessagePoint;
	}

	void GUIProcess::UpdateCommandLine()
	{
		int argc;
		const auto argv = std::unique_ptr<wchar_t*, decltype(&LocalFree)>(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

		commandLineSource.clear();
		commandLine.clear();
		commandLineSource.reserve(argc);
		commandLine.reserve(argc);

		for (int i = 0; i < argc; ++i)
		{
			const std::wstring_view source = argv.get()[i];
			const std::size_t size = Platform::Windows::GetStringSize(source);
			std::string arg;
			arg.resize(size);
			const std::size_t copied = Platform::Windows::ConvertToString(source, arg);
			arg.resize(copied);
			arg.shrink_to_fit();

			commandLineSource.push_back(std::move(arg));
			commandLine.push_back(commandLineSource.back());
		}
	}

	void GUIProcess::AddApplicationInterfaces()
	{
		bool mainDataAdded = false;
		bool resourceProviderAdded = false;
		bool messagePumpAdded = false;
		try
		{
			application->AddInterface<IMainData>(*this);
			mainDataAdded = true;
			application->AddInterface<IResourceProvider>(*this);
			resourceProviderAdded = true;
			application->AddInterface<IMessagePump>(*this);
			messagePumpAdded = true;
		}
		catch (...)
		{
			if (messagePumpAdded)
			{
				application->RemoveInterface<IMessagePump>(*this);
			}
			if (resourceProviderAdded)
			{
				application->RemoveInterface<IResourceProvider>(*this);
			}
			if (mainDataAdded)
			{
				application->RemoveInterface<IResourceProvider>(*this);
			}

			throw;
		}
	}

	void GUIProcess::RemoveApplicationInterfaces()
	{
		application->RemoveInterface<IMessagePump>(*this);
		application->RemoveInterface<IResourceProvider>(*this);
		application->RemoveInterface<IMainData>(*this);
	}

	void GUIProcess::Initialize()
	{
		bool early = false;
		bool normal = false;
		bool late = false;
		try
		{
			application->InitializeEarly();
			early = true;
			application->InitializeNormal();
			normal = true;
			application->InitializeLate();
			late = true;
		}
		catch (...)
		{
			if (late)
			{
				application->FinalizeLate();
			}
			if (normal)
			{
				application->FinalizeNormal();
			}
			if (early)
			{
				application->FinalizeEarly();
			}

			throw;
		}
	}

	void GUIProcess::Finalize()
	{
		application->FinalizeLate();
		application->FinalizeNormal();
		application->FinalizeEarly();
	}

	int GUIProcess::RunMainLoop()
	{
		std::optional<int> exitCode;

		for (exitCode = application->ExitCode(); !exitCode; exitCode = application->ExitCode())
		{
			application->BeginFrame();
			TickMessagePump();
			application->Tick();
			application->EndFrame();
		}

		return *exitCode;
	}

	void GUIProcess::TickMessagePump()
	{
		MSG message;
		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			lastMessageType = message.message;
			UpdateMessageTime(message.time);
			lastMessagePoint = message.pt;

			if (message.message == WM_QUIT) [[unlikely]]
			{
				const int exitCode = static_cast<int>(message.wParam);
				PONY_LOG(application->LogService(), Log::LogType::Info, "Quit message received. Stopping application with code '{}'.", exitCode);
				application->Stop(exitCode);
			}

			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}

	void GUIProcess::UpdateMessageTime(const DWORD newMessageTime) noexcept
	{
		const DWORD prevToNowDiff = newMessageTime - lastMessageRawTime;
		const DWORD nowToPrevDiff = lastMessageRawTime - newMessageTime;

		if (newMessageTime < lastMessageRawTime && prevToNowDiff > nowToPrevDiff) [[unlikely]]
		{
			lastMessageTime -= std::chrono::milliseconds(nowToPrevDiff);
		}
		else [[likely]]
		{
			lastMessageTime += std::chrono::milliseconds(prevToNowDiff);
		}

		lastMessageRawTime = newMessageTime;
	}
}

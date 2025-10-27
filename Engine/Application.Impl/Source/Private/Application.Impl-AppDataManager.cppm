/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#include "PonyEngine/Platform/Windows/Resource.h"
#endif

export module PonyEngine.Application.Impl:AppDataManager;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.File;
import PonyEngine.Log;
import PonyEngine.Text;

#if PONY_WINDOWS
export namespace PonyEngine::Application::Windows
{
	/// @brief Application data manager.
	class AppDataManager final
	{
	public:
		/// @brief Creates an application data manager.
		/// @param application Application context.
		/// @param instance Instance.
		/// @param prevInstance Previous instance.
		/// @param commandLine Command line.
		/// @param showCommand Show command.
		[[nodiscard("Pure constructor")]]
		AppDataManager(IApplicationContext& application, HINSTANCE instance, HINSTANCE prevInstance, PSTR commandLine, int showCommand);
		AppDataManager(const AppDataManager&) = delete;
		AppDataManager(AppDataManager&&) = delete;

		~AppDataManager() noexcept = default;

		/// @brief Gets the application instance.
		/// @return Application instance.
		[[nodiscard("Pure function")]]
		HINSTANCE Instance() const noexcept;
		/// @brief Gets the previous application instance.
		/// @return Previous application instance.
		[[nodiscard("Pure function")]]
		HINSTANCE PrevInstance() const noexcept;
		/// @brief Gets the command line excluding an executable name.
		/// @return Command line.
		[[nodiscard("Pure function")]]
		std::string_view CommandLine() const noexcept;
		/// @brief Gets the show command.
		/// @return Show command.
		[[nodiscard("Pure function")]]
		int ShowCommand() const noexcept;

		/// @brief Gets the application icon.
		/// @return Application icon.
		[[nodiscard("Pure function")]]
		HICON AppIcon() const noexcept;
		/// @brief Gets the application cursor.
		/// @return Application cursor.
		[[nodiscard("Pure function")]]
		HCURSOR AppCursor() const noexcept;

		AppDataManager& operator =(const AppDataManager&) = delete;
		AppDataManager& operator =(AppDataManager&&) = delete;

	private:
		IApplicationContext* application; ///< Application context.

		HINSTANCE instance; ///< Instance.
		HINSTANCE prevInstance; ///< Previous instance.
		std::string_view commandLine; ///< Command line.
		int showCommand; ///< Show command.

		HICON appIcon; ///< Application icon.
		HCURSOR appCursor; ///< Application cursor.
	};
}
#endif

#if PONY_WINDOWS
namespace PonyEngine::Application::Windows
{
	AppDataManager::AppDataManager(IApplicationContext& application, const HINSTANCE instance, const HINSTANCE prevInstance,
		const PSTR commandLine, const int showCommand) :
		application{&application},
		instance(instance),
		prevInstance(prevInstance),
		commandLine(commandLine),
		showCommand{showCommand},
		appIcon(nullptr),
		appCursor(nullptr)
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Main data received. Instance: '0x{:X}'; Previous instance: '0x{:X}'; Show command: '{}'; Command line: '{}'.",
			reinterpret_cast<std::uintptr_t>(this->instance), reinterpret_cast<std::uintptr_t>(this->prevInstance), this->showCommand, this->commandLine);

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Loading application resources...");
		const HMODULE appModule = File::Windows::GetModule();
#ifdef PONY_APP_ICON
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Loading application icon...");
		appIcon = LoadIconA(appModule, MAKEINTRESOURCEA(IDI_APP_ICON));
		if (!appIcon) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to load application icon. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Loading application icon done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(appIcon));
#endif
#ifdef PONY_APP_CURSOR
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Loading application cursor...");
		appCursor = LoadCursorA(appModule, MAKEINTRESOURCEA(IDC_APP_CURSOR));
		if (!appCursor) [[unlikely]]
		{
			throw std::runtime_error(Text::FormatSafe("Failed to load application cursor. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Loading application cursor done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(appCursor));
#endif
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Loading application resources done.");
	}

	HINSTANCE AppDataManager::Instance() const noexcept
	{
		return instance;
	}

	HINSTANCE AppDataManager::PrevInstance() const noexcept
	{
		return prevInstance;
	}

	std::string_view AppDataManager::CommandLine() const noexcept
	{
		return commandLine;
	}

	int AppDataManager::ShowCommand() const noexcept
	{
		return showCommand;
	}

	HICON AppDataManager::AppIcon() const noexcept
	{
		return appIcon;
	}

	HCURSOR AppDataManager::AppCursor() const noexcept
	{
		return appCursor;
	}
}
#endif

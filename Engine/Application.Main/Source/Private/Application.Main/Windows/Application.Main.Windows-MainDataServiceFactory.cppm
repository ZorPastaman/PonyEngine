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
#include "PonyEngine/Platform/Windows/Framework.h"
#include "PonyEngine/Platform/Windows/Resource.h"

export module PonyEngine.Application.Main.Windows:MainDataServiceFactory;

import std;

import PonyEngine.Application.Windows;
import PonyEngine.Log;
import PonyEngine.Platform.Windows;
import PonyEngine.Utility;

import :MainDataService;

export namespace PonyEngine::Application::Windows
{
	/// @brief Windows main data service factory.
	class MainDataServiceFactory final : public IServiceFactory
	{
	public:
		/// @brief Creates a Windows main data service factory.
		/// @param context Module context.
		/// @param instance Instance.
		/// @param prevInstance Previous instance.
		/// @param commandLine Command line.
		/// @param showCommand Show command.
		[[nodiscard("Pure constructor")]]
		MainDataServiceFactory(IModuleContext& context, HINSTANCE instance, HINSTANCE prevInstance, const char* commandLine, int showCommand) noexcept;
		MainDataServiceFactory(const MainDataServiceFactory&) = delete;
		MainDataServiceFactory(MainDataServiceFactory&&) = delete;

		~MainDataServiceFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual ServiceData Create(IApplicationContext& application) override;

		MainDataServiceFactory& operator =(const MainDataServiceFactory&) = delete;
		MainDataServiceFactory& operator =(MainDataServiceFactory&&) = delete;

	private:
		IModuleContext* context; ///< Module context.

		HINSTANCE instance; ///< Instance.
		HINSTANCE prevInstance; ///< Previous instance.
		const char* commandLine; ///< Command line.
		int showCommand; ///< Show command.
	};
}

namespace PonyEngine::Application::Windows
{
	MainDataServiceFactory::MainDataServiceFactory(IModuleContext& context, const HINSTANCE instance, const HINSTANCE prevInstance, const char* const commandLine, const int showCommand) noexcept :
		context{&context},
		instance{instance},
		prevInstance{prevInstance},
		commandLine{commandLine},
		showCommand{showCommand}
	{
	}

	ServiceData MainDataServiceFactory::Create(IApplicationContext& application)
	{
		HICON appIcon = nullptr;
		HCURSOR appCursor = nullptr;
		const HMODULE appModule = Platform::Windows::GetModule();
#if PONY_APP_ICON
		PONY_LOG(context->Logger(), Log::LogType::Info, "Loading application icon...");
		appIcon = LoadIconA(appModule, MAKEINTRESOURCEA(IDI_APP_ICON));
		if (!appIcon) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to load application icon. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(context->Logger(), Log::LogType::Info, "Loading application icon done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(appIcon));
#endif
#if PONY_APP_CURSOR
		PONY_LOG(context->Logger(), Log::LogType::Info, "Loading application cursor...");
		appCursor = LoadCursorA(appModule, MAKEINTRESOURCEA(IDC_APP_CURSOR));
		if (!appCursor) [[unlikely]]
		{
			throw std::runtime_error(Utility::SafeFormat("Failed to load application cursor. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(context->Logger(), Log::LogType::Info, "Loading application cursor done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(appCursor));
#endif

		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(MainDataService).name());
		const auto mainData = std::make_shared<MainDataService>(instance, prevInstance, commandLine, showCommand, appIcon, appCursor);
		ServiceData data;
		data.service = mainData;
		data.publicInterfaces.AddInterface<IMainDataService>(mainData->PublicMainDataService());
		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(MainDataService).name());

		return data;
	}
}

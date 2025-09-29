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

export module PonyEngine.Application.Main.Windows:MainDataServiceModule;

import std;

import PonyEngine.Application.Windows;
import PonyEngine.Log;

import :MainDataServiceFactory;

export namespace PonyEngine::Application::Windows
{
	/// @brief Windows main data service module.
	class MainDataServiceModule final : public IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		MainDataServiceModule() noexcept = default;
		MainDataServiceModule(const MainDataServiceModule&) = delete;
		MainDataServiceModule(MainDataServiceModule&&) = delete;

		~MainDataServiceModule() noexcept = default;

		/// @brief Sets up the main data service module.
		/// @details Must be called before the module is used.
		/// @param instance Instance.
		/// @param prevInstance Previous instance.
		/// @param commandLine Command line.
		/// @param showCommand Show command.
		static void Setup(HINSTANCE instance, HINSTANCE prevInstance, const char* commandLine, int showCommand) noexcept;

		virtual void StartUp(IModuleContext& context) override;
		virtual void ShutDown(const IModuleContext& context) override;

		MainDataServiceModule& operator =(const MainDataServiceModule&) = delete;
		MainDataServiceModule& operator =(MainDataServiceModule&&) = delete;

	private:
		static inline HINSTANCE instance; ///< Instance.
		static inline HINSTANCE prevInstance; ///< Previous instance.
		static inline const char* commandLine; ///< Command line.
		static inline int showCommand; ///< Show command.
		static inline bool setup = false; ///< If the module is set up.
	};
}

namespace PonyEngine::Application::Windows
{
	void MainDataServiceModule::Setup(const HINSTANCE instance, const HINSTANCE prevInstance, const char* const commandLine, const int showCommand) noexcept
	{
		assert(!setup && "The main data service module has already been set up.");
		MainDataServiceModule::instance = instance;
		MainDataServiceModule::prevInstance = prevInstance;
		MainDataServiceModule::commandLine = commandLine;
		MainDataServiceModule::showCommand = showCommand;
		setup = true;
	}

	void MainDataServiceModule::StartUp(IModuleContext& context)
	{
		assert(setup && "The main data service module wasn't set up.");

		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}'...", typeid(MainDataServiceFactory).name());
		const auto mainDataFactory = std::make_shared<MainDataServiceFactory>(context, instance, prevInstance, commandLine, showCommand);
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}' done.", typeid(MainDataServiceFactory).name());
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as service.", typeid(MainDataServiceFactory).name());
		context.AddService(mainDataFactory);
	}

	void MainDataServiceModule::ShutDown(const IModuleContext& context)
	{
	}
}

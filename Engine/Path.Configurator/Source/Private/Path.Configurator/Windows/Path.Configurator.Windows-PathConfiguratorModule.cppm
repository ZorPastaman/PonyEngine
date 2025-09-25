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

export module PonyEngine.Path.Configurator.Windows:PathConfiguratorModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Path.Extension.Windows;
import PonyEngine.Path.Configurator;
import PonyEngine.Platform.Windows;

export namespace PonyEngine::Path::Windows
{
	/// @brief Windows path configurator module.
	class PathConfiguratorModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		PathConfiguratorModule() noexcept = default;
		PathConfiguratorModule(const PathConfiguratorModule&) = delete;
		PathConfiguratorModule(PathConfiguratorModule&&) = delete;

		~PathConfiguratorModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(const Application::IModuleContext& context) override;

		PathConfiguratorModule& operator =(const PathConfiguratorModule&) = delete;
		PathConfiguratorModule& operator =(PathConfiguratorModule&&) = delete;
	};
}

namespace PonyEngine::Path::Windows
{
	void PathConfiguratorModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}'...", typeid(PathParams).name());
		const auto params = std::make_shared<PathParams>();
		params->localDataPath = AddProjectTail(GetKnownPath(FOLDERID_LocalAppData));
		params->userDataPath = AddProjectTail(GetKnownPath(FOLDERID_SavedGames));
		params->logPath = AddLogTail(params->localDataPath);
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}' done.", typeid(PathParams).name());
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as data...", typeid(PathParams).name());
		context.AddData<PathParams>(params);
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Adding '{}' as data done.", typeid(PathParams).name());
	}

	void PathConfiguratorModule::ShutDown(const Application::IModuleContext&)
	{
	}
}

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

export module PonyEngine.Path.Main.Windows:PathServiceModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :PathServiceFactory;

export namespace PonyEngine::Path::Windows
{
	/// @brief Path service module.
	class PathServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		PathServiceModule() noexcept = default;
		PathServiceModule(const PathServiceModule&) = delete;
		PathServiceModule(PathServiceModule&&) = delete;

		~PathServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(const Application::IModuleContext& context) override;

		PathServiceModule& operator =(const PathServiceModule&) = delete;
		PathServiceModule& operator =(PathServiceModule&&) = delete;
	};
}

namespace PonyEngine::Path::Windows
{
	void PathServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Debug, "Constructing '{}' and adding it to context as service factory.", typeid(PathServiceFactory).name());
		context.AddService(std::make_shared<PathServiceFactory>(context));
	}

	void PathServiceModule::ShutDown(const Application::IModuleContext&)
	{
	}
}

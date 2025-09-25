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

export module PonyEngine.Log.File:FileSubLoggerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Log;

import :FileSubLoggerFactory;

export namespace PonyEngine::Log
{
	/// @brief File sub-logger module.
	class FileSubLoggerModule final : public Application::IModule
	{
	public:
		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(const Application::IModuleContext& context) override;
	};
}

namespace PonyEngine::Log
{
	void FileSubLoggerModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}'...", typeid(FileSubLoggerFactory).name());
		const auto fileSubLoggerFactory = std::make_shared<FileSubLoggerFactory>(context);
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}' done.", typeid(FileSubLoggerFactory).name());
		PONY_LOG(context.Logger(), LogType::Debug, "Adding '{}' as data of type '{}'...", typeid(FileSubLoggerFactory).name(), typeid(ISubLoggerFactory).name());
		context.AddData<ISubLoggerFactory>(fileSubLoggerFactory);
		PONY_LOG(context.Logger(), LogType::Debug, "Adding '{}' as data of type '{}' done.", typeid(FileSubLoggerFactory).name(), typeid(ISubLoggerFactory).name());
	}

	void FileSubLoggerModule::ShutDown(const Application::IModuleContext&)
	{
	}
}

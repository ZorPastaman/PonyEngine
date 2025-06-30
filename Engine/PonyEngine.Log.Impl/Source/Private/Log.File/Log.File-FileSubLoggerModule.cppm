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

import PonyEngine.Core;
import PonyEngine.Log;

import :FileSubLoggerFactory;

export namespace PonyEngine::Log
{
	/// @brief File sub-logger module.
	class FileSubLoggerModule final : public Core::IModule
	{
	public:
		virtual void StartUp(Core::IModuleContext& context) override;
		virtual void ShutDown(const Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
	};
}

namespace PonyEngine::Log
{
	void FileSubLoggerModule::StartUp(Core::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), LogType::Debug, "Constructing '{}' and adding it to context as '{}'.", typeid(FileSubLoggerFactory).name(), typeid(ISubLoggerFactory).name());
		context.AddData<ISubLoggerFactory>(std::make_shared<FileSubLoggerFactory>(context));
	}

	void FileSubLoggerModule::ShutDown(const Core::IModuleContext&)
	{
	}

	std::string_view FileSubLoggerModule::Name() const noexcept
	{
		return "PonyEngineFileSubLogger";
	}
}

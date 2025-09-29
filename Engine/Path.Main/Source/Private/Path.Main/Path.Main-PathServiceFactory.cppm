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

export module PonyEngine.Path.Main:PathServiceFactory;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Path.Extension;

import :PathService;

export namespace PonyEngine::Path
{
	/// @brief Path service factory.
	class PathServiceFactory : public Application::IServiceFactory
	{
	public:
		PathServiceFactory(const PathServiceFactory&) = delete;
		PathServiceFactory(PathServiceFactory&&) = delete;

		virtual ~PathServiceFactory() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual Application::ServiceData Create(Application::IApplicationContext& application) override final;

		PathServiceFactory& operator =(const PathServiceFactory&) = delete;
		PathServiceFactory& operator =(PathServiceFactory&&) = delete;

	protected:
		/// @brief Creates a path service factory.
		/// @param context Module context.
		[[nodiscard("Pure constuctor")]]
		explicit PathServiceFactory(Application::IModuleContext& context) noexcept;

		/// @brief Gets a path to the executable.
		/// @return Path to the executable.
		[[nodiscard("Pure function")]]
		virtual std::filesystem::path GetExecutablePath() const = 0;

		Application::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Path
{
	Application::ServiceData PathServiceFactory::Create(Application::IApplicationContext& application)
	{
		PONY_LOG(context->Logger(), Log::LogType::Debug, "Getting path parameters...");
		if (context->DataCount<PathParams>() == 0uz) [[unlikely]]
		{
			throw std::logic_error("Path parameters not found.");
		}
		PONY_LOG_IF(context->DataCount<PathParams>() > 1uz, context->Logger(), Log::LogType::Warning, "Multiple path parameters found. First one will be used.");
		const auto params = context->GetData<PathParams>(0uz);
		if (!params) [[unlikely]]
		{
			throw std::logic_error("Path parameters is nullptr.");
		}
		if (!params->rootPath.is_relative()) [[unlikely]]
		{
			throw std::logic_error("Root path is not relative.");
		}
		if (!params->localDataPath.is_absolute()) [[unlikely]]
		{
			throw std::logic_error("Local data path is not absolute.");
		}
		if (!params->userDataPath.is_absolute()) [[unlikely]]
		{
			throw std::logic_error("User data path is not absolute.");
		}
		if (!params->logPath.is_absolute()) [[unlikely]]
		{
			throw std::logic_error("Log path is not absolute.");
		}

		const std::filesystem::path executablePath = GetExecutablePath();
		const std::filesystem::path executableDirectoryPath = executablePath.parent_path();
		const std::filesystem::path rootPath = executableDirectoryPath / params->rootPath;
		if (!std::filesystem::exists(rootPath)) [[unlikely]]
		{
			throw std::logic_error("Root path doesn't exist.");
		}
		PONY_LOG(context->Logger(), Log::LogType::Debug, "Getting path parameters.");

		PONY_LOG(context->Logger(), Log::LogType::Info, "Creating main path directories...");
		std::filesystem::create_directories(params->localDataPath);
		std::filesystem::create_directories(params->userDataPath);
		std::filesystem::create_directories(params->logPath);
		PONY_LOG(context->Logger(), Log::LogType::Info, "Creating main path directories done.");

		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(PathService).name());
		auto pathService = std::make_shared<PathService>(application);
		pathService->AddPath(MainPathIds::Root, rootPath);
		pathService->AddPath(MainPathIds::Executable, executablePath);
		pathService->AddPath(MainPathIds::ExecutableDirectory, executableDirectoryPath);
		pathService->AddPath(MainPathIds::LocalData, params->localDataPath);
		pathService->AddPath(MainPathIds::UserData, params->userDataPath);
		pathService->AddPath(MainPathIds::Log, params->logPath);
		Application::ServiceData data;
		data.service = pathService;
		data.publicInterfaces.AddInterface<IPathService>(pathService->PublicPathService());
		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing '{}' done", typeid(PathService).name());

		return data;
	}

	PathServiceFactory::PathServiceFactory(Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}
}

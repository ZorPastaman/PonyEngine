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
#include "PonyEngine/Utility/Macro.h"

export module PonyEngine.Path.Main.Windows:PathServiceFactory;

import PonyEngine.Log;
import PonyEngine.Path.Main;

import :PathHelper;

export namespace PonyEngine::Path::Windows
{
	/// @brief Path service factory.
	class PathServiceFactory final : public Path::PathServiceFactory
	{
	public:
		/// @brief Creates a path service factory.
		/// @param context Module context.
		[[nodiscard("Pure constuctor")]]
		explicit PathServiceFactory(Application::IModuleContext& context) noexcept;
		PathServiceFactory(const PathServiceFactory&) = delete;
		PathServiceFactory(PathServiceFactory&&) = delete;

		virtual ~PathServiceFactory() noexcept override = default;

		PathServiceFactory& operator =(const PathServiceFactory&) = delete;
		PathServiceFactory& operator =(PathServiceFactory&&) = delete;

	protected:
		virtual void FillPaths(IPathService& pathService) override;
	};
}

namespace PonyEngine::Path::Windows
{
	PathServiceFactory::PathServiceFactory(Application::IModuleContext& context) noexcept :
		Path::PathServiceFactory(context)
	{
	}

	void PathServiceFactory::FillPaths(IPathService& pathService)
	{
		PONY_LOG(context->Logger(), Log::LogType::Debug, "Getting paths.");
		const std::filesystem::path executablePath = GetExecutablePath();
		const std::filesystem::path localDataPath = GetLocalDataPath() / PONY_STRINGIFY_VALUE(PONY_COMPANY_NAME) / PONY_STRINGIFY_VALUE(PONY_PROJECT_NAME);
		const std::filesystem::path userDataPath = GetUserDataPath() / PONY_STRINGIFY_VALUE(PONY_COMPANY_NAME) / PONY_STRINGIFY_VALUE(PONY_PROJECT_NAME);

		const std::filesystem::path executableDirectoryPath = executablePath.parent_path();
		const std::filesystem::path rootPath = executableDirectoryPath / PONY_STRINGIFY_VALUE(PONY_ENGINE_PATH_ROOT_PATH);
		const std::filesystem::path logPath = localDataPath / PONY_STRINGIFY_VALUE(PONY_ENGINE_PATH_LOG_PATH);

		assert(std::filesystem::exists(rootPath) && "Root path is incorrect.");

		PONY_LOG(context->Logger(), Log::LogType::Debug, "Creating directories.");
		std::filesystem::create_directories(localDataPath);
		std::filesystem::create_directories(userDataPath);
		std::filesystem::create_directories(logPath);

		PONY_LOG(context->Logger(), Log::LogType::Debug, "Adding paths.");
		pathService.AddPath(PathIds::Root, rootPath);
		pathService.AddPath(PathIds::Executable, executablePath);
		pathService.AddPath(PathIds::ExecutableDirectory, executableDirectoryPath);
		pathService.AddPath(PathIds::LocalData, localDataPath);
		pathService.AddPath(PathIds::UserData, userDataPath);
		pathService.AddPath(PathIds::Log, logPath);
	}
}

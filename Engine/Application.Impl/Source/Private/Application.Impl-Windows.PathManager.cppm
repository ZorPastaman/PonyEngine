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
#include "PonyEngine/Macro/Text.h"
#include "PonyEngine/Platform/Windows/Storage.h"

export module PonyEngine.Application.Impl:Windows.PathManager;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Platform;

import :Path;

export namespace PonyEngine::Application::Windows
{
	/// @brief Windows path manager.
	class PathManager final
	{
	public:
		/// @brief Creates a path manager.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit PathManager(IApplicationContext& application);
		PathManager(const PathManager&) = delete;
		PathManager(PathManager&&) = delete;

		~PathManager() noexcept = default;

		/// @brief Gets the executable file.
		/// @return Executable file.
		[[nodiscard("Pure function")]]
		const std::filesystem::path& ExecutableFile() const noexcept;
		/// @brief Gets the executable directory.
		/// @return Executable directory.
		[[nodiscard("Pure function")]]
		const std::filesystem::path& ExecutableDirectory() const noexcept;
		/// @brief Gets the root directory.
		/// @return Root directory.
		[[nodiscard("Pure function")]]
		const std::filesystem::path& RootDirectory() const noexcept;
		/// @brief Gets the local data directory.
		/// @return Local data directory.
		[[nodiscard("Pure function")]]
		const std::filesystem::path& LocalDataDirectory() const noexcept;
		/// @brief Gets the user data directory.
		/// @return User data directory.
		[[nodiscard("Pure function")]]
		const std::filesystem::path& UserDataDirectory() const noexcept;
		/// @brief Gets the temp data directory.
		/// @return Temp data directory.
		[[nodiscard("Pure function")]]
		const std::filesystem::path& TempDataDirectory() const noexcept;

		PathManager& operator =(const PathManager&) = delete;
		PathManager& operator =(PathManager&&) = delete;

	private:
		std::filesystem::path executableFile; ///< Path to the executable.
		std::filesystem::path executableDirectory; ///< Executable directory.
		std::filesystem::path rootDirectory; ///< Root directory.
		std::filesystem::path localDataDirectory; ///< Local data directory.
		std::filesystem::path userDataDirectory; ///< User data directory.
		std::filesystem::path tempDataDirectory; ///< Temporal data directory.
	};
}

namespace PonyEngine::Application::Windows
{
	PathManager::PathManager(IApplicationContext& application)
	{
		PONY_LOG(application.Logger(), Log::LogType::Info, "Getting executable file...");
		executableFile = Platform::Windows::GetModulePath(nullptr).lexically_normal();
		executableDirectory = executableFile.parent_path();
		rootDirectory = (executableDirectory / PONY_STRINGIFY_VALUE(PONY_ENGINE_ROOT_PATH)).lexically_normal();
		if (!std::filesystem::exists(rootDirectory)) [[unlikely]]
		{
			throw std::logic_error("Root directory doesn't exist.");
		}
		PONY_LOG(application.Logger(), Log::LogType::Info, "Getting executable file done. File: '{}'; Directory: '{}'; Root: '{}'.",
			executableFile.string(), executableDirectory.string(), rootDirectory.string());

		PONY_LOG(application.Logger(), Log::LogType::Info, "Getting data directories...");
		localDataDirectory = AddTail(Platform::Windows::GetKnownPath(FOLDERID_LocalAppData));
		userDataDirectory = AddTail(Platform::Windows::GetKnownPath(FOLDERID_SavedGames));
		tempDataDirectory = AddTail(Platform::Windows::GetTemporaryPath());
		PONY_LOG(application.Logger(), Log::LogType::Info, "Getting data directories done. Local data: '{}'; User data: '{}'; Temp data: '{}'.",
			localDataDirectory.string(), userDataDirectory.string(), tempDataDirectory.string());
	}

	const std::filesystem::path& PathManager::ExecutableFile() const noexcept
	{
		return executableFile;
	}

	const std::filesystem::path& PathManager::ExecutableDirectory() const noexcept
	{
		return executableDirectory;
	}

	const std::filesystem::path& PathManager::RootDirectory() const noexcept
	{
		return rootDirectory;
	}

	const std::filesystem::path& PathManager::LocalDataDirectory() const noexcept
	{
		return localDataDirectory;
	}

	const std::filesystem::path& PathManager::UserDataDirectory() const noexcept
	{
		return userDataDirectory;
	}

	const std::filesystem::path& PathManager::TempDataDirectory() const noexcept
	{
		return tempDataDirectory;
	}
}

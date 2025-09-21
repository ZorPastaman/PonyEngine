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

export module PonyEngine.Path.Main:PathService;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Path;

export namespace PonyEngine::Path
{
	/// @brief Path service.
	class PathService final : public Application::IService, private IPathService
	{
	public:
		/// @brief Creates a path service.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit PathService(Application::IApplicationContext& application) noexcept;
		PathService(const PathService&) = delete;
		PathService(PathService&&) = delete;

		~PathService() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		virtual std::size_t PathCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view PathId(std::size_t index) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::filesystem::path* FindPath(std::string_view pathId) const noexcept override;
		virtual void AddPath(std::string_view pathId, const std::filesystem::path& path) override;

		/// @brief Gets a public path service.
		/// @return Public path service.
		[[nodiscard("Pure function")]]
		IPathService& PublicPathService() noexcept;
		/// @brief Gets a public path service.
		/// @return Public path service.
		[[nodiscard("Pure function")]]
		const IPathService& PublicPathService() const noexcept;

		PathService& operator =(const PathService&) = delete;
		PathService& operator =(PathService&&) = delete;

	private:
		Application::IApplicationContext* application; ///< Application context.

		std::unordered_map<std::string_view, std::filesystem::path> paths; ///< Path ID to path map.
		std::vector<std::string> pathIds; ///< Registered path IDs.
	};
}

namespace PonyEngine::Path
{
	PathService::PathService(Application::IApplicationContext& application) noexcept :
		application{&application}
	{
	}

	void PathService::Begin()
	{
	}

	void PathService::End()
	{
	}

	std::size_t PathService::PathCount() const noexcept
	{
		return pathIds.size();
	}

	std::string_view PathService::PathId(const std::size_t index) const noexcept
	{
		return pathIds[index];
	}

	const std::filesystem::path* PathService::FindPath(const std::string_view pathId) const noexcept
	{
		if (const auto position = paths.find(pathId); position != paths.end()) [[likely]]
		{
			return &position->second;
		}

		return nullptr;
	}

	void PathService::AddPath(const std::string_view pathId, const std::filesystem::path& path)
	{
		if (paths.contains(pathId)) [[unlikely]]
		{
			throw std::invalid_argument("PathId has already been added.");
		}
		if (!path.is_absolute()) [[unlikely]]
		{
			throw std::invalid_argument("Path isn't absolute.");
		}

		pathIds.push_back(std::string(pathId));
		try
		{
			paths.emplace(pathIds.back(), path.lexically_normal());
		}
		catch (...)
		{
			pathIds.pop_back();
			throw;
		}

		PONY_LOG(application->Logger(), Log::LogType::Info, "Path added. PathId: '{}', Path: '{}'.", pathIds.back(), paths[pathIds.back()].string());
	}

	IPathService& PathService::PublicPathService() noexcept
	{
		return *this;
	}

	const IPathService& PathService::PublicPathService() const noexcept
	{
		return *this;
	}
}

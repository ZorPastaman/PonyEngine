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
import PonyEngine.Path;

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

		/// @brief Fills predefined paths.
		/// @param pathService Path service.
		virtual void FillPaths(PathService& pathService) = 0;

		Application::IModuleContext* context; ///< Module context.
	};
}

namespace PonyEngine::Path
{
	Application::ServiceData PathServiceFactory::Create(Application::IApplicationContext& application)
	{
		PONY_LOG(context->Logger(), Log::LogType::Info, "Constructing path service.");
		auto pathService = std::make_shared<PathService>(application);

		Application::ServiceData data;
		data.service = pathService;
		data.publicInterfaces.AddInterface<IPathService>(pathService->PublicPathService());

		PONY_LOG(context->Logger(), Log::LogType::Info, "Filling default paths.");
		FillPaths(*pathService);

		return data;
	}

	PathServiceFactory::PathServiceFactory(Application::IModuleContext& context) noexcept :
		context{&context}
	{
	}
}

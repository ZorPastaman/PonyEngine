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

export module PonyEngine.World.Impl:WorldServiceModule;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

import :WorldService;

export namespace PonyEngine::World
{
	/// @brief World service module.
	class WorldServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		WorldServiceModule() noexcept = default;
		WorldServiceModule(const WorldServiceModule&) = delete;
		WorldServiceModule(WorldServiceModule&&) = delete;

		~WorldServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		WorldServiceModule& operator =(const WorldServiceModule&) = delete;
		WorldServiceModule& operator =(WorldServiceModule&&) = delete;

	private:
		Application::ServiceHandle worldServiceHandle; ///< World service handle.
	};
}

namespace PonyEngine::World
{
	void WorldServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(WorldService).name());
		worldServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
		{
			return std::make_shared<WorldService>(application);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(WorldService).name());
	}

	void WorldServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(WorldService).name());
		context.ServiceModuleContext().RemoveService(worldServiceHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(WorldService).name());
	}
}

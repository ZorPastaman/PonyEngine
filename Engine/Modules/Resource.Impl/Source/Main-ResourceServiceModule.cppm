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

export module PonyEngine.Resource.Impl:ResourceServiceModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

import :ResourceService;

export namespace PonyEngine::Resource
{
	/// @brief Resource service module.
	class ResourceServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceServiceModule() noexcept = default;
		ResourceServiceModule(const ResourceServiceModule&) = delete;
		ResourceServiceModule(ResourceServiceModule&&) = delete;

		~ResourceServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		ResourceServiceModule& operator =(const ResourceServiceModule&) = delete;
		ResourceServiceModule& operator =(ResourceServiceModule&&) = delete;

	private:
		Application::ModuleDataHandle inputServiceModuleHandle; ///< Resource service module handle.
		Application::ServiceHandle inputServiceHandle; ///< Resource service handle.
	};
}

namespace PonyEngine::Resource
{
	void ResourceServiceModule::StartUp(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(ResourceService).name());
		try
		{
			inputServiceHandle = context.ServiceModuleContext().AddService([&](Application::IApplicationContext& application)
			{
				const auto input = std::make_shared<ResourceService>(application);
				inputServiceModuleHandle = context.AddData(std::shared_ptr<IResourceModuleContext>(input, input.get()));

				return input;
			});
		}
		catch (...)
		{
			if (inputServiceModuleHandle.IsValid())
			{
				context.RemoveData(inputServiceModuleHandle);
			}
			throw;
		}
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(ResourceService).name());
	}

	void ResourceServiceModule::ShutDown(Application::IModuleContext& context)
	{
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(ResourceService).name());
		context.ServiceModuleContext().RemoveService(inputServiceHandle);
		context.RemoveData(inputServiceModuleHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(ResourceService).name());
	}
}

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

export module PonyEngine.Resource.Pack.Impl:PackResourceProviderModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Resource.Ext;

import :PackResourceProvider;

export namespace PonyEngine::Resource::Pack
{
	class PackResourceProviderModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackResourceProviderModule() noexcept = default;
		PackResourceProviderModule(const PackResourceProviderModule&) = delete;
		PackResourceProviderModule(PackResourceProviderModule&&) = delete;

		~PackResourceProviderModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		PackResourceProviderModule& operator =(const PackResourceProviderModule&) = delete;
		PackResourceProviderModule& operator =(PackResourceProviderModule&&) = delete;

	private:
		ResourceProviderHandle providerHandle;
	};
}

namespace PonyEngine::Resource::Pack
{
	void PackResourceProviderModule::StartUp(Application::IModuleContext& context)
	{
		IResourceModuleContext* const resourceModuleContext = context.GetData<IResourceModuleContext>();
#ifndef NDEBUG
		if (!resourceModuleContext) [[unlikely]]
		{
			throw std::logic_error("Resource module context not found");
		}
#endif

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(PackResourceProvider).name());
		providerHandle = resourceModuleContext->AddProvider([](IResourceContext& resourceContext)
		{
			return std::make_shared<PackResourceProvider>(resourceContext);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(PackResourceProvider).name());
	}

	void PackResourceProviderModule::ShutDown(Application::IModuleContext& context)
	{
		IResourceModuleContext* const resourceModuleContext = context.GetData<IResourceModuleContext>();
#ifndef NDEBUG
		if (!resourceModuleContext) [[unlikely]]
		{
			throw std::logic_error("Render device module context not found");
		}
#endif

		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(PackResourceProvider).name());
		resourceModuleContext->RemoveProvider(providerHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(PackResourceProvider).name());
	}
}

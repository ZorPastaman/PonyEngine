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

export module PonyEngine.Resource.File.Impl:FileResourceProviderModule;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Resource.Ext;

import :FileResourceProvider;

export namespace PonyEngine::Resource::File
{
	class FileResourceProviderModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		FileResourceProviderModule() noexcept = default;
		FileResourceProviderModule(const FileResourceProviderModule&) = delete;
		FileResourceProviderModule(FileResourceProviderModule&&) = delete;

		~FileResourceProviderModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		FileResourceProviderModule& operator =(const FileResourceProviderModule&) = delete;
		FileResourceProviderModule& operator =(FileResourceProviderModule&&) = delete;

	private:
		ResourceProviderHandle providerHandle;
	};
}

namespace PonyEngine::Resource::File
{
	void FileResourceProviderModule::StartUp(Application::IModuleContext& context)
	{
		IResourceModuleContext* const resourceModuleContext = context.GetData<IResourceModuleContext>();
#ifndef NDEBUG
		if (!resourceModuleContext) [[unlikely]]
		{
			throw std::logic_error("Resource module context not found");
		}
#endif

		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}'...", typeid(FileResourceProvider).name());
		providerHandle = resourceModuleContext->AddProvider([](IResourceContext& resourceContext)
		{
			return std::make_shared<FileResourceProvider>(resourceContext);
		});
		PONY_LOG(context.Logger(), Log::LogType::Info, "Constructing '{}' done.", typeid(FileResourceProvider).name());
	}

	void FileResourceProviderModule::ShutDown(Application::IModuleContext& context)
	{
		IResourceModuleContext* const resourceModuleContext = context.GetData<IResourceModuleContext>();
#ifndef NDEBUG
		if (!resourceModuleContext) [[unlikely]]
		{
			throw std::logic_error("Render device module context not found");
		}
#endif

		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}'...", typeid(FileResourceProvider).name());
		resourceModuleContext->RemoveProvider(providerHandle);
		PONY_LOG(context.Logger(), Log::LogType::Info, "Releasing '{}' done.", typeid(FileResourceProvider).name());
	}
}

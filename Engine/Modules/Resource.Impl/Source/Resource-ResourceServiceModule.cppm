/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:ResourceServiceModule;

import std;

import PonyEngine.Application;
import PonyEngine.Utility;

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
		std::unique_ptr<ResourceService> resourceService; ///< Resource service.
	};
}

namespace PonyEngine::Resource
{
	void ResourceServiceModule::StartUp(Application::IModuleContext& context)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		resourceService = std::make_unique<ResourceService>(context.Application());
		const auto resourceServiceScopeGuard = Utility::ScopeGuard([&]() noexcept { resourceService.reset(); }, scopeGuardFlag);
		context.AddInterface<IResourceService>(*resourceService);
		const auto resourceServiceInterfaceScopeGuard = Utility::ScopeGuard([&]() noexcept { context.RemoveInterface<IResourceService>(*resourceService); }, scopeGuardFlag);
		context.AddInterface<IResourceHub>(*resourceService);

		scopeGuardFlag.Release();
	}

	void ResourceServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveInterface<IResourceHub>(*resourceService);
		context.RemoveInterface<IResourceService>(*resourceService);
		resourceService.reset();
	}
}

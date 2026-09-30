/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Hierarchy.Impl:HierarchyServiceModule;

import std;

import PonyEngine.Application;

import :HierarchyService;

export namespace PonyEngine::World::Hierarchy
{
	/// @brief Hierarchy service module.
	class HierarchyServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		HierarchyServiceModule() noexcept = default;
		HierarchyServiceModule(const HierarchyServiceModule&) = delete;
		HierarchyServiceModule(HierarchyServiceModule&&) = delete;

		~HierarchyServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		HierarchyServiceModule& operator =(const HierarchyServiceModule&) = delete;
		HierarchyServiceModule& operator =(HierarchyServiceModule&&) = delete;

	private:
		std::unique_ptr<HierarchyService> hierarchyService; ///< Hierarchy service.
	};
}

namespace PonyEngine::World::Hierarchy
{
	void HierarchyServiceModule::StartUp(Application::IModuleContext& context)
	{
		hierarchyService = std::make_unique<HierarchyService>(context.Application());
		try
		{
			context.AddInterface<IHierarchyService>(*hierarchyService);
		}
		catch (...)
		{
			hierarchyService.reset();
			throw;
		}
	}

	void HierarchyServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveInterface<IHierarchyService>(*hierarchyService);
		hierarchyService.reset();
	}
}

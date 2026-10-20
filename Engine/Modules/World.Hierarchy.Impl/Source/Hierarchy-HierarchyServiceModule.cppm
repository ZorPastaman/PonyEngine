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
		/// @brief Registers hierarchy component.
		/// @param worldService World service.
		static void RegisterComponents(IWorldService& worldService);

		std::unique_ptr<HierarchyService> hierarchyService; ///< Hierarchy service.
	};
}

namespace PonyEngine::World::Hierarchy
{
	void HierarchyServiceModule::StartUp(Application::IModuleContext& context)
	{
		Application::IApplication& application = context.Application();
		RegisterComponents(application.GetInterface<IWorldService>());

		hierarchyService = std::make_unique<HierarchyService>(application);
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

	void HierarchyServiceModule::RegisterComponents(IWorldService& worldService)
	{
		worldService.RegisterComponent<Parent>();
		worldService.RegisterEntityReferenceMember(&Parent::value);
		worldService.RegisterComponent<LocalTransform2D>();
		worldService.RegisterComponent<LocalTransform3D>();
		worldService.RegisterComponent<WorldTransform2D>();
		worldService.RegisterComponent<WorldTransform3D>();
		worldService.RegisterComponent<DirtyTransform>();
	}
}

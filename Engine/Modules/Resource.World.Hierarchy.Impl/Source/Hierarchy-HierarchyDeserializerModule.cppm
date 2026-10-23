/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World.Hierarchy.Impl:HierarchyDeserializerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Resource.World.Ext;
import PonyEngine.Utility;
import PonyEngine.World.Hierarchy;

import :Transform2DDeserializer;
import :Transform3DDeserializer;

export namespace PonyEngine::Resource::World::Hierarchy
{
	/// @brief Hierarchy deserializer module.
	class HierarchyDeserializerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		HierarchyDeserializerModule() noexcept = default;
		HierarchyDeserializerModule(const HierarchyDeserializerModule&) = delete;
		HierarchyDeserializerModule(HierarchyDeserializerModule&&) = delete;

		~HierarchyDeserializerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		HierarchyDeserializerModule& operator =(const HierarchyDeserializerModule&) = delete;
		HierarchyDeserializerModule& operator =(HierarchyDeserializerModule&&) = delete;

	private:
		/// @brief Creates a transform 2D deserializer.
		/// @param loader World definition loader.
		void CreateTransform2DDeserializer(IWorldDefinitionLoader& loader);
		/// @brief Destroys a transform 2D deserializer.
		/// @param loader World definition loader.
		void DestroyTransform2DDeserializer(IWorldDefinitionLoader& loader);
		/// @brief Creates a transform 3D deserializer.
		/// @param loader World definition loader.
		void CreateTransform3DDeserializer(IWorldDefinitionLoader& loader);
		/// @brief Destroys a transform 3D deserializer.
		/// @param loader World definition loader.
		void DestroyTransform3DDeserializer(IWorldDefinitionLoader& loader);

		/// @brief Registers components that can be simply copied.
		/// @param copyComponentDeserializer Copy component deserializer.
		static void RegisterCopyComponents(ICopyComponentDeserializer& copyComponentDeserializer);

		static constexpr std::string_view ParentType = "Pony.Parent"; ///< PonyEngine::World::Hierarchy::Parent serialized type.
		static constexpr std::string_view Transform2DType = "Pony.Transform2D"; ///< PonyEngine::World::Hierarchy::Transform2D serialized type.
		static constexpr std::string_view Transform3DType = "Pony.Transform3D"; ///< PonyEngine::World::Hierarchy::Transform3D serialized type.

		std::unique_ptr<Transform2DDeserializer> transform2DDeserializer; ///< Transform 2D deserializer.
		std::unique_ptr<Transform3DDeserializer> transform3DDeserializer; ///< Transform 3D deserializer.
	};
}

namespace PonyEngine::Resource::World::Hierarchy
{
	void HierarchyDeserializerModule::StartUp(Application::IModuleContext& context)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		const Application::IApplication& application = context.Application();
		IWorldDefinitionLoader& loader = application.GetInterface<IWorldDefinitionLoader>();
		ICopyComponentDeserializer& copyComponentDeserializer = context.Application().GetInterface<ICopyComponentDeserializer>();
		CreateTransform2DDeserializer(loader);
		const auto transform2DScopeGuard = Utility::ScopeGuard([&]() noexcept { DestroyTransform2DDeserializer(loader); }, scopeGuardFlag);
		CreateTransform3DDeserializer(loader);
		const auto transform3DScopeGuard = Utility::ScopeGuard([&]() noexcept { DestroyTransform3DDeserializer(loader); }, scopeGuardFlag);
		RegisterCopyComponents(copyComponentDeserializer);

		scopeGuardFlag.Release();
	}

	void HierarchyDeserializerModule::ShutDown(Application::IModuleContext& context)
	{
		const Application::IApplication& application = context.Application();
		IWorldDefinitionLoader& loader = application.GetInterface<IWorldDefinitionLoader>();
		DestroyTransform3DDeserializer(loader);
		DestroyTransform2DDeserializer(loader);
	}

	void HierarchyDeserializerModule::CreateTransform2DDeserializer(IWorldDefinitionLoader& loader)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		transform2DDeserializer = std::make_unique<Transform2DDeserializer>();
		const auto deserializerScopeGuard = Utility::ScopeGuard([&]() noexcept { transform2DDeserializer.reset(); }, scopeGuardFlag);
		loader.RegisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform2D>(Transform2DType, *transform2DDeserializer);

		scopeGuardFlag.Release();
	}

	void HierarchyDeserializerModule::DestroyTransform2DDeserializer(IWorldDefinitionLoader& loader)
	{
		loader.UnregisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform2D>(Transform2DType, *transform2DDeserializer);
		transform2DDeserializer.reset();
	}

	void HierarchyDeserializerModule::CreateTransform3DDeserializer(IWorldDefinitionLoader& loader)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		transform3DDeserializer = std::make_unique<Transform3DDeserializer>();
		const auto deserializerScopeGuard = Utility::ScopeGuard([&]() noexcept { transform3DDeserializer.reset(); }, scopeGuardFlag);
		loader.RegisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform3D>(Transform3DType, *transform3DDeserializer);

		scopeGuardFlag.Release();
	}

	void HierarchyDeserializerModule::DestroyTransform3DDeserializer(IWorldDefinitionLoader& loader)
	{
		loader.UnregisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform3D>(Transform3DType, *transform3DDeserializer);
		transform3DDeserializer.reset();
	}

	void HierarchyDeserializerModule::RegisterCopyComponents(ICopyComponentDeserializer& copyComponentDeserializer)
	{
		copyComponentDeserializer.Associate<PonyEngine::World::Hierarchy::Parent>(ParentType);
	}
}

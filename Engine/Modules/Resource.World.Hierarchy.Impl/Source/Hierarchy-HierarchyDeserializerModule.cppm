/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World.Hierarchy.Impl:HierarchyDeserializerModule;

import PonyEngine.Application;
import PonyEngine.Resource.World;
import PonyEngine.World.Hierarchy;

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
		static constexpr std::string_view ParentType = "Pony.Parent"; ///< PonyEngine::World::Hierarchy::Parent serialized type.
		static constexpr std::string_view Transform2DType = "Pony.Transform2D"; ///< PonyEngine::World::Hierarchy::Transform2D serialized type.
		static constexpr std::string_view Transform3DType = "Pony.Transform3D"; ///< PonyEngine::World::Hierarchy::Transform3D serialized type.
	};
}

namespace PonyEngine::Resource::World::Hierarchy
{
	void HierarchyDeserializerModule::StartUp(Application::IModuleContext& context)
	{
		IWorldDefinitionLoader& worldDefinitionLoader = context.Application().GetInterface<IWorldDefinitionLoader>();
		worldDefinitionLoader.RegisterComponentDeserializer<PonyEngine::World::Hierarchy::Parent>(ParentType);
		try
		{
			worldDefinitionLoader.RegisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform2D>(Transform2DType);
			try
			{
				worldDefinitionLoader.RegisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform3D>(Transform3DType);
			}
			catch (...)
			{
				worldDefinitionLoader.UnregisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform2D>(Transform2DType);
				throw;
			}
		}
		catch (...)
		{
			worldDefinitionLoader.UnregisterComponentDeserializer<PonyEngine::World::Hierarchy::Parent>(ParentType);
			throw;
		}
	}

	void HierarchyDeserializerModule::ShutDown(Application::IModuleContext& context)
	{
		IWorldDefinitionLoader& worldDefinitionLoader = context.Application().GetInterface<IWorldDefinitionLoader>();
		worldDefinitionLoader.UnregisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform3D>(Transform3DType);
		worldDefinitionLoader.UnregisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform2D>(Transform2DType);
		worldDefinitionLoader.UnregisterComponentDeserializer<PonyEngine::World::Hierarchy::Parent>(ParentType);
	}
}

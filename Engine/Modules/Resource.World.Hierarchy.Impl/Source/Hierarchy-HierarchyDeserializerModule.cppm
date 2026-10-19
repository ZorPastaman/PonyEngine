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
		void CreateTransform2DDeserializer(IWorldDefinitionLoader& loader);
		void DestroyTransform2DDeserializer(IWorldDefinitionLoader& loader);
		void CreateTransform3DDeserializer(IWorldDefinitionLoader& loader);
		void DestroyTransform3DDeserializer(IWorldDefinitionLoader& loader);

		static void RegisterCopyComponents(ICopyComponentDeserializer& copyComponentDeserializer);

		static constexpr std::string_view ParentType = "Pony.Parent"; ///< PonyEngine::World::Hierarchy::Parent serialized type.
		static constexpr std::string_view Transform2DType = "Pony.Transform2D"; ///< PonyEngine::World::Hierarchy::Transform2D serialized type.
		static constexpr std::string_view Transform3DType = "Pony.Transform3D"; ///< PonyEngine::World::Hierarchy::Transform3D serialized type.

		std::unique_ptr<Transform2DDeserializer> transform2DDeserializer;
		std::unique_ptr<Transform3DDeserializer> transform3DDeserializer;
	};
}

namespace PonyEngine::Resource::World::Hierarchy
{
	void HierarchyDeserializerModule::StartUp(Application::IModuleContext& context)
	{
		const Application::IApplication& application = context.Application();
		IWorldDefinitionLoader& loader = application.GetInterface<IWorldDefinitionLoader>();
		ICopyComponentDeserializer& copyComponentDeserializer = context.Application().GetInterface<ICopyComponentDeserializer>();

		CreateTransform2DDeserializer(loader);
		try
		{
			CreateTransform3DDeserializer(loader);
			try
			{
				RegisterCopyComponents(copyComponentDeserializer);
			}
			catch (...)
			{
				DestroyTransform3DDeserializer(loader);
				throw;
			}
		}
		catch (...)
		{
			DestroyTransform2DDeserializer(loader);
			throw;
		}
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
		transform2DDeserializer = std::make_unique<Transform2DDeserializer>();
		try
		{
			loader.RegisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform2D>(Transform2DType, *transform2DDeserializer);
		}
		catch (...)
		{
			transform2DDeserializer.reset();
			throw;
		}
	}

	void HierarchyDeserializerModule::DestroyTransform2DDeserializer(IWorldDefinitionLoader& loader)
	{
		loader.UnregisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform2D>(Transform2DType, *transform2DDeserializer);
		transform2DDeserializer.reset();
	}

	void HierarchyDeserializerModule::CreateTransform3DDeserializer(IWorldDefinitionLoader& loader)
	{
		transform3DDeserializer = std::make_unique<Transform3DDeserializer>();
		try
		{
			loader.RegisterComponentDeserializer<PonyEngine::World::Hierarchy::LocalTransform3D>(Transform3DType, *transform3DDeserializer);
		}
		catch (...)
		{
			transform3DDeserializer.reset();
			throw;
		}
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

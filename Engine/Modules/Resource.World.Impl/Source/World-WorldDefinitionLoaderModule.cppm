/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World.Impl:WorldDefinitionLoaderModule;

import std;

import PonyEngine.Application;
import PonyEngine.World;

import :CopyComponentDeserializer;
import :ResourceObjectDeserializer;
import :WorldDefinitionLoader;

export namespace PonyEngine::Resource::World
{
	/// @brief World definition loader module.
	class WorldDefinitionLoaderModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		WorldDefinitionLoaderModule() noexcept = default;
		WorldDefinitionLoaderModule(const WorldDefinitionLoaderModule&) = delete;
		WorldDefinitionLoaderModule(WorldDefinitionLoaderModule&&) = delete;

		~WorldDefinitionLoaderModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		WorldDefinitionLoaderModule& operator =(const WorldDefinitionLoaderModule&) = delete;
		WorldDefinitionLoaderModule& operator =(WorldDefinitionLoaderModule&&) = delete;

	private:
		void CreateWorldDefinitionLoader(Application::IModuleContext& context);
		void DestroyWorldDefinitionLoader(Application::IModuleContext& context);

		void CreateCopyComponentDeserializer(Application::IModuleContext& context);
		void DestroyCopyComponentDeserializer(Application::IModuleContext& context);

		void CreateResourceObjectDeserializer(Application::IModuleContext& context);
		void DestroyResourceObjectDeserializer(Application::IModuleContext& context);

		/// @brief Registers basic deserializers.
		void RegisterDeserializers() const;

		static constexpr std::string_view WorldDefinitionResourceType = "Pony.WorldDefinition"; ///< World definition resource type.
		static constexpr std::string_view NameType = "Pony.Name"; ///< PonyEngine::World::Name serialized type.
		static constexpr std::string_view DescriptionType = "Pony.Description"; ///< PonyEngine::World::Description serialized type.
		static constexpr std::string_view ResourceType = "Pony.Resource";
		static constexpr std::string_view StringType = "Pony.String";

		std::unique_ptr<WorldDefinitionLoader> worldDefinitionLoader; ///< World definition loader.
		std::unique_ptr<CopyComponentDeserializer> copyComponentDeserializer; ///< Copy component deserializer.
		std::unique_ptr<ResourceObjectDeserializer> resourceObjectDeserializer;
	};
}

namespace PonyEngine::Resource::World
{
	void WorldDefinitionLoaderModule::StartUp(Application::IModuleContext& context)
	{
		CreateWorldDefinitionLoader(context);
		try
		{
			CreateCopyComponentDeserializer(context);
			try
			{
				CreateResourceObjectDeserializer(context);
				try
				{
					RegisterDeserializers();
				}
				catch (...)
				{
					DestroyResourceObjectDeserializer(context);
					throw;
				}
			}
			catch (...)
			{
				DestroyCopyComponentDeserializer(context);
				throw;
			}
		}
		catch (...)
		{
			DestroyWorldDefinitionLoader(context);
			throw;
		}
	}

	void WorldDefinitionLoaderModule::ShutDown(Application::IModuleContext& context)
	{
		DestroyResourceObjectDeserializer(context);
		DestroyCopyComponentDeserializer(context);
		DestroyWorldDefinitionLoader(context);
	}

	void WorldDefinitionLoaderModule::CreateWorldDefinitionLoader(Application::IModuleContext& context)
	{
		IResourceHub& resourceHub = context.Application().GetInterface<IResourceHub>();
		const Resource::ResourceType worldDefinitionResourceType = resourceHub.MakeResourceType(WorldDefinitionResourceType);

		worldDefinitionLoader = std::make_unique<WorldDefinitionLoader>(context.Application());
		try
		{
			resourceHub.RegisterLoader(*worldDefinitionLoader, std::span(&worldDefinitionResourceType, 1uz));
			try
			{
				context.AddInterface<IWorldDefinitionLoader>(*worldDefinitionLoader);
			}
			catch (...)
			{
				resourceHub.UnregisterLoader(*worldDefinitionLoader);
				throw;
			}
		}
		catch (...)
		{
			worldDefinitionLoader.reset();
			throw;
		}
	}

	void WorldDefinitionLoaderModule::DestroyWorldDefinitionLoader(Application::IModuleContext& context)
	{
		IResourceHub& resourceHub = context.Application().GetInterface<IResourceHub>();
		context.RemoveInterface<IWorldDefinitionLoader>(*worldDefinitionLoader);
		resourceHub.UnregisterLoader(*worldDefinitionLoader);
		worldDefinitionLoader.reset();
	}

	void WorldDefinitionLoaderModule::CreateCopyComponentDeserializer(Application::IModuleContext& context)
	{
		copyComponentDeserializer = std::make_unique<CopyComponentDeserializer>(context.Application(), *worldDefinitionLoader);
		try
		{
			context.AddInterface<ICopyComponentDeserializer>(*copyComponentDeserializer);
		}
		catch (...)
		{
			copyComponentDeserializer.reset();
			throw;
		}
	}

	void WorldDefinitionLoaderModule::DestroyCopyComponentDeserializer(Application::IModuleContext& context)
	{
		context.RemoveInterface<ICopyComponentDeserializer>(*copyComponentDeserializer);
		copyComponentDeserializer.reset();
	}

	void WorldDefinitionLoaderModule::CreateResourceObjectDeserializer(Application::IModuleContext& context)
	{
		resourceObjectDeserializer = std::make_unique<ResourceObjectDeserializer>(context.Application());
		try
		{
			worldDefinitionLoader->RegisterObjectDeserializer(ResourceType, *resourceObjectDeserializer);
		}
		catch (...)
		{
			resourceObjectDeserializer.reset();
			throw;
		}
	}

	void WorldDefinitionLoaderModule::DestroyResourceObjectDeserializer(Application::IModuleContext& context)
	{
		worldDefinitionLoader->UnregisterObjectDeserializer(ResourceType, *resourceObjectDeserializer);
		resourceObjectDeserializer.reset();
	}

	void WorldDefinitionLoaderModule::RegisterDeserializers() const
	{
		const auto deserializer = static_cast<ICopyComponentDeserializer*>(copyComponentDeserializer.get());
		deserializer->Associate<PonyEngine::World::Name>(NameType);
		deserializer->Associate<PonyEngine::World::Description>(DescriptionType);
	}
}

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
		/// @brief Registers basic deserializers.
		void RegisterDeserializers() const;
		/// @brief Unregisters basic deserializers.
		void UnregisterDeserializers() const;

		static constexpr std::string_view WorldDefinitionResourceType = "Pony.WorldDefinition"; ///< World definition resource type.
		static constexpr std::string_view NameType = "Pony.Name"; ///< PonyEngine::World::Name serialized type.
		static constexpr std::string_view DescriptionType = "Pony.Description"; ///< PonyEngine::World::Description serialized type.

		std::unique_ptr<WorldDefinitionLoader> worldDefinitionLoader; ///< World definition loader.
	};
}

namespace PonyEngine::Resource::World
{
	void WorldDefinitionLoaderModule::StartUp(Application::IModuleContext& context)
	{
		IResourceHub& resourceHub = context.Application().GetInterface<IResourceHub>();
		const ResourceType worldDefinitionResourceType = resourceHub.MakeResourceType(WorldDefinitionResourceType);

		worldDefinitionLoader = std::make_unique<WorldDefinitionLoader>(context.Application());
		try
		{
			resourceHub.RegisterLoader(*worldDefinitionLoader, std::span(&worldDefinitionResourceType, 1uz));
			try
			{
				context.AddInterface<IWorldDefinitionLoader>(*worldDefinitionLoader);
				try
				{
					RegisterDeserializers();
				}
				catch (...)
				{
					context.RemoveInterface<IWorldDefinitionLoader>(*worldDefinitionLoader);
					throw;
				}
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

	void WorldDefinitionLoaderModule::ShutDown(Application::IModuleContext& context)
	{
		IResourceHub& resourceHub = context.Application().GetInterface<IResourceHub>();
		UnregisterDeserializers();
		context.RemoveInterface<IWorldDefinitionLoader>(*worldDefinitionLoader);
		resourceHub.UnregisterLoader(*worldDefinitionLoader);
		worldDefinitionLoader.reset();
	}

	void WorldDefinitionLoaderModule::RegisterDeserializers() const
	{
		const auto loader = static_cast<IWorldDefinitionLoader*>(worldDefinitionLoader.get());
		loader->RegisterComponentDeserializer<PonyEngine::World::Name>(NameType);
		loader->RegisterComponentDeserializer<PonyEngine::World::Description>(DescriptionType);
	}

	void WorldDefinitionLoaderModule::UnregisterDeserializers() const
	{
		const auto loader = static_cast<IWorldDefinitionLoader*>(worldDefinitionLoader.get());
		loader->UnregisterComponentDeserializer<PonyEngine::World::Description>(DescriptionType);
		loader->UnregisterComponentDeserializer<PonyEngine::World::Name>(NameType);
	}
}

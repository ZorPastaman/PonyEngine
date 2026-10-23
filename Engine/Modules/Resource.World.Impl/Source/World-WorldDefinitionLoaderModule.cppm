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
import PonyEngine.Utility;
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
		/// @brief Creates a world definition loader.
		/// @param context Module context.
		void CreateWorldDefinitionLoader(Application::IModuleContext& context);
		/// @brief Destroys a world definition loader.
		/// @param context Module context.
		void DestroyWorldDefinitionLoader(Application::IModuleContext& context);

		/// @brief Creates a copy component deserializer.
		/// @param context Module context.
		void CreateCopyComponentDeserializer(Application::IModuleContext& context);
		/// @brief Destroys a copy component deserializer.
		/// @param context Module context.
		void DestroyCopyComponentDeserializer(Application::IModuleContext& context);

		/// @brief Creates a resource object deserializer.
		/// @param context Module context.
		void CreateResourceObjectDeserializer(Application::IModuleContext& context);
		/// @brief Destroys a resource object deserializer.
		/// @param context Module context.
		void DestroyResourceObjectDeserializer(Application::IModuleContext& context);

		/// @brief Registers resource object deserializers.
		void RegisterResourceDeserializers() const;

		static constexpr std::string_view WorldDefinitionResourceType = "Pony.WorldDefinition"; ///< World definition resource type.
		static constexpr std::string_view ResourceType = "Pony.Resource"; ///< Resource object type.
		static constexpr std::string_view StringType = "Pony.String"; ///< std::string_view type.

		std::unique_ptr<WorldDefinitionLoader> worldDefinitionLoader; ///< World definition loader.
		std::unique_ptr<CopyComponentDeserializer> copyComponentDeserializer; ///< Copy component deserializer.
		std::unique_ptr<ResourceObjectDeserializer> resourceObjectDeserializer; ///< Resource object deserializer.
	};
}

namespace PonyEngine::Resource::World
{
	void WorldDefinitionLoaderModule::StartUp(Application::IModuleContext& context)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		CreateWorldDefinitionLoader(context);
		const auto loaderScopeGuard = Utility::ScopeGuard([&]() noexcept { DestroyWorldDefinitionLoader(context); }, scopeGuardFlag);
		CreateCopyComponentDeserializer(context);
		const auto copyComponentScopeGuard = Utility::ScopeGuard([&]() noexcept { DestroyCopyComponentDeserializer(context); }, scopeGuardFlag);
		CreateResourceObjectDeserializer(context);
		const auto resourceObjectScopeGuard = Utility::ScopeGuard([&]() noexcept { DestroyResourceObjectDeserializer(context); }, scopeGuardFlag);
		RegisterResourceDeserializers();

		scopeGuardFlag.Release();
	}

	void WorldDefinitionLoaderModule::ShutDown(Application::IModuleContext& context)
	{
		DestroyResourceObjectDeserializer(context);
		DestroyCopyComponentDeserializer(context);
		DestroyWorldDefinitionLoader(context);
	}

	void WorldDefinitionLoaderModule::CreateWorldDefinitionLoader(Application::IModuleContext& context)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		IResourceHub& resourceHub = context.Application().GetInterface<IResourceHub>();
		const Resource::ResourceType worldDefinitionResourceType = resourceHub.MakeResourceType(WorldDefinitionResourceType);
		worldDefinitionLoader = std::make_unique<WorldDefinitionLoader>(context.Application());
		const auto loaderScopeGuard = Utility::ScopeGuard([&]() noexcept { worldDefinitionLoader.reset(); }, scopeGuardFlag);
		resourceHub.RegisterLoader(*worldDefinitionLoader, std::span(&worldDefinitionResourceType, 1uz));
		const auto registerScopeGuard = Utility::ScopeGuard([&]() noexcept { resourceHub.UnregisterLoader(*worldDefinitionLoader); }, scopeGuardFlag);
		context.AddInterface<IWorldDefinitionLoader>(*worldDefinitionLoader);

		scopeGuardFlag.Release();
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
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		copyComponentDeserializer = std::make_unique<CopyComponentDeserializer>(context.Application(), *worldDefinitionLoader);
		const auto deserializerScopeGuard = Utility::ScopeGuard([&]() noexcept { copyComponentDeserializer.reset(); }, scopeGuardFlag);
		context.AddInterface<ICopyComponentDeserializer>(*copyComponentDeserializer);

		scopeGuardFlag.Release();
	}

	void WorldDefinitionLoaderModule::DestroyCopyComponentDeserializer(Application::IModuleContext& context)
	{
		context.RemoveInterface<ICopyComponentDeserializer>(*copyComponentDeserializer);
		copyComponentDeserializer.reset();
	}

	void WorldDefinitionLoaderModule::CreateResourceObjectDeserializer(Application::IModuleContext& context)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		resourceObjectDeserializer = std::make_unique<ResourceObjectDeserializer>(context.Application());
		const auto deserializerScopeGuard = Utility::ScopeGuard([&]() noexcept { resourceObjectDeserializer.reset(); }, scopeGuardFlag);
		worldDefinitionLoader->RegisterObjectDeserializer(ResourceType, *resourceObjectDeserializer);

		scopeGuardFlag.Release();
	}

	void WorldDefinitionLoaderModule::DestroyResourceObjectDeserializer(Application::IModuleContext& context)
	{
		worldDefinitionLoader->UnregisterObjectDeserializer(ResourceType, *resourceObjectDeserializer);
		resourceObjectDeserializer.reset();
	}

	void WorldDefinitionLoaderModule::RegisterResourceDeserializers() const
	{
		const auto deserializer = static_cast<IResourceObjectDeserializer*>(resourceObjectDeserializer.get());
		deserializer->Associate<std::string_view>(StringType);
	}
}

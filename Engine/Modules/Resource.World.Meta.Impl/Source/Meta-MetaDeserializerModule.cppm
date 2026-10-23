/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.World.Meta.Impl:MetaDeserializerModule;

import std;

import PonyEngine.Application;
import PonyEngine.Resource.World.Ext;
import PonyEngine.Utility;
import PonyEngine.World.Meta;

import :NameDeserializer;

export namespace PonyEngine::Resource::World::Meta
{
	/// @brief Meta deserializer module.
	class MetaDeserializerModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		MetaDeserializerModule() noexcept = default;
		MetaDeserializerModule(const MetaDeserializerModule&) = delete;
		MetaDeserializerModule(MetaDeserializerModule&&) = delete;

		~MetaDeserializerModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		MetaDeserializerModule& operator =(const MetaDeserializerModule&) = delete;
		MetaDeserializerModule& operator =(MetaDeserializerModule&&) = delete;

	private:
		/// @brief Creates a name deserializer.
		/// @param loader World definition loader.
		void CreateNameDeserializer(IWorldDefinitionLoader& loader);
		/// @brief Destroys a name deserializer.
		/// @param loader World definition loader.
		void DestroyNameDeserializer(IWorldDefinitionLoader& loader);

		/// @brief Registers components that can be simply copied.
		/// @param copyComponentDeserializer Copy component deserializer.
		static void RegisterCopyComponents(ICopyComponentDeserializer& copyComponentDeserializer);

		static constexpr std::string_view NameType = "Pony.Name"; ///< PonyEngine::World::Meta::Name serialized type.
		static constexpr std::string_view DescriptionType = "Pony.Description"; ///< PonyEngine::World::Meta::Description serialized type.

		std::unique_ptr<NameDeserializer> nameDeserializer; ///< Name deserializer.
	};
}

namespace PonyEngine::Resource::World::Meta
{
	void MetaDeserializerModule::StartUp(Application::IModuleContext& context)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		const Application::IApplication& application = context.Application();
		IWorldDefinitionLoader& loader = application.GetInterface<IWorldDefinitionLoader>();
		ICopyComponentDeserializer& copyComponentDeserializer = context.Application().GetInterface<ICopyComponentDeserializer>();
		CreateNameDeserializer(loader);
		const auto deserializerScopeGuard = Utility::ScopeGuard([&]() noexcept { DestroyNameDeserializer(loader); }, scopeGuardFlag);
		RegisterCopyComponents(copyComponentDeserializer);

		scopeGuardFlag.Release();
	}

	void MetaDeserializerModule::ShutDown(Application::IModuleContext& context)
	{
		const Application::IApplication& application = context.Application();
		IWorldDefinitionLoader& loader = application.GetInterface<IWorldDefinitionLoader>();
		DestroyNameDeserializer(loader);
	}

	void MetaDeserializerModule::CreateNameDeserializer(IWorldDefinitionLoader& loader)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		nameDeserializer = std::make_unique<NameDeserializer>();
		const auto deserializerScopeGuard = Utility::ScopeGuard([&]() noexcept { nameDeserializer.reset(); }, scopeGuardFlag);
		loader.RegisterComponentDeserializer<PonyEngine::World::Meta::Name>(NameType, *nameDeserializer);

		scopeGuardFlag.Release();
	}

	void MetaDeserializerModule::DestroyNameDeserializer(IWorldDefinitionLoader& loader)
	{
		loader.UnregisterComponentDeserializer<PonyEngine::World::Meta::Name>(NameType, *nameDeserializer);
		nameDeserializer.reset();
	}

	void MetaDeserializerModule::RegisterCopyComponents(ICopyComponentDeserializer& copyComponentDeserializer)
	{
		copyComponentDeserializer.Associate<PonyEngine::World::Meta::Description>(DescriptionType);
	}
}

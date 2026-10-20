/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Meta.Impl:MetaModule;

import std;

import PonyEngine.Application;
import PonyEngine.World.Meta;

export namespace PonyEngine::World::Meta
{
	/// @brief World meta module.
	class MetaModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		MetaModule() noexcept = default;
		MetaModule(const MetaModule&) = delete;
		MetaModule(MetaModule&&) = delete;

		~MetaModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		MetaModule& operator =(const MetaModule&) = delete;
		MetaModule& operator =(MetaModule&&) = delete;
	};
}

namespace PonyEngine::World::Meta
{
	void MetaModule::StartUp(Application::IModuleContext& context)
	{
		IWorldService& service = context.Application().GetInterface<IWorldService>();
		service.RegisterComponent<Name>();
		service.RegisterComponent<Description>();
		service.RegisterObjectHandleMember(&Description::value);
	}

	void MetaModule::ShutDown(Application::IModuleContext& context)
	{
	}
}

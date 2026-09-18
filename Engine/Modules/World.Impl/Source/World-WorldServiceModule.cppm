/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World.Impl:WorldServiceModule;

import PonyEngine.Application;

import :WorldService;

export namespace PonyEngine::World
{
	/// @brief World service module.
	class WorldServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		WorldServiceModule() noexcept = default;
		WorldServiceModule(const WorldServiceModule&) = delete;
		WorldServiceModule(WorldServiceModule&&) = delete;

		~WorldServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		WorldServiceModule& operator =(const WorldServiceModule&) = delete;
		WorldServiceModule& operator =(WorldServiceModule&&) = delete;

	private:
		std::unique_ptr<WorldService> worldService; ///< World service.
	};
}

namespace PonyEngine::World
{
	void WorldServiceModule::StartUp(Application::IModuleContext& context)
	{
		worldService = std::make_unique<WorldService>(context.Application());
		try
		{
			context.AddInterface<IWorldService>(*worldService);
		}
		catch (...)
		{
			worldService.reset();
			throw;
		}
	}

	void WorldServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveInterface<IWorldService>(*worldService);
		worldService.reset();
	}
}

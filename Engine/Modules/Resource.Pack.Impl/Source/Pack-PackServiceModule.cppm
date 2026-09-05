/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:PackServiceModule;

import std;

import PonyEngine.Application;

import :PackService;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack resource provider module.
	class PackServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackServiceModule() noexcept = default;
		PackServiceModule(const PackServiceModule&) = delete;
		PackServiceModule(PackServiceModule&&) = delete;

		~PackServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		PackServiceModule& operator =(const PackServiceModule&) = delete;
		PackServiceModule& operator =(PackServiceModule&&) = delete;

	private:
		std::unique_ptr<PackService> packService; ///< Pack service.
	};
}

namespace PonyEngine::Resource::Pack
{
	void PackServiceModule::StartUp(Application::IModuleContext& context)
	{
		packService = std::make_unique<PackService>(context.Application());
		try
		{
			context.AddInterface<IPackService>(*packService);
		}
		catch (...)
		{
			packService.reset();
			throw;
		}
	}

	void PackServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveInterface<IPackService>(*packService);
		packService.reset();
	}
}

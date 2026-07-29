/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Impl:RawInputServiceModule;

import std;

import PonyEngine.Application;
import PonyEngine.RawInput.Ext;

import :RawInputService;

export namespace PonyEngine::RawInput
{
	/// @brief Raw input service module.
	class RawInputServiceModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		RawInputServiceModule() noexcept = default;
		RawInputServiceModule(const RawInputServiceModule&) = delete;
		RawInputServiceModule(RawInputServiceModule&&) = delete;

		~RawInputServiceModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		RawInputServiceModule& operator =(const RawInputServiceModule&) = delete;
		RawInputServiceModule& operator =(RawInputServiceModule&&) = delete;

	private:
		std::unique_ptr<RawInputService> rawInput; ///< Raw input service.
	};
}

namespace PonyEngine::RawInput
{
	void RawInputServiceModule::StartUp(Application::IModuleContext& context)
	{
		rawInput = std::make_unique<RawInputService>(context.Application());
		try
		{
			context.AddInterface<IRawInputService>(*rawInput);
			try
			{
				context.AddInterface<IDeviceHub>(*rawInput);
				try
				{
					context.AddTickable(rawInput->Tickable(), Application::TickableOrder{.tickOrder = PONY_ENGINE_RAW_INPUT_TICK_ORDER});
				}
				catch (...)
				{
					context.RemoveInterface<IDeviceHub>(*rawInput);
					throw;
				}
			}
			catch (...)
			{
				context.RemoveInterface<IRawInputService>(*rawInput);
				throw;
			}
		}
		catch (...)
		{
			rawInput.reset();
			throw;
		}
	}

	void RawInputServiceModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveTickable(rawInput->Tickable(), Application::TickableOrder{.tickOrder = PONY_ENGINE_RAW_INPUT_TICK_ORDER});
		context.RemoveInterface<IDeviceHub>(*rawInput);
		context.RemoveInterface<IRawInputService>(*rawInput);
		rawInput.reset();
	}
}

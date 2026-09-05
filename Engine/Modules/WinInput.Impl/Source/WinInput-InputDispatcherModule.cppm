/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.WinInput.Impl:InputDispatcherModule;

import std;

import PonyEngine.Application;

import :InputDispatcher;

export namespace PonyEngine::WinInput
{
	/// @brief WinAPI input dispatcher module.
	class InputDispatcherModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		InputDispatcherModule() noexcept = default;
		InputDispatcherModule(const InputDispatcherModule&) = delete;
		InputDispatcherModule(InputDispatcherModule&&) = delete;

		~InputDispatcherModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		InputDispatcherModule& operator =(const InputDispatcherModule&) = delete;
		InputDispatcherModule& operator =(InputDispatcherModule&&) = delete;

	private:
		std::unique_ptr<InputDispatcher> inputDispatcher; ///< WinAPI input dispatcher.
	};
}

namespace PonyEngine::WinInput
{
	void InputDispatcherModule::StartUp(Application::IModuleContext& context)
	{
		inputDispatcher = std::make_unique<InputDispatcher>(context.Application());
		try
		{
			context.AddInterface<IInputDispatcher>(*inputDispatcher);
		}
		catch (...)
		{
			inputDispatcher.reset();
			throw;
		}
	}

	void InputDispatcherModule::ShutDown(Application::IModuleContext& context)
	{
		context.RemoveInterface<IInputDispatcher>(*inputDispatcher);
		inputDispatcher.reset();
	}
}

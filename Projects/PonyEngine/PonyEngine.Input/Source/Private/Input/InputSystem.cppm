/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Input.Detail:InputSystem;

import <cstddef>;
import <cstdint>;
import <exception>;
import <memory>;
import <queue>;
import <ranges>;
import <string>;
import <string_view>;
import <typeinfo>;
import <unordered_map>;
import <utility>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Input;

export namespace PonyEngine::Input
{
	/// @brief Input system.
	class InputSystem final : public Core::TickableSystem, public IInputSystem, private IInputSystemContext
	{
	public:
		/// @brief Creates an input system
		/// @param engine Engine context.
		/// @param systemParams System parameters.
		/// @param inputParams Input system parameters.
		[[nodiscard("Pure constructor")]]
		InputSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const InputSystemParams& inputParams) noexcept;
		InputSystem(const InputSystem&) = delete;
		InputSystem(InputSystem&&) = delete;

		virtual ~InputSystem() noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputReceiver> CreateReceiver(std::string_view id) override;

		InputSystem& operator =(const InputSystem&) = delete;
		InputSystem& operator =(InputSystem&&) = delete;

	private:
		/// @brief Input mapping value.
		struct InputMappingValue final
		{
			std::string id; ///< Binding id.
			float multiplier; ///< Input multiplier.
		};

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Core::ISystemManager& SystemManager() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Core::ISystemManager& SystemManager() const noexcept override;

		virtual void AddInputEvent(const InputEvent& inputEvent) override;

		/// @brief Cleans out of dead handles.
		void Clean() noexcept;
		/// @brief Ticks devices.
		void TickDevices();
		/// @brief Processes the current input queue.
		void ProcessInput();

		/// @brief Processes the @p inputEvent.
		/// @param inputEvent Input event to process.
		void ProcessInputEvent(const InputEvent& inputEvent);
		/// @brief Execute bound actions.
		/// @param mapping Mapping to execute.
		/// @param value Input event value.
		void ExecuteReceivers(const InputMappingValue& mapping, float value);

		std::vector<std::unique_ptr<InputDevice>> devices; ///< Input devices.
		std::unordered_map<InputCode, std::vector<InputMappingValue>> inputMapping; ///< Input mapping.

		std::queue<InputEvent> inputQueue; ///< Current input queue.

		std::unordered_map<std::string, std::vector<std::shared_ptr<InputReceiver>>> inputReceivers; ///< Input receivers.
	};
}

namespace PonyEngine::Input
{
	InputSystem::InputSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const InputSystemParams& inputParams) noexcept :
		TickableSystem(engine, systemParams)
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create devices.");
		for (const std::shared_ptr<IInputDeviceFactory>& deviceFactory : inputParams.inputDeviceFactories)
		{
			assert(deviceFactory && "The device factory is nullptr.");
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Create '{}' device with '{}' factory.", deviceFactory->DeviceType().name(), typeid(*deviceFactory).name());
			InputDeviceData device = deviceFactory->CreateDevice(*static_cast<IInputSystemContext*>(this), InputDeviceParams{});
			assert(device.inputDevice && "The device is nullptr");
			devices.push_back(std::move(device.inputDevice));
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Device created.");
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Devices created.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Set input bindings.");
		for (const auto& [id, binding] : inputParams.inputBindings)
		{
			for (const InputBindingValue& bindingValue : binding)
			{
				PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Set input binding. ID: '{}'; Input code: '{}'; Multiplier: '{}'.", id, ToString(bindingValue.inputCode), bindingValue.multiplier);
				inputMapping[bindingValue.inputCode].push_back(InputMappingValue{.id = id, .multiplier = bindingValue.multiplier});
			}
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Input bindings set.");
	}

	InputSystem::~InputSystem() noexcept
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy devices.");
		for (auto it = devices.rbegin(); it != devices.rend(); ++it)
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' device.", typeid(**it).name());
			it->reset();
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Device destroyed.");
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Devices destroyed.");
	}

	void InputSystem::Begin()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Begin devices.");
		for (const std::unique_ptr<InputDevice>& device : devices)
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Begin '{}' device.", typeid(*device).name());
			device->Begin();
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Device begun.");
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Devices begun.");
	}

	void InputSystem::End()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "End devices.");
		for (auto it = devices.crbegin(); it != devices.crend(); ++it)
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "End '{}' device.", typeid(**it).name());
			try
			{
				(*it)->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(Engine().Logger(), e, "On ending '{}' device.", typeid(**it).name());
			}
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Device ended.");
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Devices ended.");
	}

	void InputSystem::Tick()
	{
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Clean.");
		Clean();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Tick devices.");
		TickDevices();
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Process input.");
		ProcessInput();
	}

	std::shared_ptr<InputReceiver> InputSystem::CreateReceiver(const std::string_view id)
	{
		auto receiver = std::make_shared<InputReceiver>();
		inputReceivers[std::string(id)].push_back(receiver);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Input receiver added with '{}' ID. Receiver: '0x{:X}'.", id, reinterpret_cast<std::uintptr_t>(receiver.get()));

		return receiver;
	}

	PonyDebug::Log::ILogger& InputSystem::Logger() noexcept
	{
		return Engine().Logger();
	}

	const PonyDebug::Log::ILogger& InputSystem::Logger() const noexcept
	{
		return Engine().Logger();
	}

	Core::ISystemManager& InputSystem::SystemManager() noexcept
	{
		return Engine().SystemManager();
	}

	const Core::ISystemManager& InputSystem::SystemManager() const noexcept
	{
		return Engine().SystemManager();
	}

	void InputSystem::AddInputEvent(const InputEvent& inputEvent)
	{
		inputQueue.push(inputEvent);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Input event added with '{}' input code.", ToString(inputEvent.inputCode));
	}

	void InputSystem::Clean() noexcept
	{
		for (std::vector<std::shared_ptr<InputReceiver>>& receivers : std::ranges::views::values(inputReceivers))
		{
			for (std::size_t i = receivers.size(); i-- > 0; )
			{
				if (receivers[i].use_count() <= 1)
				{
					PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Destroy input receiver at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(receivers[i].get()));
					receivers.erase(receivers.cbegin() + i);
					PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Input receiver destroyed.");
				}
			}
		}
	}

	void InputSystem::TickDevices()
	{
		for (const std::unique_ptr<InputDevice>& device : devices)
		{
			device->Tick();
		}
	}

	void InputSystem::ProcessInput()
	{
		while (!inputQueue.empty())
		{
			ProcessInputEvent(inputQueue.front());
			inputQueue.pop();
		}
	}

	void InputSystem::ProcessInputEvent(const InputEvent& inputEvent)
	{
		if (const auto& mappingPosition = inputMapping.find(inputEvent.inputCode); mappingPosition != inputMapping.cend())
		{
			for (const InputMappingValue& inputMappingValue : mappingPosition->second)
			{
				ExecuteReceivers(inputMappingValue, inputEvent.value);
			}
		}
	}

	void InputSystem::ExecuteReceivers(const InputMappingValue& mapping, const float value)
	{
		if (const auto& receivers = inputReceivers.find(mapping.id); receivers != inputReceivers.cend())
		{
			const float inputValue = value * mapping.multiplier;
			for (const std::shared_ptr<InputReceiver>& receiver : receivers->second)
			{
				receiver->Execute(inputValue);
			}
		}
	}
}

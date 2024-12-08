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

import <cmath>;
import <cstddef>;
import <cstdint>;
import <exception>;
import <functional>;
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
		virtual std::shared_ptr<InputHandle> Bind(std::string_view id, const std::function<void(bool)>& action, float magnitudeThreshold) override;
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputHandle> Bind(std::string_view id, const std::function<void(float)>& action) override;

		InputSystem& operator =(const InputSystem&) = delete;
		InputSystem& operator =(InputSystem&&) = delete;

	private:
		/// @brief Input mapping value.
		struct InputMappingValue final
		{
			std::string id; ///< Binding id.
			float multiplier; ///< Input multiplier.
		};

		/// @brief Bool action binding.
		struct BoolBinding final
		{
			std::shared_ptr<InputHandle> handle; ///< Input handle.
			std::function<void(bool)> action; ///< Input action.
			float magnitudeThreshold; ///< Input magnitude threshold to be @true.
		};
		/// @brief Float action binding.
		struct FloatBinding final
		{
			std::shared_ptr<InputHandle> handle; ///< Input handle.
			std::function<void(float)> action; ///< Input action.
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
		void ExecuteActions(const InputMappingValue& mapping, float value);

		std::vector<std::unique_ptr<InputDevice>> devices; ///< Input devices.
		std::unordered_map<InputCode, std::vector<InputMappingValue>> inputMapping; ///< Input mapping.

		std::queue<InputEvent> inputQueue; ///< Current input queue.

		std::unordered_map<std::string, std::vector<BoolBinding>> boolBindings; ///< Bool input bindings.
		std::unordered_map<std::string, std::vector<FloatBinding>> floatBindings; ///< Float input bindings.
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
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' device.", typeid(*it).name());
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

	std::shared_ptr<InputHandle> InputSystem::Bind(const std::string_view id, const std::function<void(bool)>& action, const float magnitudeThreshold)
	{
		const auto handle = std::make_shared<InputHandle>();
		boolBindings[std::string(id)].push_back(BoolBinding{.handle = handle, .action = action, .magnitudeThreshold = magnitudeThreshold});
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Bool input binding added with '{}' ID. Handle: '0x{:X}'.", id, reinterpret_cast<std::uintptr_t>(handle.get()));

		return handle;
	}

	std::shared_ptr<InputHandle> InputSystem::Bind(const std::string_view id, const std::function<void(float)>& action)
	{
		const auto handle = std::make_shared<InputHandle>();
		floatBindings[std::string(id)].push_back(FloatBinding{.handle = handle, .action = action});
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Float input binding added with '{}' ID. Handle: '0x{:X}'.", id, reinterpret_cast<std::uintptr_t>(handle.get()));

		return handle;
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
		for (std::vector<BoolBinding>& binding : std::ranges::views::values(boolBindings))
		{
			for (std::size_t i = binding.size(); i-- > 0; )
			{
				const std::shared_ptr<InputHandle>& handle = binding[i].handle;
				if (handle.use_count() <= 1)
				{
					PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Bool input binding with '0x{:X}' handled removed.", reinterpret_cast<std::uintptr_t>(handle.get()));
					binding.erase(binding.cbegin() + i);
				}
			}
		}

		for (std::vector<FloatBinding>& binding : std::ranges::views::values(floatBindings))
		{
			for (std::size_t i = binding.size(); i-- > 0; )
			{
				const std::shared_ptr<InputHandle>& handle = binding[i].handle;
				if (handle.use_count() <= 1)
				{
					PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Float input binding with '0x{:X}' handled removed.", reinterpret_cast<std::uintptr_t>(handle.get()));
					binding.erase(binding.cbegin() + i);
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
				ExecuteActions(inputMappingValue, inputEvent.value);
			}
		}
	}

	void InputSystem::ExecuteActions(const InputMappingValue& mapping, const float value)
	{
		const float inputValue = value * mapping.multiplier;

		if (const auto& boolBinding = boolBindings.find(mapping.id); boolBinding != boolBindings.cend())
		{
			for (const BoolBinding& binding : boolBinding->second)
			{
				binding.action(std::abs(inputValue) > binding.magnitudeThreshold);
			}
		}

		if (const auto& floatBinding = floatBindings.find(mapping.id); floatBinding != floatBindings.cend())
		{
			for (const FloatBinding& binding : floatBinding->second)
			{
				binding.action(inputValue);
			}
		}
	}
}

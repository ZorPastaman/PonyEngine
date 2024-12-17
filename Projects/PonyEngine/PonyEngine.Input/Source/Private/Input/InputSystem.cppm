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
import <numeric>;
import <queue>;
import <stdexcept>;
import <string>;
import <string_view>;
import <typeinfo>;
import <unordered_map>;
import <utility>;
import <vector>;

import PonyBase.StringUtility;

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
		virtual void End() noexcept override;

		virtual void Tick() override;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputReceiver> CreateReceiver(std::string_view id) override;

		[[nodiscard("Pure function")]]
		virtual float State(std::string_view id) const override;

		InputSystem& operator =(const InputSystem&) = delete;
		InputSystem& operator =(InputSystem&&) = delete;

	private:
		/// @brief Input mapping value.
		struct InputMappingValue final
		{
			std::size_t idIndex; ///< Binding id index.
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

		virtual void AddInputEvent(const IInputDevice& inputSource, const InputEvent& inputEvent) override;

		/// @brief Gets an index of the @p id.
		/// @param id Id.
		/// @return Index.
		[[nodiscard("Pure function")]]
		std::size_t IdIndex(std::string_view id) const;
		/// @brief Gets an index of the @p device.
		/// @param device Device.
		/// @return Device index.
		[[nodiscard("Pure function")]]
		std::size_t DeviceIndex(const IInputDevice& device) const;

		/// @brief Cleans out of dead handles.
		void Clean() noexcept;
		/// @brief Ticks devices.
		void TickDevices();
		/// @brief Processes the current input queue.
		void ProcessInput();

		/// @brief Processes the @p inputEvent.
		/// @param input Input event to process.
		void ProcessInputEvent(const std::pair<const IInputDevice*, InputEvent>& input);
		/// @brief Updates an input state.
		/// @param inputSource Input source.
		/// @param idIndex ID index.
		/// @param value Input value.
		void UpdateInputState(const IInputDevice& inputSource, std::size_t idIndex, float value);
		/// @brief Execute bound actions.
		/// @param idIndex ID index.
		/// @param value Input value.
		void ExecuteReceivers(std::size_t idIndex, float value);

		std::vector<std::unique_ptr<InputDevice>> devices; ///< Input devices.
		std::vector<std::string> inputIds; ///< Input ids.
		std::unordered_map<InputCode, std::vector<InputMappingValue>> inputMapping; ///< Input mapping.

		std::queue<std::pair<const IInputDevice*, InputEvent>> inputQueue; ///< Current input queue.
		std::vector<std::vector<float>> states; ///< Input state. First level is bound to the @p inputIds via index. Second level is bound to the @p devices via index.
		std::vector<std::vector<std::shared_ptr<InputReceiver>>> inputReceivers; ///< Input receivers. First level is bound to the @p inputIds via index.
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
			inputIds.push_back(id);
			for (const InputBindingValue& bindingValue : binding)
			{
				PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Set input binding. ID: '{}'; Input code: '{}'; Multiplier: '{}'.", id, ToString(bindingValue.inputCode), bindingValue.multiplier);
				inputMapping[bindingValue.inputCode].push_back(InputMappingValue{.idIndex = inputIds.size() - 1, .multiplier = bindingValue.multiplier});
			}
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Input bindings set.");

		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Prewarm caches.");
		states.resize(inputIds.size());
		for (auto& state : states)
		{
			state.resize(devices.size());
		}
		inputReceivers.resize(inputIds.size());
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Info, "Caches prewarmed.");
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

	void InputSystem::End() noexcept
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
		inputReceivers[IdIndex(id)].push_back(receiver);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Input receiver added with '{}' ID. Receiver: '0x{:X}'.", id, reinterpret_cast<std::uintptr_t>(receiver.get()));

		return receiver;
	}

	float InputSystem::State(const std::string_view id) const
	{
		const std::vector<float>& state = states[IdIndex(id)];

		return std::reduce(state.begin(), state.end());
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

	void InputSystem::AddInputEvent(const IInputDevice& inputSource, const InputEvent& inputEvent)
	{
		inputQueue.emplace(&inputSource, inputEvent);
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Input event from '0x{:X}' added with '{}' input code.", reinterpret_cast<std::uintptr_t>(&inputSource), ToString(inputEvent.inputCode));
	}

	std::size_t InputSystem::IdIndex(const std::string_view id) const
	{
		for (std::size_t i = 0; i < inputIds.size(); ++i)
		{
			if (id == inputIds[i])
			{
				return i;
			}
		}

		throw std::invalid_argument(PonyBase::Utility::SafeFormat("No input is bound to '{}' id.", id));
	}

	std::size_t InputSystem::DeviceIndex(const IInputDevice& device) const
	{
		for (std::size_t i = 0; i < devices.size(); ++i)
		{
			if (static_cast<const IInputDevice*>(devices[i].get()) == &device)
			{
				return i;
			}
		}

		throw std::invalid_argument(PonyBase::Utility::SafeFormat("No device is bound by interface at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&device)));
	}

	void InputSystem::Clean() noexcept
	{
		for (std::vector<std::shared_ptr<InputReceiver>>& receivers : inputReceivers)
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

	void InputSystem::ProcessInputEvent(const std::pair<const IInputDevice*, InputEvent>& input)
	{
		if (const auto& mappingPosition = inputMapping.find(input.second.inputCode); mappingPosition != inputMapping.cend())
		{
			for (const InputMappingValue& inputMappingValue : mappingPosition->second)
			{
				const float value = input.second.value * inputMappingValue.multiplier;
				UpdateInputState(*input.first, inputMappingValue.idIndex, value);
				ExecuteReceivers(inputMappingValue.idIndex, value);
			}
		}
	}

	void InputSystem::UpdateInputState(const IInputDevice& inputSource, const std::size_t idIndex, const float value)
	{
		states[idIndex][DeviceIndex(inputSource)] = value;
	}

	void InputSystem::ExecuteReceivers(const std::size_t idIndex, const float value)
	{
		for (const std::shared_ptr<InputReceiver>& receiver : inputReceivers[idIndex])
		{
			receiver->Execute(value);
		}
	}
}

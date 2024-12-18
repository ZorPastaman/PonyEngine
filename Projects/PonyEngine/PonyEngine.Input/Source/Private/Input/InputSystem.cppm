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

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <exception>;
import <memory>;
import <numeric>;
import <optional>;
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
		virtual void End() noexcept override;

		virtual void Tick() override;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<InputReceiver> CreateReceiver(std::string_view id) override;

		[[nodiscard("Pure function")]]
		virtual float State(std::string_view id) const noexcept override;

		InputSystem& operator =(const InputSystem&) = delete;
		InputSystem& operator =(InputSystem&&) = delete;

	private:
		/// @brief Input mapping entry.
		struct InputMappingEntry final
		{
			std::size_t idIndex; ///< Binding id index.
			InputCode inputCode; ///< Input code.
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

		/// @brief Zeroes deltas.
		void ZeroDeltas() noexcept;
		/// @brief Cleans out of dead receivers.
		void Clean() noexcept;
		/// @brief Ticks devices.
		void TickDevices();
		/// @brief Processes the current input queue.
		void ProcessInput();

		/// @brief Processes the @p inputEvent.
		/// @param inputEntry Input entry to process.
		void ProcessInputEvent(const std::pair<const IInputDevice*, InputEvent>& inputEntry);
		/// @brief Updates a state and a delta.
		/// @param inputEntry Input entry.
		void UpdateStateAndDelta(const std::pair<const IInputDevice*, InputEvent>& inputEntry);
		/// @brief Updates a state.
		/// @param inputDevice Input source.
		/// @param inputCode Input code.
		/// @param value Input value.
		void UpdateState(const IInputDevice& inputDevice, InputCode inputCode, float value);
		/// @brief Updates a delta.
		/// @param inputCode Input code.
		/// @param value Input value.
		void UpdateDelta(InputCode inputCode, float value);
		/// @brief Execute bound actions.
		/// @param idIndex Binding ID index.
		/// @param value Input value.
		void ExecuteReceivers(std::size_t idIndex, float value) const;

		/// @brief Gets an input ID index.
		/// @param id Input ID.
		/// @return Input ID index. If there's no such an ID, it's nullopt.
		[[nodiscard("Pure function")]]
		std::optional<std::size_t> InputIdIndex(std::string_view id) const noexcept;
		/// @brief Gets a device index.
		/// @param device Device.
		/// @return Device index. If there's no such a device, it's nullopt.
		[[nodiscard("Pure function")]]
		std::optional<std::size_t> DeviceIndex(const IInputDevice& device) const noexcept;

		std::vector<std::unique_ptr<InputDevice>> devices; ///< Input devices.

		std::vector<std::string> inputIds; ///< Input ids.
		std::vector<InputMappingEntry> inputMapping; ///< Input mapping.

		std::unordered_map<std::size_t, std::vector<std::size_t>> idToInputMapping; ///< Input ID index to input mapping entries map.
		std::unordered_map<InputCode, std::vector<std::size_t>> codeToInputMapping; ///< Input code to input mapping entries map.

		std::queue<std::pair<const IInputDevice*, InputEvent>> inputQueue; ///< Input queue.
		std::unordered_map<std::size_t, std::vector<std::shared_ptr<InputReceiver>>> inputReceivers; ///< Input ID index to input receivers map.

		std::unordered_map<InputCode, std::vector<float>> inputStates; ///< Input states. Input code to input states. Inputs states are synced with corresponding devices via index.
		std::unordered_map<InputCode, float> inputDeltas; ///< Input deltas.
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
			const std::size_t idIndex = inputIds.size() - 1;
			for (const auto& [inputCode, multiplier] : binding)
			{
				PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Set input binding. ID: '{}'; Input code: '{}'; Multiplier: '{}'.", id, ToString(inputCode), multiplier);
				inputMapping.push_back(InputMappingEntry{.idIndex = idIndex, .inputCode = inputCode, .multiplier = multiplier});
				const std::size_t entryIndex = inputMapping.size() - 1;
				idToInputMapping[idIndex].push_back(entryIndex);
				codeToInputMapping[inputCode].push_back(entryIndex);
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
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Verbose, "Zero deltas.");
		ZeroDeltas();
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
		if (const std::optional<std::size_t> inputIdIndex = InputIdIndex(id)) [[likely]]
		{
			inputReceivers[inputIdIndex.value()].push_back(receiver);
		}
		else [[unlikely]]
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Warning, "Input receiver created for a not bound input ID: '{}'.", id);
		}
		PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "Input receiver created with '{}' ID. Receiver: '0x{:X}'.", id, reinterpret_cast<std::uintptr_t>(receiver.get()));

		return receiver;
	}

	float InputSystem::State(const std::string_view id) const noexcept
	{
		float value = 0.f;

		if (const std::optional<std::size_t> idIndex = InputIdIndex(id)) [[likely]]
		{
			for (const auto mappingIndex : idToInputMapping.at(idIndex.value()))
			{
				const InputMappingEntry& mapping = inputMapping[mappingIndex];

				if (const auto state = inputStates.find(mapping.inputCode); state != inputStates.cend())
				{
					value += std::reduce(state->second.begin(), state->second.end()) * mapping.multiplier;
				}

				if (const auto delta = inputDeltas.find(mapping.inputCode); delta != inputDeltas.cend())
				{
					value += delta->second * mapping.multiplier;
				}
			}
		}
		else [[unlikely]]
		{
			PONY_LOG(Engine().Logger(), PonyDebug::Log::LogType::Debug, "No input is bound by '{}' ID.", id);
		}

		return value;
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

	void InputSystem::ZeroDeltas() noexcept
	{
		std::ranges::fill(std::ranges::views::values(inputDeltas), 0.f);
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

	void InputSystem::ProcessInputEvent(const std::pair<const IInputDevice*, InputEvent>& inputEntry)
	{
		UpdateStateAndDelta(inputEntry);

		if (const auto& mappingPosition = codeToInputMapping.find(inputEntry.second.inputCode); mappingPosition != codeToInputMapping.cend())
		{
			for (const std::size_t inputMappingIndex : mappingPosition->second)
			{
				const InputMappingEntry& inputMappingEntry = inputMapping[inputMappingIndex];
				const float value = inputEntry.second.inputValue * inputMappingEntry.multiplier;
				ExecuteReceivers(inputMappingEntry.idIndex, value);
			}
		}
	}

	void InputSystem::UpdateStateAndDelta(const std::pair<const IInputDevice*, InputEvent>& inputEntry)
	{
		switch (inputEntry.second.inputType)
		{
		case InputType::State:
			UpdateState(*inputEntry.first, inputEntry.second.inputCode, inputEntry.second.inputValue);
			break;
		case InputType::Delta:
			UpdateDelta(inputEntry.second.inputCode, inputEntry.second.inputValue);
			break;
		default: [[unlikely]]
			assert(false && "The incorrect input type has been received.");
			break;
		}
	}

	void InputSystem::UpdateState(const IInputDevice& inputDevice, const InputCode inputCode, const float value)
	{
		const std::optional<std::size_t> deviceIndex = DeviceIndex(inputDevice);
		assert(deviceIndex && "The input with the wrong input device has been received.");

		std::vector<float>* states;
		if (const auto statesPosition = inputStates.find(inputCode); statesPosition != inputStates.cend()) [[likely]]
		{
			states = &statesPosition->second;
		}
		else [[unlikely]]
		{
			std::vector<float>& newStates = inputStates[inputCode];
			newStates.resize(devices.size());
			std::ranges::fill(newStates, 0.f);
			states = &newStates;
		}

		(*states)[deviceIndex.value()] = value;
	}

	void InputSystem::UpdateDelta(const InputCode inputCode, const  float value)
	{
		inputDeltas[inputCode] += value;
	}

	void InputSystem::ExecuteReceivers(const std::size_t idIndex, const float value) const
	{
		if (const auto receivers = inputReceivers.find(idIndex); receivers != inputReceivers.cend())
		{
			for (const std::shared_ptr<InputReceiver>& receiver : receivers->second)
			{
				receiver->Execute(value);
			}
		}
	}

	std::optional<std::size_t> InputSystem::InputIdIndex(const std::string_view id) const noexcept
	{
		for (std::size_t i = 0; i < inputIds.size(); ++i)
		{
			if (inputIds[i] == id)
			{
				return i;
			}
		}

		return std::optional<std::size_t>{};
	}

	std::optional<std::size_t> InputSystem::DeviceIndex(const IInputDevice& device) const noexcept
	{
		for (std::size_t i = 0; i < devices.size(); ++i)
		{
			if (static_cast<IInputDevice*>(devices[i].get()) == &device)
			{
				return i;
			}
		}

		return std::optional<std::size_t>{};
	}
}

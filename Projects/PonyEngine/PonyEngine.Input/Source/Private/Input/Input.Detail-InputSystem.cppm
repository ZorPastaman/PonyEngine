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

import :InputReceiver;

export namespace PonyEngine::Input
{
	/// @brief Input system.
	class InputSystem final : public Core::TickableSystem, public IInputSystem
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
		virtual std::shared_ptr<IInputReceiver> CreateReceiver(std::string_view id) override;

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

		/// @brief Input system context wrapper.
		class InputSystemContextWrapper final : public IInputSystemContext
		{
		public:
			/// @brief Creates a wrapper.
			/// @param inputSystem Input system.
			/// @param deviceIndex Device index.
			[[nodiscard("Pure constructor")]]
			InputSystemContextWrapper(InputSystem* inputSystem, std::size_t deviceIndex) noexcept;
			[[nodiscard("Pure constructor")]]
			InputSystemContextWrapper(const InputSystemContextWrapper& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			InputSystemContextWrapper(InputSystemContextWrapper&& other) noexcept = default;

			~InputSystemContextWrapper() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual std::uint64_t FrameCount() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual PonyDebug::Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual const Core::ISystemManager& SystemManager() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual bool IsRunning() const noexcept override;

			virtual void AddInputEvent(const InputEvent& inputEvent) override;

			InputSystemContextWrapper& operator =(const InputSystemContextWrapper& other) noexcept = default;
			InputSystemContextWrapper& operator =(InputSystemContextWrapper&& other) noexcept = default;

		private:
			InputSystem* inputSystem; ///< Input system.
			std::size_t deviceIndex; ///< Device index.
		};

		/// @brief Gets the current frame count.
		/// @return Frame count.
		[[nodiscard("Pure function")]]
		std::uint64_t FrameCount() const noexcept;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		PonyDebug::Log::ILogger& Logger() noexcept;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		const PonyDebug::Log::ILogger& Logger() const noexcept;

		/// @brief Gets the system manager.
		/// @return System manager.
		[[nodiscard("Pure function")]]
		const Core::ISystemManager& SystemManager() const noexcept;

		/// @brief Is the engine running now?
		/// @return @a True if it's running; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsRunning() const noexcept;

		/// @brief Adds an input event.
		/// @param deviceIndex Device index.
		/// @param inputEvent Input event.
		void AddInputEvent(std::size_t deviceIndex, const InputEvent& inputEvent);

		/// @brief Zeroes deltas.
		void ZeroDeltas() noexcept;
		/// @brief Cleans out of dead receivers.
		void Clean() noexcept;
		/// @brief Ticks devices.
		void TickDevices();
		/// @brief Processes the current input queue.
		void ProcessInput();

		/// @brief Processes the @p inputEvent.
		/// @param inputEntry Input entry to process. Device index - input event.
		void ProcessInputEvent(const std::pair<std::size_t, InputEvent>& inputEntry);
		/// @brief Updates a state and a delta.
		/// @param inputEntry Input entry. Device index - input event.
		void UpdateStateAndDelta(const std::pair<std::size_t, InputEvent>& inputEntry);
		/// @brief Updates a state.
		/// @param deviceIndex Input source.
		/// @param inputCode Input code.
		/// @param value Input value.
		void UpdateState(std::size_t deviceIndex, InputCode inputCode, float value);
		/// @brief Updates a delta.
		/// @param inputCode Input code.
		/// @param value Input value.
		void UpdateDelta(InputCode inputCode, float value);
		/// @brief Updates recievers.
		/// @param inputEntry Input entry. Device index - input event.
		void UpdateReceivers(const std::pair<std::size_t, InputEvent>& inputEntry);
		/// @brief Execute bound actions.
		/// @param idIndex Binding ID index.
		/// @param value Input value.
		void ExecuteReceivers(std::size_t idIndex, float value) const;

		/// @brief Gets an input ID index.
		/// @param id Input ID.
		/// @return Input ID index. If there's no such an ID, it's nullopt.
		[[nodiscard("Pure function")]]
		std::optional<std::size_t> InputIdIndex(std::string_view id) const noexcept;

		std::vector<std::shared_ptr<Device>> devices; ///< Input devices.
		std::vector<InputSystemContextWrapper> contextWrappers; ///< Context wrappers for devices.

		std::vector<std::string> inputIds; ///< Input ids.
		std::vector<InputMappingEntry> inputMapping; ///< Input mapping.

		std::unordered_map<std::size_t, std::vector<std::size_t>> idToInputMapping; ///< Input ID index to input mapping entries map.
		std::unordered_map<InputCode, std::vector<std::size_t>> codeToInputMapping; ///< Input code to input mapping entries map.

		std::vector<std::pair<std::size_t, InputEvent>> inputQueue; ///< Input queue.
		std::unordered_map<std::size_t, std::vector<std::shared_ptr<InputReceiver>>> inputReceivers; ///< Input ID index to input receivers map.

		std::unordered_map<InputCode, std::vector<float>> inputStates; ///< Input states. Input code to input states. Inputs states are synced with corresponding devices via index.
		std::unordered_map<InputCode, float> inputDeltas; ///< Input deltas.
	};
}

namespace PonyEngine::Input
{
	InputSystem::InputSystemContextWrapper::InputSystemContextWrapper(InputSystem* const inputSystem, const std::size_t deviceIndex) noexcept :
		inputSystem{inputSystem},
		deviceIndex{deviceIndex}
	{
	}

	std::uint64_t InputSystem::InputSystemContextWrapper::FrameCount() const noexcept
	{
		return inputSystem->FrameCount();
	}

	PonyDebug::Log::ILogger& InputSystem::InputSystemContextWrapper::Logger() noexcept
	{
		return inputSystem->Logger();
	}

	const PonyDebug::Log::ILogger& InputSystem::InputSystemContextWrapper::Logger() const noexcept
	{
		return inputSystem->Logger();
	}

	const Core::ISystemManager& InputSystem::InputSystemContextWrapper::SystemManager() const noexcept
	{
		return inputSystem->SystemManager();
	}

	bool InputSystem::InputSystemContextWrapper::IsRunning() const noexcept
	{
		return inputSystem->IsRunning();
	}

	void InputSystem::InputSystemContextWrapper::AddInputEvent(const InputEvent& inputEvent)
	{
		inputSystem->AddInputEvent(deviceIndex, inputEvent);
	}

	InputSystem::InputSystem(Core::IEngineContext& engine, const Core::SystemParams& systemParams, const InputSystemParams& inputParams) noexcept :
		TickableSystem(engine, systemParams)
	{
		devices.reserve(inputParams.inputDeviceFactories.size());
		contextWrappers.reserve(inputParams.inputDeviceFactories.size());
		inputIds.reserve(inputParams.inputBindings.size());
		inputMapping.reserve(std::reduce(inputParams.inputBindings.begin(), inputParams.inputBindings.end(), std::size_t{0}, [](const std::size_t value, const std::pair<std::string, std::vector<InputBindingValue>>& entry) { return value + entry.second.size(); }));
		idToInputMapping.reserve(inputParams.inputBindings.size());
		for (std::size_t index = 0; const auto& binding : std::ranges::views::values(inputParams.inputBindings))
		{
			idToInputMapping[index].reserve(binding.size());
			++index;
		}
		std::size_t uniqueInputCodeCount = 0;
		for (const auto& binding : std::ranges::views::values(inputParams.inputBindings))
		{
			for (const auto& [inputCode, multiplier] : binding)
			{
				bool uniqueCode = true;

				for (const auto& bindingSecond : std::ranges::views::values(inputParams.inputBindings))
				{
					for (const auto& [inputCodeSecond, multiplierSecond] : bindingSecond)
					{
						if (&inputCode == &inputCodeSecond)
						{
							break;
						}

						if (inputCode == inputCodeSecond)
						{
							uniqueCode = false;
							break;
						}
					}
				}

				uniqueInputCodeCount += uniqueCode;
			}
		}
		codeToInputMapping.reserve(uniqueInputCodeCount);
		for (const auto& binding : std::ranges::views::values(inputParams.inputBindings))
		{
			for (const auto& [inputCode, multiplier] : binding)
			{
				std::size_t inputCodeCount = 0;
				for (const auto& bindingSecond : std::ranges::views::values(inputParams.inputBindings))
				{
					for (const auto& [inputCodeSecond, multiplierSecond] : bindingSecond)
					{
						inputCodeCount += inputCode == inputCodeSecond;
					}
				}

				codeToInputMapping[inputCode].reserve(inputCodeCount);
			}
		}
		inputQueue.reserve(128);
		inputStates.reserve(uniqueInputCodeCount);
		for (const auto& binding : std::ranges::views::values(inputParams.inputBindings))
		{
			for (const auto& [inputCode, multiplier] : binding)
			{
				inputStates[inputCode].resize(inputParams.inputDeviceFactories.size());
			}
		}
		inputDeltas.reserve(uniqueInputCodeCount);
		for (const auto& binding : std::ranges::views::values(inputParams.inputBindings))
		{
			for (const auto& [inputCode, multiplier] : binding)
			{
				inputDeltas[inputCode] = 0.f;
			}
		}

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create devices.");
		for (const std::shared_ptr<IDeviceFactory>& deviceFactory : inputParams.inputDeviceFactories)
		{
			assert(deviceFactory && "The device factory is nullptr.");
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Create '{}' device with '{}' factory.", deviceFactory->DeviceType().name(), typeid(*deviceFactory).name());
			contextWrappers.push_back(InputSystemContextWrapper(this, devices.size()));
			DeviceData device = deviceFactory->CreateDevice(contextWrappers.back(), DeviceParams{});
			assert(device.inputDevice && "The device is nullptr");
			devices.push_back(device.inputDevice);
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Device created.");
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Devices created.");

		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Set input bindings.");
		for (const auto& [id, binding] : inputParams.inputBindings)
		{
			inputIds.push_back(id);
			const std::size_t idIndex = inputIds.size() - 1;
			std::vector<std::size_t>& idToInput = idToInputMapping[idIndex];
			for (const auto& [inputCode, multiplier] : binding)
			{
				PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Set input binding. ID: '{}'; Input code: '{}'; Multiplier: '{}'.", id, ToString(inputCode), multiplier);
				inputMapping.push_back(InputMappingEntry{.idIndex = idIndex, .inputCode = inputCode, .multiplier = multiplier});
				const std::size_t entryIndex = inputMapping.size() - 1;
				idToInput.push_back(entryIndex);
				codeToInputMapping[inputCode].push_back(entryIndex);
			}
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Input bindings set.");
	}

	InputSystem::~InputSystem() noexcept
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy devices.");
		for (auto it = devices.rbegin(); it != devices.rend(); ++it)
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Destroy '{}' device.", typeid(**it).name());
			it->reset();
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Device destroyed.");
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Info, "Devices destroyed.");
	}

	void InputSystem::Begin()
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Begin devices.");
		for (const std::shared_ptr<Device>& device : devices)
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Begin '{}' device.", typeid(*device).name());
			device->Begin();
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Device begun.");
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Devices begun.");
	}

	void InputSystem::End() noexcept
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "End devices.");
		for (auto it = devices.crbegin(); it != devices.crend(); ++it)
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "End '{}' device.", typeid(**it).name());
			try
			{
				(*it)->End();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(Logger(), e, "On ending '{}' device.", typeid(**it).name());
			}
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Device ended.");
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Devices ended.");
	}

	void InputSystem::Tick()
	{
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Zero deltas.");
		ZeroDeltas();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Clean.");
		Clean();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Tick devices.");
		TickDevices();
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Verbose, "Process input.");
		ProcessInput();
	}

	std::shared_ptr<IInputReceiver> InputSystem::CreateReceiver(const std::string_view id)
	{
		auto receiver = std::make_shared<InputReceiver>();
		if (const std::optional<std::size_t> inputIdIndex = InputIdIndex(id)) [[likely]]
		{
			inputReceivers[inputIdIndex.value()].push_back(receiver);
		}
		else [[unlikely]]
		{
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Warning, "Input receiver created for a not bound input ID: '{}'.", id);
		}
		PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Input receiver created with '{}' ID at '0x{:X}'.", id, reinterpret_cast<std::uintptr_t>(receiver.get()));

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
			PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "No input is bound with '{}' ID.", id);
		}

		return value;
	}

	std::uint64_t InputSystem::FrameCount() const noexcept
	{
		return Engine().FrameCount();
	}

	PonyDebug::Log::ILogger& InputSystem::Logger() noexcept
	{
		return Engine().Logger();
	}

	const PonyDebug::Log::ILogger& InputSystem::Logger() const noexcept
	{
		return Engine().Logger();
	}

	const Core::ISystemManager& InputSystem::SystemManager() const noexcept
	{
		return Engine().SystemManager();
	}

	bool InputSystem::IsRunning() const noexcept
	{
		return Engine().IsRunning();
	}

	void InputSystem::AddInputEvent(const std::size_t deviceIndex, const InputEvent& inputEvent)
	{
		if (!codeToInputMapping.contains(inputEvent.inputCode))
		{
			return; // No mapping. So, it can be safely ignored.
		}

		inputQueue.emplace_back(deviceIndex, inputEvent);
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
				if (receivers[i].use_count() <= 1L)
				{
					PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Destroy input receiver at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(receivers[i].get()));
					receivers.erase(receivers.cbegin() + i);
					PONY_LOG(Logger(), PonyDebug::Log::LogType::Debug, "Input receiver destroyed.");
				}
			}
		}
	}

	void InputSystem::TickDevices()
	{
		for (const std::shared_ptr<Device>& device : devices)
		{
			device->Tick();
		}
	}

	void InputSystem::ProcessInput()
	{
		try
		{
			for (const std::pair<std::size_t, InputEvent>& inputEntry : inputQueue)
			{
				ProcessInputEvent(inputEntry);
			}
		}
		catch (...)
		{
			inputQueue.clear();

			throw;
		}

		inputQueue.clear();
	}

	void InputSystem::ProcessInputEvent(const std::pair<std::size_t, InputEvent>& inputEntry)
	{
		UpdateStateAndDelta(inputEntry);
		UpdateReceivers(inputEntry);
	}

	void InputSystem::UpdateStateAndDelta(const std::pair<std::size_t, InputEvent>& inputEntry)
	{
		switch (inputEntry.second.inputType)
		{
		case InputType::State:
			UpdateState(inputEntry.first, inputEntry.second.inputCode, inputEntry.second.inputValue);
			break;
		case InputType::Delta:
			UpdateDelta(inputEntry.second.inputCode, inputEntry.second.inputValue);
			break;
		default: [[unlikely]]
			assert(false && "The incorrect input type has been received.");
			break;
		}
	}

	void InputSystem::UpdateState(const std::size_t deviceIndex, const InputCode inputCode, const float value)
	{
		const auto statesPosition = inputStates.find(inputCode);
		assert(statesPosition != inputStates.cend() && "Tried to update a state by an invalid input code.");

		statesPosition->second[deviceIndex] = value;
	}

	void InputSystem::UpdateDelta(const InputCode inputCode, const  float value)
	{
		const auto inputDeltaPosition = inputDeltas.find(inputCode);
		assert(inputDeltaPosition != inputDeltas.cend() && "Tried to update a delta by an invalid input code.");

		inputDeltaPosition->second += value;
	}

	void InputSystem::UpdateReceivers(const std::pair<std::size_t, InputEvent>& inputEntry)
	{
		const auto& mappingPosition = codeToInputMapping.find(inputEntry.second.inputCode);
		assert(mappingPosition != codeToInputMapping.cend() && "The input code is incorrect.");
		for (const std::size_t inputMappingIndex : mappingPosition->second)
		{
			const InputMappingEntry& inputMappingEntry = inputMapping[inputMappingIndex];
			const float value = inputEntry.second.inputValue * inputMappingEntry.multiplier;
			ExecuteReceivers(inputMappingEntry.idIndex, value);
		}
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
}

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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Input.Impl:InputService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Input.Ext;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.Text;

export namespace PonyEngine::Input
{
	/// @brief Input service.
	class InputService final : public Application::ITickableService, private IInputContext, private IInputModuleContext, private IInputService
	{
	public:
		/// @brief Creates an input service.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit InputService(Application::IApplicationContext& application) noexcept;
		InputService(const InputService&) = delete;
		InputService(InputService&&) = delete;

		~InputService() noexcept;

		virtual void Begin() override;
		virtual void End() noexcept override;
		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Must be used to unregister")]]
		virtual DeviceHandle RegisterDevice(const DeviceData& data) override;
		virtual void UnregisterDevice(DeviceHandle deviceHandle) override;

		virtual void AddInput(DeviceHandle deviceHandle, const RawInputEvent& input) override;
		virtual void Connect(DeviceHandle deviceHandle, bool isConnected) override;

		[[nodiscard("Must be used to remove")]]
		virtual InputProviderHandle AddProvider(const std::function<std::shared_ptr<IInputProvider>(IInputContext&)>& factory) override;
		virtual void RemoveProvider(InputProviderHandle handle) override;

		[[nodiscard("Pure function")]]
		virtual std::size_t AxisCount(ActionId actionId) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual void Value(ActionId actionId, std::span<float> values) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual void Value(DeviceHandle deviceHandle, ActionId actionId, std::span<float> values) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual float Value(const Axis& axis) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual float Value(DeviceHandle deviceHandle, const Axis& axis) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual DeviceHandle LastInputDevice() const noexcept override;

		virtual ActionBindingHandle Bind(ActionId actionId, std::span<const AxisBinding> axisBindings) override;
		virtual void Unbind(ActionBindingHandle handle) override;

		[[nodiscard("Pure function")]]
		virtual std::span<const DeviceHandle> Devices() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(DeviceHandle deviceHandle) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::span<const std::type_index> Layouts(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]]
		virtual std::span<const std::type_index> Features(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]]
		virtual void* Feature(DeviceHandle deviceHandle, std::type_index featureType) override;
		[[nodiscard("Pure function")]]
		virtual const void* Feature(DeviceHandle deviceHandle, std::type_index featureType) const override;
		[[nodiscard("Pure function")]]
		virtual bool IsConnected(DeviceHandle deviceHandle) const override;

		[[nodiscard("Wierd call")]]
		virtual ActionId HashActionId(std::string_view actionId) override;
		[[nodiscard("Pure function")]]
		virtual std::string_view UnhashActionId(ActionId actionId) const noexcept override;

		virtual void AddObserver(IDeviceObserver& observer) override;
		virtual void RemoveObserver(IDeviceObserver& observer) noexcept override;
		virtual void AddObserver(DeviceHandle deviceHandle, IDeviceObserver& observer) override;
		virtual void RemoveObserver(DeviceHandle deviceHandle, IDeviceObserver& observer) noexcept override;
		virtual void AddObserver(IInputObserver& observer) override;
		virtual void RemoveObserver(IInputObserver& observer) noexcept override;
		virtual void AddObserver(DeviceHandle deviceHandle, IInputObserver& observer) override;
		virtual void RemoveObserver(DeviceHandle deviceHandle, IInputObserver& observer) noexcept override;
		virtual void AddObserver(IRawInputObserver& observer) override;
		virtual void RemoveObserver(IRawInputObserver& observer) noexcept override;
		virtual void AddObserver(DeviceHandle deviceHandle, IRawInputObserver& observer) override;
		virtual void RemoveObserver(DeviceHandle deviceHandle, IRawInputObserver& observer) noexcept override;

		/// @brief Gets the public input module context.
		/// @return Input module context.
		[[nodiscard("Pure function")]]
		IInputModuleContext& PublicInputContext() noexcept;
		/// @brief Gets the public input module context.
		/// @return Input module context.
		[[nodiscard("Pure function")]]
		const IInputModuleContext& PublicInputContext() const noexcept;
		/// @brief Gets the public input service interface.
		/// @return Input service interface.
		[[nodiscard("Pure function")]]
		IInputService& PublicInputService() noexcept;
		/// @brief Gets the public input service interface.
		/// @return Input service interface.
		[[nodiscard("Pure function")]]
		const IInputService& PublicInputService() const noexcept;

		InputService& operator =(const InputService&) = delete;
		InputService& operator =(InputService&&) = delete;

	private:
		/// @brief Device info.
		struct DeviceInfo final
		{
			std::shared_ptr<IDevice> device; ///< Device.
			std::vector<std::type_index> deviceLayouts; ///< Device layouts.
			std::vector<std::type_index> deviceFeatureTypes; ///< Device feature types.
			std::vector<void*> deviceFeatures; ///< Device features. They are synced with the @p deviceFeatureTypes by index.
			bool deviceConnection; ///< Is the device connected?
		};

		/// @brief Raw input.
		struct RawInput final
		{
			std::size_t valueIndex; ///< Value index.
			std::size_t valueCount; ///< Value count.
			DeviceHandle deviceHandle; ///< Device handle.
			InputEventType eventType; ///< Event type.

			std::chrono::time_point<std::chrono::steady_clock> timePoint; ///< Time point when the event was created.
			std::optional<Math::Vector2<std::int32_t>> cursorPosition; ///< Cursor position in screen coordinates; std::nullopt if not applicable.
		};

		/// @brief Input value.
		struct InputValue final
		{
			float state = 0.f;
			float delta = 0.f;
		};

		/// @brief Action binding.
		struct ActionBinding final
		{
			std::vector<std::shared_ptr<IModifier>> modifiers; ///< Input value modifiers.
			Axis axis; ///< Axis.
			std::uint8_t actionAxisIndex = 0u; ///< Action axis index.
		};

		/// @brief Begins the providers.
		/// @param count How many providers are begun.
		void Begin(std::size_t& count);
		/// @brief Ends the providers.
		/// @param count How many providers to end.
		void End(std::size_t count) noexcept;

		/// @brief Clears data from the previous tick.
		void ClearOldData() noexcept;
		/// @brief Ticks the providers.
		void TickProviders();
		/// @brief Sorts the raw input.
		void SortInput() noexcept;
		/// @brief Reads the raw input and updates the data.
		void UpdateInput();

		/// @brief Adds action values.
		/// @param actionValues Action values source.
		/// @param actionId Action ID.
		/// @param values Target values.
		static void Value(const std::unordered_map<ActionId, std::vector<InputValue>>& actionValues, ActionId actionId, std::span<float> values) noexcept;
		/// @brief Gets an axis value.
		/// @param values Axes source.
		/// @param axis Axis.
		/// @return Axis value.
		[[nodiscard("Pure function")]]
		static float Value(const std::unordered_map<Axis, InputValue>& values, const Axis& axis) noexcept;

		/// @brief Checks if the @p bindings have at least one axis from the @p axes.
		/// @param bindings Bindings.
		/// @param axes Axes.
		/// @return @a True if they have; @a false otherwise.
		[[nodiscard("Pure function")]]
		static bool HasAxis(std::span<const ActionBinding> bindings, std::span<const Axis> axes) noexcept;

		/// @brief Calls on device added observers.
		/// @param observers Observers to call.
		/// @param deviceHandle Added device handle.
		void ObserveDeviceAdded(std::span<IDeviceObserver*> observers, DeviceHandle deviceHandle) noexcept;
		/// @brief Calls on device removed observers.
		/// @param observers Observers to call.
		/// @param deviceHandle Removed device handle.
		void ObserveDeviceRemoved(std::span<IDeviceObserver*> observers, DeviceHandle deviceHandle) noexcept;
		/// @brief Calls on connection changed observers.
		/// @param observers Observers to call.
		/// @param deviceHandle Device which connection is changed.
		/// @param isConnected Is it changed to connected?
		void ObserveDeviceConnectionChanged(std::span<IDeviceObserver*> observers, DeviceHandle deviceHandle, bool isConnected) noexcept;
		/// @brief Calls action input observers.
		/// @param observers Observers to call.
		/// @param deviceHandle Device handle.
		/// @param inputEvent Action input event.
		void ObserveInput(std::span<IInputObserver*> observers, DeviceHandle deviceHandle, const InputEvent& inputEvent) noexcept;
		/// @brief Calls raw input observers.
		/// @param observers Observers to call.
		/// @param deviceHandle Device handle.
		/// @param inputEvent Raw input event.
		void ObserveRawInput(std::span<IRawInputObserver*> observers, DeviceHandle deviceHandle, const RawInputEvent& inputEvent) noexcept;

		Application::IApplicationContext* application; ///< Application context.

		// These vectors are synced by index.
		std::vector<InputProviderHandle> providerHandles; ///< Provider handles.
		std::vector<std::shared_ptr<IInputProvider>> providers; ///< Providers.

		// These vectors are synced by index.
		std::vector<DeviceHandle> devices; ///< Device handles.
		std::vector<DeviceInfo> deviceInfos; ///< Device infos.
		std::vector<std::unordered_map<Axis, InputValue>> deviceAxisValues; ///< Device axis values.
		std::vector<std::unordered_map<ActionId, std::vector<InputValue>>> deviceActionValues; ///< Device action values.

		// These vectors are synced by index.
		std::vector<ActionBindingHandle> actionBindingHandles; ///< Action binding handles.
		std::vector<ActionId> actionIds; ///< Action IDs.
		std::vector<std::vector<ActionBinding>> actionBindings; ///< Action bindings.

		std::unordered_map<ActionId, std::string> actionIdHashCache; ///< Action ID to its original string cache.

		std::vector<RawInput> rawInputs; ///< Raw input events.
		std::vector<Axis> rawInputAxes; ///< Raw input axes. They are referenced by index from a @p RawInput.
		std::vector<float> rawInputValues; ///< Raw input values. They are referenced by index from a @p RawInput.

		std::vector<float> actionValuesTemp; ///< Temp action values.

		std::vector<IDeviceObserver*> globalDeviceObservers; ///< Global device observers.
		std::vector<IInputObserver*> globalInputObservers; ///< Global action input observers.
		std::vector<IRawInputObserver*> globalRawInputObservers; ///< Global raw input observers.

		std::unordered_map<DeviceHandle, std::vector<IDeviceObserver*>> deviceObservers; ///< Device observers.
		std::unordered_map<DeviceHandle, std::vector<IInputObserver*>> inputObservers; ///< Action input observers.
		std::unordered_map<DeviceHandle, std::vector<IRawInputObserver*>> rawInputObservers; ///< Raw input observers.

		DeviceHandle lastInputDevice; ///< Last input device. Can be invalid if there was no input from any device last tick.

		InputProviderHandle nextProviderHandle; ///< Next provider handle.
		DeviceHandle nextDeviceHandle; ///< Next device handle.
		ActionBindingHandle nextActionHandle; ///< Next action handle.
	};

	InputService::InputService(Application::IApplicationContext& application) noexcept :
		application{&application},
		nextProviderHandle{.id = 1u},
		nextDeviceHandle{.id = 1u},
		nextActionHandle{.id = 1u}
	{
	}

	InputService::~InputService() noexcept
	{
		if (actionBindingHandles.size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Actions weren't removed:");
			for (const ActionBindingHandle action : actionBindingHandles)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Action id: '0x{:X}'.", action.id);
			}
		}

		if (deviceInfos.size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Devices weren't removed:");
			for (const DeviceInfo& info : deviceInfos)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Device: '{}'.", typeid(*info.device).name());
			}
		}

		if (providers.size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Providers weren't removed:");
			for (const std::shared_ptr<IInputProvider>& provider : providers)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Provider: '{}'.", typeid(*provider).name());
			}
		}
	}

	void InputService::Begin()
	{
		std::size_t count = 0uz;
		try
		{
			Begin(count);
		}
		catch (...)
		{
			End(count);
			throw;
		}
	}

	void InputService::End() noexcept
	{
		End(providers.size());
	}

	void InputService::Tick()
	{
		ClearOldData();
		TickProviders();
		SortInput();
		UpdateInput();
	}

	Application::IApplicationContext& InputService::Application() noexcept
	{
		return *application;
	}

	const Application::IApplicationContext& InputService::Application() const noexcept
	{
		return *application;
	}

	Log::ILogger& InputService::Logger() noexcept
	{
		return application->Logger();
	}

	const Log::ILogger& InputService::Logger() const noexcept
	{
		return application->Logger();
	}

	DeviceHandle InputService::RegisterDevice(const DeviceData& data)
	{
		if (!nextDeviceHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more device handles available.");
		}

		if (!data.device) [[unlikely]]
		{
			throw std::invalid_argument("Device is nullptr.");
		}
		for (const DeviceInfo& info : deviceInfos)
		{
			if (info.device == data.device) [[unlikely]]
			{
				throw std::invalid_argument("Device is already registered.");
			}
		}

		if (data.layouts.size() == 0uz) [[unlikely]]
		{
			throw std::invalid_argument("Device has no layout.");
		}
		for (std::size_t i = 1uz; i < data.layouts.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				if (data.layouts[i] == data.layouts[j]) [[unlikely]]
				{
					throw std::invalid_argument(Text::FormatSafe("Layouts have duplicates at indices '{}' and '{}'.", i, j));
				}
			}
		}

		const DeviceHandle currentDeviceHandle = nextDeviceHandle;
		devices.push_back(currentDeviceHandle);
		try
		{
			auto deviceInfo = DeviceInfo{.device = data.device, .deviceConnection = data.isConnected};
			deviceInfo.deviceLayouts.assign(data.layouts.cbegin(), data.layouts.cend());
			for (const auto [featureType, feature] : data.features)
			{
				if (!feature) [[unlikely]]
				{
					throw std::invalid_argument(Text::FormatSafe("Feature of type '{}' is nullptr.", featureType.name()));
				}

				deviceInfo.deviceFeatureTypes.push_back(featureType);
				deviceInfo.deviceFeatures.push_back(feature);
			}
			deviceInfos.push_back(std::move(deviceInfo));

			try
			{
				deviceAxisValues.push_back(std::unordered_map<Axis, InputValue>());
				try
				{
					deviceActionValues.push_back(std::unordered_map<ActionId, std::vector<InputValue>>());
				}
				catch (...)
				{
					deviceAxisValues.pop_back();
					throw;
				}
			}
			catch (...)
			{
				deviceInfos.pop_back();
				throw;
			}
		}
		catch (...)
		{
			devices.pop_back();
			throw;
		}
		++nextDeviceHandle.id;

		PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' device added. Handle: '0x{:X}'.", typeid(*data.device).name(), currentDeviceHandle.id);

		ObserveDeviceAdded(globalDeviceObservers, currentDeviceHandle);

		return currentDeviceHandle;
	}

	void InputService::UnregisterDevice(const DeviceHandle deviceHandle)
	{
		if (const auto position = std::ranges::find(devices, deviceHandle); position != devices.cend()) [[likely]]
		{
			const std::size_t index = position - devices.cbegin();
			const char* const deviceName = typeid(*deviceInfos[index].device).name();

			if (const auto observePosition = deviceObservers.find(deviceHandle); observePosition != deviceObservers.cend())
			{
				ObserveDeviceRemoved(observePosition->second, deviceHandle);
			}
			ObserveDeviceRemoved(globalDeviceObservers, deviceHandle);

			deviceActionValues.erase(deviceActionValues.cbegin() + index);
			deviceAxisValues.erase(deviceAxisValues.cbegin() + index);
			deviceInfos.erase(deviceInfos.cbegin() + index);
			devices.erase(position);

			for (std::size_t i = rawInputs.size(); i-- > 0; )
			{
				if (rawInputs[i].deviceHandle == deviceHandle)
				{
					rawInputs.erase(rawInputs.cbegin() + i);
				}
			}

			deviceObservers.erase(deviceHandle);
			inputObservers.erase(deviceHandle);
			rawInputObservers.erase(deviceHandle);

			PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' device removed. Handle: '0x{:X}'.", deviceName, deviceHandle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	void InputService::AddInput(const DeviceHandle deviceHandle, const RawInputEvent& input)
	{
		static constexpr auto validateLayout = [](const Axis& axis, const DeviceInfo& deviceInfo) noexcept
		{
			for (const std::type_index layout : deviceInfo.deviceLayouts)
			{
				if (layout == axis.Layout())
				{
					return true;
				}
			}

			return false;
		};

		if (input.axes.size() != input.values.size()) [[unlikely]]
		{
			throw std::invalid_argument("Axis and values aren't the same size.");
		}
		if (input.axes.size() == 0uz) [[unlikely]]
		{
			throw std::invalid_argument("Empty input.");
		}
		for (std::size_t i = 1uz; i < input.axes.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				if (input.axes[i] == input.axes[j]) [[unlikely]]
				{
					throw std::invalid_argument(Text::FormatSafe("Same axes at indices '{}' and '{}'.", i, j));
				}
			}
		}

		if (const auto position = std::ranges::find(devices, deviceHandle); position != devices.cend()) [[likely]]
		{
			const std::size_t index = position - devices.cbegin();
			const DeviceInfo& deviceInfo = deviceInfos[index];
			for (const Axis& axis : input.axes)
			{
				if (!validateLayout(axis, deviceInfo)) [[unlikely]]
				{
					throw std::invalid_argument(Text::FormatSafe("Device doesn't support '{}' layout.", axis.Layout().name()));
				}
			}
			const std::size_t valueIndex = rawInputAxes.size();
			for (std::size_t i = 0; i < input.axes.size(); ++i)
			{
				rawInputAxes.push_back(input.axes[i]);
				try
				{
					rawInputValues.push_back(input.values[i]);
				}
				catch (...)
				{
					rawInputAxes.pop_back();
					throw;
				}
			}
			rawInputs.push_back(RawInput
			{
				.valueIndex = valueIndex,
				.valueCount = input.axes.size(),
				.deviceHandle = devices[index],
				.eventType = input.eventType,
				.timePoint = input.timePoint,
				.cursorPosition = input.cursorPosition
			});
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	void InputService::Connect(const DeviceHandle deviceHandle, const bool isConnected)
	{
		if (const auto position = std::ranges::find(devices, deviceHandle); position != devices.cend()) [[likely]]
		{
			const std::size_t index = position - devices.cbegin();
			if (deviceInfos[index].deviceConnection == isConnected) [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Warning, "Device connection was updated to the same value. Handle: '0x{:X}'.", deviceHandle.id);
				return;
			}
			deviceInfos[index].deviceConnection = isConnected;
			PONY_LOG(application->Logger(), Log::LogType::Info, "Device connection changed to '{}'. Handle: '0x{:X}'.", isConnected, deviceHandle.id);

			if (const auto observePosition = deviceObservers.find(deviceHandle); observePosition != deviceObservers.cend())
			{
				ObserveDeviceConnectionChanged(observePosition->second, deviceHandle, isConnected);
			}
			ObserveDeviceConnectionChanged(globalDeviceObservers, deviceHandle, isConnected);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found.");
		}
	}

	InputProviderHandle InputService::AddProvider(const std::function<std::shared_ptr<IInputProvider>(IInputContext&)>& factory)
	{
		if (!nextProviderHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more input provider handles available.");
		}
		if (application->FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Input providers can be added only on start-up.");
		}

		const std::shared_ptr<IInputProvider> provider = factory(*this);
		if (!provider) [[unlikely]]
		{
			throw std::invalid_argument("Input provider is nullptr.");
		}
		if (const auto position = std::ranges::find(providers, provider); position != providers.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Input provider has already been added.");
		}

		const InputProviderHandle currentHandle = nextProviderHandle;
		providerHandles.push_back(currentHandle);
		try
		{
			providers.push_back(provider);
		}
		catch (...)
		{
			providerHandles.pop_back();
			throw;
		}
		++nextProviderHandle.id;

		PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' provider added. Handle: '0x{:X}'.", typeid(*provider).name(), currentHandle.id);

		return currentHandle;
	}

	void InputService::RemoveProvider(const InputProviderHandle handle)
	{
		if (application->FlowState() != Application::FlowState::StartingUp && application->FlowState() != Application::FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Input provider can be removed only on start-up or shut-down.");
		}

		if (const auto position = std::find(providerHandles.crbegin(), providerHandles.crend(), handle); position != providerHandles.crend()) [[likely]]
		{
			const std::size_t index = std::distance(providerHandles.cbegin(), position.base()) - 1uz;
			const char* const providerName = typeid(*providers[index]).name();
			providers.erase(providers.cbegin() + index);
			providerHandles.erase(providerHandles.cbegin() + index);
			PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' provider removed. Handle: '0x{:X}'.", providerName, handle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Input provider not found.");
		}
	}

	std::size_t InputService::AxisCount(const ActionId actionId) const noexcept
	{
		if (const auto position = std::ranges::find(actionIds, actionId); position != actionIds.cend()) [[likely]]
		{
			return actionBindings[position - actionIds.cbegin()].back().actionAxisIndex;
		}

		return 0uz;
	}

	void InputService::Value(const ActionId actionId, const std::span<float> values) const noexcept
	{
		std::ranges::fill(values, 0.f);
		for (const std::unordered_map<ActionId, std::vector<InputValue>>& actionValues : deviceActionValues)
		{
			Value(actionValues, actionId, values);
		}
	}

	void InputService::Value(const DeviceHandle deviceHandle, const ActionId actionId, const std::span<float> values) const noexcept
	{
		std::ranges::fill(values, 0.f);
		if (const auto actionPosition = std::ranges::find(actionIds, actionId); actionPosition != actionIds.cend()) [[likely]]
		{
			if (const auto axisValuesPosition = std::ranges::find(devices, deviceHandle); axisValuesPosition != devices.cend()) [[likely]]
			{
				Value(deviceActionValues[axisValuesPosition - devices.cbegin()], actionId, values);
			}
		}
	}

	float InputService::Value(const Axis& axis) const noexcept
	{
		float answer = 0.f;
		for (const std::unordered_map<Axis, InputValue>& axes : deviceAxisValues)
		{
			answer += Value(axes, axis);
		}

		return answer;
	}

	float InputService::Value(const DeviceHandle deviceHandle, const Axis& axis) const noexcept
	{
		if (const auto position = std::ranges::find(devices, deviceHandle); position != devices.cend()) [[likely]]
		{
			return Value(deviceAxisValues[position - devices.cbegin()], axis);
		}

		return 0.f;
	}

	DeviceHandle InputService::LastInputDevice() const noexcept
	{
		return lastInputDevice;
	}

	ActionBindingHandle InputService::Bind(const ActionId actionId, const std::span<const AxisBinding> axisBindings)
	{
		if (axisBindings.size() == 0uz) [[unlikely]]
		{
			throw std::invalid_argument("Axis bindings size is 0.");
		}
		if (std::ranges::find(actionIds, actionId) != actionIds.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Action ID is already bound.");
		}
		for (const AxisBinding& binding : axisBindings)
		{
			for (const std::shared_ptr<IModifier>& modifier : binding.modifiers)
			{
				if (!modifier) [[unlikely]]
				{
					throw std::invalid_argument("Modifier is nullptr.");
				}
			}
		}

		const ActionBindingHandle currentHandle = nextActionHandle;
		actionBindingHandles.push_back(currentHandle);
		try
		{
			actionIds.push_back(actionId);
			try
			{
				std::vector<ActionBinding> bindings;
				bindings.reserve(axisBindings.size());
				for (const AxisBinding& binding : axisBindings)
				{
					bindings.push_back(ActionBinding
					{
						.modifiers = std::vector<std::shared_ptr<IModifier>>(binding.modifiers.cbegin(), binding.modifiers.cend()),
						.axis = binding.axis,
						.actionAxisIndex = binding.actionAxisIndex
					});
				}
				std::ranges::sort(bindings, [](const ActionBinding& lhs, const ActionBinding& rhs) { return lhs.actionAxisIndex < rhs.actionAxisIndex; });
				actionBindings.push_back(std::move(bindings));
			}
			catch (...)
			{
				actionIds.pop_back();
				throw;
			}
		}
		catch (...)
		{
			actionBindingHandles.pop_back();
			throw;
		}

		PONY_LOG(application->Logger(), Log::LogType::Debug, "'{}' action id bound. Handle: '0x{:X}'.", actionId.hash, currentHandle.id);

		return currentHandle;
	}

	void InputService::Unbind(const ActionBindingHandle handle)
	{
		if (const auto position = std::ranges::find(actionBindingHandles, handle); position != actionBindingHandles.cend()) [[likely]]
		{
			const std::size_t index = position - actionBindingHandles.cbegin();
			const ActionId actionId = actionIds[index];

			for (std::unordered_map<ActionId, std::vector<InputValue>>& actionValues : deviceActionValues)
			{
				actionValues.erase(actionId);
			}

			actionBindings.erase(actionBindings.cbegin() + index);
			actionIds.erase(actionIds.cbegin() + index);
			actionBindingHandles.erase(position);

			PONY_LOG(application->Logger(), Log::LogType::Debug, "'{}' action id unbound. Handle: '0x{:X}'.", actionId.hash, handle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	std::span<const DeviceHandle> InputService::Devices() const noexcept
	{
		return devices;
	}

	bool InputService::IsValid(const DeviceHandle deviceHandle) const noexcept
	{
		return std::ranges::find(devices, deviceHandle) != devices.cend();
	}

	std::span<const std::type_index> InputService::Layouts(const DeviceHandle deviceHandle) const
	{
		if (const auto position = std::ranges::find(devices, deviceHandle); position != devices.cend()) [[likely]]
		{
			return deviceInfos[position - devices.cbegin()].deviceLayouts;
		}

		throw std::invalid_argument("Device not found.");
	}

	std::span<const std::type_index> InputService::Features(const DeviceHandle deviceHandle) const
	{
		if (const auto position = std::ranges::find(devices, deviceHandle); position != devices.cend()) [[likely]]
		{
			return deviceInfos[position - devices.cbegin()].deviceFeatureTypes;
		}

		throw std::invalid_argument("Device not found.");
	}

	void* InputService::Feature(const DeviceHandle deviceHandle, const std::type_index featureType)
	{
		return const_cast<void*>(const_cast<const InputService*>(this)->Feature(deviceHandle, featureType));
	}

	const void* InputService::Feature(const DeviceHandle deviceHandle, const std::type_index featureType) const
	{
		if (const auto position = std::ranges::find(devices, deviceHandle); position != devices.cend()) [[likely]]
		{
			const DeviceInfo& info = deviceInfos[position - devices.cbegin()];

			for (std::size_t i = 0uz; i < info.deviceFeatureTypes.size(); ++i)
			{
				if (info.deviceFeatureTypes[i] == featureType)
				{
					return info.deviceFeatures[i];
				}
			}

			return nullptr;
		}

		throw std::invalid_argument("Device not found.");
	}

	bool InputService::IsConnected(const DeviceHandle deviceHandle) const
	{
		if (const auto position = std::ranges::find(devices, deviceHandle); position != devices.cend()) [[likely]]
		{
			return deviceInfos[position - devices.cbegin()].deviceConnection;
		}

		throw std::invalid_argument("Device not found.");
	}

	ActionId InputService::HashActionId(const std::string_view actionId)
	{
		const auto hash = ActionId{.hash = Hash::FNV1a64(actionId)};
		if (const auto position = actionIdHashCache.find(hash); position != actionIdHashCache.cend()) [[unlikely]]
		{
			if (position->second != actionId) [[unlikely]]
			{
				throw std::invalid_argument("Hash collision.");
			}

			return hash;
		}

		actionIdHashCache[hash] = actionId;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "New action ID hashed. Action ID: '{}'; Hash: '0x{:X}'.", actionId, hash.hash);

		return hash;
	}

	std::string_view InputService::UnhashActionId(const ActionId actionId) const noexcept
	{
		if (const auto position = actionIdHashCache.find(actionId); position != actionIdHashCache.cend()) [[unlikely]]
		{
			return position->second;
		}

		return std::string_view();
	}

	void InputService::AddObserver(IDeviceObserver& observer)
	{
		globalDeviceObservers.push_back(&observer);
	}

	void InputService::RemoveObserver(IDeviceObserver& observer) noexcept
	{
		if (const auto position = std::ranges::find(globalDeviceObservers, &observer); position != globalDeviceObservers.cend()) [[likely]]
		{
			globalDeviceObservers.erase(position);
		}
	}

	void InputService::AddObserver(const DeviceHandle deviceHandle, IDeviceObserver& observer)
	{
		if (std::ranges::find(devices, deviceHandle) == devices.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Device not found.");
		}

		std::vector<IDeviceObserver*>& observers = deviceObservers[deviceHandle];
		observers.push_back(&observer);
	}

	void InputService::RemoveObserver(const DeviceHandle deviceHandle, IDeviceObserver& observer) noexcept
	{
		if (const auto mapPosition = deviceObservers.find(deviceHandle); mapPosition != deviceObservers.cend()) [[likely]]
		{
			if (const auto position = std::ranges::find(mapPosition->second, &observer); position != mapPosition->second.cend()) [[likely]]
			{
				mapPosition->second.erase(position);
			}
		}
	}

	void InputService::AddObserver(IInputObserver& observer)
	{
		globalInputObservers.push_back(&observer);
	}

	void InputService::RemoveObserver(IInputObserver& observer) noexcept
	{
		if (const auto position = std::ranges::find(globalInputObservers, &observer); position != globalInputObservers.cend()) [[likely]]
		{
			globalInputObservers.erase(position);
		}
	}

	void InputService::AddObserver(const DeviceHandle deviceHandle, IInputObserver& observer)
	{
		if (std::ranges::find(devices, deviceHandle) == devices.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Device not found.");
		}

		std::vector<IInputObserver*>& observers = inputObservers[deviceHandle];
		observers.push_back(&observer);
	}

	void InputService::RemoveObserver(const DeviceHandle deviceHandle, IInputObserver& observer) noexcept
	{
		if (const auto mapPosition = inputObservers.find(deviceHandle); mapPosition != inputObservers.cend()) [[likely]]
		{
			if (const auto position = std::ranges::find(mapPosition->second, &observer); position != mapPosition->second.cend()) [[likely]]
			{
				mapPosition->second.erase(position);
			}
		}
	}

	void InputService::AddObserver(IRawInputObserver& observer)
	{
		globalRawInputObservers.push_back(&observer);
	}

	void InputService::RemoveObserver(IRawInputObserver& observer) noexcept
	{
		if (const auto position = std::ranges::find(globalRawInputObservers, &observer); position != globalRawInputObservers.cend()) [[likely]]
		{
			globalRawInputObservers.erase(position);
		}
	}

	void InputService::AddObserver(const DeviceHandle deviceHandle, IRawInputObserver& observer)
	{
		if (std::ranges::find(devices, deviceHandle) == devices.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Device not found.");
		}

		std::vector<IRawInputObserver*>& observers = rawInputObservers[deviceHandle];
		observers.push_back(&observer);
	}

	void InputService::RemoveObserver(const DeviceHandle deviceHandle, IRawInputObserver& observer) noexcept
	{
		if (const auto mapPosition = rawInputObservers.find(deviceHandle); mapPosition != rawInputObservers.cend()) [[likely]]
		{
			if (const auto position = std::ranges::find(mapPosition->second, &observer); position != mapPosition->second.cend()) [[likely]]
			{
				mapPosition->second.erase(position);
			}
		}
	}

	IInputModuleContext& InputService::PublicInputContext() noexcept
	{
		return *this;
	}

	const IInputModuleContext& InputService::PublicInputContext() const noexcept
	{
		return *this;
	}

	IInputService& InputService::PublicInputService() noexcept
	{
		return *this;
	}

	const IInputService& InputService::PublicInputService() const noexcept
	{
		return *this;
	}

	void InputService::Begin(std::size_t& count)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning input providers...");
		for (const std::shared_ptr<IInputProvider>& provider : providers)
		{
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' input provider...", typeid(*provider).name());
				provider->Begin();
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' input provider done.", typeid(*provider).name());
				++count;
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On beginning '{}' input provider.", typeid(*provider).name());
				throw;
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on beginning '{}' input provider.", typeid(*provider).name());
				throw;
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning input providers done.");
	}

	void InputService::End(const std::size_t count) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending input providers...");
		for (std::size_t i = count; i-- > 0uz; )
		{
			const std::shared_ptr<IInputProvider>& provider = providers[i];
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' input provider...", typeid(*provider).name());
				provider->End();
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' input provider done.", typeid(*provider).name());
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On ending '{}' input provider.", typeid(*provider).name());
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on ending '{}' input provider.", typeid(*provider).name());
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending input providers done.");
	}

	void InputService::ClearOldData() noexcept
	{
		for (std::unordered_map<Axis, InputValue>& deviceValue : deviceAxisValues)
		{
			for (InputValue& value : std::views::values(deviceValue))
			{
				value.delta = 0.f;
			}
		}
		for (std::unordered_map<ActionId, std::vector<InputValue>>& deviceValue : deviceActionValues)
		{
			for (std::vector<InputValue>& values : std::views::values(deviceValue))
			{
				for (InputValue& value : values)
				{
					value.delta = 0.f;
				}
			}
		}

		rawInputs.clear();
		rawInputAxes.clear();
		rawInputValues.clear();

		lastInputDevice = DeviceHandle();
	}

	void InputService::TickProviders()
	{
		for (const std::shared_ptr<IInputProvider>& provider : providers)
		{
			PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking '{}' input provider.", typeid(*provider).name());
			try
			{
				provider->Tick();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On ticking '{}' input provider.", typeid(*provider).name());
				throw;
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on ticking '{}' input provider.", typeid(*provider).name());
				throw;
			}
		}
	}

	void InputService::SortInput() noexcept
	{
		std::ranges::sort(rawInputs, [](const RawInput& lhs, const RawInput& rhs)
		{
			return lhs.timePoint < rhs.timePoint;
		});
	}

	void InputService::UpdateInput()
	{
		for (const RawInput& rawInput : rawInputs)
		{
			const auto devicePosition = std::ranges::find(devices, rawInput.deviceHandle);
			assert(devicePosition != devices.cend() && "Device not found.");
			const std::size_t deviceIndex = devicePosition - devices.cbegin();
			const auto eventAxes = std::span<const Axis>(&rawInputAxes[rawInput.valueIndex], rawInput.valueCount);
			const auto eventValues = std::span<const float>(&rawInputValues[rawInput.valueIndex], rawInput.valueCount);

			const auto rawInputEvent = RawInputEvent
			{
				.axes = eventAxes,
				.values = eventValues,
				.eventType = rawInput.eventType,
				.timePoint = rawInput.timePoint,
				.cursorPosition = rawInput.cursorPosition
			};
			if (const auto position = rawInputObservers.find(rawInput.deviceHandle); position != rawInputObservers.cend())
			{
				ObserveRawInput(position->second, rawInput.deviceHandle, rawInputEvent);
			}
			ObserveRawInput(globalRawInputObservers, rawInput.deviceHandle, rawInputEvent);

			std::unordered_map<Axis, InputValue>& deviceValues = deviceAxisValues[deviceIndex];
			for (std::size_t i = 0uz; i < eventAxes.size(); ++i)
			{
				const Axis& axis = eventAxes[i];
				const float value = eventValues[i];
				InputValue& deviceInputValue = deviceValues[axis];
				switch (rawInput.eventType)
				{
				case InputEventType::State:
					deviceInputValue.state = value;
					break;
				case InputEventType::Delta:
					deviceInputValue.delta += value;
					break;
				default: [[unlikely]]
					assert(false && "Invalid input event type.");
					break;
				}
			}

			lastInputDevice = *devicePosition;

			for (std::size_t i = 0uz; i < actionBindings.size(); ++i)
			{
				const std::span<const ActionBinding> binding = actionBindings[i];
				if (!HasAxis(binding, eventAxes))
				{
					continue;
				}

				const std::size_t bindingSize = binding.back().actionAxisIndex;
				actionValuesTemp.resize(bindingSize);
				std::ranges::fill(actionValuesTemp, 0.f);
				for (std::size_t axisIndex = 0uz; axisIndex < bindingSize; ++axisIndex)
				{
					const ActionBinding& actionBinding = binding[axisIndex];
					if (const auto position = std::ranges::find(eventAxes, actionBinding.axis); position != eventAxes.cend())
					{
						const float initialValue = eventValues[position - eventAxes.cbegin()];
						float currentValue = initialValue;
						for (const std::shared_ptr<IModifier>& modifier : actionBinding.modifiers)
						{
							currentValue = modifier->Modify(initialValue, currentValue);
						}
						actionValuesTemp[actionBinding.actionAxisIndex] = currentValue;
					}
				}

				const auto inputEvent = InputEvent
				{
					.actionId = actionIds[i],
					.values = actionValuesTemp,
					.eventType = rawInput.eventType,
					.timePoint = rawInput.timePoint,
					.cursorPosition = rawInput.cursorPosition
				};
				if (const auto position = inputObservers.find(rawInput.deviceHandle); position != inputObservers.cend())
				{
					ObserveInput(position->second, rawInput.deviceHandle, inputEvent);
				}
				ObserveInput(globalInputObservers, rawInput.deviceHandle, inputEvent);

				std::vector<InputValue>& actionValues = deviceActionValues[deviceIndex][actionIds[i]];
				actionValues.resize(actionValuesTemp.size());
				for (std::size_t j = 0uz; j < actionValues.size(); ++j)
				{
					InputValue& actionValue = actionValues[j];
					const float value = actionValuesTemp[j];

					switch (rawInput.eventType)
					{
					case InputEventType::State:
						actionValue.state = value;
						break;
					case InputEventType::Delta:
						actionValue.delta += value;
						break;
					default: [[unlikely]]
						assert(false && "Invalid input event type.");
						break;
					}
				}
			}
		}
	}

	void InputService::Value(const std::unordered_map<ActionId, std::vector<InputValue>>& actionValues, const ActionId actionId, const std::span<float> values) noexcept
	{
		if (const auto position = actionValues.find(actionId); position != actionValues.cend())
		{
			for (std::size_t i = 0uz; i < std::min(position->second.size(), values.size()); ++i)
			{
				const InputValue& input = position->second[i];
				values[i] += input.state + input.delta;
			}
		}
	}

	float InputService::Value(const std::unordered_map<Axis, InputValue>& values, const Axis& axis) noexcept
	{
		if (const auto position = values.find(axis); position != values.cend()) [[likely]]
		{
			const InputValue& value = position->second;
			return value.state + value.delta;
		}

		return 0.f;
	}

	bool InputService::HasAxis(const std::span<const ActionBinding> bindings, const std::span<const Axis> axes) noexcept
	{
		for (const ActionBinding& binding : bindings)
		{
			for (const Axis& axis : axes)
			{
				if (binding.axis == axis)
				{
					return true;
				}
			}
		}

		return false;
	}

	void InputService::ObserveDeviceAdded(const std::span<IDeviceObserver*> observers, const DeviceHandle deviceHandle) noexcept
	{
		for (IDeviceObserver* const observer : observers)
		{
			try
			{
				observer->OnDeviceAdded(deviceHandle);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing device added.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing device added.");
			}
		}
	}

	void InputService::ObserveDeviceRemoved(const std::span<IDeviceObserver*> observers, const DeviceHandle deviceHandle) noexcept
	{
		for (IDeviceObserver* const observer : observers)
		{
			try
			{
				observer->OnDeviceRemoved(deviceHandle);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing device removed.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing device removed.");
			}
		}
	}

	void InputService::ObserveDeviceConnectionChanged(const std::span<IDeviceObserver*> observers, const DeviceHandle deviceHandle, const bool isConnected) noexcept
	{
		for (IDeviceObserver* const observer : observers)
		{
			try
			{
				observer->OnDeviceConnectionChanged(deviceHandle, isConnected);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing device connection changed.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing device connection changed.");
			}
		}
	}

	void InputService::ObserveInput(const std::span<IInputObserver*> observers, const DeviceHandle deviceHandle, const InputEvent& inputEvent) noexcept
	{
		for (IInputObserver* const observer : observers)
		{
			try
			{
				observer->OnInput(deviceHandle, inputEvent);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing action input.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing action input.");
			}
		}
	}

	void InputService::ObserveRawInput(const std::span<IRawInputObserver*> observers, const DeviceHandle deviceHandle, const RawInputEvent& inputEvent) noexcept
	{
		for (IRawInputObserver* const observer : observers)
		{
			try
			{
				observer->OnRawInput(deviceHandle, inputEvent);
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On observing raw input.");
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on observing raw input.");
			}
		}
	}
}

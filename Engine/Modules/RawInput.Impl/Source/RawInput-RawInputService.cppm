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

export module PonyEngine.RawInput.Impl:RawInputService;

import std;

import PonyEngine.Application;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.RawInput.Ext;
import PonyEngine.Utility;

import :InputDeviceContainer;
import :RawInputQueue;

export namespace PonyEngine::RawInput
{
	/// @brief Raw input service.
	class RawInputService final : public IRawInputService, public IDeviceHub, private Application::ITickable
	{
	public:
		/// @brief Creates an input service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit RawInputService(const Application::IApplication& application) noexcept;
		RawInputService(const RawInputService&) = delete;
		RawInputService(RawInputService&&) = delete;

		~RawInputService() noexcept;

		[[nodiscard("Pure function")]] 
		virtual float Value(Axis axis) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual float Value(Axis axis, DeviceHandle deviceHandle) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual DeviceHandle LastInputDevice() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::size_t DeviceCount() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual DeviceHandle Device(std::size_t index) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsValid(DeviceHandle deviceHandle) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsConnected(DeviceHandle deviceHandle) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view DeviceName(DeviceHandle deviceHandle) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual struct DeviceType DeviceType(DeviceHandle deviceHandle) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual struct DeviceStyle DeviceStyle(DeviceHandle deviceHandle) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual void* FindFeature(DeviceHandle deviceHandle, std::type_index type) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual Axis MakeAxis(std::string_view axis) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsAxisValid(Axis axis) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetAxisString(Axis axis) const override;
		[[nodiscard("Pure function")]] 
		virtual struct DeviceType MakeDeviceType(std::string_view deviceType) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsDeviceTypeValid(struct DeviceType deviceType) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetDeviceTypeString(struct DeviceType deviceType) const override;
		[[nodiscard("Pure function")]] 
		virtual struct DeviceStyle MakeDeviceStyle(std::string_view deviceStyle) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsDeviceStyleValid(struct DeviceStyle deviceStyle) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetDeviceStyleString(struct DeviceStyle deviceStyle) const override;

		virtual void AddObserver(IRawInputObserver& observer) const override;
		virtual void RemoveObserver(IRawInputObserver& observer) const override;

		[[nodiscard("Must be used to unregister")]] 
		virtual DeviceHandle RegisterDevice(IDeviceController& deviceController, bool isConnected, const DeviceParams& params) override;
		virtual void UnregisterDevice(DeviceHandle deviceHandle, IDeviceController& deviceController) override;

		/// @brief Gets the tickable.
		/// @return Tickable.
		[[nodiscard("Pure function")]]
		Application::ITickable& Tickable() noexcept;

		RawInputService& operator =(const RawInputService&) = delete;
		RawInputService& operator =(RawInputService&&) = delete;

	private:
		virtual void Tick() override;

		/// @brief Input registry.
		class InputRegistry final : public IInputRegistry
		{
		public:
			/// @brief Creates an input registry.
			/// @param rawInput Raw input service.
			/// @param device Device handle.
			[[nodiscard("Pure constructor")]]
			explicit InputRegistry(RawInputService& rawInput, DeviceHandleID device) noexcept;
			[[nodiscard("Pure constructor")]]
			InputRegistry(const InputRegistry& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			InputRegistry(InputRegistry&& other) noexcept = default;

			~InputRegistry() noexcept = default;

			virtual void AddInput(const RawInputEvent& input) override;
			virtual void Connect(const ConnectionEvent& connection) override;

			InputRegistry& operator =(const InputRegistry& other) noexcept = default;
			InputRegistry& operator =(InputRegistry&& other) noexcept = default;

		private:
			RawInputService* rawInput; ///< Raw input service.
			DeviceHandleID device; ///< Device handle.
		};

		/// @brief Ticks controllers.
		void TickControllers();
		/// @brief Processes the input queue.
		/// @remark The queue must be sorted.
		void ProcessInputQueue();

		/// @brief Adds the input.
		/// @param device Input device.
		/// @param input Input event.
		void AddInput(DeviceHandleID device, const RawInputEvent& input);
		/// @brief Adds the connection event.
		/// @param device Input device.
		/// @param connection Connection event.
		void Connect(DeviceHandleID device, const ConnectionEvent& connection);

		/// @brief Checks if the device handle is invalid.
		/// @param handle Handle to check.
		/// @return @a True if it's invalid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsInvalid(DeviceHandle handle) const noexcept;
		/// @brief Makes a new device handle.
		/// @return Device handle.
		[[nodiscard("Weird call")]]
		DeviceHandle MakeDeviceHandle();
		/// @brief Resurrects a device handle.
		/// @return Device handle.
		[[nodiscard("Weird call")]]
		DeviceHandle ResurrectDeviceHandle() noexcept;
		/// @brief Kills the device handle.
		/// @param handle Device handle to kill.
		void KillDeviceHandle(DeviceHandle handle) noexcept;

		/// @brief Calls connection observers.
		/// @param device Device.
		/// @param connection Connection event.
		void ObserveConnection(DeviceHandle device, const ConnectionEvent& connection) const noexcept;
		/// @brief Calls input observers.
		/// @param device Device.
		/// @param input Input event.
		void ObserveInput(DeviceHandle device, const RawInputEvent& input) const noexcept;

		/// @brief Calls device observers on adding.
		/// @param device Device.
		void ObserveDeviceAdded(DeviceHandle device) const noexcept;
		/// @brief Calls device observers on removing.
		/// @param device Device.
		void ObserveDeviceRemoved(DeviceHandle device) const noexcept;

		const Application::IApplication* application; ///< Application.
		const Log::ILogService* logService; ///< Log service.

		InputDeviceContainer devices; ///< Input devices.
		RawInputQueue inputQueue; ///< Input queue.

		std::vector<DeviceHandleVersion> deviceHandleVersions; ///< Device handle versions.
		std::vector<DeviceHandleID> deadDeviceHandleIds; ///< Device handle IDs.
		DeviceHandle lastInputDevice; ///< Last device that sent input.

		std::unordered_map<std::uint64_t, std::vector<std::string>> axisHashMap; ///< Input axis hash map. It has a hash and a vector that is synced by index.
		std::unordered_map<struct DeviceType, std::string> deviceTypeHashMap; ///< Device type hash map.
		std::unordered_map<struct DeviceStyle, std::string> deviceStyleHashMap; ///< Device style hash map.

		mutable std::vector<IRawInputObserver*> inputObservers; ///< Input observers.
	};
}

namespace PonyEngine::RawInput
{
	RawInputService::RawInputService(const Application::IApplication& application) noexcept :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()}
	{
	}

	RawInputService::~RawInputService() noexcept
	{
		assert(devices.Size() == 0uz && "Some raw input devices weren't removed.");
		assert(inputObservers.empty() && "Some input observers weren't removed.");
	}

	float RawInputService::Value(const Axis axis) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return devices.Value(axis);
	}

	float RawInputService::Value(const Axis axis, const DeviceHandle deviceHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(!IsInvalid(deviceHandle) && "Invalid device handle.");
		return devices.Value(axis, devices.IndexOf(deviceHandle.id));
	}

	DeviceHandle RawInputService::LastInputDevice() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return lastInputDevice;
	}

	std::size_t RawInputService::DeviceCount() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return devices.Size();
	}

	DeviceHandle RawInputService::Device(const std::size_t index) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		const DeviceHandleID id = devices.Handle(index);
		return DeviceHandle{.id = id, .version = deviceHandleVersions[id]};
	}

	bool RawInputService::IsValid(const DeviceHandle deviceHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return !IsInvalid(deviceHandle);
	}

	bool RawInputService::IsConnected(const DeviceHandle deviceHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(!IsInvalid(deviceHandle) && "Invalid device handle.");
		return devices.IsConnected(devices.IndexOf(deviceHandle.id));
	}

	std::string_view RawInputService::DeviceName(const DeviceHandle deviceHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(!IsInvalid(deviceHandle) && "Invalid device handle.");
		return devices.DeviceName(devices.IndexOf(deviceHandle.id));
	}

	struct DeviceType RawInputService::DeviceType(const DeviceHandle deviceHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(!IsInvalid(deviceHandle) && "Invalid device handle.");
		return devices.DeviceType(devices.IndexOf(deviceHandle.id));
	}

	struct DeviceStyle RawInputService::DeviceStyle(const DeviceHandle deviceHandle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(!IsInvalid(deviceHandle) && "Invalid device handle.");
		return devices.DeviceStyle(devices.IndexOf(deviceHandle.id));
	}

	void* RawInputService::FindFeature(const DeviceHandle deviceHandle, const std::type_index type) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(!IsInvalid(deviceHandle) && "Invalid device handle.");
		return devices.FindFeature(devices.IndexOf(deviceHandle.id), type);
	}

	Axis RawInputService::MakeAxis(const std::string_view axis)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");

		const std::uint64_t hash = Hash::FNV1a64(axis);
		auto axisId = Axis{.hash = hash};

		if (const auto position = axisHashMap.find(hash); position != axisHashMap.cend())
		{
			std::vector<std::string>& axes = position->second;
			const auto axisPosition = std::ranges::find(axes, axis);
			axisId.index = static_cast<std::uint64_t>(axisPosition - axes.cbegin());

			if (axisPosition == axes.cend()) [[unlikely]]
			{
				PONY_LOG(logService, Log::LogType::Info, "Adding new input axis. Axis: '{}'; AxisHash: '{}'; AxisIndex: '{}'.", axis, axisId.hash, axisId.index);
				if (axes.size() >= std::numeric_limits<std::uint64_t>::max()) [[unlikely]]
				{
					throw std::overflow_error("Max number of axis with the same hash has been reached");
				}

				axes.push_back(std::string(axis));
			}
		}
		else
		{
			axisId.index = 0u;
			PONY_LOG(logService, Log::LogType::Info, "Adding new input axis. Axis: '{}'; AxisHash: '{}'; AxisIndex: '{}'.", axis, axisId.hash, axisId.index);
			axisHashMap.emplace(hash, std::vector<std::string>{ std::string(axis) });
		}

		return axisId;
	}

	bool RawInputService::IsAxisValid(const Axis axis) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		const auto position = axisHashMap.find(axis.hash);
		return position != axisHashMap.cend() && axis.index < position->second.size();
	}

	std::string_view RawInputService::GetAxisString(const Axis axis) const
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		const auto position = axisHashMap.find(axis.hash);
		if (position == axisHashMap.cend() || axis.index >= position->second.size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid axis");
		}

		return position->second[axis.index];
	}

	struct DeviceType RawInputService::MakeDeviceType(const std::string_view deviceType)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");

		const auto deviceTypeId = RawInput::DeviceType{ .hash = Hash::FNV1a64(deviceType) };

		if (const auto position = deviceTypeHashMap.find(deviceTypeId); position != deviceTypeHashMap.cend())
		{
			if (position->second != deviceType) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(logService, Log::LogType::Info, "Adding new input device type. DeviceType: '{}'; DeviceTypeHash: '{}'.", deviceType, deviceTypeId.hash);
			deviceTypeHashMap.emplace(deviceTypeId, deviceType);
		}

		return deviceTypeId;
	}

	bool RawInputService::IsDeviceTypeValid(const struct DeviceType deviceType) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return deviceTypeHashMap.contains(deviceType);
	}

	std::string_view RawInputService::GetDeviceTypeString(const struct DeviceType deviceType) const
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");

		const auto position = deviceTypeHashMap.find(deviceType);
		if (position == deviceTypeHashMap.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid device type");
		}

		return position->second;
	}

	struct DeviceStyle RawInputService::MakeDeviceStyle(const std::string_view deviceStyle)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");

		const auto deviceStyleId = RawInput::DeviceStyle{ .hash = Hash::FNV1a64(deviceStyle) };

		if (const auto position = deviceStyleHashMap.find(deviceStyleId); position != deviceStyleHashMap.cend())
		{
			if (position->second != deviceStyle) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(logService, Log::LogType::Info, "Adding new input device style. DeviceStyle: '{}'; DeviceStyleHash: '{}'.", deviceStyle, deviceStyleId.hash);
			deviceStyleHashMap.emplace(deviceStyleId, deviceStyle);
		}

		return deviceStyleId;
	}

	bool RawInputService::IsDeviceStyleValid(const struct DeviceStyle deviceStyle) const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		return deviceStyleHashMap.contains(deviceStyle);
	}

	std::string_view RawInputService::GetDeviceStyleString(const struct DeviceStyle deviceStyle) const
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");

		const auto position = deviceStyleHashMap.find(deviceStyle);
		if (position == deviceStyleHashMap.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid device style");
		}

		return position->second;
	}

	void RawInputService::AddObserver(IRawInputObserver& observer) const
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		inputObservers.push_back(&observer);
	}

	void RawInputService::RemoveObserver(IRawInputObserver& observer) const
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		const auto position = std::ranges::find(inputObservers, &observer);
		assert(position != inputObservers.cend() && "Observer wasn't added");
		inputObservers.erase(position);
	}

	DeviceHandle RawInputService::RegisterDevice(IDeviceController& deviceController, const bool isConnected, const DeviceParams& params)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(IsDeviceTypeValid(params.type) && "Device type is invalid");
		assert(IsDeviceStyleValid(params.style) && "Device style is invalid");
		for (const FeatureEntry& feature : params.features)
		{
			assert(feature.feature && "Feature is nullptr");
		}
		for (std::size_t i = 1uz; i < params.features.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				assert(params.features[i].featureType == params.features[j].featureType && "Feature type duplicate found.");
			}
		}

		const DeviceHandle currentHandle = deadDeviceHandleIds.empty()
			? MakeDeviceHandle()
			: ResurrectDeviceHandle();
		try
		{
			devices.Add(currentHandle.id, deviceController, isConnected, params);
		}
		catch (...)
		{
			KillDeviceHandle(currentHandle);
			throw;
		}

		PONY_LOG(logService, Log::LogType::Info, "Device registered. HandleID: '0x{:X}'; Controller: '{}'; Name: '{}'.", 
			currentHandle.id, typeid(deviceController).name(), params.name);

		ObserveDeviceAdded(currentHandle);

		return currentHandle;
	}

	void RawInputService::UnregisterDevice(const DeviceHandle deviceHandle, IDeviceController& deviceController)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread.");
		assert(!IsInvalid(deviceHandle) && "Invalid device handle.");
		const std::size_t deviceIndex = devices.IndexOf(deviceHandle.id);
		assert(&devices.Controller(deviceIndex) == &deviceController && "Invalid controller");

		ObserveDeviceRemoved(deviceHandle);

		if (lastInputDevice == deviceHandle)
		{
			lastInputDevice = DeviceHandle{};
		}

		inputQueue.Remove(deviceHandle.id);
		devices.Remove(deviceIndex);
		KillDeviceHandle(deviceHandle);
	}

	Application::ITickable& RawInputService::Tickable() noexcept
	{
		return *this;
	}

	void RawInputService::Tick()
	{
		PONY_LOG(logService, Log::LogType::Verbose, "Clearing input data.");
		inputQueue.Clear();
		devices.ClearDeltas();

		PONY_LOG(logService, Log::LogType::Verbose, "Ticking input device controllers.");
		TickControllers();

		PONY_LOG(logService, Log::LogType::Verbose, "Processing input queue.");
		inputQueue.SortEvents();
		ProcessInputQueue();
	}

	RawInputService::InputRegistry::InputRegistry(RawInputService& rawInput, const DeviceHandleID device) noexcept :
		rawInput{&rawInput},
		device(device)
	{
	}

	void RawInputService::InputRegistry::AddInput(const RawInputEvent& input)
	{
		rawInput->AddInput(device, input);
	}

	void RawInputService::InputRegistry::Connect(const ConnectionEvent& connection)
	{
		rawInput->Connect(device, connection);
	}

	void RawInputService::TickControllers()
	{
		for (std::size_t i = 0uz; i < devices.Size(); ++i)
		{
			IDeviceController& controller = devices.Controller(i);
			const DeviceHandleID deviceHandleId = devices.Handle(i);
			auto registry = InputRegistry(*this, deviceHandleId);
			PONY_LOG(logService, Log::LogType::Verbose, "Ticking '{}' input device controller.", typeid(controller).name());
			controller.Tick(registry);
		}
	}

	void RawInputService::ProcessInputQueue()
	{
		for (std::size_t eventIndex = 0uz; eventIndex < inputQueue.EventCount(); ++eventIndex)
		{
			const DeviceHandleID device = inputQueue.Device(eventIndex);
			const auto deviceHandle = DeviceHandle{.id = device, .version = deviceHandleVersions[device]};
			const std::variant<RawInputEvent, ConnectionEvent> event = inputQueue.Event(eventIndex);
			const std::size_t deviceIndex = devices.IndexOf(device);

			std::visit(Utility::Overload
			{
				[&](const RawInputEvent& inputEvent)
				{
					for (std::size_t axisIndex = 0uz; axisIndex < inputEvent.axes.size(); ++axisIndex)
					{
						devices.Value(deviceIndex, inputEvent.axes[axisIndex], inputEvent.values[axisIndex], inputEvent.eventType);
					}
					lastInputDevice = deviceHandle;

					ObserveInput(deviceHandle, inputEvent);
				},
				[&](const ConnectionEvent& connectionEvent)
				{
					PONY_LOG(logService, Log::LogType::Debug, "Connection status of device '0x{:X}' changed to '{}'.", device, connectionEvent.isConnected);
					devices.IsConnected(devices.IndexOf(device), connectionEvent.isConnected);
					ObserveConnection(deviceHandle, connectionEvent);
				}
			}, event);
		}
	}

	void RawInputService::AddInput(const DeviceHandleID device, const RawInputEvent& input)
	{
		inputQueue.AddInput(device, input);
	}

	void RawInputService::Connect(const DeviceHandleID device, const ConnectionEvent& connection)
	{
		inputQueue.AddConnection(device, connection);
	}

	bool RawInputService::IsInvalid(const DeviceHandle handle) const noexcept
	{
		return Math::IsEven(handle.version) || handle.id >= deviceHandleVersions.size() || deviceHandleVersions[handle.id] != handle.version;
	}

	DeviceHandle RawInputService::MakeDeviceHandle()
	{
		if (deviceHandleVersions.size() >= std::numeric_limits<DeviceHandleID>::max()) [[unlikely]]
		{
			throw std::overflow_error("No more device handles available");
		}

		const DeviceHandleID handleId = static_cast<DeviceHandleID>(deviceHandleVersions.size());

		constexpr DeviceHandleVersion handleVersion = 1u;
		deviceHandleVersions.push_back(handleVersion);

		return DeviceHandle{.id = handleId, .version = handleVersion};
	}

	DeviceHandle RawInputService::ResurrectDeviceHandle() noexcept
	{
		const DeviceHandleID handleId = deadDeviceHandleIds.back();
		deadDeviceHandleIds.pop_back();

		const DeviceHandleVersion handleVersion = ++deviceHandleVersions[handleId];

		return DeviceHandle{.id = handleId, .version = handleVersion};
	}

	void RawInputService::KillDeviceHandle(const DeviceHandle handle) noexcept
	{
		try
		{
			++deviceHandleVersions[handle.id];
			deadDeviceHandleIds.push_back(handle.id);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On killing device handle. HandleID: '0x{:X}'.", handle.id);
			// Just forget about this handle.
		}
	}

	void RawInputService::ObserveConnection(const DeviceHandle device, const ConnectionEvent& connection) const noexcept
	{
		for (IRawInputObserver* const observer : inputObservers)
		{
			try
			{
				observer->OnDeviceConnectionChanged(device, connection);
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On calling '{}' on connection change.", typeid(*observer).name());
			}
		}
	}

	void RawInputService::ObserveInput(const DeviceHandle device, const RawInputEvent& input) const noexcept
	{
		for (IRawInputObserver* const observer : inputObservers)
		{
			try
			{
				observer->OnRawInput(device, input);
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On calling '{}' on raw input.", typeid(*observer).name());
			}
		}
	}

	void RawInputService::ObserveDeviceAdded(const DeviceHandle device) const noexcept
	{
		for (IRawInputObserver* const observer : inputObservers)
		{
			try
			{
				observer->OnDeviceAdded(device);
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On calling '{}' on device added.", typeid(*observer).name());
			}
		}
	}

	void RawInputService::ObserveDeviceRemoved(const DeviceHandle device) const noexcept
	{
		for (IRawInputObserver* const observer : inputObservers)
		{
			try
			{
				observer->OnDeviceRemoved(device);
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On calling '{}' on device removed.", typeid(*observer).name());
			}
		}
	}
}

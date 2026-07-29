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
import PonyEngine.RawInput.Ext;
import PonyEngine.Type;

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
		virtual float Value(Axis axis) const override;
		[[nodiscard("Pure function")]] 
		virtual float Value(Axis axis, DeviceHandle deviceHandle) const override;

		[[nodiscard("Pure function")]] 
		virtual DeviceHandle LastInputDevice() const override;

		[[nodiscard("Pure function")]] 
		virtual std::size_t DeviceCount() const override;
		[[nodiscard("Pure function")]] 
		virtual DeviceHandle Device(std::size_t index) const override;
		[[nodiscard("Pure function")]] 
		virtual bool IsValid(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]] 
		virtual bool IsConnected(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view DeviceName(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]] 
		virtual RawInput::DeviceType DeviceType(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]] 
		virtual void* FindFeature(DeviceHandle deviceHandle, std::type_index type) const override;

		[[nodiscard("Pure function")]] 
		virtual Axis MakeAxis(std::string_view axis) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsAxisValid(Axis axis) const override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetAxisString(Axis axis) const override;

		[[nodiscard("Pure function")]] 
		virtual struct DeviceType MakeDeviceType(std::string_view deviceType) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsDeviceTypeValid(struct DeviceType deviceType) const override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetDeviceTypeString(struct DeviceType deviceType) const override;

		virtual void AddObserver(IRawInputObserver& observer) override;
		virtual void RemoveObserver(IRawInputObserver& observer) override;

		[[nodiscard("Must be used to unregister")]] 
		virtual DeviceHandle RegisterDevice(IDeviceController& deviceController, std::string_view deviceName, struct DeviceType deviceType, bool isConnected) override;
		virtual void UnregisterDevice(IDeviceController& deviceController, DeviceHandle deviceHandle) override;

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
			explicit InputRegistry(RawInputService& rawInput, DeviceHandle device) noexcept;
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
			DeviceHandle device; ///< Device handle.
		};

		/// @brief Ticks controllers.
		void TickControllers();
		/// @brief Processes the input queue.
		/// @remark The queue must be sorted.
		void ProcessInputQueue();

		/// @brief Adds the input.
		/// @param device Input device.
		/// @param input Input event.
		void AddInput(DeviceHandle device, const RawInputEvent& input);
		/// @brief Adds the connection event.
		/// @param device Input device.
		/// @param connection Connection event.
		void Connect(DeviceHandle device, const ConnectionEvent& connection);

		/// @brief Gets a device index.
		/// @param deviceHandle Device handle.
		/// @return Device index.
		/// @remark Throws if the handle is invalid.
		[[nodiscard("Pure function")]]
		std::size_t DeviceIndex(DeviceHandle deviceHandle) const;

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

		/// @brief Validates if the current thread is main.
		void ValidateMainThread() const;

		const Application::IApplication* application; ///< Application.
		const Log::ILogService* logService; ///< Log service.

		InputDeviceContainer devices; ///< Input devices.
		RawInputQueue inputQueue; ///< Input queue.

		std::unordered_map<std::uint32_t, std::vector<std::string>> axisHashMap; ///< Input axis hash map. It has a hash and a vector that is synced by index.
		std::unordered_map<struct DeviceType, std::string> deviceTypeHashMap; ///< Device type hash map.

		std::vector<IRawInputObserver*> inputObservers; ///< Input observers.

		DeviceHandle lastInputDevice; ///< Last device that sent input.
		DeviceHandle nextDeviceHandle; ///< Next device handle.
	};
}

namespace PonyEngine::RawInput
{
	RawInputService::RawInputService(const Application::IApplication& application) noexcept :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		lastInputDevice{.id = 0u},
		nextDeviceHandle{.id = 1u}
	{
	}

	RawInputService::~RawInputService() noexcept
	{
		assert(devices.Size() == 0uz && "Some raw input devices weren't removed.");
	}

	float RawInputService::Value(const Axis axis) const
	{
		ValidateMainThread();
		return devices.Value(axis);
	}

	float RawInputService::Value(const Axis axis, const DeviceHandle deviceHandle) const
	{
		ValidateMainThread();
		return devices.Value(axis, DeviceIndex(deviceHandle));
	}

	DeviceHandle RawInputService::LastInputDevice() const
	{
		ValidateMainThread();
		return lastInputDevice;
	}

	std::size_t RawInputService::DeviceCount() const
	{
		ValidateMainThread();
		return devices.Size();
	}

	DeviceHandle RawInputService::Device(const std::size_t index) const
	{
		ValidateMainThread();
		if (index >= devices.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid device handle");
		}

		return devices.Handle(index);
	}

	bool RawInputService::IsValid(const DeviceHandle deviceHandle) const
	{
		return devices.IndexOf(deviceHandle) < devices.Size();
	}

	bool RawInputService::IsConnected(const DeviceHandle deviceHandle) const
	{
		ValidateMainThread();
		return devices.IsConnected(DeviceIndex(deviceHandle));
	}

	std::string_view RawInputService::DeviceName(const DeviceHandle deviceHandle) const
	{
		ValidateMainThread();
		return devices.DeviceName(DeviceIndex(deviceHandle));
	}

	struct DeviceType RawInputService::DeviceType(const DeviceHandle deviceHandle) const
	{
		ValidateMainThread();
		return devices.DeviceType(DeviceIndex(deviceHandle));
	}

	void* RawInputService::FindFeature(const DeviceHandle deviceHandle, const std::type_index type) const
	{
		ValidateMainThread();
		return devices.Controller(DeviceIndex(deviceHandle)).FindFeature(deviceHandle, type);
	}

	Axis RawInputService::MakeAxis(const std::string_view axis)
	{
		ValidateMainThread();

		const std::uint32_t hash = Hash::FNV1a32(axis);
		auto axisId = Axis{.hash = hash};

		if (const auto position = axisHashMap.find(hash); position != axisHashMap.cend())
		{
			std::vector<std::string>& axes = position->second;
			const auto axisPosition = std::ranges::find(axes, axis);
			axisId.index = static_cast<std::uint32_t>(axisPosition - axes.cbegin());

			if (axisPosition == axes.cend()) [[unlikely]]
			{
				PONY_LOG(logService, Log::LogType::Info, "Adding new input axis. Axis: '{}'; AxisHash: '{}'; AxisIndex: '{}'.", axis, axisId.hash, axisId.index);
				if (axes.size() >= std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
				{
					throw std::bad_alloc();
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

	bool RawInputService::IsAxisValid(const Axis axis) const
	{
		ValidateMainThread();
		const auto position = axisHashMap.find(axis.hash);
		return position != axisHashMap.cend() && axis.index < position->second.size();
	}

	std::string_view RawInputService::GetAxisString(const Axis axis) const
	{
		ValidateMainThread();
		const auto position = axisHashMap.find(axis.hash);
		if (position == axisHashMap.cend() || axis.index >= position->second.size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid axis");
		}

		return position->second[axis.index];
	}

	struct DeviceType RawInputService::MakeDeviceType(const std::string_view deviceType)
	{
		ValidateMainThread();

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

	bool RawInputService::IsDeviceTypeValid(const struct DeviceType deviceType) const
	{
		ValidateMainThread();
		return deviceTypeHashMap.contains(deviceType);
	}

	std::string_view RawInputService::GetDeviceTypeString(const struct DeviceType deviceType) const
	{
		ValidateMainThread();

		const auto position = deviceTypeHashMap.find(deviceType);
		if (position == deviceTypeHashMap.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid device type");
		}

		return position->second;
	}

	void RawInputService::AddObserver(IRawInputObserver& observer)
	{
		ValidateMainThread();
		inputObservers.push_back(&observer);
	}

	void RawInputService::RemoveObserver(IRawInputObserver& observer)
	{
		ValidateMainThread();

		if (const auto position = std::ranges::find(inputObservers, &observer); position != inputObservers.cend()) [[likely]]
		{
			inputObservers.erase(position);
		}
		else [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Warning, "Tried to remove raw input observer that hadn't been added.");
		}
	}

	DeviceHandle RawInputService::RegisterDevice(IDeviceController& deviceController, const std::string_view deviceName, const struct DeviceType deviceType, 
		const bool isConnected)
	{
		ValidateMainThread();
#ifndef NDEBUG
		if (!IsDeviceTypeValid(deviceType)) [[unlikely]]
		{
			throw std::invalid_argument("Device type is invalid");
		}
#endif

		if (!nextDeviceHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more device handles available");
		}

		const DeviceHandle currentHandle = nextDeviceHandle;
		devices.Add(deviceController, currentHandle, deviceName, deviceType, isConnected);
		++nextDeviceHandle.id;

		PONY_LOG(logService, Log::LogType::Info, "Device registered. Handle: '0x{:X}'; Name: '{}'.", currentHandle.id, deviceName);

		ObserveDeviceAdded(currentHandle);

		return currentHandle;
	}

	void RawInputService::UnregisterDevice(IDeviceController& deviceController, const DeviceHandle deviceHandle)
	{
		ValidateMainThread();

		const std::size_t deviceIndex = devices.IndexOf(deviceHandle);

#ifndef NDEBUG
		if (deviceIndex >= devices.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid device handle");
		}
		if (&devices.Controller(deviceIndex) != &deviceController) [[unlikely]]
		{
			throw std::invalid_argument("Invalid controller");
		}
#endif

		ObserveDeviceRemoved(deviceHandle);

		if (lastInputDevice == deviceHandle)
		{
			lastInputDevice.id = 0u;
		}

		inputQueue.Remove(deviceHandle);
		devices.Remove(deviceIndex);
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

	RawInputService::InputRegistry::InputRegistry(RawInputService& rawInput, const DeviceHandle device) noexcept :
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
			const DeviceHandle deviceHandle = devices.Handle(i);
			auto registry = InputRegistry(*this, deviceHandle);
			PONY_LOG(logService, Log::LogType::Verbose, "Ticking '{}' input device controller.", typeid(controller).name());
			controller.Tick(deviceHandle, registry);
		}
	}

	void RawInputService::ProcessInputQueue()
	{
		for (std::size_t eventIndex = 0uz; eventIndex < inputQueue.EventCount(); ++eventIndex)
		{
			const DeviceHandle device = inputQueue.Device(eventIndex);
			const std::variant<RawInputEvent, ConnectionEvent> event = inputQueue.Event(eventIndex);
			const std::size_t deviceIndex = devices.IndexOf(device);

			std::visit(Type::Overload
			{
				[&](const RawInputEvent& inputEvent)
				{
					for (std::size_t axisIndex = 0uz; axisIndex < inputEvent.axes.size(); ++axisIndex)
					{
						devices.Value(deviceIndex, inputEvent.axes[axisIndex], inputEvent.values[axisIndex], inputEvent.eventType);
					}
					lastInputDevice = device;

					ObserveInput(device, inputEvent);
				},
				[&](const ConnectionEvent& connectionEvent)
				{
					PONY_LOG(logService, Log::LogType::Debug, "Connection status of device '0x{:X}' changed to '{}'.", device.id, connectionEvent.isConnected);
					devices.IsConnected(devices.IndexOf(device), connectionEvent.isConnected);
					ObserveConnection(device, connectionEvent);
				}
			}, event);
		}
	}

	void RawInputService::AddInput(const DeviceHandle device, const RawInputEvent& input)
	{
		inputQueue.AddInput(device, input);
	}

	void RawInputService::Connect(const DeviceHandle device, const ConnectionEvent& connection)
	{
		inputQueue.AddConnection(device, connection);
	}

	std::size_t RawInputService::DeviceIndex(const DeviceHandle deviceHandle) const
	{
		const std::size_t deviceIndex = devices.IndexOf(deviceHandle);
		if (deviceIndex >= devices.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid device handle");
		}

		return deviceIndex;
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

	void RawInputService::ValidateMainThread() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif
	}
}

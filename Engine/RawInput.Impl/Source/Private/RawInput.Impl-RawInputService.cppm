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

import PonyEngine.Application.Ext;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.RawInput.Ext;
import PonyEngine.Type;

import :InputDeviceContainer;
import :InputProviderContainer;
import :RawInputQueue;

export namespace PonyEngine::Input
{
	/// @brief Raw input service.
	class RawInputService final : public Application::ITickableService, private IRawInputContext, private IRawInputModuleContext, private IRawInputService
	{
	public:
		/// @brief Creates an input service.
		/// @param application Application context.
		[[nodiscard("Pure constructor")]]
		explicit RawInputService(Application::IApplicationContext& application) noexcept;
		RawInputService(const RawInputService&) = delete;
		RawInputService(RawInputService&&) = delete;

		~RawInputService() noexcept;

		virtual void Begin() override;
		virtual void End() noexcept override;
		virtual void Tick() override;

		/// @brief Gets the public input module context.
		/// @return Input module context.
		[[nodiscard("Pure function")]]
		IRawInputModuleContext& PublicInputContext() noexcept;
		/// @brief Gets the public input module context.
		/// @return Input module context.
		[[nodiscard("Pure function")]]
		const IRawInputModuleContext& PublicInputContext() const noexcept;
		/// @brief Gets the public input service interface.
		/// @return Input service interface.
		[[nodiscard("Pure function")]]
		IRawInputService& PublicInputService() noexcept;
		/// @brief Gets the public input service interface.
		/// @return Input service interface.
		[[nodiscard("Pure function")]]
		const IRawInputService& PublicInputService() const noexcept;

		RawInputService& operator =(const RawInputService&) = delete;
		RawInputService& operator =(RawInputService&&) = delete;

	private:
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
		virtual void Connect(DeviceHandle deviceHandle, const ConnectionEvent& connection) override;

		[[nodiscard("Must be used to remove")]]
		virtual InputProviderHandle AddProvider(const std::function<std::shared_ptr<IInputProvider>(IRawInputContext&)>& factory) override;
		virtual void RemoveProvider(InputProviderHandle providerHandle) override;

		[[nodiscard("Pure function")]]
		virtual float Value(AxisId axis) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual float Value(AxisId axis, DeviceHandle deviceHandle) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual DeviceHandle LastInputDevice() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::size_t DeviceCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual DeviceHandle Device(std::size_t index) const override;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(DeviceHandle deviceHandle) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual bool IsConnected(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]]
		virtual std::string_view DeviceName(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]]
		virtual DeviceTypeId DeviceType(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]]
		virtual std::span<const std::type_index> FeatureTypes(DeviceHandle deviceHandle) const override;
		[[nodiscard("Pure function")]]
		virtual void* FindFeature(DeviceHandle deviceHandle, std::type_index type)override;
		[[nodiscard("Pure function")]]
		virtual const void* FindFeature(DeviceHandle deviceHandle, std::type_index type) const override;

		[[nodiscard("Pure function")]]
		virtual AxisId Hash(const Axis& axis) override;
		[[nodiscard("Pure function")]]
		virtual const Axis& Unhash(AxisId axisId) const override;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(AxisId axisId) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual DeviceTypeId Hash(const class DeviceType& deviceType) override;
		[[nodiscard("Pure function")]]
		virtual const class DeviceType& Unhash(DeviceTypeId deviceTypeId) override;
		[[nodiscard("Pure function")]]
		virtual bool IsValid(DeviceTypeId deviceTypeId) const noexcept override;

		virtual void AddObserver(IDeviceObserver& observer) override;
		virtual void RemoveObserver(IDeviceObserver& observer) noexcept override;
		virtual void AddObserver(IRawInputObserver& observer) override;
		virtual void RemoveObserver(IRawInputObserver& observer) noexcept override;

		/// @brief Begins the providers.
		/// @param count How many providers are begun.
		void Begin(std::size_t& count);
		/// @brief Ends the providers.
		/// @param count How many providers to end.
		void End(std::size_t count) noexcept;

		/// @brief Ticks the providers
		void TickProviders();
		/// @brief Processes input queue and sends events.
		void ProcessInputQueue();

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

		Application::IApplicationContext* application; ///< Application context.

		InputProviderContainer providers; ///< Input providers.
		InputDeviceContainer devices; ///< Input devices.

		RawInputQueue inputQueue; ///< Input queue.
		DeviceHandle lastInputDevice; ///< Last device that sent input.

		std::unordered_map<std::uint32_t, std::vector<Axis>> axisHashMap; ///< Input axis hash map. It has a hash and a vector that is synced by index.
		std::unordered_map<DeviceTypeId, class DeviceType> deviceTypeHashMap; ///< Device type hash map.

		std::vector<IDeviceObserver*> deviceObservers; ///< Device observers.
		std::vector<IRawInputObserver*> inputObservers; ///< Input observers.

		InputProviderHandle nextProviderHandle; ///< Next input provider handle.
		DeviceHandle nextDeviceHandle; ///< Next device handle.
	};

	RawInputService::RawInputService(Application::IApplicationContext& application) noexcept :
		application{&application},
		lastInputDevice{.id = 0u},
		nextProviderHandle{.id = 1u},
		nextDeviceHandle{.id = 1u}
	{
	}

	RawInputService::~RawInputService() noexcept
	{
		if (devices.Size() > 0uz)
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Input devices weren't removed:");
			for (std::size_t i = 0uz; i < devices.Size(); ++i)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Device handle: '0x{:X}'.", devices.Handle(i).id);
			}
		}

		if (providers.Size() > 0uz)
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Input providers weren't removed:");
			for (std::size_t i = 0uz; i < providers.Size(); ++i)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Provider: '{}'.", typeid(providers.Provider(i)).name());
			}
		}
	}

	void RawInputService::Begin()
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

	void RawInputService::End() noexcept
	{
		End(providers.Size());
	}

	void RawInputService::Tick()
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Clearing input data.");
		inputQueue.Clear();
		devices.ClearDeltas();

		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking input providers.");
		TickProviders();

		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Sorting input events.");
		inputQueue.SortEvents();

		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Processing input queue.");
		ProcessInputQueue();
	}

	IRawInputModuleContext& RawInputService::PublicInputContext() noexcept
	{
		return *this;
	}

	const IRawInputModuleContext& RawInputService::PublicInputContext() const noexcept
	{
		return *this;
	}

	IRawInputService& RawInputService::PublicInputService() noexcept
	{
		return *this;
	}

	const IRawInputService& RawInputService::PublicInputService() const noexcept
	{
		return *this;
	}

	Application::IApplicationContext& RawInputService::Application() noexcept
	{
		return *application;
	}

	const Application::IApplicationContext& RawInputService::Application() const noexcept
	{
		return *application;
	}

	Log::ILogger& RawInputService::Logger() noexcept
	{
		return application->Logger();
	}

	const Log::ILogger& RawInputService::Logger() const noexcept
	{
		return application->Logger();
	}

	DeviceHandle RawInputService::RegisterDevice(const DeviceData& data)
	{
		if (!nextDeviceHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more device handles available");
		}

		if (!deviceTypeHashMap.contains(data.type))
		{
			throw std::invalid_argument("Device type is invalid");
		}

		const DeviceHandle currentHandle = nextDeviceHandle;
		devices.Add(currentHandle, data);
		++nextDeviceHandle.id;

		PONY_LOG(application->Logger(), Log::LogType::Info, "Device registered. Handle: '0x{:X}'; Name: '{}'.", currentHandle.id, data.name);

		ObserveDeviceAdded(currentHandle);

		return currentHandle;
	}

	void RawInputService::UnregisterDevice(const DeviceHandle deviceHandle)
	{
		if (const std::size_t index = devices.IndexOf(deviceHandle); index < devices.Size()) [[likely]]
		{
			devices.Remove(index);
			inputQueue.Remove(deviceHandle);

			if (lastInputDevice == deviceHandle)
			{
				lastInputDevice.id = 0u;
			}

			PONY_LOG(application->Logger(), Log::LogType::Info, "Device unregistered. Handle: '0x{:X}'.", deviceHandle.id);

			ObserveDeviceRemoved(deviceHandle);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	void RawInputService::AddInput(const DeviceHandle deviceHandle, const RawInputEvent& input)
	{
		if (const std::size_t index = devices.IndexOf(deviceHandle); index < devices.Size()) [[likely]]
		{
			inputQueue.AddInput(deviceHandle, input);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	void RawInputService::Connect(const DeviceHandle deviceHandle, const ConnectionEvent& connection)
	{
		if (const std::size_t index = devices.IndexOf(deviceHandle); index < devices.Size()) [[likely]]
		{
			inputQueue.AddConnection(deviceHandle, connection);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	InputProviderHandle RawInputService::AddProvider(const std::function<std::shared_ptr<IInputProvider>(IRawInputContext&)>& factory)
	{
		if (!nextProviderHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more input provider handles available");
		}
		if (application->FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Input providers can be added only on start-up");
		}

		const std::shared_ptr<IInputProvider> provider = factory(*this);
		if (!provider) [[unlikely]]
		{
			throw std::invalid_argument("Input provider is nullptr");
		}
		if (providers.IndexOf(*provider) < providers.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Input provider has already been added");
		}

		const InputProviderHandle currentHandle = nextProviderHandle;
		providers.Add(currentHandle, provider);
		++nextProviderHandle.id;

		PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' provider added. Handle: '0x{:X}'.", typeid(*provider).name(), currentHandle.id);

		return currentHandle;
	}

	void RawInputService::RemoveProvider(const InputProviderHandle providerHandle)
	{
		if (application->FlowState() != Application::FlowState::StartingUp && application->FlowState() != Application::FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Input provider can be removed only on start-up or shut-down");
		}

		if (const std::size_t index = providers.IndexOf(providerHandle); index < providers.Size()) [[likely]]
		{
			const char* const providerName = typeid(providers.Provider(index)).name();
			providers.Remove(index);
			PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' provider removed. Handle: '0x{:X}'.", providerName, providerHandle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Input provider not found");
		}
	}

	float RawInputService::Value(const AxisId axis) const noexcept
	{
		return devices.Value(axis);
	}

	float RawInputService::Value(const AxisId axis, const DeviceHandle deviceHandle) const noexcept
	{
		return devices.Value(axis, deviceHandle);
	}

	DeviceHandle RawInputService::LastInputDevice() const noexcept
	{
		return lastInputDevice;
	}

	std::size_t RawInputService::DeviceCount() const noexcept
	{
		return devices.Size();
	}

	DeviceHandle RawInputService::Device(const std::size_t index) const
	{
		if (index >= devices.Size()) [[unlikely]]
		{
			throw std::out_of_range("Index is out of range");
		}

		return devices.Handle(index);
	}

	bool RawInputService::IsValid(const DeviceHandle deviceHandle) const noexcept
	{
		return devices.IndexOf(deviceHandle) < devices.Size();
	}

	bool RawInputService::IsConnected(const DeviceHandle deviceHandle) const
	{
		if (const std::size_t index = devices.IndexOf(deviceHandle); index < devices.Size()) [[likely]]
		{
			return devices.IsConnected(index);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	std::string_view RawInputService::DeviceName(const DeviceHandle deviceHandle) const
	{
		if (const std::size_t index = devices.IndexOf(deviceHandle); index < devices.Size()) [[likely]]
		{
			return devices.DeviceName(index);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	DeviceTypeId RawInputService::DeviceType(const DeviceHandle deviceHandle) const
	{
		if (const std::size_t index = devices.IndexOf(deviceHandle); index < devices.Size()) [[likely]]
		{
			return devices.DeviceType(index);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	std::span<const std::type_index> RawInputService::FeatureTypes(const DeviceHandle deviceHandle) const
	{
		if (const std::size_t index = devices.IndexOf(deviceHandle); index < devices.Size()) [[likely]]
		{
			return devices.DeviceFeatures(index).FeatureTypes();
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	void* RawInputService::FindFeature(const DeviceHandle deviceHandle, const std::type_index type)
	{
		if (const std::size_t index = devices.IndexOf(deviceHandle); index < devices.Size()) [[likely]]
		{
			const DeviceFeatureContainer& features = devices.DeviceFeatures(index);
			const std::size_t featureIndex = features.IndexOf(type);

			return featureIndex < features.Size() ? features.Feature(featureIndex) : nullptr;
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	const void* RawInputService::FindFeature(const DeviceHandle deviceHandle, const std::type_index type) const
	{
		if (const std::size_t index = devices.IndexOf(deviceHandle); index < devices.Size()) [[likely]]
		{
			const DeviceFeatureContainer& features = devices.DeviceFeatures(index);
			const std::size_t featureIndex = features.IndexOf(type);

			return featureIndex < features.Size() ? features.Feature(featureIndex) : nullptr;
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Device not found");
		}
	}

	AxisId RawInputService::Hash(const Axis& axis)
	{
		const std::uint32_t hash = Hash::FNV1a32(axis.Path());
		auto axisId = AxisId{.hash = hash};

		if (const auto position = axisHashMap.find(hash); position != axisHashMap.cend())
		{
			std::vector<Axis>& axes = position->second;
			const auto axisPosition = std::ranges::find(axes, axis);

			if (axisPosition == axes.cend()) [[unlikely]]
			{
				if (axes.size() >= std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
				{
					throw std::bad_alloc();
				}

				axes.push_back(axis);
			}

			axisId.index = static_cast<std::uint32_t>(axisPosition - axes.cbegin());
		}
		else
		{
			axisHashMap[hash] = std::vector<Axis>{ axis };
			axisId.index = 0u;
		}

		return axisId;
	}

	const Axis& RawInputService::Unhash(const AxisId axisId) const
	{
		if (const auto position = axisHashMap.find(axisId.hash); position != axisHashMap.cend()) [[likely]]
		{
			if (axisId.index < position->second.size()) [[likely]]
			{
				return position->second[axisId.index];
			}
		}

		throw std::invalid_argument("Invalid axis ID");
	}

	bool RawInputService::IsValid(const AxisId axisId) const noexcept
	{
		const auto position = axisHashMap.find(axisId.hash);
		return position != axisHashMap.cend() && axisId.index < position->second.size();
	}

	DeviceTypeId RawInputService::Hash(const class DeviceType& deviceType)
	{
		const auto deviceTypeId = DeviceTypeId{.hash = Hash::FNV1a64(deviceType.Type())};

		if (const auto position = deviceTypeHashMap.find(deviceTypeId); position != deviceTypeHashMap.cend())
		{
			if (position->second != deviceType) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			deviceTypeHashMap[deviceTypeId] = deviceType;
		}

		return deviceTypeId;
	}

	const DeviceType& RawInputService::Unhash(const DeviceTypeId deviceTypeId)
	{
		if (const auto position = deviceTypeHashMap.find(deviceTypeId); position != deviceTypeHashMap.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Invalid device type ID");
	}

	bool RawInputService::IsValid(const DeviceTypeId deviceTypeId) const noexcept
	{
		return deviceTypeHashMap.contains(deviceTypeId);
	}

	void RawInputService::AddObserver(IDeviceObserver& observer)
	{
		deviceObservers.push_back(&observer);
	}

	void RawInputService::RemoveObserver(IDeviceObserver& observer) noexcept
	{
		if (const auto position = std::ranges::find(deviceObservers, &observer); position != deviceObservers.cend()) [[likely]]
		{
			deviceObservers.erase(position);
		}
		else [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove input device observer that hadn't been added.");
		}
	}

	void RawInputService::AddObserver(IRawInputObserver& observer)
	{
		inputObservers.push_back(&observer);
	}

	void RawInputService::RemoveObserver(IRawInputObserver& observer) noexcept
	{
		if (const auto position = std::ranges::find(inputObservers, &observer); position != inputObservers.cend()) [[likely]]
		{
			inputObservers.erase(position);
		}
		else [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove raw input observer that hadn't been added.");
		}
	}

	void RawInputService::Begin(std::size_t& count)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning input providers...");
		for (std::size_t i = 0uz; i < providers.Size(); ++i)
		{
			IInputProvider& provider = providers.Provider(i);

			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' input provider...", typeid(provider).name());
				provider.Begin();
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' input provider done.", typeid(provider).name());
				++count;
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On beginning '{}' input provider.", typeid(provider).name());
				throw;
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning input providers done.");
	}

	void RawInputService::End(const std::size_t count) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending input providers...");
		for (std::size_t i = count; i-- > 0uz; )
		{
			IInputProvider& provider = providers.Provider(i);
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' input provider...", typeid(provider).name());
				provider.End();
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' input provider done.", typeid(provider).name());
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On ending '{}' input provider.", typeid(provider).name());
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending input providers done.");
	}

	void RawInputService::TickProviders()
	{
		for (std::size_t i = 0uz; i < providers.Size(); ++i)
		{
			IInputProvider& provider = providers.Provider(i);
			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking '{}' provider.", typeid(provider).name());
				provider.Tick();
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On ticking '{}' provider.", typeid(provider).name());
				throw;
			}
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
					devices.IsConnected(devices.IndexOf(device), connectionEvent.isConnected);
					ObserveConnection(device, connectionEvent);
				}
			}, event);
		}
	}

	void RawInputService::ObserveConnection(const DeviceHandle device, const ConnectionEvent& connection) const noexcept
	{
		for (IDeviceObserver* const observer : deviceObservers)
		{
			try
			{
				observer->OnDeviceConnectionChanged(device, connection);
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On calling '{}' device observer on connection change.", typeid(*observer).name());
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
				PONY_LOG_X(application->Logger(), std::current_exception(), "On calling '{}' raw input observer.", typeid(*observer).name());
			}
		}
	}

	void RawInputService::ObserveDeviceAdded(const DeviceHandle device) const noexcept
	{
		for (IDeviceObserver* const observer : deviceObservers)
		{
			try
			{
				observer->OnDeviceAdded(device);
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On calling '{}' device observer on device added.", typeid(*observer).name());
			}
		}
	}

	void RawInputService::ObserveDeviceRemoved(const DeviceHandle device) const noexcept
	{
		for (IDeviceObserver* const observer : deviceObservers)
		{
			try
			{
				observer->OnDeviceRemoved(device);
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On calling '{}' device observer on device removed.", typeid(*observer).name());
			}
		}
	}
}

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

export module PonyEngine.Application.Impl:ServiceContainer;

import std;

import PonyEngine.Application.Ext;

import :InterfaceContainer;
import :TickableServiceInfo;

export namespace PonyEngine::Application
{
	class ServiceContainer
	{
	public:
		[[nodiscard("Pure constructor")]]
		ServiceContainer() noexcept = default;
		ServiceContainer(const ServiceContainer& other) = default;
		ServiceContainer(ServiceContainer&& other) = default;

		~ServiceContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t IndexOf(ServiceHandle handle) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const IService& service) const noexcept;

		[[nodiscard("Pure function")]]
		ServiceHandle Handle(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		IService& Service(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		const TickableServiceInfo& TickableService(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		const InterfaceContainer& Interfaces(std::size_t index) const noexcept;

		[[nodiscard("Pure function")]]
		bool ContainsInterface(std::type_index type) const noexcept;

		void Add(ServiceHandle handle, const ServiceData& serviceData);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		ServiceContainer& operator =(const ServiceContainer& other) = default;
		ServiceContainer& operator =(ServiceContainer&& other) = default;

	private:
		std::vector<ServiceHandle> serviceHandles; ///< Service handles.
		std::vector<std::shared_ptr<IService>> services; ///< Services.
		std::vector<TickableServiceInfo> tickableServices; ///< Tickable services.
		std::vector<InterfaceContainer> interfaces; ///< Service interfaces.
	};
}

namespace PonyEngine::Application
{
	std::size_t ServiceContainer::Size() const noexcept
	{
		return serviceHandles.size();
	}

	std::size_t ServiceContainer::IndexOf(const ServiceHandle handle) const noexcept
	{
		return std::ranges::find(serviceHandles, handle) - serviceHandles.cbegin();
	}

	std::size_t ServiceContainer::IndexOf(const IService& service) const noexcept
	{
		return std::ranges::find_if(services, [&](const std::shared_ptr<IService>& s) { return s.get() == &service; }) - services.cbegin();
	}

	ServiceHandle ServiceContainer::Handle(const std::size_t index) const noexcept
	{
		return serviceHandles[index];
	}

	IService& ServiceContainer::Service(const std::size_t index) const noexcept
	{
		return *services[index];
	}

	const TickableServiceInfo& ServiceContainer::TickableService(const std::size_t index) const noexcept
	{
		return tickableServices[index];
	}

	const InterfaceContainer& ServiceContainer::Interfaces(const std::size_t index) const noexcept
	{
		return interfaces[index];
	}

	bool ServiceContainer::ContainsInterface(const std::type_index type) const noexcept
	{
		for (const InterfaceContainer& interfaceContainer : interfaces)
		{
			if (interfaceContainer.IndexOf(type) < interfaceContainer.Size())
			{
				return true;
			}
		}

		return false;
	}

	void ServiceContainer::Add(const ServiceHandle handle, const ServiceData& serviceData)
	{
		assert(serviceData.service && "The service is nullptr.");

		serviceHandles.push_back(handle);
		try
		{
			services.push_back(serviceData.service);
			try
			{
				tickableServices.push_back(TickableServiceInfo{.tickableService = serviceData.tickableService, .tickOrder = serviceData.tickOrder});
				try
				{
					interfaces.push_back(InterfaceContainer(serviceData.publicInterfaces.size()));

					try
					{
						InterfaceContainer& interfaceContainer = interfaces.back();
						for (const auto [type, interface] : serviceData.publicInterfaces)
						{
							interfaceContainer.Add(type, interface);
						}
					}
					catch (...)
					{
						interfaces.pop_back();
						throw;
					}
				}
				catch (...)
				{
					tickableServices.pop_back();
					throw;
				}
			}
			catch (...)
			{
				services.pop_back();
				throw;
			}
		}
		catch (...)
		{
			serviceHandles.pop_back();
			throw;
		}
	}

	void ServiceContainer::Remove(const std::size_t index) noexcept
	{
		interfaces.erase(interfaces.cbegin() + index);
		tickableServices.erase(tickableServices.cbegin() + index);
		services.erase(services.cbegin() + index);
		serviceHandles.erase(serviceHandles.cbegin() + index);
	}

	void ServiceContainer::Clear() noexcept
	{
		serviceHandles.clear();
		services.clear();
		tickableServices.clear();
		interfaces.clear();
	}
}

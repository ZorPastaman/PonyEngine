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
	/// @brief Service container.
	class ServiceContainer
	{
	public:
		[[nodiscard("Pure constructor")]]
		ServiceContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		ServiceContainer(const ServiceContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		ServiceContainer(ServiceContainer&& other) noexcept = default;

		~ServiceContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds an index of the @p handle.
		/// @param handle Service handle.
		/// @return Service handle index or @p Size if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(ServiceHandle handle) const noexcept;
		/// @brief Finds an index of the @p service.
		/// @param service Service.
		/// @return Service index or @p Size if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const IService& service) const noexcept;

		/// @brief Gets a service handle at the @p index.
		/// @param index Handle index.
		/// @return Service handle.
		[[nodiscard("Pure function")]]
		ServiceHandle Handle(std::size_t index) const noexcept;
		/// @brief Gets a service at the @p index.
		/// @param index Service index.
		/// @return Service.
		[[nodiscard("Pure function")]]
		IService& Service(std::size_t index) const noexcept;
		/// @brief Gets a tickable service info vector at the @p index.
		/// @param index Service index.
		/// @return Tickable service info vector.
		[[nodiscard("Pure function")]]
		std::vector<TickableServiceInfo>& TickableServices(std::size_t index) noexcept;
		/// @brief Gets a tickable service info vector at the @p index.
		/// @param index Service index.
		/// @return Tickable service info vector.
		[[nodiscard("Pure function")]]
		const std::vector<TickableServiceInfo>& TickableServices(std::size_t index) const noexcept;
		/// @brief Gets interfaces at the @p index.
		/// @param index Interface set index.
		/// @return Interfaces.
		[[nodiscard("Pure function")]]
		InterfaceContainer& Interfaces(std::size_t index) noexcept;
		/// @brief Gets interfaces at the @p index.
		/// @param index Interface set index.
		/// @return Interfaces.
		[[nodiscard("Pure function")]]
		const InterfaceContainer& Interfaces(std::size_t index) const noexcept;

		/// @brief Adds data.
		/// @param handle Service handle.
		/// @param service Service.
		/// @return Service index.
		std::size_t Add(ServiceHandle handle, const std::shared_ptr<IService>& service);
		/// @brief Removes data.
		/// @param index Data index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears data.
		void Clear() noexcept;

		ServiceContainer& operator =(const ServiceContainer& other) = delete;
		ServiceContainer& operator =(ServiceContainer&& other) noexcept = default;

	private:
		std::vector<ServiceHandle> serviceHandles; ///< Service handles.
		std::vector<std::shared_ptr<IService>> services; ///< Services.
		std::vector<std::vector<TickableServiceInfo>> tickableServices; ///< Tickable services.
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

	std::vector<TickableServiceInfo>& ServiceContainer::TickableServices(const std::size_t index) noexcept
	{
		return tickableServices[index];
	}

	const std::vector<TickableServiceInfo>& ServiceContainer::TickableServices(const std::size_t index) const noexcept
	{
		return tickableServices[index];
	}

	InterfaceContainer& ServiceContainer::Interfaces(const std::size_t index) noexcept
	{
		return interfaces[index];
	}

	const InterfaceContainer& ServiceContainer::Interfaces(const std::size_t index) const noexcept
	{
		return interfaces[index];
	}

	std::size_t ServiceContainer::Add(const ServiceHandle handle, const std::shared_ptr<IService>& service)
	{
		assert(service && "The service is nullptr.");

		serviceHandles.push_back(handle);
		try
		{
			services.push_back(service);
			try
			{
				tickableServices.push_back(std::vector<TickableServiceInfo>());
				try
				{
					interfaces.push_back(InterfaceContainer());
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

		return Size() - 1uz;
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

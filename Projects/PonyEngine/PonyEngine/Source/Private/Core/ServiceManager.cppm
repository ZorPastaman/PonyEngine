/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:ServiceManager;

import <algorithm>;
import <cassert>;
import <utility>;
import <vector>;

import PonyEngine.Core;

namespace PonyEngine::Core
{
	/// @brief Holder of services.
	export class ServiceManager final : public IServiceManager
	{
	public:
		/// @brief Creates a @p ServiceManager.
		[[nodiscard("Pure constructor")]]
		inline ServiceManager() noexcept;
		ServiceManager(const ServiceManager&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		inline ServiceManager(ServiceManager&& other) noexcept;

		inline virtual ~ServiceManager() noexcept = default;

		inline virtual void AddService(IService* service) override;
		virtual void RemoveService(IService* service) override;

		[[nodiscard("Pure function")]]
		virtual IService* FindService(const std::function<bool(const IService*)>& predicate) const override;

		/// @brief Move assignment.
		/// @param other Move source.
		/// @return @a This.
		inline ServiceManager& operator =(ServiceManager&& other) noexcept;

	private:
		std::vector<IService*> m_services; /// @brief Services.
	};

	inline ServiceManager::ServiceManager() noexcept :
		m_services{}
	{
	}

	inline ServiceManager::ServiceManager(ServiceManager&& other) noexcept :
		m_services(std::move(other.m_services))
	{
	}

	inline void ServiceManager::AddService(IService* const service)
	{
		assert((service != nullptr));
		m_services.push_back(service);
	}

	void ServiceManager::RemoveService(IService* const service)
	{
		const std::vector<IService*>::const_iterator position = std::find(m_services.cbegin(), m_services.cend(), service);

		if (position != m_services.cend()) [[likely]]
		{
			m_services.erase(position);
		}
	}

	IService* ServiceManager::FindService(const std::function<bool(const IService*)>& predicate) const
	{
		for (IService* const service : m_services)
		{
			if (predicate(service))
			{
				return service;
			}
		}

		return nullptr;
	}

	inline ServiceManager& ServiceManager::operator =(ServiceManager&& other) noexcept
	{
		m_services = std::move(other.m_services);

		return *this;
	}
}

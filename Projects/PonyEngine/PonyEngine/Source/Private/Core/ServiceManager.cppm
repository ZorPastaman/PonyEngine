/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:ServiceManager;

import <utility>;
import <vector>;

import PonyEngine.Core;

namespace PonyEngine::Core
{
	export class ServiceManager final : public IServiceManager
	{
	public:
		ServiceManager() noexcept;
		ServiceManager(ServiceManager&& other) noexcept;

		virtual ~ServiceManager() noexcept = default;

		virtual void AddService(IService& service) override;
		virtual void RemoveService(IService& service) override;

		virtual IService* FindService(const std::function<bool(const IService&)>& predicate) const override;

	private:
		std::vector<IService*> m_services;
	};

	ServiceManager::ServiceManager() noexcept :
		m_services{}
	{
	}

	ServiceManager::ServiceManager(ServiceManager&& other) noexcept :
		m_services(std::move(m_services))
	{
	}

	void ServiceManager::AddService(IService& service)
	{
		m_services.push_back(&service);
	}

	void ServiceManager::RemoveService(IService& service)
	{
		const std::vector<IService*>::iterator position = std::find(m_services.begin(), m_services.end(), &service);

		if (position != m_services.end()) [[likely]]
		{
			m_services.erase(position);
		}
	}

	IService* ServiceManager::FindService(const std::function<bool(const IService&)>& predicate) const
	{
		for (IService* const service : m_services)
		{
			if (predicate(*service))
			{
				return service;
			}
		}

		return nullptr;
	}
}

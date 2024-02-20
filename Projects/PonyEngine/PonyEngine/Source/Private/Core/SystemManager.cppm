/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:SystemManager;

import <utility>;
import <vector>;

import PonyEngine.Core;

namespace PonyEngine::Core
{
	export class SystemManager final : public ISystemManager
	{
	public:
		SystemManager() noexcept;
		SystemManager(SystemManager&& other) noexcept;

		virtual ~SystemManager() noexcept = default;

		virtual void AddSystem(ISystem& system) noexcept override;
		virtual void RemoveSystem(ISystem& system) noexcept override;

		virtual ISystem* FindSystem(const std::function<bool(const ISystem&)>& predicate) override;

		void Tick() const;

	private:
		std::vector<ISystem*> m_systems;
	};

	SystemManager::SystemManager() noexcept :
		m_systems{}
	{
	}

	SystemManager::SystemManager(SystemManager&& other) noexcept :
		m_systems(std::move(other.m_systems))
	{
	}

	void SystemManager::AddSystem(ISystem& system) noexcept
	{
		m_systems.push_back(&system);
	}

	void SystemManager::RemoveSystem(ISystem& system) noexcept
	{
		const std::vector<ISystem*>::iterator position = std::find(m_systems.begin(), m_systems.end(), &system);

		if (position != m_systems.end()) [[likely]]
		{
			m_systems.erase(position);
		}
	}

	ISystem* SystemManager::FindSystem(const std::function<bool(const ISystem&)>& predicate)
	{
		for (ISystem* const system : m_systems)
		{
			if (predicate(*system))
			{
				return system;
			}
		}

		return nullptr;
	}

	void SystemManager::Tick() const
	{
		for (ISystem* const system : m_systems)
		{
			system->Tick();
		}
	}
}

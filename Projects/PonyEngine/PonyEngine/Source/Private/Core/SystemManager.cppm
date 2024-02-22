/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:SystemManager;

import <algorithm>;
import <cassert>;
import <utility>;
import <vector>;

import PonyEngine.Core;

namespace PonyEngine::Core
{
	/// @brief Holder and ticker of systems.
	export class SystemManager final : public ISystemManager
	{
	public:
		/// @brief Creates a @p SystemManager.
		[[nodiscard("Pure constructor")]]
		inline SystemManager() noexcept;
		SystemManager(const SystemManager&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		inline SystemManager(SystemManager&& other) noexcept;

		inline virtual ~SystemManager() noexcept = default;

		inline virtual void AddSystem(ISystem* system) override;
		virtual void RemoveSystem(ISystem* system) override;

		[[nodiscard("Pure function")]]
		virtual ISystem* FindSystem(const std::function<bool(const ISystem*)>& predicate) const override;

		/// @brief Ticks the systems.
		void Tick() const;

		/// @brief Move assignment.
		/// @param other Move source.
		/// @return @a This.
		inline SystemManager& operator =(SystemManager&& other) noexcept;

	private:
		std::vector<ISystem*> m_systems; /// @brief Systems.
	};

	inline SystemManager::SystemManager() noexcept :
		m_systems{}
	{
	}

	inline SystemManager::SystemManager(SystemManager&& other) noexcept :
		m_systems(std::move(other.m_systems))
	{
	}

	inline void SystemManager::AddSystem(ISystem* const system)
	{
		assert((system != nullptr));
		m_systems.push_back(system);
	}

	void SystemManager::RemoveSystem(ISystem* const system)
	{
		const std::vector<ISystem*>::const_iterator position = std::find(m_systems.cbegin(), m_systems.cend(), system);

		if (position != m_systems.cend()) [[likely]]
		{
			m_systems.erase(position);
		}
	}

	ISystem* SystemManager::FindSystem(const std::function<bool(const ISystem*)>& predicate) const
	{
		for (ISystem* const system : m_systems)
		{
			if (predicate(system))
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

	inline SystemManager& SystemManager::operator =(SystemManager&& other) noexcept
	{
		m_systems = std::move(other.m_systems);

		return *this;
	}
}

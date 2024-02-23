/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ISystemManager;

import <functional>;

import :ISystem;

namespace PonyEngine::Core
{
	/// @brief Holder and ticker of systems.
	export class ISystemManager
	{
	public:
		/// @brief Finds a system by the @p predicate.
		/// @param predicate Predicate.
		/// @return Found system. It's nullptr if no system is found.
		virtual ISystem* FindSystem(const std::function<bool(const ISystem*)>& predicate) const = 0;

	protected:
		inline virtual ~ISystemManager() noexcept = default;
	};

	/// @brief Finds a system of the type @p T in the @p systemManager.
	/// @tparam T System type to find.
	/// @param systemManager System manager.
	/// @return Found system. It's nullptr if no system is found.
	export template<typename T>
	T* FindSystem(const ISystemManager& systemManager);

	template<typename T>
	T* FindSystem(const ISystemManager& systemManager)
	{
		ISystem* const system = systemManager.FindSystem([](const ISystem* const system) { return dynamic_cast<const T*>(system) != nullptr; });
		return dynamic_cast<T*>(system);
	}
}

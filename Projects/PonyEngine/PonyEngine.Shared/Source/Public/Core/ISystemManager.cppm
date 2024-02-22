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
import <type_traits>;

import :ISystem;

namespace PonyEngine::Core
{
	/// @brief Holder and ticker of systems.
	export class ISystemManager
	{
	public:
		/// @brief Adds the @p system.
		/// @param system System to add. Mustn't be nullptr. Mustn't be already added.
		virtual void AddSystem(ISystem* system) = 0;
		/// @brief Removes the @p system.
		/// @param system System to remove.
		virtual void RemoveSystem(ISystem* system) = 0;

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
	T* FindSystem(const ISystemManager& systemManager) requires std::is_convertible_v<ISystem*, T*>;

	template<typename T>
	T* FindSystem(const ISystemManager& systemManager)
	{
		ISystem* const service = systemManager.FindSystem([](const ISystem* const system) {return dynamic_cast<const T*>(system) != nullptr;});
		return system != nullptr ? dynamic_cast<T*>(system) : nullptr;
	}
}

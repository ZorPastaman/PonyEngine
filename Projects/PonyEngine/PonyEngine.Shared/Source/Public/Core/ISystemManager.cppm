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
	export class ISystemManager
	{
	public:
		virtual void AddSystem(ISystem& system) noexcept = 0;
		virtual void RemoveSystem(ISystem& system) noexcept = 0;

		virtual ISystem* FindSystem(const std::function<bool(const ISystem&)>& predicate) = 0;

	protected:
		virtual ~ISystemManager() noexcept = default;
	};

	export template<typename T>
	T* FindSystem(const ISystemManager& systemManager) requires std::is_convertible_v<ISystem*, T*>;

	template<typename T>
	T* FindSystem(const ISystemManager& systemManager)
	{
		ISystem* const service = systemManager.FindSystem([](const ISystem& system) {return dynamic_cast<const T*>(&system) != nullptr;});
		return system != nullptr ? static_cast<T*>(system) : nullptr;
	}
}

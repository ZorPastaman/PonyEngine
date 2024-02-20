/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:IServiceManager;

import <functional>;
import <type_traits>;

import :IService;

namespace PonyEngine::Core
{
	export class IServiceManager
	{
	public:
		virtual void AddService(IService& service) = 0;
		virtual void RemoveService(IService& service) = 0;

		virtual IService* FindService(const std::function<bool(const IService&)>& predicate) const = 0;

	protected:
		virtual ~IServiceManager() noexcept = default;
	};

	export template<typename T>
	T* FindService(const IServiceManager& serviceManager) requires std::is_convertible_v<IService*, T*>;

	template<typename T>
	T* FindService(const IServiceManager& serviceManager)
	{
		IService* const service = serviceManager.FindService([](const IService& service) {return dynamic_cast<const T*>(&service) != nullptr;});
		return service != nullptr ? static_cast<T*>(service) : nullptr;
	}
}

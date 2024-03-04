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
	/// @brief Holder of services.
	export class IServiceManager
	{
	public:
		/// @brief Finds a service by the @p predicate.
		/// @param predicate Predicate.
		/// @return Found service. It's nullptr if no service is found.
		[[nodiscard("Pure function")]]
		virtual IService* FindService(const std::function<bool(const IService*)>& predicate) const = 0;

	protected:
		inline virtual ~IServiceManager() noexcept = default;
	};

	/// @brief Finds a service of the type @p T in the @p serviceManager.
	/// @tparam T Service type to find.
	/// @param serviceManager Service manager.
	/// @return Found service. It's nullptr if no service is found.
	export template<typename T> [[nodiscard("Pure function")]]
	T* FindService(const IServiceManager& serviceManager);

	template<typename T>
	T* FindService(const IServiceManager& serviceManager)
	{
		IService* const service = serviceManager.FindService([](const IService* const service) { return dynamic_cast<const T*>(service) != nullptr; });
		return dynamic_cast<T*>(service);
	}
}

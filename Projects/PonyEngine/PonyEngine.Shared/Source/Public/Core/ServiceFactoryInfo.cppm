/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ServiceFactoryInfo;

import <functional>;

import :IEngine;
import :IService;

namespace PonyEngine::Core
{
	/// @brief Service factory functions wrapper.
	export struct ServiceFactoryInfo final
	{
	public:
		/// @brief Creates a @p ServiceFactoryInfo.
		/// @param createFunction Create function.
		/// @param destroyFunction Destroy function.
		[[nodiscard("Pure constructor")]]
		inline ServiceFactoryInfo(const std::function<IService*(IEngine&)>& createFunction, const std::function<void(IService*)>& destroyFunction);
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		inline ServiceFactoryInfo(const ServiceFactoryInfo& other);
		ServiceFactoryInfo(ServiceFactoryInfo&&) = delete;

		inline ~ServiceFactoryInfo() noexcept = default;

		const std::function<IService*(IEngine&)> createFunction; /// @brief Create function.
		const std::function<void(IService*)> destroyFunction; /// @brief Destroy function.
	};

	inline ServiceFactoryInfo::ServiceFactoryInfo(const std::function<IService*(IEngine&)>& createFunction, const std::function<void(IService*)>& destroyFunction) :
		createFunction(createFunction),
		destroyFunction(destroyFunction)
	{
	}

	inline ServiceFactoryInfo::ServiceFactoryInfo(const ServiceFactoryInfo& other) :
		createFunction(other.createFunction),
		destroyFunction(other.destroyFunction)
	{
	}
}

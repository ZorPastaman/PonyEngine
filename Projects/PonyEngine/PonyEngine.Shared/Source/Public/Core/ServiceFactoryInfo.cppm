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
	export struct ServiceFactoryInfo final
	{
	public:
		[[nodiscard("Pure constructor")]]
		inline ServiceFactoryInfo(const std::function<IService*(IEngine&)>& createFunction, const std::function<void(IService*)>& destroyFunction);
		[[nodiscard("Pure constructor")]]
		inline ServiceFactoryInfo(const ServiceFactoryInfo& other);

		inline ~ServiceFactoryInfo() noexcept = default;

		const std::function<IService*(IEngine&)> createFunction;
		const std::function<void(IService*)> destroyFunction;
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

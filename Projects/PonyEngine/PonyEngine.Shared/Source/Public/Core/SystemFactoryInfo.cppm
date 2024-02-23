/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:SystemFactoryInfo;

import <functional>;

import :IEngine;
import :ISystem;

namespace PonyEngine::Core
{
	export struct SystemFactoryInfo final
	{
	public:
		[[nodiscard("Pure constructor")]]
		inline SystemFactoryInfo(const std::function<ISystem*(IEngine&)>& createFunction, const std::function<void(ISystem*)>& destroyFunction);
		[[nodiscard("Pure constructor")]]
		inline SystemFactoryInfo(const SystemFactoryInfo& other);

		inline ~SystemFactoryInfo() noexcept = default;

		const std::function<ISystem*(IEngine&)> createFunction;
		const std::function<void(ISystem*)> destroyFunction;
	};

	inline SystemFactoryInfo::SystemFactoryInfo(const std::function<ISystem*(IEngine&)>& createFunction, const std::function<void(ISystem*)>& destroyFunction) :
		createFunction(createFunction),
		destroyFunction(destroyFunction)
	{
	}

	inline SystemFactoryInfo::SystemFactoryInfo(const SystemFactoryInfo& other) :
		createFunction(other.createFunction),
		destroyFunction(other.destroyFunction)
	{
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <memory>
#include <string_view>

export module PonyEngine.Log.Core:LoggerFactory;

import PonyEngine.Core;
import PonyEngine.Log;

import :Logger;

export namespace PonyEngine::Log::Core
{
	/// @brief Logger factory.
	class LoggerFactory final : public PonyEngine::Core::IFactory<ILogger>
	{
	public:
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ILogger> Create(const PonyEngine::Core::IModuleContext& context) override;
	};
}

namespace PonyEngine::Log::Core
{
	std::shared_ptr<ILogger> LoggerFactory::Create(const PonyEngine::Core::IModuleContext& context)
	{
		return std::make_shared<Logger>();
	}
}

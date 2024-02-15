/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:EngineParams;

import <utility>;

export import :LoggerParams;
export import :WindowParams;

namespace PonyEngine::Core
{
	/// @brief Holds engine parameters.
	export struct EngineParams final
	{
	public:
		/// @brief Creates an @p EngineParams.
		[[nodiscard("Pure constructor")]]
		EngineParams();
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		EngineParams(const EngineParams& other);
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		EngineParams(EngineParams&& other);

		~EngineParams() = default;

		LoggerParams loggerParams; /// @brief Logger parameters.
		WindowParams windowParams; /// @brief Window parameters.
	};

	EngineParams::EngineParams() :
		loggerParams(),
		windowParams()
	{
	}

	EngineParams::EngineParams(const EngineParams& other) :
		loggerParams(other.loggerParams),
		windowParams(other.windowParams)
	{
	}

	EngineParams::EngineParams(EngineParams&& other) :
		loggerParams(std::move(other.loggerParams)),
		windowParams(std::move(other.windowParams))
	{
	}
}

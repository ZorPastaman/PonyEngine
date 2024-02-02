/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.EngineParams;

import <utility>;

import PonyEngine.LoggerParams;

namespace PonyEngine
{
	/// @brief Holds engine parameters.
	export struct EngineParams final
	{
	public:
		/// @brief Creates an @p EngineParams.
		EngineParams();
		/// @brief Copy constructor.
		/// @param other Copy source.
		EngineParams(const EngineParams& other);
		/// @brief Move constructor.
		/// @param other Move source.
		EngineParams(EngineParams&& other);

		~EngineParams() = default;

		LoggerParams loggerParams; /// @brief Logger parameters.
	};

	EngineParams::EngineParams() :
		loggerParams()
	{
	}

	EngineParams::EngineParams(const EngineParams& other) :
		loggerParams(other.loggerParams)
	{
	}

	EngineParams::EngineParams(EngineParams&& other) :
		loggerParams(std::move(other.loggerParams))
	{
	}
}

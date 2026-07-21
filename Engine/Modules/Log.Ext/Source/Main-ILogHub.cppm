/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Log.Ext:ILogHub;

import std;

import :ILogger;

export namespace PonyEngine::Log
{
	/// @brief Log hub.
	/// @details It gets a log request, builds a formatted string and sends it to registered loggers.
	class ILogHub
	{
		PONY_INTERFACE_BODY(ILogHub)

		/// @brief Adds the logger.
		/// @param logger Logger to add. Must be unique.
		virtual void AddLogger(ILogger& logger) = 0;
		/// @brief Removes the logger.
		/// @param logger Logger to remove. Must be previously added.
		virtual void RemoveLogger(ILogger& logger) = 0;
	};
}

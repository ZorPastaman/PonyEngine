/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

export module PonyDebug.Log.Windows.Detail:OutputDebugStringSubLogger;

import <exception>;

import PonyDebug.Log.Windows;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger that puts logs into the @p OutputDebugString.
	class OutputDebugStringSubLogger final : public SubLogger
	{
	public:
		/// @brief Creates an @p OutputDebugStringSubLogger.
		/// @param params Output debug string sub-logger parameters.
		[[nodiscard("Pure constructor")]]
		explicit OutputDebugStringSubLogger(const OutputDebugStringSubLoggerParams& params) noexcept;
		OutputDebugStringSubLogger(const OutputDebugStringSubLogger&) = delete;
		OutputDebugStringSubLogger(OutputDebugStringSubLogger&&) = delete;

		virtual ~OutputDebugStringSubLogger() noexcept override = default;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		OutputDebugStringSubLogger& operator =(const OutputDebugStringSubLogger&) = delete;
		OutputDebugStringSubLogger& operator =(OutputDebugStringSubLogger&&) = delete;
	};
}

namespace PonyDebug::Log
{
	OutputDebugStringSubLogger::OutputDebugStringSubLogger(const OutputDebugStringSubLoggerParams&) noexcept
	{
	}

	void OutputDebugStringSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		OutputDebugStringA(logEntry.ToString().data());
	}
}

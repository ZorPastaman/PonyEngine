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

export module PonyDebug.Log.Windows.Implementation:OutputDebugStringSubLogger;

import <exception>;

import PonyDebug.Log.Windows;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger that puts logs into the @p OutputDebugString.
	class OutputDebugStringSubLogger final : public IWindowsSubLogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		OutputDebugStringSubLogger() noexcept = default;
		OutputDebugStringSubLogger(const OutputDebugStringSubLogger&) = delete;
		OutputDebugStringSubLogger(OutputDebugStringSubLogger&&) = delete;

		~OutputDebugStringSubLogger() noexcept = default;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		OutputDebugStringSubLogger& operator =(const OutputDebugStringSubLogger&) = delete;
		OutputDebugStringSubLogger& operator =(OutputDebugStringSubLogger&&) = delete;

		static constexpr auto StaticName = "PonyDebug::Log::OutputDebugStringSubLogger"; ///< Class name.
	};

	void OutputDebugStringSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		OutputDebugStringA(logEntry.ToString());
	}

	const char* OutputDebugStringSubLogger::Name() const noexcept
	{
		return StaticName;
	}
}

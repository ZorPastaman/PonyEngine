/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Log.Windows.Implementation:OutputDebugStringSubLogger;

import <exception>;

import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger that puts logs into the @p OutputDebugString.
	class OutputDebugStringSubLogger final : public ISubLogger
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

		static constexpr auto StaticName = "PonyEngine::Log::OutputDebugStringSubLogger"; ///< Class name.
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

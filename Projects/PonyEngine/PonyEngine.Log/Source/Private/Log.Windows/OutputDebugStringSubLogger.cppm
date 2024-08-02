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
		virtual const char* GetName() const noexcept override;

		OutputDebugStringSubLogger& operator =(const OutputDebugStringSubLogger&) = delete;
		OutputDebugStringSubLogger& operator =(OutputDebugStringSubLogger&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Log::OutputDebugStringSubLogger"; ///< Class name.
	};

	void OutputDebugStringSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			OutputDebugStringA(logEntry.ToString());
		}
		catch (std::exception& e)
		{
			PONY_CONSOLE_E(e, "On writing to the Windows console.");
		}
	}

	const char* OutputDebugStringSubLogger::GetName() const noexcept
	{
		return StaticName;
	}
}
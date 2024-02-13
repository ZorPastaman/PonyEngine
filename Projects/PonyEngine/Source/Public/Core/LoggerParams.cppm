/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:LoggerParams;

import <filesystem>;
import <utility>;
import <vector>;

import PonyEngine.Debug.Log.ISubLogger;

#pragma warning(disable:4251) // It's a requirement to build everything in one solution with the same parameters. So, no worry here.

namespace PonyEngine::Core
{
	/// @brief Holds engine logger parameters.
	export struct __declspec(dllexport) LoggerParams final
	{
	public:
		/// @brief Creates a @p LoggerParams.
		[[nodiscard("Pure constructor")]]
		LoggerParams();
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		LoggerParams(const LoggerParams& other);
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		LoggerParams(LoggerParams&& other);

		~LoggerParams() = default;

		std::filesystem::path logFilePath; /// @brief Path to a log file. It's used only if the @p addLogFileSubLogger is true. The default value is Log.log.
		std::vector<Debug::Log::ISubLogger*> subLoggers; /// @brief Collection of sub-loggers added to a logger on start. Their lifetimes won't be controlled by the engine.
		bool addConsoleSubLogger; /// @brief If it's @a true, adds a sub-logger that prints logs to a console. The default value is @a true.
		bool addLogFileSubLogger; /// @brief If it's @a true, adds a sub-logger that prints logs to a file which path is set in the @p logFilePath. The default value is @a true.
	};

	LoggerParams::LoggerParams() :
		logFilePath("Log.log"),
		subLoggers{},
		addConsoleSubLogger{true},
		addLogFileSubLogger{true}
	{
	}

	LoggerParams::LoggerParams(const LoggerParams& other) :
		logFilePath(other.logFilePath),
		subLoggers(other.subLoggers),
		addConsoleSubLogger{other.addConsoleSubLogger},
		addLogFileSubLogger{other.addLogFileSubLogger}
	{
	}

	LoggerParams::LoggerParams(LoggerParams&& other) :
		logFilePath(std::move(other.logFilePath)),
		subLoggers(std::move(other.subLoggers)),
		addConsoleSubLogger{other.addConsoleSubLogger},
		addLogFileSubLogger{other.addLogFileSubLogger}
	{
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.LoggerParams;

import <filesystem>;
import <vector>;

import PonyEngine.Debug.Log.ILogger;
import PonyEngine.Debug.Log.ISubLogger;
import PonyEngine.Factories.IEngineFeatureFactory;

namespace PonyEngine
{
	/// <summary>
	/// Holds parameters to set an engine logger.
	/// </summary>
	export struct LoggerParams final
	{
	public:
		/// <summary>
		/// Path to a log file. It's used only if <see cref="addLogFileLoggerEntry"/> is true.
		/// </summary>
		std::filesystem::path logFilePath{"Log.log"};
		/// <summary>
		/// Collection of logger entry factories. The produced logger entries lifetimes will be controlled by the engine.
		/// </summary>
		std::vector<Factories::IEngineFeatureFactory<Debug::Log::ISubLogger>*> subLoggerFactories{};
		/// <summary>
		/// Collection of legger entries. Their lifetimes won't be controlled by the engine.
		/// </summary>
		std::vector<Debug::Log::ISubLogger*> subLoggers{};
		/// <summary>
		/// Logger factory. The produced logger lifetime is controlled by the engine.
		/// </summary>
		Factories::IEngineFeatureFactory<Debug::Log::ILogger>* loggerFactory{nullptr};
		/// <summary>
		/// If it's true, adds a logger entry that prints logs to a console.
		/// </summary>
		bool addConsoleSubLogger{true};
		/// <summary>
		/// If it's true, adds a logger entry that prints logs to a file which path is set in <see cref="logFilePath"/>.
		/// </summary>
		bool addLogFileLoggerEntry{true};
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.StandardOutputLoggerEntry;

import <iostream>;

import PonyEngine.Debug.ILoggerEntry;

namespace PonyEngine::Debug
{
	/// <summary>
	/// Logger entry that sends logs to std::cout, std::clog and std::cerr.
	/// </summary>
	export class StandardOutputLoggerEntry final : public ILoggerEntry
	{
	public:
		StandardOutputLoggerEntry() noexcept = default;
		StandardOutputLoggerEntry(const StandardOutputLoggerEntry&) = delete;
		StandardOutputLoggerEntry(StandardOutputLoggerEntry&&) = delete;

		virtual ~StandardOutputLoggerEntry() noexcept = default;

		virtual void Log(const std::string& log) noexcept override;

		virtual void LogWarning(const std::string& log) noexcept override;

		virtual void LogError(const std::string& log) noexcept override;

		virtual void LogException(const std::string& log, const std::exception& exception) noexcept override;
	};

	void StandardOutputLoggerEntry::Log(const std::string& log) noexcept
	{
		std::cout << log << std::endl;
	}

	void StandardOutputLoggerEntry::LogWarning(const std::string& log) noexcept
	{
		std::clog << log << std::endl;
	}

	void StandardOutputLoggerEntry::LogError(const std::string& log) noexcept
	{
		std::cerr << log << std::endl;
	}

	void StandardOutputLoggerEntry::LogException(const std::string& log, const std::exception& exception) noexcept
	{
		std::cerr << log << std::endl;
	}
}

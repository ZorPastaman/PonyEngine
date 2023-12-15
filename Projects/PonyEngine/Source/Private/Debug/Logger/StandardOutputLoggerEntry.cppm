/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.StandardOutputLoggerEntry;

import <string>;
import <exception>;
import <iostream>;

import PonyEngine.Debug.ILoggerEntry;

namespace PonyEngine::Debug
{
	export class StandardOutputLoggerEntry final : public ILoggerEntry
	{
	public:
		StandardOutputLoggerEntry() noexcept = default;
		StandardOutputLoggerEntry(const StandardOutputLoggerEntry&) = delete;
		StandardOutputLoggerEntry(StandardOutputLoggerEntry&&) = delete;

		virtual ~StandardOutputLoggerEntry() noexcept = default;

		virtual void Log(const std::string& log) const noexcept override;

		virtual void LogWarning(const std::string& log) const noexcept override;

		virtual void LogError(const std::string& log) const noexcept override;

		virtual void LogException(const std::string& log, const std::exception& exception) const noexcept override;
	};

	void StandardOutputLoggerEntry::Log(const std::string& log) const noexcept
	{
		std::cout << log << std::endl;
	}

	void StandardOutputLoggerEntry::LogWarning(const std::string& log) const noexcept
	{
		std::clog << log << std::endl;
	}

	void StandardOutputLoggerEntry::LogError(const std::string& log) const noexcept
	{
		std::cerr << log << std::endl;
	}

	void StandardOutputLoggerEntry::LogException(const std::string& log, const std::exception& exception) const noexcept
	{
		std::cerr << log << std::endl;
	}
}

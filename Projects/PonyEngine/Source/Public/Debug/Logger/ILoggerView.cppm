/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.ILoggerView;

import <string>;
import <exception>;

import PonyEngine.Debug.ILoggerEntryView;

namespace PonyEngine::Debug
{
	export class ILoggerView
	{
	public:
		virtual void Log(const std::string& message) const noexcept = 0;

		virtual void LogWarning(const std::string& message) const noexcept = 0;

		virtual void LogError(const std::string& message) const noexcept = 0;

		virtual void LogException(const std::exception& exception) const noexcept = 0;

		virtual void AddLoggerEntry(ILoggerEntryView* loggerEntry) = 0;

		virtual void RemoveLoggerEntry(ILoggerEntryView* loggerEntry) = 0;

	protected:
		virtual ~ILoggerView() noexcept = default;
	};
}

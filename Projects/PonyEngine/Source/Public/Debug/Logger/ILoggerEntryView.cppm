/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.ILoggerEntryView;

import <string>;
import <exception>;

namespace PonyEngine::Debug
{
	export class ILoggerEntryView
	{
	public:
		virtual void Log(const std::string& log) noexcept = 0;

		virtual void LogWarning(const std::string& log) noexcept = 0;

		virtual void LogError(const std::string& log) noexcept = 0;

		virtual void LogException(const std::string& log, const std::exception& exception) noexcept = 0;

	protected:
		virtual ~ILoggerEntryView() noexcept = default;
	};
}

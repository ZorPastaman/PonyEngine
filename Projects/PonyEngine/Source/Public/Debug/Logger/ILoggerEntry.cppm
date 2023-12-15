/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.ILoggerEntry;

import PonyEngine.Debug.ILoggerEntryView;

namespace PonyEngine::Debug
{
	export class ILoggerEntry : public ILoggerEntryView
	{
	public:
		virtual ~ILoggerEntry() noexcept = default;
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.ILogger;

import PonyEngine.Debug.ILoggerView;

namespace PonyEngine::Debug
{
	/// <summary>
	/// Logger interface.
	/// </summary>
	/// <remarks>
	///	This class is supposed to be pointed only by its owner.
	/// </remarks>
	export class ILogger : public ILoggerView
	{
	public:
		virtual ~ILogger() noexcept = default;
	};
}

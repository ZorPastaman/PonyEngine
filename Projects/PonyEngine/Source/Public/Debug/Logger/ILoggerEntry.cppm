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
	/// <summary>
	/// Logger entry interface.
	/// </summary>
	/// <remarks>
	///	This class is supposed to be pointed only by its owner.
	/// </remarks>
	export class ILoggerEntry : public ILoggerEntryView
	{
	public:
		virtual ~ILoggerEntry() noexcept = default;
	};
}

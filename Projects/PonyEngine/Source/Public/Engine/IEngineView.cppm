/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.IEngineView;

import <cstddef>;

import PonyEngine.Debug.ILoggerView;

namespace PonyEngine
{
	/// <summary>
	/// Pony Engine view interface.
	/// </summary>
	export class IEngineView
	{
	public:
		/// <summary>
		/// Gets current frame count.
		/// </summary>
		/// <returns>Current frame count.</returns>
		virtual size_t GetFrameCount() const noexcept = 0;

		virtual Debug::ILoggerView* GetLogger() const noexcept = 0;

	protected:
		virtual ~IEngineView() noexcept = default;
	};
}

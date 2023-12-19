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
	/// <remarks>
	///	This class is supposed to be pointed by external users.
	/// </remarks>
	export class IEngineView
	{
	public:
		/// <summary>
		/// Gets current frame count.
		/// </summary>
		/// <returns>Current frame count.</returns>
		virtual size_t GetFrameCount() const noexcept = 0;

		/// <summary>
		/// Gets engine logger.
		/// </summary>
		/// <returns>Engine logger.</returns>
		/// <remarks>
		/// Usually, it's used by classes that are dependent on the engine.
		virtual Debug::ILoggerView* GetLogger() const noexcept = 0;

	protected:
		virtual ~IEngineView() noexcept = default;
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.IEngine;

import <cstddef>;

namespace PonyEngine
{
	/// <summary>
	/// Pony Engine interface.
	/// </summary>
	export class IEngine
	{
	public:
		virtual ~IEngine() = default;

		/// <summary>
		/// Gets current frame count.
		/// </summary>
		/// <returns>Current frame count.</returns>
		virtual size_t GetFrameCount() const = 0;

		/// <summary>
		/// Ticks the engine.
		/// </summary>
		/// <remarks>
		/// It increments frame count.
		/// </remarks>
		virtual void Tick() = 0;
	};
}

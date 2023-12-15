/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.IEngine;

import PonyEngine.IEngineView;

namespace PonyEngine
{
	/// <summary>
	/// Pony Engine interface.
	/// </summary>
	export class IEngine : public IEngineView
	{
	public:
		virtual ~IEngine() noexcept = default;

		/// <summary>
		/// Ticks the engine.
		/// </summary>
		/// <remarks>
		/// It increments frame count.
		/// </remarks>
		virtual void Tick() = 0;
	};
}

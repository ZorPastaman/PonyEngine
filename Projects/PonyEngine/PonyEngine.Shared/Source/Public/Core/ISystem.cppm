/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ISystem;

import <cstdint>;

namespace PonyEngine::Core
{
	/// @brief Engine system.
	export class ISystem
	{
	public:
		/// @brief Ticks the system.
		virtual void Tick() = 0;

	protected:
		inline virtual ~ISystem() noexcept = default;
	};
}

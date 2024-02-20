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
	export class ISystem
	{
	public:
		virtual ~ISystem() noexcept = default;

		virtual void Tick() = 0;
	};
}

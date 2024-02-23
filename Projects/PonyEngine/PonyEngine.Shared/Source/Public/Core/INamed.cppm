/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:INamed;

import <string>;

namespace PonyEngine::Core
{
	export class INamed
	{
	public:
		virtual const std::string& GetName() const noexcept = 0;

	protected:
		inline virtual ~INamed() noexcept = default;
	};
}

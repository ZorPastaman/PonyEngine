/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Container:BufferParams;

import <cstddef>;

export namespace PonyBase::Container
{
	/// @brief Buffer parameters.
	struct BufferParams final
	{
		std::size_t stride = 0u; ///< Element size.
		std::size_t count = 0u; ///< Element count.
	};
}

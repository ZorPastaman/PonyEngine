/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Ext:TempBuffer;

import std;

export namespace PonyEngine::Application
{
	/// @brief Temporary buffer.
	struct TempBuffer final
	{
		std::span<std::byte> buffer; ///< Buffer.
	};
}

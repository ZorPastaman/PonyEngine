/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:LogicOperation;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Logic operation.
	enum class LogicOperation : std::uint8_t
	{
		Noop,
		Clear,
		Set,
		Copy,
		CopyInverted,
		Invert,
		And,
		AndReverse,
		AndInverted,
		Nand,
		Or,
		OrReverse,
		OrInverted,
		Nor,
		Xor,
		Equal
	};
}

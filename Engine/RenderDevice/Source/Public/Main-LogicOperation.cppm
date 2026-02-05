/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:LogicOperation;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class LogicOperation : std::uint8_t
	{
		Noop,
		Clear,
		Set,
		Copy,
		CopyInverted,
		Equivalent,
		Invert,
		And,
		AndReverse,
		AndInverted,
		Nand,
		Or,
		OrReverse,
		OrInverted,
		Xor,
		Nor
	};
}

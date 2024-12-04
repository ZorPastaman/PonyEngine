/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputEntry;

import :InputCode;

export namespace PonyEngine::Input
{
	struct InputEntry final
	{
		InputCode inputCode;
		float value;
	};
}

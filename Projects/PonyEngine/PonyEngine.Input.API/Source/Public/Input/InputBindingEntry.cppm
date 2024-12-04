/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputBindingEntry;

import <span>;
import <string_view>;
import <utility>;

import :InputCode;

export namespace PonyEngine::Input
{
	struct InputBindingEntry final
	{
		InputCode inputCode;
		float multiplier = 1.f;
	};
}

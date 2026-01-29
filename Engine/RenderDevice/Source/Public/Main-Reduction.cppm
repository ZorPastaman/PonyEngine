/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:Reduction;

import std;

import :ComparisonFunc;

export namespace PonyEngine::RenderDevice
{
	struct StandardReduction final
	{
	};

	struct ComparisonReduction final
	{
		ComparisonFunc func;
	};

	struct MinimumReduction final
	{
	};

	struct MaximumReduction final
	{
	};

	using Reduction = std::variant<StandardReduction, ComparisonReduction, MinimumReduction, MaximumReduction>;
}

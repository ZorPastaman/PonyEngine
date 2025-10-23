/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.Application.Extension:FlowState;

import std;

namespace PonyEngine::Application
{
	/// @brief Flow state names.
	constexpr std::array<std::string_view, 6> FlowStateNames
	{
		"StartingUp",
		"Beginning",
		"Running",
		"Stopped",
		"Ending",
		"ShuttingDown"
	};
}

export namespace PonyEngine::Application
{
	/// @brief Flow state.
	enum class FlowState : std::uint8_t
	{
		StartingUp,
		Beginning,
		Running,
		Stopped,
		Ending,
		ShuttingDown
	};

	ENUM_VALUE_FEATURES(FlowState, FlowStateNames)
}

export
{
	ENUM_VALUE_FORMATTER(PonyEngine::Application, FlowState)
}

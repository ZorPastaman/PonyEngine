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

export module PonyEngine.Application:FlowState;

import std;

namespace PonyEngine::Application
{
	/// @brief Flow state names.
	constexpr std::array<std::string_view, 8> FlowStateNames
	{
		"NotInitialized",
		"StartingUp",
		"Beginning",
		"Running",
		"Stopped",
		"Ending",
		"ShuttingDown",
		"Finalized"
	};
}

export namespace PonyEngine::Application
{
	/// @brief Flow state.
	enum class FlowState : std::uint8_t
	{
		NotInitialized,
		StartingUp,
		Beginning,
		Running,
		Stopped,
		Ending,
		ShuttingDown,
		Finalized
	};

	/// @brief Flow info.
	struct FlowInfo final
	{
		int exitCode; ///< Exit code. Has a valid value only if the @p flowState >= Stopped.
		FlowState flowState; ///< Flow state.
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::Application::FlowState, PonyEngine::Application::FlowStateNames)
}

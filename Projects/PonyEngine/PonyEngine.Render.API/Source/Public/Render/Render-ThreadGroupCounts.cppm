/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:ThreadGroupCounts;

import PonyShader.Core;

import :ThreadGroupCountsMode;

export namespace PonyEngine::Render
{
	/// @brief Describes how to calculate thread group counts that must be dispatched by a graphics pipeline to render an object.
	struct ThreadGroupCounts final
	{
		PonyShader::Core::ThreadGroupCounts threadGroupCounts; ///< Thread group counts. Its usage is dependent on the @p mode.
		ThreadGroupCountsMode mode = ThreadGroupCountsMode::SetMesh; ///< Thread group counts calculation mode.

		[[nodiscard("Pure operator")]]
		bool operator ==(const ThreadGroupCounts& other) const noexcept = default;
	};
}

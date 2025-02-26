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
	struct ThreadGroupCounts final
	{
		PonyShader::Core::ThreadGroupCounts threadGroupCounts;
		ThreadGroupCountsMode mode = ThreadGroupCountsMode::SetMesh;

		[[nodiscard("Pure operator")]]
		bool operator ==(const ThreadGroupCounts& other) const noexcept = default;
	};
}

/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

module;

#include <cassert>

export module PonyEngine.Render:ThreadGroupCountsUtility;

import <array>;
import <cmath>;

import PonyMath.Core;

import PonyShader.Core;

import :ThreadGroupCounts;
import :ThreadGroupCountsMode;

export namespace PonyEngine::Render
{
	[[nodiscard("Pure function")]]
	PonyShader::Core::ThreadGroupCounts CreateDispatchThreadGroupCounts(const ThreadGroupCounts& materialCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts) noexcept;
	[[nodiscard("Pure function")]]
	PonyShader::Core::ThreadGroupCounts CreateDispatchThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& materialCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts, ThreadGroupCountsMode mode) noexcept;
}

namespace PonyEngine::Render
{
	[[nodiscard("Pure function")]]
	PonyShader::Core::ThreadGroupCounts CreateDividedThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& materialCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts) noexcept;

	PonyShader::Core::ThreadGroupCounts CreateDispatchThreadGroupCounts(const ThreadGroupCounts& materialCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts) noexcept
	{
		return CreateDispatchThreadGroupCounts(materialCounts.threadGroupCounts, meshCounts, materialCounts.mode);
	}

	PonyShader::Core::ThreadGroupCounts CreateDispatchThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& materialCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts, const ThreadGroupCountsMode mode) noexcept
	{
		switch (mode)
		{
		case ThreadGroupCountsMode::SetMesh:
			return meshCounts;
		case ThreadGroupCountsMode::SetMaterial:
			return materialCounts;
		case ThreadGroupCountsMode::DivideMeshByMaterial:
			return CreateDividedThreadGroupCounts(materialCounts, meshCounts);
		default: [[unlikely]]
			assert(false && "Unsupported ThreadGroupCountsMode.");
			return CreateDividedThreadGroupCounts(materialCounts, meshCounts);
		}
	}

	PonyShader::Core::ThreadGroupCounts CreateDividedThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& materialCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts) noexcept
	{
		return PonyShader::Core::ThreadGroupCounts(
			materialCounts.ThreadGroupCountX() > 0u ? PonyMath::Core::CeilDivision(meshCounts.ThreadGroupCountX(), materialCounts.ThreadGroupCountX()) : 0u,
			materialCounts.ThreadGroupCountY() > 0u ? PonyMath::Core::CeilDivision(meshCounts.ThreadGroupCountY(), materialCounts.ThreadGroupCountY()) : 0u,
			materialCounts.ThreadGroupCountZ() > 0u ? PonyMath::Core::CeilDivision(meshCounts.ThreadGroupCountZ(), materialCounts.ThreadGroupCountZ()) : 0u
		);
	}
}

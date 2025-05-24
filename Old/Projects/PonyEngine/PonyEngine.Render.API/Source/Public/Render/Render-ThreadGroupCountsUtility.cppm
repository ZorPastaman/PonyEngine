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
import <cstddef>;

import PonyMath.Core;

import PonyShader.Core;

import :ThreadGroupCounts;
import :ThreadGroupCountsMode;

export namespace PonyEngine::Render
{
	/// @brief Creates thread group counts that must be dispatched by the parameters.
	/// @param pipelineStateCounts Pipeline state thread group counts.
	/// @param meshCounts Mesh thread group counts.
	/// @return Thread group counts to dispatch.
	[[nodiscard("Pure function")]]
	PonyShader::Core::ThreadGroupCounts CreateDispatchThreadGroupCounts(const ThreadGroupCounts& pipelineStateCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts) noexcept;
	/// @brief Creates thread group counts that must be dispatched by the parameters.
	/// @param pipelineStateCounts Pipeline state thread group counts.
	/// @param meshCounts Mesh thread group counts.
	/// @param mode Calculation mode.
	/// @return Thread group counts to dispatch.
	[[nodiscard("Pure function")]]
	PonyShader::Core::ThreadGroupCounts CreateDispatchThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& pipelineStateCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts, ThreadGroupCountsMode mode) noexcept;
}

namespace PonyEngine::Render
{
	/// @brief Creates thread group counts by the mode of multiplication.
	/// @param multiplicand Multiplicand.
	/// @param multiplier Multiplier.
	/// @return Product.
	[[nodiscard("Pure function")]]
	PonyShader::Core::ThreadGroupCounts CreateMultipliedThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& multiplicand, const PonyShader::Core::ThreadGroupCounts& multiplier) noexcept;
	/// @brief Creates thread group counts by the mode of division.
	/// @param numerator Numerator.
	/// @param denominator Denominator.
	/// @return Quotient.
	[[nodiscard("Pure function")]]
	PonyShader::Core::ThreadGroupCounts CreateDividedThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& numerator, const PonyShader::Core::ThreadGroupCounts& denominator) noexcept;

	PonyShader::Core::ThreadGroupCounts CreateDispatchThreadGroupCounts(const ThreadGroupCounts& pipelineStateCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts) noexcept
	{
		return CreateDispatchThreadGroupCounts(pipelineStateCounts.threadGroupCounts, meshCounts, pipelineStateCounts.mode);
	}

	PonyShader::Core::ThreadGroupCounts CreateDispatchThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& pipelineStateCounts, const PonyShader::Core::ThreadGroupCounts& meshCounts, const ThreadGroupCountsMode mode) noexcept
	{
		switch (mode)
		{
		case ThreadGroupCountsMode::SetMesh:
			return meshCounts;
		case ThreadGroupCountsMode::SetPipelineState:
			return pipelineStateCounts;
		case ThreadGroupCountsMode::Multiply:
			return CreateMultipliedThreadGroupCounts(pipelineStateCounts, meshCounts);
		case ThreadGroupCountsMode::DivideMeshByPipelineState:
			return CreateDividedThreadGroupCounts(meshCounts, pipelineStateCounts);
		case ThreadGroupCountsMode::DividePipelineStateByMesh:
			return CreateDividedThreadGroupCounts(pipelineStateCounts, meshCounts);
		default: [[unlikely]]
			assert(false && "Unsupported ThreadGroupCountsMode.");
			return CreateDividedThreadGroupCounts(meshCounts, pipelineStateCounts);
		}
	}

	PonyShader::Core::ThreadGroupCounts CreateMultipliedThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& multiplicand, const PonyShader::Core::ThreadGroupCounts& multiplier) noexcept
	{
		std::array<std::uint32_t, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountCount> counts;
		for (std::size_t i = 0; i < PonyShader::Core::ThreadGroupCounts::ThreadGroupCountCount; ++i)
		{
			counts[i] = multiplicand.ThreadGroupCount(i) * multiplier.ThreadGroupCount(i);
		}

		return PonyShader::Core::ThreadGroupCounts(counts);
	}

	PonyShader::Core::ThreadGroupCounts CreateDividedThreadGroupCounts(const PonyShader::Core::ThreadGroupCounts& numerator, const PonyShader::Core::ThreadGroupCounts& denominator) noexcept
	{
		std::array<std::uint32_t, PonyShader::Core::ThreadGroupCounts::ThreadGroupCountCount> counts;
		for (std::size_t i = 0; i < PonyShader::Core::ThreadGroupCounts::ThreadGroupCountCount; ++i)
		{
			counts[i] = denominator.ThreadGroupCount(i) > 0u ? PonyMath::Core::DivideCeil(numerator.ThreadGroupCount(i), denominator.ThreadGroupCount(i)) : 0u;
		}

		return PonyShader::Core::ThreadGroupCounts(counts);
	}
}

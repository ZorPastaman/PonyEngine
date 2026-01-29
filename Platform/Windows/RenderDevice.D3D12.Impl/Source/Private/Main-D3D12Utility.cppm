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

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Utility;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Windows
{
	[[nodiscard("Pure function")]]
	constexpr D3D12_COMPARISON_FUNC ToComparisonFunc(ComparisonFunc func) noexcept;
}

namespace PonyEngine::RenderDevice::Windows
{
	constexpr D3D12_COMPARISON_FUNC ToComparisonFunc(const ComparisonFunc func) noexcept
	{
		switch (func)
		{
		case ComparisonFunc::None:
			return D3D12_COMPARISON_FUNC_NONE;
		case ComparisonFunc::Never:
			return D3D12_COMPARISON_FUNC_NEVER;
		case ComparisonFunc::Always:
			return D3D12_COMPARISON_FUNC_ALWAYS;
		case ComparisonFunc::Equal:
			return D3D12_COMPARISON_FUNC_EQUAL;
		case ComparisonFunc::NotEqual:
			return D3D12_COMPARISON_FUNC_NOT_EQUAL;
		case ComparisonFunc::Less:
			return D3D12_COMPARISON_FUNC_LESS;
		case ComparisonFunc::LessOrEqual:
			return D3D12_COMPARISON_FUNC_LESS_EQUAL;
		case ComparisonFunc::Greater:
			return D3D12_COMPARISON_FUNC_GREATER;
		case ComparisonFunc::GreaterOrEqual:
			return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
		default: [[unlikely]]
			assert(false && "Invalid comparison func.");
			return D3D12_COMPARISON_FUNC_NONE;
		}
	}
}

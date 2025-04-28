/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:Blend;

import <variant>;

import :LogicBlend;
import :OpaqueBlend;
import :TransparentBlend;

export namespace PonyEngine::Render
{
	/// @brief Blend.
	struct Blend final
	{
		std::variant<OpaqueBlend, TransparentBlend, LogicBlend> renderTargetBlend = OpaqueBlend{}; ///< Render target blend.
		bool alphaToCoverage = false; ///< Enable alpha to coverage?

		[[nodiscard("Pure operator")]]
		bool operator ==(const Blend& other) const noexcept = default;
	};
}

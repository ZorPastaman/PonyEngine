/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:TransparentBlend;

import :BlendFactor;
import :BlendOperation;

export namespace PonyEngine::Render
{
	/// @brief Transparent blend operation.
	struct TransparentBlend final
	{
		BlendFactor sourceBlend = BlendFactor::One; ///< Source color blend factor.
		BlendFactor destinationBlend = BlendFactor::Zero; ///< Destination color blend factor.
		BlendOperation blendOperation = BlendOperation::Add; ///< Color blend operation.

		BlendFactor sourceBlendAlpha = BlendFactor::One; ///< Source alpha blend factor.
		BlendFactor destinationBlendAlpha = BlendFactor::Zero; ///< Destination alpha blend factor.
		BlendOperation blendOperationAlpha = BlendOperation::Add; ///< Alpha blend operation.

		[[nodiscard("Pure operator")]]
		bool operator ==(const TransparentBlend& other) const noexcept = default;
	};
}

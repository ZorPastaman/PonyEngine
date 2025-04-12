/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Rasterizer;

import :CullMode;
import :FillMode;

export namespace PonyEngine::Render
{
	/// @brief Rasterizer parameters.
	struct Rasterizer final
	{
		FillMode fillMode = FillMode::Solid; ///< Fill mode.
		CullMode cullMode = CullMode::Back; ///< Cull mode.

		std::int32_t depthBias = 0; ///< Added depth value.
		float slopeScaledDepthBias = 0.f; ///< Pixel slope multiplier.
		float depthBiasClamp = 0.f; ///< Maximum depth bias.
		bool depthClip = true; ///< Is clipping based on distance enabled?

		[[nodiscard("Pure operator")]]
		bool operator ==(const Rasterizer& other) const noexcept = default;
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:TextureFormatId;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture format id.
	struct TextureFormatID final
	{
		std::uint64_t hash = 0u; ///< Hash.

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const TextureFormatID& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::RenderDevice::TextureFormatID> final
{
	[[nodiscard("Pure operator")]]
	std::size_t operator ()(const PonyEngine::RenderDevice::TextureFormatID textureFormatId) const noexcept
	{
		return std::hash<std::uint64_t>()(textureFormatId.hash);
	}
};

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SubTextureIndex;

import std;

import PonyEngine.Math;

import :Aspect;

export namespace PonyEngine::RenderDevice
{
	/// @brief Sub-texture index.
	struct SubTextureIndex final
	{
		std::uint16_t arrayIndex = 0u; ///< Array element index.
		std::uint8_t mipIndex = 0u; ///< Mip index.
		Aspect aspect = Aspect::Color; ///< Aspect.
	};

	/// @brief Copy sub-texture index.
	struct CopySubTextureIndex final
	{
		std::uint16_t sourceArrayIndex = 0u; ///< Source array element index.
		std::uint16_t destinationArrayIndex = 0u; ///< Destination array element index.
		std::uint8_t sourceMipIndex = 0u; ///< Source mip index.
		std::uint8_t destinationMipIndex = 0u; ///< Destination mip index.
		Aspect aspect = Aspect::Color; ///< Aspect.
	};

	/// @brief Copy sub-texture box.
	struct CopySubTextureBox final
	{
		Math::Vector3<std::uint32_t> sourceOffset; ///< Source offset.
		Math::Vector3<std::uint32_t> destinationOffset; ///< Destination offset.
		Math::Vector3<std::uint32_t> sourceSize; ///< Source size.
	};
}

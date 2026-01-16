/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:TextureFormat;

import std;

export namespace PonyEngine::RenderDevice
{
	struct TextureFormat final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(TextureFormat)

		static constexpr std::string_view R32G32B32A32_Float = "R32G32B32A32_Float";
		static constexpr std::string_view R32G32B32A32_Uint = "R32G32B32A32_Uint";
		static constexpr std::string_view R32G32B32A32_Sint = "R32G32B32A32_Sint";

		static constexpr std::string_view R32G32B32_Float = "R32G32B32_Float";
		static constexpr std::string_view R32G32B32_Uint = "R32G32B32_Uint";
		static constexpr std::string_view R32G32B32_Sint = "R32G32B32_Sint";

		static constexpr std::string_view R32G32_Float = "R32G32_Float";
		static constexpr std::string_view R32G32_Uint = "R32G32_Uint";
		static constexpr std::string_view R32G32_Sint = "R32G32_Sint";

		static constexpr std::string_view D32_Float_S8X24_Uint = "D32_Float_S8X24_Uint";
		static constexpr std::string_view D32_Float = "D32_Float";

		static constexpr std::string_view R32_Float = "R32_Float";
		static constexpr std::string_view R32_Uint = "R32_Uint";
		static constexpr std::string_view R32_Sint = "R32_Sint";

		static constexpr std::string_view D24_Unorm_S8_Uint = "D24_Unorm_S8_Uint";

		static constexpr std::string_view R16G16B16A16_Float = "R16G16B16A16_Float";
		static constexpr std::string_view R16G16B16A16_Unorm = "R16G16B16A16_Unorm";
		static constexpr std::string_view R16G16B16A16_Uint = "R16G16B16A16_Uint";
		static constexpr std::string_view R16G16B16A16_Snorm = "R16G16B16A16_Snorm";
		static constexpr std::string_view R16G16B16A16_Sint = "R16G16B16A16_Sint";

		static constexpr std::string_view R16G16_Float = "R16G16_Float";
		static constexpr std::string_view R16G16_Unorm = "R16G16_Unorm";
		static constexpr std::string_view R16G16_Uint = "R16G16_Uint";
		static constexpr std::string_view R16G16_Snorm = "R16G16_Snorm";
		static constexpr std::string_view R16G16_Sint = "R16G16_Sint";

		static constexpr std::string_view D16_Unorm = "D16_Unorm";

		static constexpr std::string_view R16_Float = "R16_Float";
		static constexpr std::string_view R16_Unorm = "R16_Unorm";
		static constexpr std::string_view R16_Uint = "R16_Uint";
		static constexpr std::string_view R16_Snorm = "R16_Snorm";
		static constexpr std::string_view R16_Sint = "R16_Sint";

		static constexpr std::string_view R11G11B10_Float = "R11G11B10_Float";

		static constexpr std::string_view R10G10B10A2_Unorm = "R10G10B10A2_Unorm";
		static constexpr std::string_view R10G10B10A2_Uint = "R10G10B10A2_Uint";

		static constexpr std::string_view R9G9B9E5_SharedExp = "R9G9B9E5_SharedExp";

		static constexpr std::string_view R8G8B8A8_Unorm = "R8G8B8A8_Unorm";
		static constexpr std::string_view R8G8B8A8_Uint = "R8G8B8A8_Uint";
		static constexpr std::string_view R8G8B8A8_Snorm = "R8G8B8A8_Snorm";
		static constexpr std::string_view R8G8B8A8_Sint = "R8G8B8A8_Sint";

		static constexpr std::string_view R8G8_Unorm = "R8G8_Unorm";
		static constexpr std::string_view R8G8_Uint = "R8G8_Uint";
		static constexpr std::string_view R8G8_Snorm = "R8G8_Snorm";
		static constexpr std::string_view R8G8_Sint = "R8G8_Sint";

		static constexpr std::string_view R8_Unorm = "R8_Unorm";
		static constexpr std::string_view R8_Uint = "R8_Uint";
		static constexpr std::string_view R8_Snorm = "R8_Snorm";
		static constexpr std::string_view R8_Sint = "R8_Sint";

		static constexpr std::string_view B8G8R8A8_Unorm = "B8G8R8A8_Unorm";
		static constexpr std::string_view B8G8R8X8_Unorm = "B8G8R8X8_Unorm";

		static constexpr std::string_view A8_Unorm = "A8_Unorm";

		static constexpr std::string_view B5G6R5_Unorm = "B5G6R5_Unorm";
		static constexpr std::string_view B5G5R5A1_Unorm = "B5G5R5A1_Unorm";

		static constexpr std::string_view BC1_Unorm = "BC1_Unorm";
		static constexpr std::string_view BC2_Unorm = "BC2_Unorm";
		static constexpr std::string_view BC3_Unorm = "BC3_Unorm";
		static constexpr std::string_view BC4_Unorm = "BC4_Unorm";
		static constexpr std::string_view BC4_Snorm = "BC4_Snorm";
		static constexpr std::string_view BC5_Unorm = "BC5_Unorm";
		static constexpr std::string_view BC5_Snorm = "BC5_Snorm";
		static constexpr std::string_view BC6H_UF16 = "BC6H_UF16";
		static constexpr std::string_view BC6H_SF16 = "BC6H_SF16";
		static constexpr std::string_view BC7_Unorm = "BC7_Unorm";
	};
}

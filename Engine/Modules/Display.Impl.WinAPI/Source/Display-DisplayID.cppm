/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.Display.Impl.WinAPI:DisplayID;

export namespace PonyEngine::Display
{
	struct DisplayID final
	{
		LUID adapterId;
		UINT32 id;

		[[nodiscard("Pure operator")]]
		constexpr auto operator ==(const DisplayID& other) const noexcept;
	};
}

namespace PonyEngine::Display
{
	constexpr auto DisplayID::operator ==(const DisplayID& other) const noexcept
	{
		return adapterId.LowPart == other.adapterId.LowPart && adapterId.HighPart == other.adapterId.HighPart && id == other.id;
	}
}

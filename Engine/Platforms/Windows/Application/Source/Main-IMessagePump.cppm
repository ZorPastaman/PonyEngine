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
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Windows:IMessagePump;

import std;

export namespace PonyEngine::Application::Windows
{
	class IMessagePump
	{
		PONY_INTERFACE_BODY(IMessagePump)

		[[nodiscard("Pure function")]]
		virtual UINT LastMessageType() const = 0;
		[[nodiscard("Pure function")]]
		virtual DWORD LastMessageRawTime() const = 0;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTime() const = 0;
		[[nodiscard("Pure function")]]
		virtual POINT LastMessagePoint() const = 0;
	};
}

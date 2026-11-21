/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Display:IWindow;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Display
{
	class IWindowObserver;

	class IWindow
	{
		PONY_INTERFACE_BODY(IWindow)

		virtual void AddObserver(IWindowObserver& observer) = 0;
		virtual void RemoveObserver(IWindowObserver& observer) = 0;
	};

	class IWindowObserver
	{
		PONY_INTERFACE_BODY(IWindowObserver)

		virtual void OnDestroyed(IWindow& window) {}

		virtual void OnSizeChanged(IWindow& window, const Math::Vector2<std::uint32_t>& size, bool minimized) {}
	};
}

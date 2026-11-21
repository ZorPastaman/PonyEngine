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

export module PonyEngine.Display:IDisplayObserver;

export namespace PonyEngine::Display
{
	class IDisplayObserver
	{
		PONY_INTERFACE_BODY(IDisplayObserver)

		virtual void OnDisplayChanged() {}
	};
}

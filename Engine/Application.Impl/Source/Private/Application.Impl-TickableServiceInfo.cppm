/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:TickableServiceInfo;

import std;

import PonyEngine.Application.Ext;

export namespace PonyEngine::Application
{
	struct TickableServiceInfo final
	{
		ITickableService* tickableService;
		std::int32_t tickOrder;
	};
}

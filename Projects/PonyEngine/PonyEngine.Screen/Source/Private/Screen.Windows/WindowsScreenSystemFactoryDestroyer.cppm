/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Screen.Windows.Implementation:WindowsScreenSystemFactoryDestroyer;

import PonyEngine.Core.Factory;

import :WindowsScreenSystemFactory;

export namespace PonyEngine::Screen
{
	struct WindowsScreenSystemFactoryDestroyer final : Core::ISystemFactoryDestroyer
	{
		virtual void Destroy(Core::ISystemFactory* factory) noexcept override;
	};
}

namespace PonyEngine::Screen
{
	void WindowsScreenSystemFactoryDestroyer::Destroy(Core::ISystemFactory* const factory) noexcept
	{
		assert(dynamic_cast<WindowsScreenSystemFactory*>(factory) && "Tried to destroy a system factory of the wrong type.");
		delete static_cast<WindowsScreenSystemFactory*>(factory);
	}
}

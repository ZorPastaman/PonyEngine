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

export module PonyEngine.Window.Windows.Implementation:WindowsWindowSystemFactoryDestroyer;

import PonyEngine.Core.Factory;

import :WindowsWindowSystemFactory;

export namespace PonyEngine::Window
{
	struct WindowsWindowSystemFactoryDestroyer final : Core::ISystemFactoryDestroyer
	{
		virtual void Destroy(Core::ISystemFactory* factory) noexcept override;
	};
}

namespace PonyEngine::Window
{
	void WindowsWindowSystemFactoryDestroyer::Destroy(Core::ISystemFactory* const factory) noexcept
	{
		assert(dynamic_cast<WindowsWindowSystemFactory*>(factory) && "Tried to destroy a system factory of the wrong type.");
		delete static_cast<WindowsWindowSystemFactory*>(factory);
	}
}

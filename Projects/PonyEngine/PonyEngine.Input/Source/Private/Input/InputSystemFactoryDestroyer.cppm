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

export module PonyEngine.Input.Implementation:InputSystemFactoryDestroyer;

import PonyEngine.Core.Factory;

import :InputSystemFactory;

export namespace PonyEngine::Input
{
	/// @brief Input system factory destroyer.
	struct InputSystemFactoryDestroyer final : Core::ISystemFactoryDestroyer
	{
		virtual void Destroy(Core::ISystemFactory* factory) noexcept override;
	};
}

namespace PonyEngine::Input
{
	void InputSystemFactoryDestroyer::Destroy(Core::ISystemFactory* const factory) noexcept
	{
		assert(dynamic_cast<InputSystemFactory*>(factory) && "Tried to destroy a system factory of the wrong type.");
		delete static_cast<InputSystemFactory*>(factory);
	}
}

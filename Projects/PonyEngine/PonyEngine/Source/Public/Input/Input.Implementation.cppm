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

#include "PonyEngine/Core/Linking.h"

export module PonyEngine.Input.Implementation;

import <functional>;
import <memory>;

import :InputSystemFactory;

export namespace PonyEngine::Input
{
	using InputUniquePtr = std::unique_ptr<IInputSystemFactory, std::function<void(IInputSystemFactory*)>>; ///< Input system factory unique_ptr typedef.

	/// @brief Creates an input system factory.
	/// @return Input system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT InputUniquePtr CreateInputSystemFactory();
}

namespace PonyEngine::Input
{
	/// @brief Destroys a previously created input system factory.
	/// @param factory Input system factory to destroy.
	void DestroyInputSystemFactory(IInputSystemFactory* factory) noexcept;

	InputUniquePtr CreateInputSystemFactory()
	{
		return std::unique_ptr<IInputSystemFactory, std::function<void(IInputSystemFactory*)>>(new InputSystemFactory(), DestroyInputSystemFactory);
	}

	void DestroyInputSystemFactory(IInputSystemFactory* const factory) noexcept
	{
		assert((dynamic_cast<InputSystemFactory*>(factory) && "An input system of the wrong type is tried to be destroyed."));
		delete static_cast<InputSystemFactory*>(factory);
	}
}

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

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Input.Implementation;

import <memory>;

export import PonyEngine.Input.Factory;

import :InputSystemFactory;

export namespace PonyEngine::Input
{
	/// @brief Input system factory deleter.
	struct PONY_DLL_EXPORT InputSystemFactoryDeleter final
	{
		/// @brief Deletes the @p factory.
		/// @param factory Input system factory to delete.
		void operator ()(IInputSystemFactory* factory) const noexcept;
	};

	using InputUniquePtr = std::unique_ptr<IInputSystemFactory, InputSystemFactoryDeleter>; ///< Input system factory unique_ptr typedef.

	/// @brief Creates an input system factory.
	/// @return Input system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT InputUniquePtr CreateInputSystemFactory();
}

namespace PonyEngine::Input
{
	void InputSystemFactoryDeleter::operator ()(IInputSystemFactory* const factory) const noexcept
	{
		assert((dynamic_cast<InputSystemFactory*>(factory) && "Tried to destroy a factory of the wrong type."));
		delete static_cast<InputSystemFactory*>(factory);
	}

	InputUniquePtr CreateInputSystemFactory()
	{
		return std::unique_ptr<IInputSystemFactory, InputSystemFactoryDeleter>(new InputSystemFactory());
	}
}

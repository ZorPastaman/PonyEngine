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
	/// @brief Destroys the input system factory.
	/// @param factory Input system factory to destroy.
	void DestroyInputSystemFactory(IInputSystemFactory* factory) noexcept;

	void InputSystemFactoryDeleter::operator ()(IInputSystemFactory* const factory) const noexcept
	{
		DestroyInputSystemFactory(factory);
	}

	InputUniquePtr CreateInputSystemFactory()
	{
		return std::unique_ptr<IInputSystemFactory, InputSystemFactoryDeleter>(new InputSystemFactory());
	}

	void DestroyInputSystemFactory(IInputSystemFactory* const factory) noexcept
	{
		assert((dynamic_cast<InputSystemFactory*>(factory) && "Tried to destroy a factory of the wrong type."));
		delete static_cast<InputSystemFactory*>(factory);
	}
}

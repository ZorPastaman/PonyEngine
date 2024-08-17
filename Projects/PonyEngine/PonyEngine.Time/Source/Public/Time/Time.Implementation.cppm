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

export module PonyEngine.Time.Implementation;

import <memory>;

export import PonyEngine.Time.Factory;

import :FrameRateSystemFactory;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory deleter.
	struct PONY_DLL_EXPORT FrameRateSystemFactoryDeleter final
	{
		/// @brief Deletes the @p factory.
		/// @param factory Frame rate system factory to delete.
		void operator ()(IFrameRateSystemFactory* factory) const noexcept;
	};

	using FrameRateUniquePtr = std::unique_ptr<IFrameRateSystemFactory, FrameRateSystemFactoryDeleter>; ///< Frame rate system factory unique_ptr typedef.

	/// @brief Creates a frame rate system factory.
	/// @return Frame rate system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FrameRateUniquePtr CreateFrameRateSystemFactory();
}

namespace PonyEngine::Time
{
	void FrameRateSystemFactoryDeleter::operator ()(IFrameRateSystemFactory* const factory) const noexcept
	{
		assert((dynamic_cast<FrameRateSystemFactory*>(factory) && "Tried to destroy a factory of the wrong type."));
		delete static_cast<FrameRateSystemFactory*>(factory);
	}

	FrameRateUniquePtr CreateFrameRateSystemFactory()
	{
		return std::unique_ptr<IFrameRateSystemFactory, FrameRateSystemFactoryDeleter>(new FrameRateSystemFactory());
	}
}

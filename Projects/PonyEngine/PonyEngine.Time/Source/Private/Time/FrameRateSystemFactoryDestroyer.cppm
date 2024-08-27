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

export module PonyEngine.Time.Implementation:FrameRateSystemFactoryDestroyer;

import PonyEngine.Core.Factory;

import :FrameRateSystemFactory;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system factory destroyer.
	struct FrameRateSystemFactoryDestroyer final : Core::ISystemFactoryDestroyer
	{
		virtual void Destroy(Core::ISystemFactory* factory) noexcept override;
	};
}

namespace PonyEngine::Time
{
	void FrameRateSystemFactoryDestroyer::Destroy(Core::ISystemFactory* const factory) noexcept
	{
		assert(dynamic_cast<FrameRateSystemFactory*>(factory) && "Tried to destroy a system factory of the wrong type.");
		delete static_cast<FrameRateSystemFactory*>(factory);
	}
}

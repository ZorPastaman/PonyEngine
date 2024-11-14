/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "TickableSystem.h"

import PonyEngine.Core.Factory;

namespace Core
{
	class TickableSystemFactory final : public PonyEngine::Core::ISystemFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::SystemData Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) override;

		[[nodiscard("Pure function")]]
		TickableSystem* GetSystem() const noexcept;
		void Reset() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

	private:
		TickableSystem* system = nullptr;
	};
}

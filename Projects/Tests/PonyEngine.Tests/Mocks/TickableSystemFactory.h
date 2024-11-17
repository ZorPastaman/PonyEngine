/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <cstddef>
#include <typeinfo>

#include "TickableSystem.h"

import PonyEngine.Core;

namespace Core
{
	class TickableSystemFactory final : public PonyEngine::Core::ISystemFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyEngine::Core::SystemData Create(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) override;
		[[nodiscard("Pure function")]]
		virtual const type_info& SystemType() const noexcept override;

		[[nodiscard("Pure function")]]
		TickableSystem* GetSystem() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t Version() const noexcept;

	private:
		TickableSystem* createdSystem = nullptr;
		std::size_t version = 0;
	};
}

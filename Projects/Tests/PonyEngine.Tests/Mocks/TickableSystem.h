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

#include "PonyBase/Utility/Interface.h"

import PonyEngine.Core;

namespace Mocks
{
	class ITickableSystemInterface
	{
		INTERFACE_BODY(ITickableSystemInterface)
	};

	class TickableSystem final : public PonyEngine::Core::TickableSystem, public ITickableSystemInterface
	{
	public:
		[[nodiscard("Pure constructor")]]
		TickableSystem(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) noexcept;
		[[nodiscard("Pure constructor")]]
		TickableSystem(const TickableSystem& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		TickableSystem(TickableSystem&& other) noexcept = default;

		virtual ~TickableSystem() noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		std::size_t BeginCount() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t EndCount() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t TickCount() const noexcept;

		TickableSystem& operator =(const TickableSystem& other) noexcept = default;
		TickableSystem& operator =(TickableSystem&& other) noexcept = default;

		bool* onDestructed = nullptr;

	private:
		std::size_t beginCount = 0;
		std::size_t endCount = 0;
		std::size_t tickCount = 0;
	};
}

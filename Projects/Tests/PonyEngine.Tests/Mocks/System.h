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
	class ISystemInterface
	{
		INTERFACE_BODY(ISystemInterface)
	};

	class System final : public PonyEngine::Core::System, public ISystemInterface
	{
	public:
		[[nodiscard("Pure constructor")]]
		System(PonyEngine::Core::IEngineContext& engine, const PonyEngine::Core::SystemParams& params) noexcept;
		[[nodiscard("Pure constructor")]]
		System(const System& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		System(System&& other) noexcept = default;

		virtual ~System() noexcept override;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Pure function")]]
		std::size_t BeginCount() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t EndCount() const noexcept;

		System& operator =(const System& other) noexcept = default;
		System& operator =(System&& other) noexcept = default;

		bool* onDestructed = nullptr;

	private:
		std::size_t beginCount = 0;
		std::size_t endCount = 0;
	};
}

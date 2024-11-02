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
#include <string_view>

import PonyEngine.Core;

namespace Core
{
	class ITickableSystemInterface : PonyEngine::Core::ISystem
	{
	public:
		ITickableSystemInterface(const ITickableSystemInterface&) = delete;
		ITickableSystemInterface(ITickableSystemInterface&&) = delete;

		ITickableSystemInterface& operator =(const ITickableSystemInterface&) = delete;
		ITickableSystemInterface& operator =(ITickableSystemInterface&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		ITickableSystemInterface() noexcept = default;

		~ITickableSystemInterface() noexcept = default;
	};

	class TickableSystem final : public PonyEngine::Core::ITickableEngineSystem, public ITickableSystemInterface
	{
	public:
		[[nodiscard("Pure constructor")]]
		TickableSystem() noexcept = default;
		[[nodiscard("Pure constructor")]]
		TickableSystem(const TickableSystem& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		TickableSystem(TickableSystem&& other) noexcept = default;

		~TickableSystem() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		std::size_t BeginCount() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t EndCount() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t TickCount() const noexcept;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		TickableSystem& operator =(const TickableSystem& other) noexcept = default;
		TickableSystem& operator =(TickableSystem&& other) noexcept = default;

		bool* onDestructed = nullptr;

	private:
		std::size_t beginCount = 0;
		std::size_t endCount = 0;
		std::size_t tickCount = 0;
	};
}

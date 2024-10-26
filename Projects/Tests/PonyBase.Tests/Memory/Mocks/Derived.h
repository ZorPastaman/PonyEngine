/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "Base.h"

namespace Memory
{
	class Derived : public Base
	{
	public:
		[[nodiscard("Pure constructor")]]
		Derived() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Derived(const Derived& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Derived(Derived&& other) noexcept = default;

		~Derived() noexcept;

		void SetOnDerivedDestructed(bool* onDestructed) noexcept;

		Derived& operator =(const Derived& other) noexcept = default;
		Derived& operator =(Derived&& other) noexcept = default;

	private:
		bool* onDerivedDestructed = nullptr;
	};
}

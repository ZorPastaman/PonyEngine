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
	class DerivedWithParams : public Base
	{
	public:
		[[nodiscard("Pure constructor")]]
		DerivedWithParams(int i, bool b) noexcept;
		[[nodiscard("Pure constructor")]]
		DerivedWithParams(const DerivedWithParams& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		DerivedWithParams(DerivedWithParams&& other) noexcept = default;

		~DerivedWithParams() noexcept = default;

		[[nodiscard("Pure function")]]
		int GetIParam() const noexcept;
		[[nodiscard("Pure function")]]
		bool GetBParam() const noexcept;

		DerivedWithParams& operator =(const DerivedWithParams& other) noexcept = default;
		DerivedWithParams& operator =(DerivedWithParams&& other) noexcept = default;

	private:
		int iParam;
		bool bParam;
	};
}

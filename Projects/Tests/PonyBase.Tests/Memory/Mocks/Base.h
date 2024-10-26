/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

namespace Memory
{
	class Base
	{
	public:
		[[nodiscard("Pure constructor")]]
		Base() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Base(const Base& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Base(Base&& other) noexcept = default;

		~Base() noexcept;

		void SetOnBaseDestructed(bool* onDestructed);

		Base& operator =(const Base& other) noexcept = default;
		Base& operator =(Base&& other) noexcept = default;

	private:
		bool* onBaseDestructed = nullptr;
	};
}

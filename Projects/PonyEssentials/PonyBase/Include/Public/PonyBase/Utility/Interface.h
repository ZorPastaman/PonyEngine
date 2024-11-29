/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

/// @brief Interface body macro. It must be used inside an interface body.
/// @param InterfaceName Interface name. Must be the same as the class name where the body is declared.
#define INTERFACE_BODY(InterfaceName) \
	protected: \
		[[nodiscard("Pure constructor")]] \
		InterfaceName() noexcept = default; \
		[[nodiscard("Pure constructor")]] \
		InterfaceName(const InterfaceName& other) noexcept = default; \
		[[nodiscard("Pure constructor")]] \
		InterfaceName(InterfaceName&& other) noexcept = default; \
		 \
		~InterfaceName() noexcept = default; \
		 \
		InterfaceName& operator =(const InterfaceName& other) noexcept = default; \
		InterfaceName& operator =(InterfaceName&& other) noexcept = default; \
		 \
	public:

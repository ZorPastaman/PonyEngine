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
	public: \
		InterfaceName(const InterfaceName&) = delete; \
		InterfaceName(InterfaceName&&) = delete; \
		 \
		InterfaceName& operator =(const InterfaceName&) = delete; \
		InterfaceName& operator =(InterfaceName&&) = delete; \
		 \
	protected: \
		[[nodiscard("Pure constructor")]] \
		InterfaceName() noexcept = default; \
		 \
		~InterfaceName() noexcept = default; \
		 \
	public:

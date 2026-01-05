/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

/// @brief Interface body macro. It must be used inside an interface class.
/// @param interfaceName Interface name. Must be the same as a class name where the body is declared.
#define PONY_INTERFACE_BODY(interfaceName) \
	protected: \
		[[nodiscard("Pure constructor")]] \
		interfaceName() noexcept = default; \
		[[nodiscard("Pure constructor")]] \
		interfaceName(const interfaceName& other) noexcept = default; \
		[[nodiscard("Pure constructor")]] \
		interfaceName(interfaceName&& other) noexcept = default; \
		 \
		~interfaceName() noexcept = default; \
		 \
		interfaceName& operator =(const interfaceName& other) noexcept = default; \
		interfaceName& operator =(interfaceName&& other) noexcept = default; \
		 \
	public:

/// @brief Non-constructible class body macro. It must be used inside a base class.
/// @param objectName Class name. Must be the same as a class name where the body is declared.
#define PONY_NON_CONSTRUCTIBLE_BODY(objectName) \
	public: \
		objectName() = delete; \
		objectName(const objectName&) = delete; \
		objectName(objectName&&) = delete; \
		 \
		~objectName() = delete; \
		 \
		objectName& operator =(const objectName&) = delete; \
		objectName& operator =(objectName&&) = delete; \

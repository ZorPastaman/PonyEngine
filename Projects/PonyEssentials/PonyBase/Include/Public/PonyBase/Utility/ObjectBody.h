/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

 /// @brief Base body macro. It must be used inside a base class.
 /// @param baseName Base name. Must be the same as a class name where the body is declared.
#define BASE_BODY(baseName) \
	public: \
		virtual ~baseName() noexcept = default; \
	 \
	protected: \
		[[nodiscard("Pure constructor")]] \
		baseName() noexcept = default; \
		[[nodiscard("Pure constructor")]] \
		baseName(const baseName& other) noexcept = default; \
		[[nodiscard("Pure constructor")]] \
		baseName(baseName&& other) noexcept = default; \
		 \
		baseName& operator =(const baseName& other) noexcept = default; \
		baseName& operator =(baseName&& other) noexcept = default; \
		 \
	private:

 /// @brief Base body macro that doesn't add a default constructor. It must be used inside a base class.
 /// @param baseName Base name. Must be the same as a class name where the body is declared.
#define BASE_BODY_WITHOUT_CONSTRUCTOR(baseName) \
	public: \
		virtual ~baseName() noexcept = default; \
	 \
	protected: \
		[[nodiscard("Pure constructor")]] \
		baseName(const baseName& other) noexcept = default; \
		[[nodiscard("Pure constructor")]] \
		baseName(baseName&& other) noexcept = default; \
		 \
		baseName& operator =(const baseName& other) noexcept = default; \
		baseName& operator =(baseName&& other) noexcept = default; \
		 \
	private:

/// @brief Interface body macro. It must be used inside an interface class.
/// @param interfaceName Interface name. Must be the same as a class name where the body is declared.
#define INTERFACE_BODY(interfaceName) \
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

#define NON_CONSTRUCTIBLE_BODY(objectName) \
	public: \
		objectName() = delete; \
		objectName(const objectName&) = delete; \
		objectName(objectName&&) = delete; \
		 \
		~objectName() = delete; \
		 \
		objectName& operator =(const objectName&) = delete; \
		objectName& operator =(objectName&&) = delete; \

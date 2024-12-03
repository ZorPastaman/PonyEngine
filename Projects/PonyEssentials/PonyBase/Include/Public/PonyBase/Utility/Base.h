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

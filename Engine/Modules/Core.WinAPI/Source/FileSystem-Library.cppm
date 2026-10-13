/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.FileSystem:Library;

import std;

export namespace PonyEngine::FileSystem
{
	/// @brief Loads a library by the path.
	/// @param path Library path.
	/// @return Library.
	[[nodiscard("Must be used")]]
	void* AcquireLibrary(const std::filesystem::path& path);
	/// @brief Frees the library.
	/// @param library Library pointer.
	void ReleaseLibrary(void* library);

	/// @brief Gets a library address by the name.
	/// @param library Library. Must be valid.
	/// @param name Name.
	/// @return Library address.
	[[nodiscard("Pure function")]]
	void* GetAddress(void* library, const char* name);
	/// @brief Gets a library address by the name.
	/// @param library Library. Must be valid.
	/// @param name Name.
	/// @return Library address.
	[[nodiscard("Pure function")]]
	void* GetAddress(void* library, std::string_view name);
}

namespace PonyEngine::FileSystem
{
	/// @brief Load library function selector.
	/// @tparam CharT Path value type. Must be @p char or @p wchar_t.
	template<typename CharT>
	struct LoadLibrarySelector;
	template<>
	struct LoadLibrarySelector<char>
	{
		static constexpr auto Value = &LoadLibraryA; ///< @p LoadLibraryA.
	};
	template<>
	struct LoadLibrarySelector<wchar_t>
	{
		static constexpr auto Value = &LoadLibraryW; ///< @p LoadLibraryW.
	};

	void* AcquireLibrary(const std::filesystem::path& path)
	{
		const HMODULE library = LoadLibrarySelector<std::filesystem::path::value_type>::Value(path.c_str());
		if (!library)
		{
			throw std::runtime_error(std::format("Failed to load library at '{}': Error code = '{}'", path.string(), GetLastError()));
		}

		return library;
	}

	void ReleaseLibrary(void* const library)
	{
		if (!library) [[unlikely]]
		{
			throw std::invalid_argument("Library is nullptr");
		}

		if (!FreeLibrary(static_cast<HMODULE>(library))) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to free library at '0x{:X}': Error code = '{}'", reinterpret_cast<std::uintptr_t>(library), GetLastError()));
		}
	}

	void* GetAddress(void* const library, const char* const name)
	{
		if (!library) [[unlikely]]
		{
			throw std::invalid_argument("Library is nullptr");
		}

		const FARPROC address = GetProcAddress(static_cast<HMODULE>(library), name);
		if (!address) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get address: Library = '0x{:X}', Name = '{}', Error code = '{}'", 
				reinterpret_cast<std::uintptr_t>(library), name, GetLastError()));
		}

		return address;
	}

	void* GetAddress(void* const library, const std::string_view name)
	{
		return GetAddress(library, name.data());
	}
}

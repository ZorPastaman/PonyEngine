/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.FileSystem:DynamicLibrary;

import std;

import :Library;

export namespace PonyEngine::FileSystem
{
	/// @brief Dynamic library raii wrapper.
	class DynamicLibrary final
	{
	public:
		/// @brief Creates an empty dynamic library.
		[[nodiscard("Pure constructor")]]
		DynamicLibrary() noexcept;
		/// @brief Creates a dynamic library with a loaded library at the path.
		/// @param path Library path.
		[[nodiscard("Pure constructor")]]
		explicit DynamicLibrary(const std::filesystem::path& path);
		DynamicLibrary(const DynamicLibrary&) = delete;
		[[nodiscard("Pure constructor")]]
		DynamicLibrary(DynamicLibrary&& other) noexcept;

		~DynamicLibrary() noexcept;

		/// @brief Checks if the dynamic library has a loaded library.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsValid() const noexcept;

		/// @brief Gets a library address by the name.
		/// @param name Name.
		/// @return Library address.
		/// @note Must have a loaded library.
		[[nodiscard("Pure function")]]
		void* GetAddress(const char* name) const;
		/// @brief Gets a library address by the name.
		/// @param name Name.
		/// @return Library address.
		/// @note Must have a loaded library.
		[[nodiscard("Pure function")]]
		void* GetAddress(std::string_view name) const;

		/// @brief Checks if the dynamic library has a loaded library.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		DynamicLibrary& operator =(const DynamicLibrary&) = delete;
		DynamicLibrary& operator =(DynamicLibrary&& other) noexcept;

	private:
		void* library; ///< Library pointer.
	};
}

namespace PonyEngine::FileSystem
{
	DynamicLibrary::DynamicLibrary() noexcept :
		library{nullptr}
	{
	}

	DynamicLibrary::DynamicLibrary(const std::filesystem::path& path) :
		library{AcquireLibrary(path)}
	{
	}

	DynamicLibrary::DynamicLibrary(DynamicLibrary&& other) noexcept :
		library{other.library}
	{
		other.library = nullptr;
	}

	DynamicLibrary::~DynamicLibrary() noexcept
	{
		if (library)
		{
			ReleaseLibrary(library);
		}
	}

	bool DynamicLibrary::IsValid() const noexcept
	{
		return library;
	}

	void* DynamicLibrary::GetAddress(const char* const name) const
	{
		return FileSystem::GetAddress(library, name);
	}

	void* DynamicLibrary::GetAddress(const std::string_view name) const
	{
		return FileSystem::GetAddress(library, name);
	}

	DynamicLibrary::operator bool() const noexcept
	{
		return library;
	}

	DynamicLibrary& DynamicLibrary::operator =(DynamicLibrary&& other) noexcept
	{
		if (library)
		{
			ReleaseLibrary(library);
		}

		library = other.library;
		other.library = nullptr;

		return *this;
	}
}

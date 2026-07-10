/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Meta:Version;

import std;

export namespace PonyEngine::Meta
{
	/// @brief Version.
	class Version final
	{
	public:
		static constexpr std::size_t VersionNumberCount = 4uz; ///< Version number count.

		/// @brief Creates a version 0.0.0.0.
		[[nodiscard("Pure constructor")]]
		constexpr Version() noexcept = default;
		/// @brief Creates a version <major>.0.0.0.
		/// @param major Major version.
		[[nodiscard("Pure constructor")]]
		explicit constexpr Version(std::uint32_t major) noexcept;
		/// @brief Creates a version <major>.<minor>.0.0.
		/// @param major Major version.
		/// @param minor Minor version.
		[[nodiscard("Pure constructor")]]
		constexpr Version(std::uint32_t major, std::uint32_t minor) noexcept;
		/// @brief Creates a version <major>.<minor>.<patch>.0.
		/// @param major Major version.
		/// @param minor Minor version.
		/// @param patch Patch version.
		[[nodiscard("Pure constructor")]]
		constexpr Version(std::uint32_t major, std::uint32_t minor, std::uint32_t patch) noexcept;
		/// @brief Creates a version <major>.<minor>.<patch>.<tweak>.
		/// @param major Major version.
		/// @param minor Minor version.
		/// @param patch Patch version.
		/// @param tweak Tweak version.
		[[nodiscard("Pure constructor")]]
		constexpr Version(std::uint32_t major, std::uint32_t minor, std::uint32_t patch, std::uint32_t tweak) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Version(const Version& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Version(Version&& other) noexcept = default;

		constexpr ~Version() noexcept = default;

		/// @brief Gets the major version.
		/// @return Major version.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t& Major() noexcept;
		/// @brief Gets the major version.
		/// @return Major version.
		[[nodiscard("Pure function")]]
		constexpr const std::uint32_t& Major() const noexcept;
		/// @brief Gets the minor version.
		/// @return Minor version.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t& Minor() noexcept;
		/// @brief Gets the minor version.
		/// @return Minor version.
		[[nodiscard("Pure function")]]
		constexpr const std::uint32_t& Minor() const noexcept;
		/// @brief Gets the patch version.
		/// @return Patch version.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t& Patch() noexcept;
		/// @brief Gets the patch version.
		/// @return Patch version.
		[[nodiscard("Pure function")]]
		constexpr const std::uint32_t& Patch() const noexcept;
		/// @brief Gets the tweak version.
		/// @return Tweak version.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t& Tweak() noexcept;
		/// @brief Gets the tweak version.
		/// @return Tweak version.
		[[nodiscard("Pure function")]]
		constexpr const std::uint32_t& Tweak() const noexcept;
		/// @brief Gets the data.
		/// @return Data. Version order: major, minor, patch, tweak.
		[[nodiscard("Pure function")]]
		constexpr std::uint32_t* Data() noexcept;
		/// @brief Gets the data.
		/// @return Data. Version order: major, minor, patch, tweak.
		[[nodiscard("Pure function")]]
		constexpr const std::uint32_t* Data() const noexcept;

		/// @brief Gets a version.
		/// @param index Version index. Order: major, minor, patch, tweak.
		/// @return Version.
		[[nodiscard("Pure operator")]]
		constexpr std::uint32_t& operator [](std::size_t index) noexcept;
		/// @brief Gets a version.
		/// @param index Version index. Order: major, minor, patch, tweak.
		/// @return Version.
		[[nodiscard("Pure operator")]]
		constexpr const std::uint32_t& operator [](std::size_t index) const noexcept;

		constexpr Version& operator =(const Version& other) noexcept = default;
		constexpr Version& operator =(Version&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const Version& other) const noexcept = default;

	private:
		std::array<std::uint32_t, VersionNumberCount> versions; ///< Versions. Order: major, minor, patch, tweak.
	};
}

/// @brief Version formatter.
/// @details The format is ":<version_args>".
///          Version args: n[1:4] - version number count.
export template<>
struct std::formatter<PonyEngine::Meta::Version, char>
{
private:
	std::size_t numbers = 3; ///< Version number count.

public:
	constexpr std::format_parse_context::iterator parse(std::format_parse_context& context)
	{
		auto it = context.begin();

#ifndef NDEBUG
		if (it == context.end()) [[unlikely]]
		{
			throw std::format_error("Unexpected context end");
		}
#endif

		for (; *it != '}'; ++it)
		{
			switch (*it)
			{
			case 'n':
				++it;
				switch (*it)
				{
				case '1':
					numbers = 1;
					break;
				case '2':
					numbers = 2;
					break;
				case '3':
					numbers = 3;
					break;
				case '4':
					numbers = 4;
					break;
				default: [[unlikely]]
#ifndef NDEBUG
					throw std::format_error("Unexpected version number count specifier");
#else
					break;
#endif
				}
				break;
			default: [[unlikely]]
#ifndef NDEBUG
				throw std::format_error("Unexpected format specifier");
#else
				break;
#endif
			}
		}

		return it;
	}

	std::format_context::iterator format(const PonyEngine::Meta::Version& version, std::format_context& context) const
	{
		auto it = context.out();

		for (std::size_t i = 0uz; i < numbers; ++i)
		{
			it = std::format_to(it, "{}", version[i]);
			
			if (i < numbers - 1uz)
			{
				*it++ = '.';
			}
		}

		return it;
	}
};

namespace PonyEngine::Meta
{
	constexpr Version::Version(const std::uint32_t major) noexcept :
		Version(major, 0u, 0u, 0u)
	{
	}

	constexpr Version::Version(const std::uint32_t major, const std::uint32_t minor) noexcept :
		Version(major, minor, 0u, 0u)
	{
	}

	constexpr Version::Version(const std::uint32_t major, const std::uint32_t minor, const std::uint32_t patch) noexcept :
		Version(major, minor, patch, 0u)
	{
	}

	constexpr Version::Version(const std::uint32_t major, const std::uint32_t minor, const std::uint32_t patch, const std::uint32_t tweak) noexcept :
		versions{major, minor, patch, tweak}
	{
	}

	constexpr std::uint32_t& Version::Major() noexcept
	{
		return versions[0];
	}

	constexpr const std::uint32_t& Version::Major() const noexcept
	{
		return versions[0];
	}

	constexpr std::uint32_t& Version::Minor() noexcept
	{
		return versions[1];
	}

	constexpr const std::uint32_t& Version::Minor() const noexcept
	{
		return versions[1];
	}

	constexpr std::uint32_t& Version::Patch() noexcept
	{
		return versions[2];
	}

	constexpr const std::uint32_t& Version::Patch() const noexcept
	{
		return versions[2];
	}

	constexpr std::uint32_t& Version::Tweak() noexcept
	{
		return versions[3];
	}

	constexpr const std::uint32_t& Version::Tweak() const noexcept
	{
		return versions[3];
	}

	constexpr std::uint32_t* Version::Data() noexcept
	{
		return versions.data();
	}

	constexpr const std::uint32_t* Version::Data() const noexcept
	{
		return versions.data();
	}

	constexpr std::uint32_t& Version::operator [](const std::size_t index) noexcept
	{
		return versions[index];
	}

	constexpr const std::uint32_t& Version::operator [](const std::size_t index) const noexcept
	{
		return versions[index];
	}
}

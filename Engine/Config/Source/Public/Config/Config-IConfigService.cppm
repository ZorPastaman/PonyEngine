/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Config:IConfigService;

import std;

export namespace PonyEngine::Config
{
	/// @brief Config service.
	class IConfigService
	{
		INTERFACE_BODY(IConfigService)

		/// @brief Checks if the config service contains a value associated with the @p key.
		/// @param key Key.
		/// @return @a True if it contains a value; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool HasValue(std::string_view key) const noexcept = 0;
		/// @brief Checks if the config service contains a value associated with the @p key that can be parsed as the @p type.
		/// @param type Value type.
		/// @param key Key.
		/// @return @a True if it contains a value that can be parsed; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool HasValue(const std::type_info& type, std::string_view key) const noexcept = 0;
		/// @brief Checks if the config service contains a value associated with the @p key that can be parsed as the @p T.
		/// @tparam T Value type.
		/// @param key Key.
		/// @return @a True if it contains a value that can be parsed; @a false otherwise.
		template<typename T> [[nodiscard("Pure function")]]
		bool HasValue(std::string_view key) const noexcept;

		/// @brief Gets a raw value associated with the @p key.
		/// @param key Key.
		/// @return Requested raw value if the config has it; empty string otherwise.
		[[nodiscard("Pure function")]]
		virtual std::string_view GetValue(std::string_view key) const noexcept = 0;
		/// @brief Gets a value associated with the @p key and parsed as the @p type.
		/// @param type Value type.
		/// @param key Key.
		/// @return Requested value if the config has it and it can be parsed as @p type; empty any otherwise.
		[[nodiscard("Pure function")]]
		virtual std::any GetValue(const std::type_info& type, std::string_view key) const noexcept = 0;
		/// @brief Gets a value associated with the @p key and parsed as the @p type or the @p defaultValue otherwise.
		/// @param type Value type.
		/// @param key Key.
		/// @param defaultValue Default value.
		/// @return Requested value if the config has it and it can be parsed as @p type; @p defaultValue otherwise.
		[[nodiscard("Pure function")]]
		std::any GetValue(const std::type_info& type, std::string_view key, const std::any& defaultValue) const noexcept;
		/// @brief Gets a value associated with the @p key and parsed as the @p T.
		/// @tparam T Value type.
		/// @param key Key.
		/// @return Requested value if the config has it and it can be parsed as @p T; nullopt otherwise.
		template<typename T> [[nodiscard("Pure function")]]
		std::optional<T> GetValue(std::string_view key) const noexcept;
		/// @brief Gets a value associated with the @p key and parsed as the @p T or the @p defaultValue otherwise.
		/// @tparam T Value type.
		/// @param key Key.
		/// @param defaultValue Default value.
		/// @return Requested value if the config has it and it can be parsed as @p T; @p defaultValue otherwise.
		template<typename T> [[nodiscard("Pure function")]]
		T GetValue(std::string_view key, const T& defaultValue) const noexcept;

		/// @brief Sets the @p value associated with the @p key.
		/// @param key Key.
		/// @param value Value.
		/// @remark If the @p value is empty, the functions removes the key-value pair.
		virtual void SetValue(std::string_view key, const std::any& value) = 0;

		/// @brief Checks if the config service can save data.
		/// @return @a True if it can save; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool CanSave() const noexcept = 0;
		/// @brief Checks if the config service can save a data with the @p key.
		/// @param key Key.
		/// @return @a True if it can save; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool CanSave(std::string_view key) const noexcept = 0;
		/// @brief Checks if the config service can save a data with the @p keys.
		/// @param keys Keys.
		/// @return @a True if it can save; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool CanSave(std::span<const std::string_view> keys) const noexcept = 0;

		/// @brief Saves all the current data that can be saved.
		virtual void Save() = 0;
		/// @brief Saves all the current data that can be saved and associated with the @p keys.
		/// @param keys Keys.
		virtual void Save(std::span<const std::string_view> keys) = 0;
	};
}

namespace PonyEngine::Config
{
	std::any IConfigService::GetValue(const std::type_info& type, const std::string_view key, const std::any& defaultValue) const noexcept
	{
		const std::any value = GetValue(type, key);
		return value ? value : defaultValue;
	}

	template<typename T>
	bool IConfigService::HasValue(const std::string_view key) const noexcept
	{
		return HasValue(typeid(T), key);
	}

	template<typename T>
	std::optional<T> IConfigService::GetValue(const std::string_view key) const noexcept
	{
		const std::any value = GetValue(typeid(T), key);
		return value ? std::optional<T>(std::any_cast<T>(value)) : std::nullopt;
	}

	template<typename T>
	T IConfigService::GetValue(const std::string_view key, const T& defaultValue) const noexcept
	{
		const std::any value = GetValue(typeid(T), key);
		return value ? std::any_cast<T>(value) : defaultValue;
	}
}

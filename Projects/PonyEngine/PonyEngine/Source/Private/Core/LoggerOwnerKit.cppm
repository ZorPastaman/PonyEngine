/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:LoggerOwnerKit;

import <utility>;
import <vector>;

import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;

namespace PonyEngine::Core
{
	/// @brief Holds pointers to a logger and its entries which lifetimes are controlled by an @p Engine.
	export struct LoggerOwnerKit final
	{
	public:
		/// @brief Creates a @p LoggerOwnerKit with default initialized values.
		[[nodiscard("Pure constructor")]]
		inline LoggerOwnerKit() noexcept;
		LoggerOwnerKit(const LoggerOwnerKit& other) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		inline LoggerOwnerKit(LoggerOwnerKit&& other) noexcept;

		inline ~LoggerOwnerKit() noexcept = default;

		/// @brief Move assignment.
		/// @param other Move source.
		/// @return @a This.
		inline LoggerOwnerKit& operator =(LoggerOwnerKit&& other) noexcept;

		std::vector<Debug::Log::ISubLogger*> subLoggers; /// @brief Main sub-loggers. The owner must destroy them on its destruction.
		Debug::Log::IEngineLogger* logger; /// @brief Logger.
	};

	inline LoggerOwnerKit::LoggerOwnerKit() noexcept :
		subLoggers{},
		logger{}
	{
	}

	inline LoggerOwnerKit::LoggerOwnerKit(LoggerOwnerKit&& other) noexcept :
		subLoggers(std::move(other.subLoggers)),
		logger{other.logger}
	{
	}

	inline LoggerOwnerKit& LoggerOwnerKit::operator =(LoggerOwnerKit&& other) noexcept
	{
		subLoggers = std::move(other.subLoggers);
		logger = other.logger;

		return *this;
	}
}

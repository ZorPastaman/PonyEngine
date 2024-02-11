/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Engine:LoggerOwnerKit;

import <utility>;
import <vector>;

import PonyEngine.Debug.Log.ILogger;
import PonyEngine.Debug.Log.ISubLogger;

namespace PonyEngine::Core
{
	/// @brief Holds pointers to a logger and its entries which lifetimes are controlled by an @p Engine.
	export struct LoggerOwnerKit final
	{
	public:
		[[nodiscard("Pure constructor")]]
		LoggerOwnerKit() noexcept;
		LoggerOwnerKit(const LoggerOwnerKit& other) = delete;
		[[nodiscard("Pure constructor")]]
		LoggerOwnerKit(LoggerOwnerKit&& other) noexcept;

		~LoggerOwnerKit() noexcept = default;

		std::vector<Debug::Log::ISubLogger*> subLoggers;
		Debug::Log::ILogger* logger;
	};

	LoggerOwnerKit::LoggerOwnerKit() noexcept :
		subLoggers{},
		logger{}
	{
	}

	LoggerOwnerKit::LoggerOwnerKit(LoggerOwnerKit&& other) noexcept :
		subLoggers(std::move(other.subLoggers)),
		logger{other.logger}
	{
	}
}

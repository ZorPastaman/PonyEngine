/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Debug.Log.Implementation:ConsoleSubLoggerFactory;

import PonyEngine.Debug.Log.Factories;

import :ConsoleSubLogger;

namespace PonyEngine::Debug::Log
{
	/// @brief Console sub-logger factory.
	export class ConsoleSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		[[nodiscard("Pure constructor")]]
		inline ConsoleSubLoggerFactory() noexcept = default;
		ConsoleSubLoggerFactory(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory(ConsoleSubLoggerFactory&&) = delete;

		inline virtual ~ConsoleSubLoggerFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		inline virtual ISubLogger* Create(Core::IEngine&) override;
		inline virtual void Destroy(ISubLogger* subLogger) noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual const char* GetSubLoggerName() const noexcept override;

		ConsoleSubLoggerFactory& operator =(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory& operator =(ConsoleSubLoggerFactory&&) = delete;
	};

	inline ISubLogger* ConsoleSubLoggerFactory::Create(Core::IEngine&)
	{
		return new ConsoleSubLogger();
	}

	inline void ConsoleSubLoggerFactory::Destroy(ISubLogger* const subLogger) noexcept
	{
		assert((dynamic_cast<ConsoleSubLogger*>(subLogger) != nullptr));
		delete static_cast<ConsoleSubLogger*>(subLogger);
	}

	inline const char* ConsoleSubLoggerFactory::GetSubLoggerName() const noexcept
	{
		return ConsoleSubLogger::Name;
	}
}

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

export module PonyEngine.Debug.Log.Factories.Implementation:ConsoleSubLoggerFactory;

import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Debug.Log.Factories;

namespace PonyEngine::Debug::Log
{
	export class ConsoleSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		inline ConsoleSubLoggerFactory() = default;
		ConsoleSubLoggerFactory(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory(ConsoleSubLoggerFactory&&) = delete;

		inline ~ConsoleSubLoggerFactory() = default;

		[[nodiscard("Pure function")]]
		virtual ISubLogger* Create(Core::IEngine& engine) override;
		virtual void Destroy(ISubLogger* subLogger) noexcept override;

		virtual const char* GetSubLoggerName() const noexcept override;

		ConsoleSubLoggerFactory& operator =(const ConsoleSubLoggerFactory&) = delete;
		ConsoleSubLoggerFactory& operator =(ConsoleSubLoggerFactory&&) = delete;
	};

	ISubLogger* ConsoleSubLoggerFactory::Create(Core::IEngine&)
	{
		return new ConsoleSubLogger();
	}

	void ConsoleSubLoggerFactory::Destroy(ISubLogger* subLogger) noexcept
	{
		assert((dynamic_cast<ConsoleSubLogger*>(subLogger) != nullptr));
		delete static_cast<ConsoleSubLogger*>(subLogger);
	}

	const char* ConsoleSubLoggerFactory::GetSubLoggerName() const noexcept
	{
		return ConsoleSubLogger::Name;
	}
}

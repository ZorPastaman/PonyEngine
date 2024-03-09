/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Factories.Implementation:ConsoleSubLoggerFactory;

import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Debug.Log.Factories;

namespace PonyEngine::Debug::Log
{
	export class ConsoleSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		ConsoleSubLoggerFactory() = default;
		~ConsoleSubLoggerFactory() = default;

		[[nodiscard("Pure function")]]
		virtual ISubLogger* Create(Core::IEngine& engine) override;
		virtual void Destroy(ISubLogger* subLogger) override;
	};

	ISubLogger* ConsoleSubLoggerFactory::Create(Core::IEngine& engine)
	{
		return new ConsoleSubLogger();
	}

	void ConsoleSubLoggerFactory::Destroy(ISubLogger* subLogger)
	{
		delete static_cast<ConsoleSubLogger*>(subLogger);
	}
}

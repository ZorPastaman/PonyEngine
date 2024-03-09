/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Factories.Implementation;

import PonyEngine.Debug.Log.Factories;

import :ConsoleSubLoggerFactory;
import :FileSubLoggerFactory;

namespace PonyEngine::Debug::Log
{
	export ISubLoggerFactory* CreateConsoleSubLoggerFactory();
	export void DestroyConsoleSubLoggerFactory(ISubLoggerFactory* subLogger);

	export ISubLoggerFactory* CreateFileSubLoggerFactory();
	export void DestroyFileSubLoggerFactory(ISubLoggerFactory* subLogger);

	ISubLoggerFactory* CreateConsoleSubLoggerFactory()
	{
		return new ConsoleSubLoggerFactory();
	}

	void DestroyConsoleSubLoggerFactory(ISubLoggerFactory* subLogger)
	{
		delete static_cast<ConsoleSubLoggerFactory*>(subLogger);
	}

	ISubLoggerFactory* CreateFileSubLoggerFactory()
	{
		return new FileSubLoggerFactory();
	}

	void DestroyFileSubLoggerFactory(ISubLoggerFactory* subLogger)
	{
		delete static_cast<FileSubLoggerFactory*>(subLogger);
	}
}

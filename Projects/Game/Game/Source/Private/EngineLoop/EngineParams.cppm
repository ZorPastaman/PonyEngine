/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module EngineRunner:EngineParams;

import <functional>;
import <iostream>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Input;
import PonyEngine.Input.Implementation;

namespace Game
{
	export [[nodiscard("Pure function")]]
	PonyEngine::Core::EngineParams GetEngineParams();

	static void GetLoggerParams(PonyEngine::Core::LoggerParams& loggerParams);

	static void GetWindowParams(PonyEngine::Core::WindowParams& windowParams);

	static void GetServiceParams(std::vector<PonyEngine::Core::ServiceFactoryInfo>& serviceFactoryInfos);
	static void GetSystemParams(std::vector<PonyEngine::Core::SystemFactoryInfo>& systemFactoryInfos);

	PonyEngine::Core::EngineParams GetEngineParams()
	{
		PONY_COUT("Create engine params.");
		PonyEngine::Core::EngineParams engineParams;
		PONY_COUT("Create logger params.");
		GetLoggerParams(engineParams.loggerParams);
		PONY_COUT("Logger params created.");
		PONY_COUT("Create window params.");
		GetWindowParams(engineParams.windowParams);
		PONY_COUT("Window params created.");
		PONY_COUT("Create service factories.");
		GetServiceParams(engineParams.serviceFactoryInfos);
		PONY_COUT("Service factories created.");
		PONY_COUT("Create system factories.");
		GetSystemParams(engineParams.systemFactoryInfos);
		PONY_COUT("System factories created.");
		PONY_COUT("Engine params created.");

		return engineParams;
	}

	void GetLoggerParams(PonyEngine::Core::LoggerParams& loggerParams)
	{
	}

	void GetWindowParams(PonyEngine::Core::WindowParams& windowParams)
	{
	}

	void GetServiceParams(std::vector<PonyEngine::Core::ServiceFactoryInfo>& serviceFactoryInfos)
	{
	}

	void GetSystemParams(std::vector<PonyEngine::Core::SystemFactoryInfo>& systemFactoryInfos)
	{
		PONY_COUT("Create an input system factory.");
		systemFactoryInfos.push_back(PonyEngine::Input::CreateSystemFactoryInfo());
		PONY_COUT("Input system factory created.");
	}
}

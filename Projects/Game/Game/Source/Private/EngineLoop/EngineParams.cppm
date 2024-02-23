/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module EngineRunner:EngineParams;

import <functional>;
import <vector>;

import PonyEngine.Core;
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
		PonyEngine::Core::EngineParams engineParams;
		GetLoggerParams(engineParams.loggerParams);
		GetWindowParams(engineParams.windowParams);
		GetServiceParams(engineParams.serviceFactoryInfos);
		GetSystemParams(engineParams.systemFactoryInfos);

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
		systemFactoryInfos.push_back(PonyEngine::Input::CreateSystemFactoryInfo());
	}
}

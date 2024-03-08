/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factories:EngineParams;

import <vector>;
import <utility>;

import PonyEngine.Debug.Log.Factories;
import PonyEngine.Window.Factories;

import :IServiceFactory;
import :ISystemFactory;

namespace PonyEngine::Core
{
	/// @brief Holds engine parameters.
	export struct EngineParams final
	{
	public:
		/// @brief Creates an @p EngineParams.
		[[nodiscard("Pure constructor")]]
		EngineParams();
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		EngineParams(const EngineParams& other);
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		EngineParams(EngineParams&& other);

		~EngineParams() noexcept = default;

		EngineParams& operator =(const EngineParams& other);
		EngineParams& operator =(EngineParams&& other) noexcept;

		std::vector<Debug::Log::ISubLoggerFactory*> subLoggerFactories;
		std::vector<IServiceFactory*> serviceFactories;
		std::vector<ISystemFactory*> systemFactories;
		Window::IWindowFactory* windowFactory;
	};

	EngineParams::EngineParams() :
		subLoggerFactories{},
		serviceFactories{},
		systemFactories{},
		windowFactory{}
	{
	}

	EngineParams::EngineParams(const EngineParams& other) :
		subLoggerFactories{other.subLoggerFactories},
		serviceFactories{other.serviceFactories},
		systemFactories{other.systemFactories},
		windowFactory{other.windowFactory}
	{
	}

	EngineParams::EngineParams(EngineParams&& other) :
		subLoggerFactories(std::move(other.subLoggerFactories)),
		serviceFactories(std::move(other.serviceFactories)),
		systemFactories(std::move(other.systemFactories)),
		windowFactory{other.windowFactory}
	{
	}

	EngineParams& EngineParams::operator=(const EngineParams& other)
	{
		subLoggerFactories = other.subLoggerFactories;
		serviceFactories = other.serviceFactories;
		systemFactories = other.systemFactories;
		windowFactory = other.windowFactory;

		return *this;
	}

	EngineParams& EngineParams::operator=(EngineParams&& other) noexcept
	{
		subLoggerFactories = std::move(other.subLoggerFactories);
		serviceFactories = std::move(other.serviceFactories);
		systemFactories = std::move(other.systemFactories);
		windowFactory = other.windowFactory;

		return *this;
	}
}

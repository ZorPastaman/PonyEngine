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
		[[nodiscard("Pure constructor")]]
		EngineParams() = default;
		[[nodiscard("Pure constructor")]]
		EngineParams(const EngineParams& other) = default;
		[[nodiscard("Pure constructor")]]
		EngineParams(EngineParams&& other) noexcept = default;

		~EngineParams() noexcept = default;

		EngineParams& operator =(const EngineParams& other) = default;
		EngineParams& operator =(EngineParams&& other) noexcept = default;

		std::vector<Debug::Log::ISubLoggerFactory*> subLoggerFactories; /// @brief Sub-logger factories. Their lifetimes must exceed the engine lifetime.
		std::vector<IServiceFactory*> serviceFactories; /// @brief Service factories. Their lifetimes must exceed the engine lifetime.
		std::vector<ISystemFactory*> systemFactories; /// @brief System factories. Their lifetimes must exceed the engine lifetime.
		Window::IWindowFactory* windowFactory; /// @brief Window factory. It's optional and can be nullptr. If it's not nullptr, its lifetime must exceed the engine lifetime.
	};
}

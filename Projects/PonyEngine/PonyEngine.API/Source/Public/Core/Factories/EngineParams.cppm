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

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Core.Factories:EngineParams;

import <algorithm>;
import <cstddef>;
import <vector>;

import PonyEngine.Debug.Log;
import PonyEngine.Window.Factories;

import :ISystemFactory;

namespace PonyEngine::Core
{
	/// @brief Holds engine parameters.
	export class EngineParams final
	{
	public:
		/// @brief System factories iterator.
		class SystemFactoriesIterator final
		{
		public:
			[[nodiscard("Pure constructor")]]
			inline SystemFactoriesIterator(const SystemFactoriesIterator& other) noexcept = default;

			inline ~SystemFactoriesIterator() noexcept = default;

			/// @brief Gets a currently pointed system factory.
			/// @return Currently pointed system factory.
			[[nodiscard("Pure operator")]]
			inline ISystemFactory* operator *() const noexcept;
			/// @brief Moves a pointer to the next system factory.
			/// @return New iterator.
			inline SystemFactoriesIterator& operator ++() noexcept;
			/// @brief Moves a pointer to the next system factory.
			/// @return Previous iterator.
			inline SystemFactoriesIterator operator ++(int) noexcept;

			/// @brief Checks if the currently pointed system factory is actually an end.
			/// @return @a True if the end is reached; @false otherwise.
			[[nodiscard("Pure function")]]
			inline bool IsEnd() const noexcept;

			inline SystemFactoriesIterator& operator =(const SystemFactoriesIterator& other) noexcept = default;

			[[nodiscard("Pure operator")]]
			inline bool operator ==(const SystemFactoriesIterator& other) const noexcept = default;

		private:
			/// @brief Creates a @p SystemFactoriesIterator.
			/// @param begin System factories begin.
			/// @param end System factories end.
			[[nodiscard("Pure constructor")]]
			inline SystemFactoriesIterator(std::vector<ISystemFactory*>::const_iterator begin, std::vector<ISystemFactory*>::const_iterator end) noexcept;

			std::vector<ISystemFactory*>::const_iterator m_current; /// @brief Current system factory.
			std::vector<ISystemFactory*>::const_iterator m_end; /// @brief System factories iterator end.

			friend EngineParams;
		};

		/// @brief Create an engine params.
		/// @param logger Logger to use.
		[[nodiscard("Pure constructor")]]
		inline EngineParams(Debug::Log::ILogger& logger) noexcept;
		[[nodiscard("Pure constructor")]]
		inline EngineParams(const EngineParams& other) = default;
		[[nodiscard("Pure constructor")]]
		inline EngineParams(EngineParams&& other) noexcept = default;

		inline ~EngineParams() noexcept = default;

		/// @brief Gets a logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		inline Debug::Log::ILogger& GetLogger() const noexcept;

		/// @brief Adds a system factory.
		/// @param systemFactory System factory. It must be unique in one @p EngineParams.
		inline void AddSystemFactory(ISystemFactory* systemFactory);
		/// @brief Gets a system factories iterator.
		/// @return System factories iterator.
		[[nodiscard("Pure function")]]
		inline SystemFactoriesIterator GetSystemFactoriesIterator() const noexcept;

		/// @brief Gets a window factory.
		/// @return Window factory.
		[[nodiscard("Pure function")]]
		inline Window::IWindowFactory* GetWindowFactory() const noexcept;
		/// @brief Sets a window factory.
		/// @details This function is expected to be called once.
		/// @param windowFactory Window factory.
		inline void SetWindowFactory(Window::IWindowFactory* windowFactory) noexcept;

		inline EngineParams& operator =(const EngineParams& other) = default;
		inline EngineParams& operator =(EngineParams&& other) noexcept = default;

	private:
		std::vector<ISystemFactory*> m_systemFactories; /// @brief System factories. Their lifetimes must exceed the engine lifetime.
		Debug::Log::ILogger& m_logger; /// @brief Logger. It mustn't be nullptr. Its lifetime must exceed the engine lifetime.
		Window::IWindowFactory* m_windowFactory; /// @brief Window factory. It's optional and can be nullptr. If it's not nullptr, its lifetime must exceed the engine lifetime.
	};

	inline ISystemFactory* EngineParams::SystemFactoriesIterator::operator *() const noexcept
	{
		return *m_current;
	}

	inline EngineParams::SystemFactoriesIterator& EngineParams::SystemFactoriesIterator::operator ++() noexcept
	{
		++m_current;

		return *this;
	}

	inline EngineParams::SystemFactoriesIterator EngineParams::SystemFactoriesIterator::operator ++(int) noexcept
	{
		SystemFactoriesIterator temp = *this;
		++(*this);

		return temp;
	}

	inline bool EngineParams::SystemFactoriesIterator::IsEnd() const noexcept
	{
		return m_current == m_end;
	}

	inline EngineParams::SystemFactoriesIterator::SystemFactoriesIterator(std::vector<ISystemFactory*>::const_iterator begin, std::vector<ISystemFactory*>::const_iterator end) noexcept :
		m_current(begin),
		m_end(end)
	{
	}

	inline EngineParams::EngineParams(Debug::Log::ILogger& logger) noexcept :
		m_systemFactories{},
		m_logger{logger},
		m_windowFactory{}
	{
	}

	inline Debug::Log::ILogger& EngineParams::GetLogger() const noexcept
	{
		return m_logger;
	}

	inline void EngineParams::AddSystemFactory(ISystemFactory* const systemFactory)
	{
		assert((systemFactory != nullptr));
		assert((std::find(m_systemFactories.cbegin(), m_systemFactories.cend(), systemFactory) == m_systemFactories.cend()));
		m_systemFactories.push_back(systemFactory);
	}

	inline EngineParams::SystemFactoriesIterator EngineParams::GetSystemFactoriesIterator() const noexcept
	{
		return SystemFactoriesIterator(m_systemFactories.cbegin(), m_systemFactories.cend());
	}

	inline Window::IWindowFactory* EngineParams::GetWindowFactory() const noexcept
	{
		return m_windowFactory;
	}

	inline void EngineParams::SetWindowFactory(Window::IWindowFactory* const windowFactory) noexcept
	{
		PONY_LOG_IF_GENERAL(m_windowFactory != nullptr, m_logger, Debug::Log::LogType::Warning, "Set a new window factory when the other window factory was already set.");
		PONY_LOG_IF_GENERAL(windowFactory == nullptr, m_logger, Debug::Log::LogType::Warning, "Set a nullptr window factory.");
		m_windowFactory = windowFactory;
	}
}

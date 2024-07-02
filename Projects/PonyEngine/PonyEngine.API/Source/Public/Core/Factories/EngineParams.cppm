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

export module PonyEngine.Core.Factories:EngineParams;

import <algorithm>;
import <cstddef>;
import <ranges>;
import <utility>;
import <vector>;

import PonyEngine.Log;

import :ISystemFactory;

export namespace PonyEngine::Core
{
	/// @brief Holds engine parameters.
	class EngineParams final
	{
	public:
		/// @brief System factories iterator.
		class SystemFactoriesIterator final
		{
		public:
			[[nodiscard("Pure constructor")]]
			SystemFactoriesIterator(const SystemFactoriesIterator& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			SystemFactoriesIterator(SystemFactoriesIterator&& other) noexcept = default;

			~SystemFactoriesIterator() noexcept = default;

			/// @brief Checks if the currently pointed system factory is actually an end.
			/// @return @a True if the end is reached; @false otherwise.
			[[nodiscard("Pure function")]]
			bool IsEnd() const noexcept;

			/// @brief Gets a currently pointed system factory.
			/// @return Currently pointed system factory.
			[[nodiscard("Pure operator")]]
			ISystemFactory* operator *() const noexcept;
			/// @brief Moves a pointer to the next system factory.
			/// @return New iterator.
			SystemFactoriesIterator& operator ++() noexcept;
			/// @brief Moves a pointer to the next system factory.
			/// @return Previous iterator.
			SystemFactoriesIterator operator ++(int) noexcept;

			SystemFactoriesIterator& operator =(const SystemFactoriesIterator& other) noexcept = default;
			SystemFactoriesIterator& operator =(SystemFactoriesIterator&& other) noexcept = default;

			[[nodiscard("Pure operator")]]
			bool operator ==(const SystemFactoriesIterator& other) const noexcept = default;

		private:
			/// @brief Creates a @p SystemFactoriesIterator.
			/// @param begin System factories begin.
			/// @param end System factories end.
			[[nodiscard("Pure constructor")]]
			SystemFactoriesIterator(const std::vector<ISystemFactory*>::const_iterator& begin, const std::vector<ISystemFactory*>::const_iterator& end) noexcept;

			std::vector<ISystemFactory*>::const_iterator m_current; ///< Current system factory.
			std::vector<ISystemFactory*>::const_iterator m_end; ///< System factories iterator end.

			friend EngineParams;
		};

		/// @brief Create an engine params.
		/// @param logger Logger to use. Mustn't be nullptr.
		[[nodiscard("Pure constructor")]]
		explicit EngineParams(Log::ILogger* logger) noexcept;
		[[nodiscard("Pure constructor")]]
		EngineParams(const EngineParams& other) = default;
		[[nodiscard("Pure constructor")]]
		EngineParams(EngineParams&& other) noexcept = default;

		~EngineParams() noexcept = default;

		/// @brief Gets a logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		Log::ILogger& GetLogger() const noexcept;

		/// @brief Adds a system factory.
		/// @param systemFactory System factory. It must be unique in one @p EngineParams.
		void AddSystemFactory(ISystemFactory* systemFactory);
		/// @brief Gets a system factories iterator.
		/// @return System factories iterator.
		[[nodiscard("Pure function")]]
		SystemFactoriesIterator GetSystemFactoriesIterator() const noexcept;

		EngineParams& operator =(const EngineParams& other) = default;
		EngineParams& operator =(EngineParams&& other) noexcept = default;

	private:
		std::vector<ISystemFactory*> m_systemFactories; ///< System factories. Their lifetimes must exceed the engine lifetime.
		Log::ILogger* m_logger; ///< Logger. It mustn't be nullptr. Its lifetime must exceed the engine lifetime.
	};
}

namespace PonyEngine::Core
{
	EngineParams::SystemFactoriesIterator::SystemFactoriesIterator(const std::vector<ISystemFactory*>::const_iterator& begin, const std::vector<ISystemFactory*>::const_iterator& end) noexcept :
		m_current(begin),
		m_end(end)
	{
	}

	bool EngineParams::SystemFactoriesIterator::IsEnd() const noexcept
	{
		return m_current == m_end;
	}

	ISystemFactory* EngineParams::SystemFactoriesIterator::operator *() const noexcept
	{
		return *m_current;
	}

	EngineParams::SystemFactoriesIterator& EngineParams::SystemFactoriesIterator::operator ++() noexcept
	{
		++m_current;

		return *this;
	}

	EngineParams::SystemFactoriesIterator EngineParams::SystemFactoriesIterator::operator ++(int) noexcept
	{
		SystemFactoriesIterator temp = *this;
		++(*this);

		return temp;
	}

	EngineParams::EngineParams(Log::ILogger* const logger) noexcept :
		m_logger{logger}
	{
		assert((m_logger != nullptr));
	}

	Log::ILogger& EngineParams::GetLogger() const noexcept
	{
		return *m_logger;
	}

	void EngineParams::AddSystemFactory(ISystemFactory* const systemFactory)
	{
		assert((systemFactory != nullptr));
		assert((std::ranges::find(std::as_const(m_systemFactories), systemFactory) == m_systemFactories.cend()));
		m_systemFactories.push_back(systemFactory);
	}

	EngineParams::SystemFactoriesIterator EngineParams::GetSystemFactoriesIterator() const noexcept
	{
		return SystemFactoriesIterator(m_systemFactories.cbegin(), m_systemFactories.cend());
	}
}

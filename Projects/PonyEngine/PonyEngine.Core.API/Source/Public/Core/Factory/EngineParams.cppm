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

export module PonyEngine.Core.Factory:EngineParams;

import <algorithm>;
import <utility>;
import <vector>;

import PonyEngine.Log;

import :ISystemFactory;

export namespace PonyEngine::Core
{
	/// @brief Engine parameters.
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

			/// @brief Checks if the currently pointed system factory is actually the end.
			/// @return @a True if the end is reached; @false otherwise.
			[[nodiscard("Pure function")]]
			bool IsEnd() const noexcept;

			/// @brief Gets a currently pointed system factory.
			/// @return Currently pointed system factory.
			[[nodiscard("Pure operator")]]
			ISystemFactory& operator *() const noexcept;
			/// @brief Iterates to the next system factory.
			/// @return New iterator.
			SystemFactoriesIterator& operator ++() noexcept;
			/// @brief Iterates to the next system factory.
			/// @return Current iterator.
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

			std::vector<ISystemFactory*>::const_iterator current; ///< Current system factory.
			std::vector<ISystemFactory*>::const_iterator end; ///< System factories iterator end.

			friend EngineParams;
		};

		/// @brief Creates an engine params.
		/// @param logger Logger to use. Its lifetime must exceed the engine lifetime.
		[[nodiscard("Pure constructor")]]
		explicit EngineParams(Log::ILogger& logger) noexcept;
		[[nodiscard("Pure constructor")]]
		EngineParams(const EngineParams& other) = default;
		[[nodiscard("Pure constructor")]]
		EngineParams(EngineParams&& other) noexcept = default;

		~EngineParams() noexcept = default;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		Log::ILogger& GetLogger() const noexcept;

		/// @brief Gets the system factories.
		/// @return System factories iterator.
		[[nodiscard("Pure function")]]
		SystemFactoriesIterator GetSystemFactories() const noexcept;
		/// @brief Adds the @p systemFactory.
		/// @param systemFactory System factory to add. It must be unique in one @p EngineParams. Its lifetime must exceed the engine lifetime.
		void AddSystemFactory(ISystemFactory& systemFactory);

		EngineParams& operator =(const EngineParams& other) = default;
		EngineParams& operator =(EngineParams&& other) noexcept = default;

	private:
		std::vector<ISystemFactory*> systemFactories; ///< System factories.
		Log::ILogger* logger; ///< Logger.
	};
}

namespace PonyEngine::Core
{
	EngineParams::SystemFactoriesIterator::SystemFactoriesIterator(const std::vector<ISystemFactory*>::const_iterator& begin, const std::vector<ISystemFactory*>::const_iterator& end) noexcept :
		current(begin),
		end(end)
	{
	}

	bool EngineParams::SystemFactoriesIterator::IsEnd() const noexcept
	{
		return current == end;
	}

	ISystemFactory& EngineParams::SystemFactoriesIterator::operator *() const noexcept
	{
		return **current;
	}

	EngineParams::SystemFactoriesIterator& EngineParams::SystemFactoriesIterator::operator ++() noexcept
	{
		++current;

		return *this;
	}

	EngineParams::SystemFactoriesIterator EngineParams::SystemFactoriesIterator::operator ++(int) noexcept
	{
		const SystemFactoriesIterator temp = *this;
		++(*this);

		return temp;
	}

	EngineParams::EngineParams(Log::ILogger& logger) noexcept :
		logger{&logger}
	{
	}

	Log::ILogger& EngineParams::GetLogger() const noexcept
	{
		return *logger;
	}

	EngineParams::SystemFactoriesIterator EngineParams::GetSystemFactories() const noexcept
	{
		return SystemFactoriesIterator(systemFactories.cbegin(), systemFactories.cend());
	}

	void EngineParams::AddSystemFactory(ISystemFactory& systemFactory)
	{
		assert((std::ranges::find(std::as_const(systemFactories), &systemFactory) == systemFactories.cend() && "The system factory has already been added."));
		systemFactories.push_back(&systemFactory);
	}
}

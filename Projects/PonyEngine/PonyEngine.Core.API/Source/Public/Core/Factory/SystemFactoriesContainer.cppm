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

export module PonyEngine.Core.Factory:SystemFactoriesContainer;

import <algorithm>;
import <utility>;
import <vector>;

import :ISystemFactory;

export namespace PonyEngine::Core
{
	/// @brief System factories container.
	///	@details System factories in it can't be nullptr and they are always unique.
	class SystemFactoriesContainer final
	{
	public:
		using Iterator = std::vector<std::pair<ISystemFactory*, int>>::iterator; ///< System factories iterator.
		using ConstIterator = std::vector<std::pair<ISystemFactory*, int>>::const_iterator; ///< System factories const iterator.

		[[nodiscard("Pure constructor")]]
		SystemFactoriesContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		SystemFactoriesContainer(const SystemFactoriesContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		SystemFactoriesContainer(SystemFactoriesContainer&& other) noexcept = default;

		~SystemFactoriesContainer() noexcept = default;

		/// @brief Adds the @p systemFactory.
		/// @param systemFactory System factory to add. It must be unique in one @p EngineParams. Its lifetime must exceed the engine lifetime.
		/// @param tickOrder Tick order. Affects tickable systems only.
		void AddSystemFactory(ISystemFactory& systemFactory, int tickOrder = 0);

		/// @brief Gets a begin iterator.
		/// @return Begin iterator.
		[[nodiscard("Pure function")]]
		Iterator Begin() noexcept;
		/// @brief Gets a begin iterator.
		/// @return Begin iterator.
		[[nodiscard("Pure function")]]
		ConstIterator Begin() const noexcept;
		/// @brief Gets an end iterator.
		/// @return End iterator.
		[[nodiscard("Pure function")]]
		Iterator End() noexcept;
		/// @brief Gets an end iterator.
		/// @return End iterator.
		[[nodiscard("Pure function")]]
		ConstIterator End() const noexcept;

		/// @brief Gets a begin iterator.
		/// @return Begin iterator.
		[[nodiscard("Pure function")]]
		Iterator begin() noexcept;
		/// @brief Gets a begin iterator.
		/// @return Begin iterator.
		[[nodiscard("Pure function")]]
		ConstIterator begin() const noexcept;
		/// @brief Gets an end iterator.
		/// @return End iterator.
		[[nodiscard("Pure function")]]
		Iterator end() noexcept;
		/// @brief Gets an end iterator.
		/// @return End iterator.
		[[nodiscard("Pure function")]]
		ConstIterator end() const noexcept;

		SystemFactoriesContainer& operator =(const SystemFactoriesContainer& other) = default;
		SystemFactoriesContainer& operator =(SystemFactoriesContainer&& other) noexcept = default;

	private:
		std::vector<std::pair<ISystemFactory*, int>> systemFactories; ///< System factories.
	};
}

namespace PonyEngine::Core
{
	void SystemFactoriesContainer::AddSystemFactory(ISystemFactory& systemFactory, const int tickOrder)
	{
		assert(std::ranges::find_if(std::as_const(systemFactories), [&](const std::pair<ISystemFactory*, int>& element) { return element.first == &systemFactory; }) == systemFactories.cend() && "The system factory has already been added.");
		systemFactories.emplace_back(&systemFactory, tickOrder);
	}

	SystemFactoriesContainer::Iterator SystemFactoriesContainer::Begin() noexcept
	{
		return systemFactories.begin();
	}

	SystemFactoriesContainer::ConstIterator SystemFactoriesContainer::Begin() const noexcept
	{
		return systemFactories.begin();
	}

	SystemFactoriesContainer::Iterator SystemFactoriesContainer::End() noexcept
	{
		return systemFactories.end();
	}

	SystemFactoriesContainer::ConstIterator SystemFactoriesContainer::End() const noexcept
	{
		return systemFactories.end();
	}

	SystemFactoriesContainer::Iterator SystemFactoriesContainer::begin() noexcept
	{
		return Begin();
	}

	SystemFactoriesContainer::ConstIterator SystemFactoriesContainer::begin() const noexcept
	{
		return Begin();
	}

	SystemFactoriesContainer::Iterator SystemFactoriesContainer::end() noexcept
	{
		return End();
	}

	SystemFactoriesContainer::ConstIterator SystemFactoriesContainer::end() const noexcept
	{
		return End();
	}
}

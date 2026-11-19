/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Display.Impl.WinAPI:DisplayContainer;

import std;

import PonyEngine.Display;
import PonyEngine.Utility;

import :DisplayID;
import :DisplayState;

export namespace PonyEngine::Display
{
	class DisplayContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		DisplayContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		DisplayContainer(const DisplayContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		DisplayContainer(DisplayContainer&& other) noexcept = default;

		~DisplayContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const DisplayID& id) const noexcept;

		[[nodiscard("Pure function")]]
		const struct DisplayID& DisplayID(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		DisplayState& State(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const DisplayState& State(std::size_t index) const noexcept;

		void Add(const struct DisplayID& id, DisplayState displayState);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		DisplayContainer& operator =(const DisplayContainer&) = delete;
		DisplayContainer& operator =(DisplayContainer&& other) noexcept = default;

	private:
		std::vector<struct DisplayID> ids;
		std::vector<DisplayState> states;
	};
}

namespace PonyEngine::Display
{
	std::size_t DisplayContainer::Size() const noexcept
	{
		return ids.size();
	}

	std::size_t DisplayContainer::IndexOf(const struct DisplayID& id) const noexcept
	{
		std::size_t i = 0uz;
		for (; i < ids.size() && ids[i] != id; ++i) {}
		return i;
	}

	const struct DisplayID& DisplayContainer::DisplayID(const std::size_t index) const noexcept
	{
		return ids[index];
	}

	DisplayState& DisplayContainer::State(const std::size_t index) noexcept
	{
		return states[index];
	}

	const DisplayState& DisplayContainer::State(const std::size_t index) const noexcept
	{
		return states[index];
	}

	void DisplayContainer::Add(const struct DisplayID& id, DisplayState displayState)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		ids.push_back(id);
		const auto idsScopeGuard = Utility::ScopeGuard([&]() noexcept { ids.pop_back(); }, scopeGuardFlag);
		states.push_back(std::move(displayState));

		scopeGuardFlag.Release();
	}

	void DisplayContainer::Remove(const std::size_t index) noexcept
	{
		ids.erase(ids.cbegin() + index);
		states.erase(states.cbegin() + index);
	}

	void DisplayContainer::Clear() noexcept
	{
		ids.clear();
		states.clear();
	}
}

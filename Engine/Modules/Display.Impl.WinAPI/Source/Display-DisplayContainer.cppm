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
import :DisplayProperties;
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
		std::size_t IndexOf(DisplayHandleID handle) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(DisplayID id) const noexcept;

		[[nodiscard("Pure function")]]
		DisplayHandleID Handle(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		struct DisplayID DisplayID(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		const DisplayProperties& Properties(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		DisplayState& State(std::size_t index) noexcept;
		[[nodiscard("Pure function")]]
		const DisplayState& State(std::size_t index) const noexcept;

		std::size_t Add(DisplayHandleID handle, struct DisplayID id, DisplayProperties displayProperties, const DisplayState& displayState);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		DisplayContainer& operator =(const DisplayContainer&) = delete;
		DisplayContainer& operator =(DisplayContainer&& other) noexcept = default;

	private:
		std::vector<DisplayHandleID> handles;
		std::vector<struct DisplayID> ids;
		std::vector<DisplayProperties> properties;
		std::vector<DisplayState> states;
	};
}

namespace PonyEngine::Display
{
	std::size_t DisplayContainer::Size() const noexcept
	{
		return handles.size();
	}

	std::size_t DisplayContainer::IndexOf(const DisplayHandleID handle) const noexcept
	{
		auto position = std::ranges::lower_bound(handles, handle);
		if (position != handles.cend() && *position != handle)
		{
			position = handles.cend();
		}

		return position - handles.cbegin();
	}

	std::size_t DisplayContainer::IndexOf(const struct DisplayID id) const noexcept
	{
		std::size_t i = 0uz;
		for (; i < ids.size() && ids[i] != id; ++i) {}
		return i;
	}

	DisplayHandleID DisplayContainer::Handle(const std::size_t index) const noexcept
	{
		return handles[index];
	}

	struct DisplayID DisplayContainer::DisplayID(const std::size_t index) const noexcept
	{
		return ids[index];
	}

	const DisplayProperties& DisplayContainer::Properties(const std::size_t index) const noexcept
	{
		return properties[index];
	}

	DisplayState& DisplayContainer::State(const std::size_t index) noexcept
	{
		return states[index];
	}

	const DisplayState& DisplayContainer::State(const std::size_t index) const noexcept
	{
		return states[index];
	}

	std::size_t DisplayContainer::Add(const DisplayHandleID handle, const struct DisplayID id, DisplayProperties displayProperties, const DisplayState& displayState)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		const std::size_t index = std::ranges::lower_bound(handles, handle) - handles.cbegin();
		handles.insert(handles.cbegin() + index, handle);
		const auto handlesScopeGuard = Utility::ScopeGuard([&]() noexcept { handles.erase(handles.cbegin() + index); }, scopeGuardFlag);
		ids.insert(ids.cbegin() + index, id);
		const auto idsScopeGuard = Utility::ScopeGuard([&]() noexcept { ids.erase(ids.cbegin() + index); }, scopeGuardFlag);
		properties.insert(properties.cbegin() + index, std::move(displayProperties));
		const auto propertiesScopeGuard = Utility::ScopeGuard([&]() noexcept { properties.erase(properties.cbegin() + index); }, scopeGuardFlag);
		states.insert(states.cbegin() + index, displayState);
		const auto statesScopeGuard = Utility::ScopeGuard([&]() noexcept { states.erase(states.cbegin() + index); }, scopeGuardFlag);

		scopeGuardFlag.Release();

		return index;
	}

	void DisplayContainer::Remove(const std::size_t index) noexcept
	{
		handles.erase(handles.cbegin() + index);
		ids.erase(ids.cbegin() + index);
		properties.erase(properties.cbegin() + index);
		states.erase(states.cbegin() + index);
	}

	void DisplayContainer::Clear() noexcept
	{
		handles.clear();
		ids.clear();
		properties.clear();
		states.clear();
	}
}

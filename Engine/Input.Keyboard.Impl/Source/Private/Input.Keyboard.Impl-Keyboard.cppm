/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Keyboard.Impl:Keyboard;

import std;

import PonyEngine.Input.Ext;

import :KeyboardEvent;

export namespace PonyEngine::Input
{
	/// @brief Keyboard device.
	class Keyboard final : public IDevice
	{
	public:
		static inline const std::array<std::type_index, 1> KeyboardLayouts
		{
			typeid(KeyboardLayout)
		};

		[[nodiscard("Pure constuctor")]]
		Keyboard(std::string_view name, bool isConnected);
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;

		~Keyboard() noexcept = default;

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const KeyboardEvent> Events() const noexcept;
		void AddEvent(const KeyboardInput& event);
		void AddEvent(const KeyboardConnection& event);
		void ClearEvents() noexcept;

		[[nodiscard("Pure function")]]
		bool IsPressed(KeyboardLayout key) const noexcept;
		[[nodiscard("Pure function")]]
		bool IsConnected() const noexcept;

		void ClearKeyStates() noexcept;

		Keyboard& operator =(const Keyboard&) = delete;
		Keyboard& operator =(Keyboard&&) = delete;

	private:
		std::string name;
		std::vector<KeyboardEvent> events;
		std::vector<bool> keyStates;
		bool isConnected;
	};
}

namespace PonyEngine::Input
{
	Keyboard::Keyboard(const std::string_view name, const bool isConnected) :
		name(name),
		keyStates(std::numeric_limits<AxisIdType>::max()),
		isConnected{isConnected}
	{
	}

	std::string_view Keyboard::Name() const noexcept
	{
		return name;
	}

	std::span<const KeyboardEvent> Keyboard::Events() const noexcept
	{
		return events;
	}

	void Keyboard::AddEvent(const KeyboardInput& event)
	{
		events.push_back(event);
		keyStates[static_cast<std::size_t>(event.key)] = event.pressed;
	}

	void Keyboard::AddEvent(const KeyboardConnection& event)
	{
		events.push_back(event);
		isConnected = event.isConnected;
	}

	void Keyboard::ClearEvents() noexcept
	{
		events.clear();
	}

	bool Keyboard::IsPressed(const KeyboardLayout key) const noexcept
	{
		return keyStates[static_cast<std::size_t>(key)];
	}

	bool Keyboard::IsConnected() const noexcept
	{
		return isConnected;
	}

	void Keyboard::ClearKeyStates() noexcept
	{
		std::ranges::fill(keyStates, false);
	}
}

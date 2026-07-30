/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

#include <xinput.h>

export module PonyEngine.RawInput.XInput.Impl.Windows:GamepadAxisMap;

import std;

import PonyEngine.RawInput.Ext;

export namespace PonyEngine::RawInput::XInput::Windows
{
	/// @brief XInput gamepad axis map.
	class GamepadAxisMap final
	{
	public:
		/// @brief Trigger axis.
		enum class TriggerAxis : std::uint8_t
		{
			Left,
			Right
		};
		/// @brief Stick placement.
		enum class StickPlacement : std::uint8_t
		{
			Left,
			Right
		};
		/// @brief Stick direction.
		enum class StickDirection : std::uint8_t
		{
			Horizontal,
			Vertical
		};

		/// @brief Creates an XInput gamepad axis map.
		/// @param hub Device hub.
		[[nodiscard("Pure constructor")]]
		explicit GamepadAxisMap(IDeviceHub& hub);
		GamepadAxisMap(const GamepadAxisMap&) = delete;
		GamepadAxisMap(GamepadAxisMap&&) = delete;

		~GamepadAxisMap() noexcept = default;

		/// @brief Gets a buttons axis.
		/// @param button Native button.
		/// @return Button axis.
		[[nodiscard("Pure function")]]
		Axis Button(WORD button) const noexcept;
		/// @brief Gets a trigger axis.
		/// @param trigger Trigger axis type.
		/// @return Trigger axis.
		[[nodiscard("Pure function")]]
		Axis Trigger(TriggerAxis trigger) const noexcept;
		/// @brief Gets a stick axis.
		/// @param placement Stick placement.
		/// @param direction Stick direction.
		/// @return Stick axis.
		[[nodiscard("Pure function")]]
		Axis Stick(StickPlacement placement, StickDirection direction) const noexcept;
		/// @brief Gets stick axes in both directions.
		/// @param placement Stick placement.
		/// @return Horizontal and vertical stick axes.
		[[nodiscard("Pure function")]]
		std::span<const Axis, 2> Stick(StickPlacement placement) const noexcept;

		GamepadAxisMap& operator =(const GamepadAxisMap&) = delete;
		GamepadAxisMap& operator =(GamepadAxisMap&&) = delete;

	private:
		static constexpr std::size_t ButtonCount = 14; ///< Button count.

		/// @brief Binds a button.
		/// @param index Button index.
		/// @param nativeAxis Button native axis.
		/// @param axis Button axis.
		/// @param hub Device hub.
		void Bind(std::size_t index, WORD nativeAxis, std::string_view axis, IDeviceHub& hub);
		/// @brief Binds a trigger.
		/// @param trigger Trigger axis type.
		/// @param axis Trigger axis.
		/// @param hub Device hub.
		void Bind(TriggerAxis trigger, std::string_view axis, IDeviceHub& hub);
		/// @brief Binds a stick.
		/// @param placement Stick placement.
		/// @param direction Stick direction.
		/// @param axis Stick axis.
		/// @param hub Device hub.
		void Bind(StickPlacement placement, StickDirection direction, std::string_view axis, IDeviceHub& hub);

		std::array<WORD, ButtonCount> nativeAxes; ///< Native button axes.
		std::array<Axis, ButtonCount> buttonAxes; ///< Button axes.
		std::array<Axis, 2> triggerAxes; ///< Trigger axes. Order: [left, right]
		std::array<std::array<Axis, 2>, 2> stickAxes; ///< Stick axes. Order: [left, right][horizontal, vertical].
	};
}

namespace PonyEngine::RawInput::XInput::Windows
{
	GamepadAxisMap::GamepadAxisMap(IDeviceHub& hub)
	{
		constexpr auto buttonMap = std::array<std::pair<WORD, std::string_view>, ButtonCount>
		{
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_DPAD_UP, GamepadLayout::DPadUpPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_DPAD_DOWN, GamepadLayout::DPadDownPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_DPAD_LEFT, GamepadLayout::DPadLeftPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_DPAD_RIGHT, GamepadLayout::DPadRightPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_START, GamepadLayout::SystemMenuPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_BACK, GamepadLayout::SystemSelectPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_LEFT_THUMB, GamepadLayout::LeftStickButtonPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_RIGHT_THUMB, GamepadLayout::RightStickButtonPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_LEFT_SHOULDER, GamepadLayout::BackButtonLeftPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_RIGHT_SHOULDER, GamepadLayout::BackButtonRightPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_A, GamepadLayout::FaceButtonDownPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_B, GamepadLayout::FaceButtonRightPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_X, GamepadLayout::FaceButtonLeftPath),
			std::pair<WORD, std::string_view>(XINPUT_GAMEPAD_Y, GamepadLayout::FaceButtonUpPath)
		};
		for (std::size_t i = 0; i < ButtonCount; ++i)
		{
			Bind(i, buttonMap[i].first, buttonMap[i].second, hub);
		}

		Bind(TriggerAxis::Left, GamepadLayout::TriggerLeftPath, hub);
		Bind(TriggerAxis::Right, GamepadLayout::TriggerRightPath, hub);

		Bind(StickPlacement::Left, StickDirection::Horizontal, GamepadLayout::LeftStickHorizontalPath, hub);
		Bind(StickPlacement::Left, StickDirection::Vertical, GamepadLayout::LeftStickVerticalPath, hub);
		Bind(StickPlacement::Right, StickDirection::Horizontal, GamepadLayout::RightStickHorizontalPath, hub);
		Bind(StickPlacement::Right, StickDirection::Vertical, GamepadLayout::RightStickVerticalPath, hub);
	}

	Axis GamepadAxisMap::Button(const WORD button) const noexcept
	{
		const std::size_t index = std::ranges::find(nativeAxes, button) - nativeAxes.cbegin();
		return buttonAxes[index];
	}

	Axis GamepadAxisMap::Trigger(const TriggerAxis trigger) const noexcept
	{
		return triggerAxes[static_cast<std::size_t>(trigger)];
	}

	Axis GamepadAxisMap::Stick(const StickPlacement placement, const StickDirection direction) const noexcept
	{
		return stickAxes[static_cast<std::size_t>(placement)][static_cast<std::size_t>(direction)];
	}

	std::span<const Axis, 2> GamepadAxisMap::Stick(const StickPlacement placement) const noexcept
	{
		return stickAxes[static_cast<std::size_t>(placement)];
	}

	void GamepadAxisMap::Bind(const std::size_t index, const WORD nativeAxis, const std::string_view axis, IDeviceHub& hub)
	{
		nativeAxes[index] = nativeAxis;
		buttonAxes[index] = hub.MakeAxis(axis);
	}

	void GamepadAxisMap::Bind(const TriggerAxis trigger, const std::string_view axis, IDeviceHub& hub)
	{
		triggerAxes[static_cast<std::size_t>(trigger)] = hub.MakeAxis(axis);
	}

	void GamepadAxisMap::Bind(const StickPlacement placement, const StickDirection direction, const std::string_view axis, IDeviceHub& hub)
	{
		stickAxes[static_cast<std::size_t>(placement)][static_cast<std::size_t>(direction)] = hub.MakeAxis(axis);
	}
}

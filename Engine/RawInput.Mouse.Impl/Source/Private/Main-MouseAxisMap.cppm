/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Mouse.Impl:MouseAxisMap;

import std;

import PonyEngine.RawInput.Ext;

import :MouseAxis;

export namespace PonyEngine::RawInput::Mouse
{
	/// @brief Mouse axis map.
	class MouseAxisMap final
	{
	public:
		/// @brief Creates a mouse axis map.
		/// @param input Raw input context.
		[[nodiscard("Pure constructor")]]
		explicit MouseAxisMap(IRawInputContext& input);
		MouseAxisMap(const MouseAxisMap&) = delete;
		MouseAxisMap(MouseAxisMap&&) = delete;

		~MouseAxisMap() noexcept = default;

		/// @brief Gets a button axis.
		/// @param button Button ID.
		/// @return Button axis.
		[[nodiscard("Pure function")]]
		AxisId Axis(MouseButton button) const noexcept;
		/// @brief Gets a wheel axis.
		/// @param wheel Wheel ID.
		/// @return Wheel axis.
		[[nodiscard("Pure function")]]
		AxisId Axis(MouseWheel wheel) const noexcept;
		/// @brief Gets a pointer axis.
		/// @param pointer Pointer ID.
		/// @return Pointer axis.
		[[nodiscard("Pure function")]]
		AxisId Axis(MousePointer pointer) const noexcept;

		/// @brief Gets all the button axes.
		/// @return Buton axes.
		[[nodiscard("Pure function")]]
		std::span<const AxisId, MouseButtonCount> Buttons() const noexcept;
		/// @brief Gets all the wheel axes.
		/// @return Wheel axes.
		[[nodiscard("Pure function")]]
		std::span<const AxisId, MouseWheelCount> Wheels() const noexcept;
		/// @brief Gets all the pointer axes.
		/// @return Pointer axes.
		[[nodiscard("Pure function")]]
		std::span<const AxisId, MousePointerCount> Pointers() const noexcept;

		MouseAxisMap& operator =(const MouseAxisMap&) = delete;
		MouseAxisMap& operator =(MouseAxisMap&&) = delete;

	private:
		std::array<AxisId, MouseButtonCount> buttonAxes; ///< Button axes.
		std::array<AxisId, MouseWheelCount> wheelAxes; ///< Wheel axes.
		std::array<AxisId, MousePointerCount> pointerAxes; ///< Pointer axes.
	};
}

namespace PonyEngine::RawInput::Mouse
{
	MouseAxisMap::MouseAxisMap(IRawInputContext& input)
	{
		for (std::size_t i = 0uz; i < buttonAxes.size(); ++i)
		{
			buttonAxes[i] = input.Hash(RawInput::Axis(std::format("{}/{}", MouseLayout::ButtonPath, i + 1)));
		}

		wheelAxes[static_cast<std::size_t>(MouseWheel::Horizontal)] = input.Hash(RawInput::Axis(MouseLayout::WheelHorizontalPath));
		wheelAxes[static_cast<std::size_t>(MouseWheel::Vertical)] = input.Hash(RawInput::Axis(MouseLayout::WheelVerticalPath));

		pointerAxes[static_cast<std::size_t>(MousePointer::X)] = input.Hash(RawInput::Axis(MouseLayout::AxisXPath));
		pointerAxes[static_cast<std::size_t>(MousePointer::Y)] = input.Hash(RawInput::Axis(MouseLayout::AxisYPath));
	}

	AxisId MouseAxisMap::Axis(const MouseButton button) const noexcept
	{
		return buttonAxes[static_cast<std::size_t>(button)];
	}

	AxisId MouseAxisMap::Axis(MouseWheel wheel) const noexcept
	{
		return wheelAxes[static_cast<std::size_t>(wheel)];
	}

	AxisId MouseAxisMap::Axis(const MousePointer pointer) const noexcept
	{
		return pointerAxes[static_cast<std::size_t>(pointer)];
	}

	std::span<const AxisId, MouseButtonCount> MouseAxisMap::Buttons() const noexcept
	{
		return buttonAxes;
	}

	std::span<const AxisId, MouseWheelCount> MouseAxisMap::Wheels() const noexcept
	{
		return wheelAxes;
	}

	std::span<const AxisId, MousePointerCount> MouseAxisMap::Pointers() const noexcept
	{
		return pointerAxes;
	}
}

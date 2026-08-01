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
		/// @param hub Device hub.
		[[nodiscard("Pure constructor")]]
		explicit MouseAxisMap(IDeviceHub& hub);
		MouseAxisMap(const MouseAxisMap&) = delete;
		MouseAxisMap(MouseAxisMap&&) = delete;

		~MouseAxisMap() noexcept = default;

		/// @brief Gets a button axis.
		/// @param button Button ID.
		/// @return Button axis.
		[[nodiscard("Pure function")]]
		struct Axis Axis(MouseButton button) const noexcept;
		/// @brief Gets a wheel axis.
		/// @param wheel Wheel ID.
		/// @return Wheel axis.
		[[nodiscard("Pure function")]]
		struct Axis Axis(MouseWheel wheel) const noexcept;
		/// @brief Gets a pointer axis.
		/// @param pointer Pointer ID.
		/// @return Pointer axis.
		[[nodiscard("Pure function")]]
		struct Axis Axis(MousePointer pointer) const noexcept;

		/// @brief Gets all the button axes.
		/// @return Buton axes.
		[[nodiscard("Pure function")]]
		std::span<const struct Axis, MouseButtonCount> Buttons() const noexcept;
		/// @brief Gets all the wheel axes.
		/// @return Wheel axes.
		[[nodiscard("Pure function")]]
		std::span<const struct Axis, MouseWheelCount> Wheels() const noexcept;
		/// @brief Gets all the pointer axes.
		/// @return Pointer axes.
		[[nodiscard("Pure function")]]
		std::span<const struct Axis, MousePointerCount> Pointers() const noexcept;

		MouseAxisMap& operator =(const MouseAxisMap&) = delete;
		MouseAxisMap& operator =(MouseAxisMap&&) = delete;

	private:
		std::array<struct Axis, MouseButtonCount> buttonAxes; ///< Button axes.
		std::array<struct Axis, MouseWheelCount> wheelAxes; ///< Wheel axes.
		std::array<struct Axis, MousePointerCount> pointerAxes; ///< Pointer axes.
	};
}

namespace PonyEngine::RawInput::Mouse
{
	MouseAxisMap::MouseAxisMap(IDeviceHub& hub)
	{
		constexpr std::array<std::string_view, 5> buttonPaths =
		{
			MouseLayout::Button1Path,
			MouseLayout::Button2Path,
			MouseLayout::Button3Path,
			MouseLayout::Button4Path,
			MouseLayout::Button5Path
		};
		for (std::size_t i = 0uz; i < buttonAxes.size(); ++i)
		{
			buttonAxes[i] = hub.MakeAxis(buttonPaths[i]);
		}

		wheelAxes[static_cast<std::size_t>(MouseWheel::Horizontal)] = hub.MakeAxis(MouseLayout::WheelHorizontalPath);
		wheelAxes[static_cast<std::size_t>(MouseWheel::Vertical)] = hub.MakeAxis(MouseLayout::WheelVerticalPath);

		pointerAxes[static_cast<std::size_t>(MousePointer::X)] = hub.MakeAxis(MouseLayout::AxisXPath);
		pointerAxes[static_cast<std::size_t>(MousePointer::Y)] = hub.MakeAxis(MouseLayout::AxisYPath);
	}

	struct Axis MouseAxisMap::Axis(const MouseButton button) const noexcept
	{
		return buttonAxes[static_cast<std::size_t>(button)];
	}

	struct Axis MouseAxisMap::Axis(MouseWheel wheel) const noexcept
	{
		return wheelAxes[static_cast<std::size_t>(wheel)];
	}

	struct Axis MouseAxisMap::Axis(const MousePointer pointer) const noexcept
	{
		return pointerAxes[static_cast<std::size_t>(pointer)];
	}

	std::span<const struct Axis, MouseButtonCount> MouseAxisMap::Buttons() const noexcept
	{
		return buttonAxes;
	}

	std::span<const struct Axis, MouseWheelCount> MouseAxisMap::Wheels() const noexcept
	{
		return wheelAxes;
	}

	std::span<const struct Axis, MousePointerCount> MouseAxisMap::Pointers() const noexcept
	{
		return pointerAxes;
	}
}

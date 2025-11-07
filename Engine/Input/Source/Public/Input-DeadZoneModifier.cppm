/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:DeadZoneModifier;

import std;

import :IModifier;

export namespace PonyEngine::Input
{
	/// @brief Dead zone modifier.
	class DeadZoneModifier final : public IModifier
	{
	public:
		/// @brief Creates a dead zone modifier.
		/// @param deadZone Dead zone.
		[[nodiscard("Pure constructor")]]
		explicit DeadZoneModifier(float deadZone) noexcept;
		[[nodiscard("Pure constructor")]]
		DeadZoneModifier(const DeadZoneModifier& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		DeadZoneModifier(DeadZoneModifier&& other) noexcept = default;

		~DeadZoneModifier() noexcept = default;

		/// @brief Gets the dead zone.
		/// @return Dead zone.
		[[nodiscard("Pure function")]]
		float& DeadZone() noexcept;
		/// @brief Gets the dead zone.
		/// @return Dead zone.
		[[nodiscard("Pure function")]]
		const float& DeadZone() const noexcept;

		[[nodiscard("Must be used")]]
		virtual float Modify(float initial, float current) noexcept override;

		DeadZoneModifier& operator =(const DeadZoneModifier& other) noexcept = default;
		DeadZoneModifier& operator =(DeadZoneModifier&& other) noexcept = default;

	private:
		float deadZone; ///< Dead zone.
	};
}

namespace PonyEngine::Input
{
	DeadZoneModifier::DeadZoneModifier(const float deadZone) noexcept :
		deadZone{deadZone}
	{
	}

	float& DeadZoneModifier::DeadZone() noexcept
	{
		return deadZone;
	}

	const float& DeadZoneModifier::DeadZone() const noexcept
	{
		return deadZone;
	}

	float DeadZoneModifier::Modify(const float initial, const float current) noexcept
	{
		return std::abs(current) < deadZone ? 0.f : current;
	}
}

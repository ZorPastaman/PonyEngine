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

export module PonyEngine.Input:ClampModifier;

import std;

import :IModifier;

export namespace PonyEngine::Input
{
	/// @brief Clamp modifier.
	class ClampModifier final : public IModifier
	{
	public:
		/// @brief Creates a clamp modifier.
		/// @param min Minimum.
		/// @param max Maximum.
		[[nodiscard("Pure constructor")]]
		explicit ClampModifier(float min, float max) noexcept;
		[[nodiscard("Pure constructor")]]
		ClampModifier(const ClampModifier& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		ClampModifier(ClampModifier&& other) noexcept = default;

		~ClampModifier() noexcept = default;

		/// @brief Gets the minimum.
		/// @return Minimum.
		[[nodiscard("Pure function")]]
		float& Min() noexcept;
		/// @brief Gets the minimum.
		/// @return Minimum.
		[[nodiscard("Pure function")]]
		const float& Min() const noexcept;
		/// @brief Gets the maximum.
		/// @return Maximum.
		[[nodiscard("Pure function")]]
		float& Max() noexcept;
		/// @brief Gets the maximum.
		/// @return Maximum.
		[[nodiscard("Pure function")]]
		const float& Max() const noexcept;

		[[nodiscard("Must be used")]]
		virtual float Modify(float initial, float current) noexcept override;

		ClampModifier& operator =(const ClampModifier& other) noexcept = default;
		ClampModifier& operator =(ClampModifier&& other) noexcept = default;

	private:
		float min; ///< Minimum.
		float max; ///< Maximum.
	};
}

namespace PonyEngine::Input
{
	ClampModifier::ClampModifier(const float min, const float max) noexcept :
		min{min},
		max{max}
	{
		assert(min <= max && "Invalid clamp parameters.");
	}

	float& ClampModifier::Min() noexcept
	{
		return min;
	}

	const float& ClampModifier::Min() const noexcept
	{
		return min;
	}

	float& ClampModifier::Max() noexcept
	{
		return max;
	}

	const float& ClampModifier::Max() const noexcept
	{
		return max;
	}

	float ClampModifier::Modify(const float initial, const float current) noexcept
	{
		return std::clamp(current, min, max);
	}
}

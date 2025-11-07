/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:ScaleModifier;

import :IModifier;

export namespace PonyEngine::Input
{
	/// @brief Scale modifier.
	class ScaleModifier final : public IModifier
	{
	public:
		/// @brief Creates a scale modifier.
		/// @param scale Scale.
		[[nodiscard("Pure constructor")]]
		explicit ScaleModifier(float scale) noexcept;
		[[nodiscard("Pure constructor")]]
		ScaleModifier(const ScaleModifier& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		ScaleModifier(ScaleModifier&& other) noexcept = default;

		~ScaleModifier() noexcept = default;

		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		float& Scale() noexcept;
		/// @brief Gets the scale.
		/// @return Scale.
		[[nodiscard("Pure function")]]
		const float& Scale() const noexcept;

		[[nodiscard("Must be used")]]
		virtual float Modify(float initial, float current) noexcept override;

		ScaleModifier& operator =(const ScaleModifier& other) noexcept = default;
		ScaleModifier& operator =(ScaleModifier&& other) noexcept = default;

	private:
		float scale; ///< Scale.
	};
}

namespace PonyEngine::Input
{
	ScaleModifier::ScaleModifier(const float scale) noexcept :
		scale{scale}
	{
	}

	float& ScaleModifier::Scale() noexcept
	{
		return scale;
	}

	const float& ScaleModifier::Scale() const noexcept
	{
		return scale;
	}

	float ScaleModifier::Modify(const float initial, const float current) noexcept
	{
		return current * scale;
	}
}

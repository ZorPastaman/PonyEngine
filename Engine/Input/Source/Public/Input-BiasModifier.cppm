/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:BiasModifier;

import std;

import :IModifier;

export namespace PonyEngine::Input
{
	/// @brief Bias modifier. It adds a bias to a positive value and subtracts it from a negative value.
	class BiasModifier final : public IModifier
	{
	public:
		/// @brief Creates a bias modifier.
		/// @param bias Bias.
		[[nodiscard("Pure constructor")]]
		explicit BiasModifier(float bias) noexcept;
		[[nodiscard("Pure constructor")]]
		BiasModifier(const BiasModifier& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		BiasModifier(BiasModifier&& other) noexcept = default;

		~BiasModifier() noexcept = default;

		/// @brief Gets the bias.
		/// @return Bias.
		[[nodiscard("Pure function")]]
		float& Bias() noexcept;
		/// @brief Gets the bias.
		/// @return Bias.
		[[nodiscard("Pure function")]]
		const float& Bias() const noexcept;

		[[nodiscard("Must be used")]]
		virtual float Modify(float initial, float current) noexcept override;

		BiasModifier& operator =(const BiasModifier& other) noexcept = default;
		BiasModifier& operator =(BiasModifier&& other) noexcept = default;

	private:
		float bias; ///< Bias
	};
}

namespace PonyEngine::Input
{
	BiasModifier::BiasModifier(const float bias) noexcept :
		bias{bias}
	{
	}

	float& BiasModifier::Bias() noexcept
	{
		return bias;
	}

	const float& BiasModifier::Bias() const noexcept
	{
		return bias;
	}

	float BiasModifier::Modify(const float initial, const float current) noexcept
	{
		if (current > 0.f)
		{
			return current + bias;
		}

		if (current < 0.f)
		{
			return current - bias;
		}

		return current;
	}
}

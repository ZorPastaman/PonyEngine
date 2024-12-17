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

export module PonyEngine.Input:InputValueConversion;

import <cmath>;
import <cstdint>;
import <functional>;

export namespace PonyEngine::Input
{
	/// @brief Comparison mode.
	enum class ComparisonMode : std::int8_t
	{
		Less,
		LessOrEqual,
		Greater,
		GreaterOrEqual
	};

	/// @brief Creates an action that transforms a float value to bool via the comparison with the magnitude and calls the action that accepts bool. The conversion is dependent on the comparison mode.
	/// @param action Action that accepts bool.
	/// @param magnitude Magnitude to compare with.
	/// @param comparisonMode Comparison mode.
	/// @return Action that accepts float.
	[[nodiscard("Pure function")]]
	std::function<void(float)> FloatToBoolAction(const std::function<void(bool)>& action, float magnitude = 0.2f, ComparisonMode comparisonMode = ComparisonMode::Greater);

	/// @brief Creates an action that invokes the action only if the input value is equal the trigger.
	/// @param action Action that's conditionally invoked.
	/// @param trigger Comparison trigger.
	/// @return Action that accepts bool.
	[[nodiscard("Pure function")]]
	std::function<void(bool)> BoolToEventAction(const std::function<void()>& action, bool trigger = true);

	/// @brief Transforms a float value to bool via the comparison with the magnitude and calls the action that accepts bool. The conversion is dependent on the comparison mode.
	/// @param value Value.
	/// @param magnitude Magnitude to compare with.
	/// @param comparisonMode Comparison mode.
	/// @return Comparison result.
	[[nodiscard("Pure function")]]
	bool FloatToBool(float value, float magnitude = 0.2f, ComparisonMode comparisonMode = ComparisonMode::Greater);
}

namespace PonyEngine::Input
{
	std::function<void(float)> FloatToBoolAction(const std::function<void(bool)>& action, const float magnitude, const ComparisonMode comparisonMode)
	{
		switch (comparisonMode)
		{
		case ComparisonMode::Less:
			return [=](const float value)
			{
				action(std::abs(value) < magnitude);
			};
		case ComparisonMode::LessOrEqual:
			return [=](const float value)
			{
				action(std::abs(value) <= magnitude);
			};
		case ComparisonMode::Greater:
			return [=](const float value)
			{
				action(std::abs(value) > magnitude);
			};
		case ComparisonMode::GreaterOrEqual:
			return [=](const float value)
			{
				action(std::abs(value) >= magnitude);
			};
		default: [[unlikely]]
			assert(false && "The comparison mode is incorrect.");
			return [](const float){};
		}
	}

	std::function<void(bool)> BoolToEventAction(const std::function<void()>& action, const bool trigger)
	{
		return [=](const bool value)
		{
			if (value == trigger)
			{
				action();
			}
		};
	}

	bool FloatToBool(const float value, const float magnitude, const ComparisonMode comparisonMode)
	{
		switch (comparisonMode)
		{
		case ComparisonMode::Less:
			return std::abs(value) < magnitude;
		case ComparisonMode::LessOrEqual:
			return std::abs(value) <= magnitude;
		case ComparisonMode::Greater:
			return std::abs(value) > magnitude;
		case ComparisonMode::GreaterOrEqual:
			return std::abs(value) >= magnitude;
		default: [[unlikely]]
			assert(false && "The comparison mode is incorrect.");
			return false;
		}
	}
}

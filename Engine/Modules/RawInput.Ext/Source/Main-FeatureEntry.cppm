/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Ext:FeatureEntry;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Feature entry.
	struct FeatureEntry final
	{
		std::type_index featureType; ///< Feature type.
		void* feature; ///< Feature.

		/// @brief Makes a feature entry.
		/// @tparam T Feature type.
		/// @param feature Feature.
		/// @return Feature entry.
		template<typename T> [[nodiscard("Pure function")]]
		static FeatureEntry Make(T& feature) noexcept;
	};
}

namespace PonyEngine::RawInput
{
	template<typename T>
	FeatureEntry FeatureEntry::Make(T& feature) noexcept
	{
		return FeatureEntry{.featureType = typeid(T), .feature = &feature};
	}
}
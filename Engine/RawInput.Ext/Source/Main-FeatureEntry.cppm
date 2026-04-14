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

		/// @brief Creates a feature entry.
		/// @tparam T Feature type.
		/// @param feature Feature.
		template<typename T> [[nodiscard("Pure constructor")]]
		explicit FeatureEntry(T& feature) noexcept;
		FeatureEntry(const FeatureEntry& other) noexcept = default;
		FeatureEntry(FeatureEntry&& other) noexcept = default;

		~FeatureEntry() noexcept = default;

		FeatureEntry& operator =(const FeatureEntry& other) noexcept = default;
		FeatureEntry& operator =(FeatureEntry&& other) noexcept = default;
	};
}

namespace PonyEngine::RawInput
{
	template<typename T>
	FeatureEntry::FeatureEntry(T& feature) noexcept :
		featureType(typeid(T)),
		feature{&feature}
	{
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Impl:DeviceFeatureContainer;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Device feature container.
	class DeviceFeatureContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		DeviceFeatureContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		DeviceFeatureContainer(const DeviceFeatureContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		DeviceFeatureContainer(DeviceFeatureContainer&& other) noexcept = default;

		~DeviceFeatureContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds an index of the type.
		/// @param type Feature type.
		/// @return Feature type index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(std::type_index type) const noexcept;

		/// @brief Gets a type.
		/// @param index Feature index.
		/// @return Feature type.
		[[nodiscard("Pure function")]]
		std::type_index Type(std::size_t index) const noexcept;
		/// @brief Gets a feature.
		/// @param index Feature index.
		/// @return Feature.
		[[nodiscard("Pure function")]]
		void* Feature(std::size_t index) const noexcept;

		/// @brief Gets the feature types.
		/// @return Feature types.
		[[nodiscard("Pure function")]]
		std::span<const std::type_index> FeatureTypes() const noexcept;

		/// @brief Adds a feature.
		/// @param type Feature type.
		/// @param feature Feature.
		void Add(std::type_index type, void* feature);
		/// @brief Removes a feature.
		/// @param index Feature index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		DeviceFeatureContainer& operator =(const DeviceFeatureContainer&) = delete;
		DeviceFeatureContainer& operator =(DeviceFeatureContainer&& other) noexcept = default;

	private:
		std::vector<std::type_index> featureTypes; ///< Feature types.
		std::vector<void*> features; ///< Features.
	};
}

namespace PonyEngine::RawInput
{
	std::size_t DeviceFeatureContainer::Size() const noexcept
	{
		return featureTypes.size();
	}

	std::size_t DeviceFeatureContainer::IndexOf(const std::type_index type) const noexcept
	{
		return std::ranges::find(featureTypes, type) - featureTypes.cbegin();
	}

	std::type_index DeviceFeatureContainer::Type(const std::size_t index) const noexcept
	{
		return featureTypes[index];
	}

	void* DeviceFeatureContainer::Feature(const std::size_t index) const noexcept
	{
		return features[index];
	}

	std::span<const std::type_index> DeviceFeatureContainer::FeatureTypes() const noexcept
	{
		return featureTypes;
	}

	void DeviceFeatureContainer::Add(const std::type_index type, void* const feature)
	{
		featureTypes.push_back(type);
		try
		{
			features.push_back(feature);
		}
		catch (...)
		{
			featureTypes.pop_back();
			throw;
		}
	}

	void DeviceFeatureContainer::Remove(const std::size_t index) noexcept
	{
		features.erase(features.cbegin() + index);
		featureTypes.erase(featureTypes.cbegin() + index);
	}

	void DeviceFeatureContainer::Clear() noexcept
	{
		featureTypes.clear();
		features.clear();
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Impl:Device;

import std;

import PonyEngine.RawInput.Ext;

export namespace PonyEngine::Input
{
	/// @brief Device.
	class Device final : public IDevice
	{
	public:
		/// @brief Creates a device.
		/// @param data Device data.
		[[nodiscard("Pure constructor")]]
		explicit Device(const DeviceData& data);
		[[nodiscard("Pure constructor")]]
		Device(const Device& other) = default;
		[[nodiscard("Pure constructor")]]
		Device(Device&& other) noexcept = default;

		~Device() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::string_view Name() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual DeviceTypeId DeviceType() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::span<const std::type_index> FeatureTypes() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual void* FindFeature(std::type_index type) noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const void* FindFeature(std::type_index type) const noexcept override;

		Device& operator =(const Device& other) = default;
		Device& operator =(Device&& other) noexcept = default;

	private:
		std::string name; ///< Device name.
		DeviceTypeId type; ///< Device type.
		
		std::vector<std::type_index> featureTypes; ///< Feature types.
		std::vector<void*> features; ///< Features.
	};
}

namespace PonyEngine::Input
{
	Device::Device(const DeviceData& data) :
		name(data.name),
		type(data.type)
	{
		for (const auto [type, feature] : data.features)
		{
			featureTypes.push_back(type);
			features.push_back(feature);
		}
	}

	std::string_view Device::Name() const noexcept
	{
		return name;
	}

	DeviceTypeId Device::DeviceType() const noexcept
	{
		return type;
	}

	std::span<const std::type_index> Device::FeatureTypes() const noexcept
	{
		return featureTypes;
	}

	void* Device::FindFeature(const std::type_index type) noexcept
	{
		if (const auto position = std::ranges::find(featureTypes, type); position != featureTypes.cend())
		{
			return features[position - featureTypes.cbegin()];
		}

		return nullptr;
	}

	const void* Device::FindFeature(const std::type_index type) const noexcept
	{
		if (const auto position = std::ranges::find(featureTypes, type); position != featureTypes.cend())
		{
			return features[position - featureTypes.cbegin()];
		}

		return nullptr;
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:RootSignature;

import <optional>;
import <string_view>;
import <unordered_map>;

import :ObjectUtility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 root signature.
	class RootSignature final
	{
	public:
		/// @brief Creates a @p RootSignature.
		/// @param rootSignature Root signature.
		[[nodiscard("Pure constructor")]]
		explicit RootSignature(ID3D12RootSignature& rootSignature);
		[[nodiscard("Pure constructor")]]
		RootSignature(const RootSignature& other) = default;
		[[nodiscard("Pure constructor")]]
		RootSignature(RootSignature&& other) noexcept = default;

		~RootSignature() noexcept = default;

		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		ID3D12RootSignature& RootSig() noexcept;
		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		const ID3D12RootSignature& RootSig() const noexcept;

		/// @brief Tries to find a data slot by the @p dataType.
		/// @param dataType Data type.
		/// @return Data slot; std::nullopt it isn't found.
		[[nodiscard("Pure function")]]
		std::optional<std::uint32_t> DataSlot(std::string_view dataType) const noexcept;
		/// @brief Gets the data slots.
		/// @return Data slots.
		[[nodiscard("Pure function")]]
		std::unordered_map<std::string, std::uint32_t>& DataSlots() noexcept;
		/// @brief Gets the data slots.
		/// @return Data slots.
		[[nodiscard("Pure function")]]
		const std::unordered_map<std::string, std::uint32_t>& DataSlots() const noexcept;

		/// @brief Sets the name to the root signature components.
		/// @param name Name.
		void Name(std::string_view name);

		RootSignature& operator =(const RootSignature& other) = default;
		RootSignature& operator =(RootSignature&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature; ///< Root signature.
		std::unordered_map<std::string, std::uint32_t> dataSlots; ///< Data slots.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	RootSignature::RootSignature(ID3D12RootSignature& rootSignature) :
		rootSignature(&rootSignature)
	{
	}

	ID3D12RootSignature& RootSignature::RootSig() noexcept
	{
		return *rootSignature.Get();
	}

	const ID3D12RootSignature& RootSignature::RootSig() const noexcept
	{
		return *rootSignature.Get();
	}

	std::optional<std::uint32_t> RootSignature::DataSlot(const std::string_view dataType) const noexcept
	{
		for (const auto& [type, slot] : dataSlots)
		{
			if (type == dataType)
			{
				return slot;
			}
		}

		return std::nullopt;
	}

	std::unordered_map<std::string, std::uint32_t>& RootSignature::DataSlots() noexcept
	{
		return dataSlots;
	}

	const std::unordered_map<std::string, std::uint32_t>& RootSignature::DataSlots() const noexcept
	{
		return dataSlots;
	}

	void RootSignature::Name(const std::string_view name)
	{
		SetName(*rootSignature.Get(), name);
	}
}

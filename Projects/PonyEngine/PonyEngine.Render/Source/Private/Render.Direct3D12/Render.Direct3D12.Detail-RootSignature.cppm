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

import <string>;
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
		/// @param mvpIndex Model-view-projection matrix slot index.
		[[nodiscard("Pure constructor")]]
		RootSignature(ID3D12RootSignature& rootSignature, const std::unordered_map<std::string, UINT>& meshDataSlots, UINT mvpIndex);
		[[nodiscard("Pure constructor")]]
		RootSignature(const RootSignature& other) = default;
		[[nodiscard("Pure constructor")]]
		RootSignature(RootSignature&& other) noexcept = default;

		~RootSignature() noexcept = default;

		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		ID3D12RootSignature& ControlledRootSignature() noexcept;
		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		const ID3D12RootSignature& ControlledRootSignature() const noexcept;

		/// @brief Gets the model-view-projection matrix slot index.
		/// @return Model-view-projection matrix slot index.
		[[nodiscard("Pure function")]]
		UINT MvpIndex() const noexcept;

		[[nodiscard("Pure function")]]
		const std::unordered_map<std::string, UINT>& MeshDataSlots() const noexcept;

		/// @brief Sets the name to the root signature components.
		/// @param name Name.
		void Name(std::string_view name);

		RootSignature& operator =(const RootSignature& other) = default;
		RootSignature& operator =(RootSignature&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature; ///< Root signature.
		std::unordered_map<std::string, UINT> meshDataSlots; ///< Mesh data slots.
		UINT mvpIndex; ///< Model-view-projection matrix slot index.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	RootSignature::RootSignature(ID3D12RootSignature& rootSignature, const std::unordered_map<std::string, UINT>& meshDataSlots, const UINT mvpIndex) :
		rootSignature(&rootSignature),
		meshDataSlots(meshDataSlots),
		mvpIndex{mvpIndex}
	{
	}

	ID3D12RootSignature& RootSignature::ControlledRootSignature() noexcept
	{
		return *rootSignature.Get();
	}

	const ID3D12RootSignature& RootSignature::ControlledRootSignature() const noexcept
	{
		return *rootSignature.Get();
	}

	UINT RootSignature::MvpIndex() const noexcept
	{
		return mvpIndex;
	}

	const std::unordered_map<std::string, UINT>& RootSignature::MeshDataSlots() const noexcept
	{
		return meshDataSlots;
	}

	void RootSignature::Name(const std::string_view name)
	{
		constexpr std::string_view rootSignatureName = " - RootSignature";
		auto componentName = std::string();
		componentName.reserve(name.size() + rootSignatureName.size());
		componentName.append(name).append(rootSignatureName);
		SetName(*rootSignature.Get(), componentName);
	}
}

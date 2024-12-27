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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RootSignature;

import <string>;
import <string_view>;

import :Direct3D12ObjectUtility;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 root signature.
	class Direct3D12RootSignature final
	{
	public:
		/// @brief Creates a @p Direct3D12RootSignature.
		/// @param rootSignature Root signature.
		/// @param mvpIndex Model-view-projection matrix slot index.
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignature(ID3D12RootSignature& rootSignature, UINT mvpIndex);
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignature(const Direct3D12RootSignature& other) = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignature(Direct3D12RootSignature&& other) noexcept = default;

		~Direct3D12RootSignature() noexcept = default;

		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		ID3D12RootSignature& RootSignature() noexcept;
		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		const ID3D12RootSignature& RootSignature() const noexcept;

		/// @brief Gets the model-view-projection matrix slot index.
		/// @return Model-view-projection matrix slot index.
		[[nodiscard("Pure function")]]
		UINT MvpIndex() const noexcept;

		/// @brief Sets the name to the root signature components.
		/// @param name Name.
		void Name(std::string_view name);

		Direct3D12RootSignature& operator =(const Direct3D12RootSignature& other) = default;
		Direct3D12RootSignature& operator =(Direct3D12RootSignature&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature; ///< Root signature.
		UINT mvpIndex; ///< Model-view-projection matrix slot index.
	};
}

namespace PonyEngine::Render
{
	Direct3D12RootSignature::Direct3D12RootSignature(ID3D12RootSignature& rootSignature, const UINT mvpIndex) :
		rootSignature(&rootSignature),
		mvpIndex{mvpIndex}
	{
	}

	ID3D12RootSignature& Direct3D12RootSignature::RootSignature() noexcept
	{
		return *rootSignature.Get();
	}

	const ID3D12RootSignature& Direct3D12RootSignature::RootSignature() const noexcept
	{
		return *rootSignature.Get();
	}

	UINT Direct3D12RootSignature::MvpIndex() const noexcept
	{
		return mvpIndex;
	}

	void Direct3D12RootSignature::Name(const std::string_view name)
	{
		constexpr std::string_view rootSignatureName = " - RootSignature";
		auto componentName = std::string();
		componentName.reserve(name.size() + rootSignatureName.size());
		componentName.append(name).append(rootSignatureName);
		SetName(*rootSignature.Get(), componentName);
	}
}

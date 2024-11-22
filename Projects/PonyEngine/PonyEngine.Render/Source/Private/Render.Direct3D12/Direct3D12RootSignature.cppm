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

import :Direct3D12Shader;

export namespace PonyEngine::Render
{
	class Direct3D12RootSignature final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignature(ID3D12RootSignature& rootSignature, UINT mvpIndex);
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignature(const Direct3D12RootSignature& other) = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12RootSignature(Direct3D12RootSignature&& other) noexcept = default;

		~Direct3D12RootSignature() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12RootSignature* RootSignature() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12RootSignature* RootSignature() const noexcept;

		[[nodiscard("Pure function")]]
		UINT MvpIndex() const noexcept;

		Direct3D12RootSignature& operator =(const Direct3D12RootSignature& other) = default;
		Direct3D12RootSignature& operator =(Direct3D12RootSignature&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
		UINT mvpIndex;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RootSignature::Direct3D12RootSignature(ID3D12RootSignature& rootSignature, const UINT mvpIndex) :
		rootSignature(&rootSignature),
		mvpIndex{mvpIndex}
	{
	}

	ID3D12RootSignature* Direct3D12RootSignature::RootSignature() noexcept
	{
		return rootSignature.Get();
	}

	const ID3D12RootSignature* Direct3D12RootSignature::RootSignature() const noexcept
	{
		return rootSignature.Get();
	}

	UINT Direct3D12RootSignature::MvpIndex() const noexcept
	{
		return mvpIndex;
	}
}

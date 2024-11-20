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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Material;

import <cstddef>;
import <stdexcept>;
import <type_traits>;

import :Direct3D12Shader;

export namespace PonyEngine::Render
{
	class Direct3D12Material final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(ID3D12RootSignature* rootSignature, ID3D12PipelineState* pipelineState);
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(const Direct3D12Material& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(Direct3D12Material&& other) noexcept = default;

		~Direct3D12Material() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12RootSignature* GetRootSignature() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12RootSignature* GetRootSignature() const noexcept;
		[[nodiscard("Pure function")]]
		ID3D12PipelineState* GetPipelineState() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12PipelineState* GetPipelineState() const noexcept;

		Direct3D12Material& operator =(const Direct3D12Material& other) noexcept = default;
		Direct3D12Material& operator =(Direct3D12Material&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Material::Direct3D12Material(ID3D12RootSignature* const rootSignature, ID3D12PipelineState* const pipelineState) :
		rootSignature(rootSignature),
		pipelineState(pipelineState)
	{
	}

	ID3D12RootSignature* Direct3D12Material::GetRootSignature() noexcept
	{
		return rootSignature.Get();
	}

	const ID3D12RootSignature* Direct3D12Material::GetRootSignature() const noexcept
	{
		return rootSignature.Get();
	}

	ID3D12PipelineState* Direct3D12Material::GetPipelineState() noexcept
	{
		return pipelineState.Get();
	}

	const ID3D12PipelineState* Direct3D12Material::GetPipelineState() const noexcept
	{
		return pipelineState.Get();
	}
}

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

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Material;

import <memory>;

import :Direct3D12RootSignature;

export namespace PonyEngine::Render
{
	class Direct3D12Material final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, ID3D12PipelineState& pipelineState, D3D_PRIMITIVE_TOPOLOGY primitiveTopology) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(const Direct3D12Material& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(Direct3D12Material&& other) noexcept = default;

		~Direct3D12Material() noexcept = default;

		[[nodiscard("Pure function")]]
		Direct3D12RootSignature& RootSignature() noexcept;
		[[nodiscard("Pure function")]]
		const Direct3D12RootSignature& RootSignature() const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12PipelineState& GetPipelineState() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12PipelineState& GetPipelineState() const noexcept;

		[[nodiscard("Pure function")]]
		D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology() const noexcept;

		Direct3D12Material& operator =(const Direct3D12Material& other) noexcept = default;
		Direct3D12Material& operator =(Direct3D12Material&& other) noexcept = default;

	private:
		std::shared_ptr<Direct3D12RootSignature> rootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
		D3D_PRIMITIVE_TOPOLOGY primitiveTopology;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Material::Direct3D12Material(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, ID3D12PipelineState& pipelineState, const D3D_PRIMITIVE_TOPOLOGY primitiveTopology) noexcept :
		rootSignature(rootSignature),
		pipelineState(&pipelineState),
		primitiveTopology{primitiveTopology}
	{
		assert(rootSignature && "The root signature is nullptr.");
	}

	Direct3D12RootSignature& Direct3D12Material::RootSignature() noexcept
	{
		return *rootSignature;
	}

	const Direct3D12RootSignature& Direct3D12Material::RootSignature() const noexcept
	{
		return *rootSignature;
	}

	ID3D12PipelineState& Direct3D12Material::GetPipelineState() noexcept
	{
		return *pipelineState.Get();
	}

	const ID3D12PipelineState& Direct3D12Material::GetPipelineState() const noexcept
	{
		return *pipelineState.Get();
	}

	D3D_PRIMITIVE_TOPOLOGY Direct3D12Material::PrimitiveTopology() const noexcept
	{
		return primitiveTopology;
	}
}

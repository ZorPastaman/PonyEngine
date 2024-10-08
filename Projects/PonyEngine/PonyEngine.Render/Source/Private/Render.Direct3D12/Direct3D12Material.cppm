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

export module PonyEngine.Render.Direct3D12:Direct3D12Material;

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
		Direct3D12Material(ID3D12Device10* device, const Direct3D12Shader& rootSignatureShader, const Direct3D12Shader& vertexShader, const Direct3D12Shader& pixelShader, DXGI_FORMAT rtvFormat);
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(const Direct3D12Material& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(Direct3D12Material&& other) noexcept = default;

		~Direct3D12Material() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12RootSignature* GetRootSignature() const noexcept;
		[[nodiscard("Pure function")]]
		ID3D12PipelineState* GetPipelineState() const noexcept;

		Direct3D12Material& operator =(const Direct3D12Material& other) noexcept = default;
		Direct3D12Material& operator =(Direct3D12Material&& other) noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Material::Direct3D12Material(ID3D12Device10* const device, const Direct3D12Shader& rootSignatureShader, const Direct3D12Shader& vertexShader, const Direct3D12Shader& pixelShader, const DXGI_FORMAT rtvFormat)
	{
		if (const HRESULT result = device->CreateRootSignature(0, rootSignatureShader.Data(), rootSignatureShader.Size(), IID_PPV_ARGS(rootSignature.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 root signature with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		constexpr auto blendState = D3D12_BLEND_DESC
		{
			.AlphaToCoverageEnable = false,
			.IndependentBlendEnable = false,
			.RenderTarget = 
			{
				D3D12_RENDER_TARGET_BLEND_DESC
				{
					.BlendEnable = false,
					.LogicOpEnable = false,
					.SrcBlend = D3D12_BLEND_ZERO,
					.DestBlend = D3D12_BLEND_ZERO,
					.BlendOp = D3D12_BLEND_OP_ADD,
					.SrcBlendAlpha = D3D12_BLEND_ZERO,
					.DestBlendAlpha = D3D12_BLEND_ZERO,
					.BlendOpAlpha = D3D12_BLEND_OP_ADD,
					.LogicOp = D3D12_LOGIC_OP_NOOP,
					.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL
				}
			}
		};
		constexpr D3D12_INPUT_ELEMENT_DESC inputLayout[] =
		{
			D3D12_INPUT_ELEMENT_DESC
			{
				.SemanticName = "POSITION",
				.SemanticIndex = 0u,
				.Format = DXGI_FORMAT_R32G32B32_FLOAT,
				.InputSlot = 0u,
				.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT,
				.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				.InstanceDataStepRate = 0u
			},
			D3D12_INPUT_ELEMENT_DESC
			{
				.SemanticName = "COLOR",
				.SemanticIndex = 0u,
				.Format = DXGI_FORMAT_R32G32B32A32_FLOAT,
				.InputSlot = 1u,
				.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT,
				.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				.InstanceDataStepRate = 0u
			}
		};
		const auto gfxPsd = D3D12_GRAPHICS_PIPELINE_STATE_DESC
		{
			.pRootSignature = rootSignature.Get(),
			.VS = D3D12_SHADER_BYTECODE{.pShaderBytecode = vertexShader.Data(), .BytecodeLength = vertexShader.Size()},
			.PS = D3D12_SHADER_BYTECODE{.pShaderBytecode = pixelShader.Data(), .BytecodeLength = pixelShader.Size()},
			.BlendState = blendState,
			.SampleMask = UINT_MAX,
			.RasterizerState = D3D12_RASTERIZER_DESC
			{
				.FillMode = D3D12_FILL_MODE_SOLID,
				.CullMode = D3D12_CULL_MODE_BACK,
				.FrontCounterClockwise = true
			},
			.InputLayout = D3D12_INPUT_LAYOUT_DESC{.pInputElementDescs = inputLayout, .NumElements = _countof(inputLayout)},
			.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED,
			.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
			.NumRenderTargets = 1,
			.RTVFormats = { rtvFormat },
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1, .Quality = 0}
		};
		if (const HRESULT result = device->CreateGraphicsPipelineState(&gfxPsd, IID_PPV_ARGS(pipelineState.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 graphics pipeline state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	ID3D12RootSignature* Direct3D12Material::GetRootSignature() const noexcept
	{
		return rootSignature.Get();
	}

	ID3D12PipelineState* Direct3D12Material::GetPipelineState() const noexcept
	{
		return pipelineState.Get();
	}
}

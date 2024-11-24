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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12MaterialManager;

import <cstddef>;
import <memory>;
import <unordered_map>;

import PonyEngine.Render.Detail;

import :Direct3D12Material;
import :Direct3D12RootSignatureManager;
import :IDirect3D12MaterialManagerPrivate;

export namespace PonyEngine::Render
{
	class Direct3D12MaterialManager final : public IDirect3D12MaterialManagerPrivate
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12MaterialManager(IDirect3D12SystemContext& renderSystem, DXGI_FORMAT rtvFormat) noexcept;
		Direct3D12MaterialManager(const Direct3D12MaterialManager&) = delete;
		Direct3D12MaterialManager(Direct3D12MaterialManager&&) = delete;

		~Direct3D12MaterialManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<Direct3D12Material> CreateMaterial(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, const Direct3D12Shader& vertexShader, const Direct3D12Shader& pixelShader) override;

		Direct3D12MaterialManager& operator =(const Direct3D12MaterialManager&) = delete;
		Direct3D12MaterialManager& operator =(Direct3D12MaterialManager&&) = delete;

	private:
		DXGI_FORMAT rtvFormat;

		IDirect3D12SystemContext* renderSystem;
	};
}

namespace PonyEngine::Render
{
	Direct3D12MaterialManager::Direct3D12MaterialManager(IDirect3D12SystemContext& renderSystem, const DXGI_FORMAT rtvFormat) noexcept :
		rtvFormat{rtvFormat},
		renderSystem{&renderSystem}
	{
	}

	std::shared_ptr<Direct3D12Material> Direct3D12MaterialManager::CreateMaterial(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, const Direct3D12Shader& vertexShader, const Direct3D12Shader& pixelShader)
	{
		auto blendState = D3D12_BLEND_DESC
		{
			.AlphaToCoverageEnable = false,
			.IndependentBlendEnable = false,
		};
		for (D3D12_RENDER_TARGET_BLEND_DESC& renderTarget : blendState.RenderTarget)
		{
			renderTarget = D3D12_RENDER_TARGET_BLEND_DESC
			{
				.BlendEnable = false,
				.LogicOpEnable = false,
				.SrcBlend = D3D12_BLEND_ONE,
				.DestBlend = D3D12_BLEND_ZERO,
				.BlendOp = D3D12_BLEND_OP_ADD,
				.SrcBlendAlpha = D3D12_BLEND_ONE,
				.DestBlendAlpha = D3D12_BLEND_ZERO,
				.BlendOpAlpha = D3D12_BLEND_OP_ADD,
				.LogicOp = D3D12_LOGIC_OP_NOOP,
				.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL
			};
		}
		constexpr auto rasterizerState = D3D12_RASTERIZER_DESC
		{
			.FillMode = D3D12_FILL_MODE_SOLID,
			.CullMode = D3D12_CULL_MODE_BACK,
			.FrontCounterClockwise = true,
			.DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
			.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
			.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
			.DepthClipEnable = true,
			.MultisampleEnable = false,
			.AntialiasedLineEnable = false,
			.ForcedSampleCount = 0u,
			.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
		};
		constexpr auto depthStencilState = D3D12_DEPTH_STENCIL_DESC
		{
			.DepthEnable = true,
			.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
			.DepthFunc = D3D12_COMPARISON_FUNC_LESS,
			.StencilEnable = false
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
		const auto gfxPsd = D3D12_GRAPHICS_PIPELINE_STATE_DESC // TODO: Many of these settings have to come with parameters.
		{
			.pRootSignature = &rootSignature->RootSignature(),
			.VS = D3D12_SHADER_BYTECODE{.pShaderBytecode = vertexShader.Data(), .BytecodeLength = vertexShader.Size()},
			.PS = D3D12_SHADER_BYTECODE{.pShaderBytecode = pixelShader.Data(), .BytecodeLength = pixelShader.Size()},
			.BlendState = blendState,
			.SampleMask = UINT_MAX,
			.RasterizerState = rasterizerState,
			.DepthStencilState = depthStencilState,
			.InputLayout = D3D12_INPUT_LAYOUT_DESC{.pInputElementDescs = inputLayout, .NumElements = _countof(inputLayout)},
			.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED,
			.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
			.NumRenderTargets = 1,
			.RTVFormats = { rtvFormat },
			.DSVFormat = DXGI_FORMAT_D32_FLOAT,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1, .Quality = 0},
			.NodeMask = 0u,
			.Flags = D3D12_PIPELINE_STATE_FLAG_NONE
		};

		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
		if (const HRESULT result = renderSystem->Device().CreateGraphicsPipelineState(&gfxPsd, IID_PPV_ARGS(pipelineState.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 graphics pipeline state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		return std::make_shared<Direct3D12Material>(rootSignature, *pipelineState.Get(), D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}

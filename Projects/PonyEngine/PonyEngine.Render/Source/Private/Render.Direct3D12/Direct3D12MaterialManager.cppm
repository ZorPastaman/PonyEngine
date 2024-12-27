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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12MaterialManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <optional>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyDebug.Log;

import :Direct3D12InputElementParams;
import :Direct3D12Material;
import :Direct3D12PipelineStateParams;
import :Direct3D12RootSignature;
import :Direct3D12Shader;
import :IDirect3D12DepthStencilPrivate;
import :IDirect3D12MaterialManagerPrivate;
import :IDirect3D12MeshManagerPrivate;
import :IDirect3D12RenderTargetPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 material manager.
	class Direct3D12MaterialManager final : public IDirect3D12MaterialManagerPrivate
	{
	public:
		/// @brief Creates a @p Direct3D12MaterialManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12MaterialManager(IDirect3D12SystemContext& d3d12System) noexcept;
		Direct3D12MaterialManager(const Direct3D12MaterialManager&) = delete;
		Direct3D12MaterialManager(Direct3D12MaterialManager&&) = delete;

		~Direct3D12MaterialManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Direct3D12Material> CreateMaterial(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, const Direct3D12Shader& vertexShader, const Direct3D12Shader& pixelShader,
			const Direct3D12PipelineStateParams& pipelineParams) override;

		/// @brief Cleans out of dead materials.
		void Clean() noexcept;

		Direct3D12MaterialManager& operator =(const Direct3D12MaterialManager&) = delete;
		Direct3D12MaterialManager& operator =(Direct3D12MaterialManager&&) = delete;

	private:
		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Direct3D12Material>> materials; ///< Materials.

		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout; ///< Input layout cache.
	};
}

namespace PonyEngine::Render
{
	Direct3D12MaterialManager::Direct3D12MaterialManager(IDirect3D12SystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Direct3D12Material> Direct3D12MaterialManager::CreateMaterial(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, const Direct3D12Shader& vertexShader, const Direct3D12Shader& pixelShader,
		const Direct3D12PipelineStateParams& pipelineParams)
	{
		// TODO: Later it must use Resource system types. This function always creates a new material. But the function that accepts MaterialResource should try to find a material created from that resource.

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
					.SrcBlend = D3D12_BLEND_ONE,
					.DestBlend = D3D12_BLEND_ZERO,
					.BlendOp = D3D12_BLEND_OP_ADD,
					.SrcBlendAlpha = D3D12_BLEND_ONE,
					.DestBlendAlpha = D3D12_BLEND_ZERO,
					.BlendOpAlpha = D3D12_BLEND_OP_ADD,
					.LogicOp = D3D12_LOGIC_OP_NOOP,
					.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL
				}
			}
		};

		constexpr auto rasterizerState = D3D12_RASTERIZER_DESC
		{
			.FillMode = D3D12_FILL_MODE_SOLID,
			.CullMode = D3D12_CULL_MODE_BACK,
			.FrontCounterClockwise = true,
			.DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
			.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
			.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
			.DepthClipEnable = true,
			.MultisampleEnable = true,
			.AntialiasedLineEnable = false,
			.ForcedSampleCount = 0u,
			.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF
		};

		constexpr auto depthStencilState = D3D12_DEPTH_STENCIL_DESC
		{
			.DepthEnable = true,
			.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
			.DepthFunc = D3D12_COMPARISON_FUNC_LESS,
			.StencilEnable = true,
			.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK,
			.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK,
			.FrontFace = D3D12_DEPTH_STENCILOP_DESC
			{
				.StencilFailOp = D3D12_STENCIL_OP_KEEP,
				.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
				.StencilPassOp = D3D12_STENCIL_OP_KEEP,
				.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS
			},
			.BackFace = D3D12_DEPTH_STENCILOP_DESC
			{
				.StencilFailOp = D3D12_STENCIL_OP_KEEP,
				.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
				.StencilPassOp = D3D12_STENCIL_OP_KEEP,
				.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS
			}
		};

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Set input layout.");
		const IDirect3D12MeshManagerPrivate& meshManager = d3d12System->MeshManagerPrivate();
		const Direct3D12InputElementParams& vertexInput = pipelineParams.vertexInputParams;
		inputLayout.clear();
		inputLayout.push_back(D3D12_INPUT_ELEMENT_DESC
		{
			.SemanticName = vertexInput.semanticName,
			.SemanticIndex = vertexInput.semanticIndex,
			.Format = meshManager.VertexFormat().VertexFormat(),
			.InputSlot = vertexInput.inputSlot,
			.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT,
			.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			.InstanceDataStepRate = 0u
		});
		if (pipelineParams.vertexColorInputParams)
		{
			const Direct3D12InputElementParams& vertexColorInput = pipelineParams.vertexColorInputParams.value();
			inputLayout.push_back(D3D12_INPUT_ELEMENT_DESC
			{
				.SemanticName = vertexColorInput.semanticName,
				.SemanticIndex = vertexColorInput.semanticIndex,
				.Format = meshManager.VertexColorFormat().VertexFormat(),
				.InputSlot = vertexColorInput.inputSlot,
				.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT,
				.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
				.InstanceDataStepRate = 0u
			});
		}
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Input layout set.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create graphics pipeline state.");
		const IDirect3D12RenderTargetPrivate& renderTarget = d3d12System->RenderTargetPrivate();
		const auto gfxPsd = D3D12_GRAPHICS_PIPELINE_STATE_DESC
		{
			.pRootSignature = &rootSignature->RootSignature(),
			.VS = D3D12_SHADER_BYTECODE{.pShaderBytecode = vertexShader.Data(), .BytecodeLength = vertexShader.Size()},
			.PS = D3D12_SHADER_BYTECODE{.pShaderBytecode = pixelShader.Data(), .BytecodeLength = pixelShader.Size()},
			.BlendState = blendState,
			.SampleMask = UINT_MAX,
			.RasterizerState = rasterizerState,
			.DepthStencilState = depthStencilState,
			.InputLayout = D3D12_INPUT_LAYOUT_DESC{.pInputElementDescs = inputLayout.data(), .NumElements = static_cast<UINT>(inputLayout.size())},
			.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED,
			.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,
			.NumRenderTargets = 1,
			.RTVFormats = { renderTarget.Format() },
			.DSVFormat = d3d12System->DepthStencilPrivate().DsvFormat(),
			.SampleDesc = renderTarget.SampleDesc(),
			.NodeMask = 0u,
			.Flags = D3D12_PIPELINE_STATE_FLAG_NONE
		};
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
		if (const HRESULT result = d3d12System->Device().CreateGraphicsPipelineState(&gfxPsd, IID_PPV_ARGS(pipelineState.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire graphics pipeline state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline state created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(pipelineState.Get()));

		const auto materialParams = Direct3D12MaterialParams
		{
			.vertexSlot = pipelineParams.vertexInputParams.inputSlot,
			.vertexColorSlot = pipelineParams.vertexColorInputParams ? std::optional<UINT>(pipelineParams.vertexColorInputParams.value().inputSlot) : std::nullopt
		};
		const auto material = std::make_shared<Direct3D12Material>(rootSignature, *pipelineState.Get(), materialParams);
		materials.push_back(material);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(material.get()));

		return material;
	}

	void Direct3D12MaterialManager::Clean() noexcept
	{
		for (std::size_t i = materials.size(); i-- > 0; )
		{
			if (materials[i].use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy material at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(materials[i].get()));
				materials.erase(materials.cbegin() + i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material destroyed.");
			}
		}
	}
}

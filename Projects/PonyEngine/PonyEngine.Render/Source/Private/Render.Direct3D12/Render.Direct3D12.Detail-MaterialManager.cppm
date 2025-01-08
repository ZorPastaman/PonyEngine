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

export module PonyEngine.Render.Direct3D12.Detail:MaterialManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <optional>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyDebug.Log;

import :IDepthStencilPrivate;
import :IMaterialManagerPrivate;
import :IMeshManagerPrivate;
import :IRenderTargetPrivate;
import :ISubSystemContext;
import :Material;
import :PipelineStateUtility;
import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 material manager.
	class MaterialManager final : public IMaterialManagerPrivate
	{
	public:
		/// @brief Creates a @p MaterialManager.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit MaterialManager(ISubSystemContext& d3d12System) noexcept;
		MaterialManager(const MaterialManager&) = delete;
		MaterialManager(MaterialManager&&) = delete;

		~MaterialManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Material> CreateMaterial(const std::shared_ptr<RootSignature>& rootSignature, const Shader& meshShader, const Shader& pixelShader) override;

		/// @brief Cleans out of dead materials.
		void Clean() noexcept;

		MaterialManager& operator =(const MaterialManager&) = delete;
		MaterialManager& operator =(MaterialManager&&) = delete;

	private:
		struct PipelineStateStream final
		{
			PipelineStateStreamRootSignature rootSignature;
			PipelineStateStreamMeshShader meshShader;
			PipelineStateStreamPixelShader pixelShader;
			PipelineStateStreamBlend blend;
			PipelineStateStreamSampleMask sampleMask;
			PipelineStateStreamRasterizer rasterizer;
			PipelineStateStreamDepthStencil1 depthStencil;
			PipelineStateStreamRenderTargetFormats renderTargetFormats;
			PipelineStateStreamDepthStencilFormat depthStencilFormat;
			PipelineStateStreamSampleDescription sampleDescription;
		};

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Material>> materials; ///< Materials.

		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout; ///< Input layout cache.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	MaterialManager::MaterialManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Material> MaterialManager::CreateMaterial(const std::shared_ptr<RootSignature>& rootSignature, const Shader& meshShader, const Shader& pixelShader)
	{
		// TODO: Later it must use Resource system types. This function always creates a new material. But the function that accepts MaterialResource should try to find a material created from that resource.

		const IRenderTargetPrivate& renderTarget = d3d12System->RenderTargetPrivate();
		auto pss = PipelineStateStream
		{
			.rootSignature = &rootSignature->ControlledRootSignature(),
			.meshShader = meshShader.ByteCode(),
			.pixelShader = pixelShader.ByteCode(),
			.blend = D3D12_BLEND_DESC
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
			},
			.sampleMask = UINT_MAX,
			.rasterizer = D3D12_RASTERIZER_DESC
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
			},
			.depthStencil = D3D12_DEPTH_STENCIL_DESC1
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
				},
				.DepthBoundsTestEnable = true
			},
			.renderTargetFormats = D3D12_RT_FORMAT_ARRAY
			{
				.RTFormats = { renderTarget.Format() },
				.NumRenderTargets = 1u
			},
			.depthStencilFormat = d3d12System->DepthStencilPrivate().DsvFormat(),
			.sampleDescription = renderTarget.SampleDesc()
		};
		const auto pssDesc = D3D12_PIPELINE_STATE_STREAM_DESC
		{
			.SizeInBytes = sizeof(pss),
			.pPipelineStateSubobjectStream = &pss
		};
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
		if (const HRESULT result = d3d12System->Device().CreatePipelineState(&pssDesc, IID_PPV_ARGS(pipelineState.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire graphics pipeline state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline state created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(pipelineState.Get()));

		const auto material = std::make_shared<Material>(rootSignature, *pipelineState.Get());
		materials.push_back(material);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(material.get()));

		return material;
	}

	void MaterialManager::Clean() noexcept
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

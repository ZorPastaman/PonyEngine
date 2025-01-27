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

import :IMaterialManager;
import :IMeshManager;
import :ISubSystemContext;
import :Material;
import :PipelineStateUtility;
import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 material manager.
	class MaterialManager final : public IMaterialManager
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
		virtual std::shared_ptr<Material> CreateMaterial(const std::shared_ptr<RootSignature>& rootSignature, const std::shared_ptr<const Shader>& amplificationShader, const std::shared_ptr<const Shader>& meshShader, 
			const std::shared_ptr<const Shader>& pixelShader) override;

		/// @brief Cleans out of dead materials.
		void Clean() noexcept;

		MaterialManager& operator =(const MaterialManager&) = delete;
		MaterialManager& operator =(MaterialManager&&) = delete;

	private:
		struct PipelineStateStream final
		{
			PipelineStateStreamRootSignature rootSignature;
			PipelineStateStreamAmplificationShader amplificationShader;
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

		struct SourceData final
		{
			std::shared_ptr<const Shader> amplificationShader;
			std::shared_ptr<const Shader> meshShader;
			std::shared_ptr<const Shader> pixelShader;
		};

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::vector<std::shared_ptr<Material>> materials; ///< Materials.
		std::vector<SourceData> sources;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	MaterialManager::MaterialManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Material> MaterialManager::CreateMaterial(const std::shared_ptr<RootSignature>& rootSignature, const std::shared_ptr<const Shader>& amplificationShader, const std::shared_ptr<const Shader>& meshShader, 
		const std::shared_ptr<const Shader>& pixelShader)
	{
		for (std::size_t i = 0; i < sources.size(); ++i)
		{
			if (sources[i].amplificationShader == amplificationShader && sources[i].meshShader == meshShader && sources[i].pixelShader == pixelShader && &materials[i]->RootSignature() == rootSignature.get())
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Material reused at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(materials[i].get()));

				return materials[i];
			}
		}

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire graphics pipeline state.");
		auto pss = PipelineStateStream
		{
			.rootSignature = &rootSignature->RootSig(),
			.amplificationShader = amplificationShader ? amplificationShader->ByteCode() : D3D12_SHADER_BYTECODE{},
			.meshShader = meshShader->ByteCode(),
			.pixelShader = pixelShader->ByteCode(),
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
				.RTFormats = { d3d12System->FrameManager().RtvFormat() },
				.NumRenderTargets = 1u
			},
			.depthStencilFormat = d3d12System->FrameManager().DsvFormat(),
			.sampleDescription = d3d12System->FrameManager().SampleDesc()
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
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline state acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(pipelineState.Get()));
		const auto material = std::make_shared<Material>(rootSignature, *pipelineState.Get());

		materials.reserve(materials.size() + 1);
		sources.reserve(sources.size() + 1);
		sources.push_back(SourceData{.amplificationShader = amplificationShader, .meshShader = meshShader, .pixelShader = pixelShader});
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

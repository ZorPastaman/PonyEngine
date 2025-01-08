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

export module PonyEngine.Render.Direct3D12.Detail:SrgbOutputQuad;

import <array>;
import <cstddef>;
import <cstring>;
import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;

import PonyBase.Utility;

import PonyMath.Core;

import :ISubSystemContext;
import :FormatUtility;
import :ObjectUtility;
import :PipelineStateUtility;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 srgb output quad.
	class SrgbOutputQuad final
	{
	public:
		static constexpr UINT RenderTargetSlot = 0u; ///< Render target texture slot.
		static constexpr UINT ThreadGroupXCount = 1u; ///< Thread group x count.
		static constexpr UINT ThreadGroupYCount = 1u; ///< Thread group y count.
		static constexpr UINT ThreadGroupZCount = 1u; ///< Thread group z count.

		/// @brief Creates a @p SrgbOutputQuad.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit SrgbOutputQuad(ISubSystemContext& d3d12System);
		SrgbOutputQuad(const SrgbOutputQuad&) = delete;
		[[nodiscard("Pure constructor")]]
		SrgbOutputQuad(SrgbOutputQuad&& other) noexcept = default;

		~SrgbOutputQuad() noexcept;

		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		ID3D12RootSignature& RootSignature() noexcept;
		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		const ID3D12RootSignature& RootSignature() const noexcept;
		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		ID3D12PipelineState& PipelineState() noexcept;
		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		const ID3D12PipelineState& PipelineState() const noexcept;

		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		SrgbOutputQuad& operator =(const SrgbOutputQuad&) = delete;
		SrgbOutputQuad& operator =(SrgbOutputQuad&& other) noexcept = default;

	private:
		/// @brief Quad pipeline state stream.
		struct QuadPipelineStateStream final
		{
			PipelineStateStreamRootSignature rootSignature; ///< Root signature stream.
			PipelineStateStreamMeshShader meshShader; ///< Mesh shader stream.
			PipelineStateStreamPixelShader pixelShader; ///< Pixel shader stream.
			PipelineStateStreamBlend blend; ///< Blend stream.
			PipelineStateStreamSampleMask sampleMask; ///< Sample mask stream.
			PipelineStateStreamRasterizer rasterizer; ///< Rasterizer stream.
			PipelineStateStreamRenderTargetFormats renderTargetFormats; ///< Render target formats stream.
			PipelineStateStreamSampleDescription sampleDescription; ///< Sample description stream.
		};

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature; ///< Root signature.
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState; ///< Pipeline state.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	SrgbOutputQuad::SrgbOutputQuad(ISubSystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create srgb output root signature.");
		const auto rootSignatureShader = Shader("OutputRootSig");
		ID3D12Device10& device = this->d3d12System->Device();
		if (const HRESULT result = device.CreateRootSignature(0u, rootSignatureShader.Data(), rootSignatureShader.Size(), IID_PPV_ARGS(rootSignature.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire srgb output root signature with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output root signature created.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create srgb output pipeline state.");
		const auto meshShader = Shader("OutputMeshShader");
		const auto pixelShader = Shader("OutputPixelShader");
		auto pss = QuadPipelineStateStream
		{
			.rootSignature = rootSignature.Get(),
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
						.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL
					}
				}
			},
			.sampleMask = UINT_MAX,
			.rasterizer = D3D12_RASTERIZER_DESC
			{
				.FillMode = D3D12_FILL_MODE_SOLID,
				.CullMode = D3D12_CULL_MODE_NONE,
				.FrontCounterClockwise = true,
				.DepthClipEnable = false,
				.MultisampleEnable = false,
				.AntialiasedLineEnable = false
			},
			.renderTargetFormats = D3D12_RT_FORMAT_ARRAY
			{
				.RTFormats = { this->d3d12System->BackPrivate().FormatSrgb() },
				.NumRenderTargets = 1u
			},
			.sampleDescription = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}
		};
		const auto pssDesc = D3D12_PIPELINE_STATE_STREAM_DESC
		{
			.SizeInBytes = sizeof(pss),
			.pPipelineStateSubobjectStream = &pss
		};
		if (const HRESULT result = device.CreatePipelineState(&pssDesc, IID_PPV_ARGS(pipelineState.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire srgb output pipeline state with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output pipeline state created.");
	}

	SrgbOutputQuad::~SrgbOutputQuad() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release srgb output pipeline state.");
		pipelineState.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output pipeline state released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release srgb output root signature.");
		pipelineState.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Srgb output root signature released.");
	}

	ID3D12RootSignature& SrgbOutputQuad::RootSignature() noexcept
	{
		return *rootSignature.Get();
	}

	const ID3D12RootSignature& SrgbOutputQuad::RootSignature() const noexcept
	{
		return *rootSignature.Get();
	}

	ID3D12PipelineState& SrgbOutputQuad::PipelineState() noexcept
	{
		return *pipelineState.Get();
	}

	const ID3D12PipelineState& SrgbOutputQuad::PipelineState() const noexcept
	{
		return *pipelineState.Get();
	}

	void SrgbOutputQuad::Name(const std::string_view name)
	{
		constexpr std::string_view rootSignatureName = " - RootSignature";
		constexpr std::string_view pipelineStateName = " - PipelineState";

		auto componentName = std::string();
		componentName.reserve(name.size() + rootSignatureName.size());

		componentName.append(name).append(rootSignatureName);
		SetName(*rootSignature.Get(), componentName);

		componentName.erase();
		componentName.append(name).append(pipelineStateName);
		SetName(*pipelineState.Get(), componentName);
	}
}

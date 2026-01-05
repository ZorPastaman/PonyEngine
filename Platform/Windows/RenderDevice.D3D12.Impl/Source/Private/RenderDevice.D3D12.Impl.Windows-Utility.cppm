/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Render/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:Utility;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::Render::Windows
{
	[[nodiscard("Pure function")]]
	TextureFormatFeature ToEngineTextureFormatFeatures(D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport) noexcept;
	[[nodiscard("Pure function")]]
	TextureFormatFeature ToEngineTextureFormatFeatures(D3D12_FORMAT_SUPPORT1 formatSupport) noexcept;
	[[nodiscard("Pure function")]]
	TextureFormatFeature ToEngineTextureFormatFeatures(D3D12_FORMAT_SUPPORT2 formatSupport) noexcept;

	/// @brief Sets the object name.
	/// @param object Target object.
	/// @param name Name to set.
	void SetName(ID3D12Object& object, std::string_view name);
}

namespace PonyEngine::Render::Windows
{
	template<typename T, std::size_t Size> [[nodiscard("Pure function")]]
	TextureFormatFeature ToEngineTextureFormatFeatures(T formatSupport, std::span<const std::pair<T, TextureFormatFeature>, Size> map) noexcept;

	TextureFormatFeature ToEngineTextureFormatFeatures(const D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport) noexcept
	{
		return ToEngineTextureFormatFeatures(formatSupport.Support1) | ToEngineTextureFormatFeatures(formatSupport.Support2);
	}

	TextureFormatFeature ToEngineTextureFormatFeatures(const D3D12_FORMAT_SUPPORT1 formatSupport) noexcept
	{
		static constexpr std::array<std::pair<D3D12_FORMAT_SUPPORT1, TextureFormatFeature>, 20> SupportMap
		{
			std::pair(D3D12_FORMAT_SUPPORT1_TEXTURE1D, TextureFormatFeature::Texture1D),
			std::pair(D3D12_FORMAT_SUPPORT1_TEXTURE2D, TextureFormatFeature::Texture2D),
			std::pair(D3D12_FORMAT_SUPPORT1_TEXTURE3D, TextureFormatFeature::Texture3D),
			std::pair(D3D12_FORMAT_SUPPORT1_TEXTURECUBE, TextureFormatFeature::TextureCube),
			std::pair(D3D12_FORMAT_SUPPORT1_SHADER_LOAD, TextureFormatFeature::ShaderLoad),
			std::pair(D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE, TextureFormatFeature::ShaderSample),
			std::pair(D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON, TextureFormatFeature::ShaderSampleComparison),
			std::pair(D3D12_FORMAT_SUPPORT1_MIP, TextureFormatFeature::Mip),
			std::pair(D3D12_FORMAT_SUPPORT1_RENDER_TARGET, TextureFormatFeature::RenderTarget),
			std::pair(D3D12_FORMAT_SUPPORT1_BLENDABLE, TextureFormatFeature::Blendable),
			std::pair(D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL, TextureFormatFeature::DepthStencil),
			std::pair(D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RESOLVE, TextureFormatFeature::MSResolve),
			std::pair(D3D12_FORMAT_SUPPORT1_DISPLAY, TextureFormatFeature::SwapChain),
			std::pair(D3D12_FORMAT_SUPPORT1_CAST_WITHIN_BIT_LAYOUT, TextureFormatFeature::CastWithinBitLayout),
			std::pair(D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET, TextureFormatFeature::MSRenderTarget),
			std::pair(D3D12_FORMAT_SUPPORT1_MULTISAMPLE_LOAD, TextureFormatFeature::MSLoad),
			std::pair(D3D12_FORMAT_SUPPORT1_SHADER_GATHER, TextureFormatFeature::ShaderGather),
			std::pair(D3D12_FORMAT_SUPPORT1_BACK_BUFFER_CAST, TextureFormatFeature::BackBufferCast),
			std::pair(D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW, TextureFormatFeature::Uav),
			std::pair(D3D12_FORMAT_SUPPORT1_SHADER_GATHER_COMPARISON, TextureFormatFeature::ShaderGatherComparison)
		};

		return ToEngineTextureFormatFeatures<D3D12_FORMAT_SUPPORT1, 20>(formatSupport, SupportMap);
	}

	TextureFormatFeature ToEngineTextureFormatFeatures(const D3D12_FORMAT_SUPPORT2 formatSupport) noexcept
	{
		static constexpr std::array<std::pair<D3D12_FORMAT_SUPPORT2, TextureFormatFeature>, 10> SupportMap
		{
			std::pair(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD, TextureFormatFeature::UavAtomicAdd),
			std::pair(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS, TextureFormatFeature::UavAtomicBitwise),
			std::pair(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE, TextureFormatFeature::UavAtomicCompareStoreCompareExchange),
			std::pair(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE, TextureFormatFeature::UavAtomicExchange),
			std::pair(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX, TextureFormatFeature::UavAtomicSignedMixMax),
			std::pair(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX, TextureFormatFeature::UavAtomicUnsignedMixMax),
			std::pair(D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD, TextureFormatFeature::UavTypedLoad),
			std::pair(D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE, TextureFormatFeature::UavTypedStore),
			std::pair(D3D12_FORMAT_SUPPORT2_OUTPUT_MERGER_LOGIC_OP, TextureFormatFeature::LogicBlendable),
			std::pair(D3D12_FORMAT_SUPPORT2_TILED, TextureFormatFeature::Tiled),
		};

		return ToEngineTextureFormatFeatures<D3D12_FORMAT_SUPPORT2, 10>(formatSupport, SupportMap);
	}

	void SetName(ID3D12Object& object, const std::string_view name)
	{
		if (const HRESULT result = object.SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(name.size()), name.data()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set name: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	template<typename T, std::size_t Size>
	TextureFormatFeature ToEngineTextureFormatFeatures(const T formatSupport, const std::span<const std::pair<T, TextureFormatFeature>, Size> map) noexcept
	{
		auto features = TextureFormatFeature::None;
		for (const auto [support, feature] : map)
		{
			features |= formatSupport & support ? feature : TextureFormatFeature::None;
		}

		return features;
	}
}

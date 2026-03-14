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

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:TextureUtility;

import std;

import PonyEngine.RenderDevice;
import PonyEngine.Type;

import :Texture;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Casts to a native texture.
	/// @param texture Engine texture.
	/// @return Native texture.
	[[nodiscard("Pure function")]]
	Texture& ToNativeTexture(ITexture& texture);
	/// @brief Casts to a native texture.
	/// @param texture Engine texture.
	/// @return Native texture.
	[[nodiscard("Pure function")]]
	const Texture& ToNativeTexture(const ITexture& texture);
	/// @brief Casts to a native texture.
	/// @param texture Engine texture.
	/// @return Native texture.
	[[nodiscard("Pure function")]]
	Texture* ToNativeTexture(ITexture* texture);
	/// @brief Casts to a native texture.
	/// @param texture Engine texture.
	/// @return Native texture.
	[[nodiscard("Pure function")]]
	const Texture* ToNativeTexture(const ITexture* texture);
	/// @brief Casts to a native texture.
	/// @param texture Engine texture.
	/// @return Native texture.
	[[nodiscard("Pure function")]]
	Texture* ToNativeTextureNotNullptr(ITexture* texture);
	/// @brief Casts to a native texture.
	/// @param texture Engine texture.
	/// @return Native texture.
	[[nodiscard("Pure function")]]
	const Texture* ToNativeTextureNotNullptr(const ITexture* texture);

	/// @brief Checks if the request for a color texture is valid.
	/// @param request Texture support request.
	/// @param support Texture format support.
	/// @return @a True if it's valid; @a false otherwise.
	[[nodiscard("Pure function")]]
	constexpr bool CheckColorSupport(const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
	/// @brief Checks if the request for a depth texture is valid.
	/// @param request Texture support request.
	/// @param support Texture format support.
	/// @return @a True if it's valid; @a false otherwise.
	[[nodiscard("Pure function")]]
	constexpr bool CheckDepthSupport(const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;

	/// @brief Gets a required format support.
	/// @param dimension Texture dimension.
	/// @return Required format support.
	[[nodiscard("Pure function")]]
	constexpr D3D12_FORMAT_SUPPORT1 GetFormatSupport(TextureDimension dimension) noexcept;
	/// @brief Gets a required format support.
	/// @param usage Texture usage.
	/// @return Required format support.
	[[nodiscard("Pure function")]]
	constexpr D3D12_FORMAT_SUPPORT1 GetFormatSupport(TextureUsage usage) noexcept;

	/// @brief Casts the engine aspect to a plane index.
	/// @param aspect Engine aspect.
	/// @return Plane index.
	[[nodiscard("Pure function")]]
	constexpr UINT8 ToPlaneIndex(Aspect aspect) noexcept;
	/// @brief Casts the engine aspect mask to a first plane index.
	/// @param aspects Engine aspect mask.
	/// @return First plane index.
	[[nodiscard("Pure function")]]
	constexpr UINT8 ToFirstPlaneIndex(AspectMask aspects) noexcept;
	/// @brief Casts the engine aspect mask to a plane count.
	/// @param aspects Engine aspect mask.
	/// @return Plane count.
	[[nodiscard("Pure function")]]
	constexpr UINT8 ToPlaneCount(AspectMask aspects) noexcept;

	/// @brief Casts the engine resource layout to a native resource layout.
	/// @param layout Engine resource layout.
	/// @return Native resource layout.
	[[nodiscard("Pure function")]]
	constexpr D3D12_BARRIER_LAYOUT ToLayout(ResourceLayout layout) noexcept;

	/// @brief Casts the engine clear value to a native clear value.
	/// @param clearValue Engine clear value.
	/// @param format Format.
	/// @return Native clear value.
	[[nodiscard("Pure function")]]
	constexpr D3D12_CLEAR_VALUE ToClearValue(const ClearValue& clearValue, DXGI_FORMAT format) noexcept;

	/// @brief Gets an array size from the resource description.
	/// @param resourceDesc Resource description.
	/// @return Array size.
	[[nodiscard("Pure function")]]
	constexpr UINT16 GetArraySize(const D3D12_RESOURCE_DESC1& resourceDesc) noexcept;
	/// @brief Calculates a subresource index.
	/// @param mipIndex Mip index.
	/// @param arrayIndex Array element index.
	/// @param planeIndex Plane index.
	/// @param mipCount Resource mip count.
	/// @param arraySize Resource array size.
	/// @return Subresource index.
	[[nodiscard("Pure function")]]
	constexpr UINT CalculateSubresource(UINT16 mipIndex, UINT16 arrayIndex, UINT8 planeIndex, UINT16 mipCount, UINT16 arraySize) noexcept;

	/// @brief Makes a texture resource description.
	/// @param params Texture parameters.
	/// @param format Native format.
	/// @return Texture resource description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_DESC1 MakeResourceDesc(const TextureParams& params, DXGI_FORMAT format) noexcept;
	/// @brief Casts the engine texture dimension to a native texture dimension.
	/// @param dimension Engine texture dimension.
	/// @return Native texture dimension.
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_DIMENSION ToResourceDimension(TextureDimension dimension) noexcept;
	/// @brief Gets a depth or array size from the texture parameters.
	/// @param params Texture parameters.
	/// @return Depth or array size.
	[[nodiscard("Pure function")]]
	constexpr UINT16 GetDepthOrArraySize(const TextureParams& params) noexcept;
	/// @brief Makes resource flags.
	/// @param usage Texture usage.
	/// @return Resource flags.
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_FLAGS MakeResourceFlags(TextureUsage usage) noexcept;

	/// @brief Makes a shader resource view description.
	/// @param params Texture shader resource view parameters.
	/// @param format Native format.
	/// @param resourceMipCount Resource mip count.
	/// @param resourceArraySize Resource array size.
	/// @return Shader resource view description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_SHADER_RESOURCE_VIEW_DESC MakeSRVDesc(const TextureSRVParams& params, DXGI_FORMAT format, std::uint8_t resourceMipCount, std::uint16_t resourceArraySize) noexcept;
	/// @brief Makes an unordered access view description.
	/// @param params Texture unordered access view parameters.
	/// @param format Native format.
	/// @param resourceArraySize Resource array size.
	/// @return Unordered access view description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_UNORDERED_ACCESS_VIEW_DESC MakeUAVDesc(const TextureUAVParams& params, DXGI_FORMAT format, std::uint16_t resourceArraySize) noexcept;
	/// @brief Makes a render target view description.
	/// @param params Render target view parameters.
	/// @param format Native format.
	/// @param resourceArraySize Resource array size.
	/// @return Render target view description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_RENDER_TARGET_VIEW_DESC MakeRTVDesc(const RTVParams& params, DXGI_FORMAT format, std::uint16_t resourceArraySize) noexcept;
	/// @brief Makes a depth stencil view description.
	/// @param params Depth stencil view parameters.
	/// @param format Native format.
	/// @param resourceArraySize Resource array size.
	/// @return Depth stencil view description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_DEPTH_STENCIL_VIEW_DESC MakeDSVDesc(const DSVParams& params, DXGI_FORMAT format, std::uint16_t resourceArraySize) noexcept;
	/// @brief Casts the engine dsv flags to native dsv flags.
	/// @param flags Engine dsv flags.
	/// @return Native dsv flags.
	[[nodiscard("Pure function")]]
	constexpr D3D12_DSV_FLAGS ToDSVFlags(DSVFlag flags) noexcept;

	/// @brief Casts the engine component swizzle to a native component mapping type.
	/// @param swizzle Engine component swizzle.
	/// @return Native component mapping type.
	[[nodiscard("Pure function")]]
	constexpr D3D12_SHADER_COMPONENT_MAPPING ToShaderMapping(ComponentSwizzle swizzle) noexcept;
	/// @brief Casts the engine component mapping to a native component mapping.
	/// @param mapping Engine component mapping.
	/// @return Native component mapping.
	[[nodiscard("Pure function")]]
	constexpr UINT ToShaderMapping(ComponentMapping mapping) noexcept;

	/// @brief Casts the engine resolve mode to a native resolve mode.
	/// @param mode Engine resolve mode.
	/// @return Native resolve mode.
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOLVE_MODE ToResolveMode(ResolveMode mode) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Texture& ToNativeTexture(ITexture& texture)
	{
#ifndef NDEBUG
		if (typeid(texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<Texture&>(texture);
	}

	const Texture& ToNativeTexture(const ITexture& texture)
	{
#ifndef NDEBUG
		if (typeid(texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<const Texture&>(texture);
	}

	Texture* ToNativeTexture(ITexture* const texture)
	{
#ifndef NDEBUG
		if (texture && typeid(*texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<Texture*>(texture);
	}

	const Texture* ToNativeTexture(const ITexture* const texture)
	{
#ifndef NDEBUG
		if (texture && typeid(*texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<const Texture*>(texture);
	}

	Texture* ToNativeTextureNotNullptr(ITexture* texture)
	{
#ifndef NDEBUG
		if (!texture || typeid(*texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<Texture*>(texture);
	}

	const Texture* ToNativeTextureNotNullptr(const ITexture* texture)
	{
#ifndef NDEBUG
		if (!texture || typeid(*texture) != typeid(Texture)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture");
		}
#endif

		return static_cast<const Texture*>(texture);
	}

	constexpr bool CheckColorSupport(const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		if (Any(TextureUsage::DepthStencil, request.usage))
		{
			return false;
		}
		const D3D12_FORMAT_SUPPORT1 requiredSupport = GetFormatSupport(request.dimension) | GetFormatSupport(request.usage);
		if ((requiredSupport & support.Support1) != requiredSupport)
		{
			return false;
		}

		return true;
	}

	constexpr bool CheckDepthSupport(const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		if (Any(TextureUsage::UnorderedAccess | TextureUsage::RenderTarget, request.usage))
		{
			return false;
		}
		const D3D12_FORMAT_SUPPORT1 requiredSupport = GetFormatSupport(request.dimension) | GetFormatSupport(request.usage);
		if ((requiredSupport & support.Support1) != requiredSupport)
		{
			return false;
		}

		return true;
	}

	constexpr D3D12_FORMAT_SUPPORT1 GetFormatSupport(const TextureDimension dimension) noexcept
	{
		switch (dimension)
		{
		case TextureDimension::Texture1D:
			return D3D12_FORMAT_SUPPORT1_TEXTURE1D;
		case TextureDimension::Texture2D:
			return D3D12_FORMAT_SUPPORT1_TEXTURE2D;
		case TextureDimension::Texture3D:
			return D3D12_FORMAT_SUPPORT1_TEXTURE3D;
		default:
			return D3D12_FORMAT_SUPPORT1_NONE;
		}
	}

	constexpr D3D12_FORMAT_SUPPORT1 GetFormatSupport(const TextureUsage usage) noexcept
	{
		D3D12_FORMAT_SUPPORT1 support = D3D12_FORMAT_SUPPORT1_NONE;
		if (Any(TextureUsage::UnorderedAccess, usage))
		{
			support |= D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW;
		}
		if (Any(TextureUsage::RenderTarget, usage))
		{
			support |= D3D12_FORMAT_SUPPORT1_RENDER_TARGET;
		}
		if (Any(TextureUsage::DepthStencil, usage))
		{
			support |= D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL;
		}

		return support;
	}

	constexpr UINT8 ToPlaneIndex(const Aspect aspect) noexcept
	{
		return aspect == Aspect::Stencil;
	}

	constexpr UINT8 ToFirstPlaneIndex(const AspectMask aspects) noexcept
	{
		return aspects == AspectMask::Stencil;
	}

	constexpr UINT8 ToPlaneCount(const AspectMask aspects) noexcept
	{
		return Any(AspectMask::Color | AspectMask::Depth, aspects) + Any(AspectMask::Stencil, aspects);
	}

	constexpr D3D12_BARRIER_LAYOUT ToLayout(const ResourceLayout layout) noexcept
	{
		switch (layout)
		{
		case ResourceLayout::Common:
			return D3D12_BARRIER_LAYOUT_COMMON;
		case ResourceLayout::Present:
			return D3D12_BARRIER_LAYOUT_PRESENT;
		case ResourceLayout::ShaderResource:
			return D3D12_BARRIER_LAYOUT_SHADER_RESOURCE;
		case ResourceLayout::RenderTarget:
			return D3D12_BARRIER_LAYOUT_RENDER_TARGET;
		case ResourceLayout::DepthStencilRead:
			return D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ;
		case ResourceLayout::DepthStencilWrite:
			return D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE;
		case ResourceLayout::UnorderedAccess:
			return D3D12_BARRIER_LAYOUT_UNORDERED_ACCESS;
		case ResourceLayout::CopySource:
			return D3D12_BARRIER_LAYOUT_COPY_SOURCE;
		case ResourceLayout::CopyDestination:
			return D3D12_BARRIER_LAYOUT_COPY_DEST;
		case ResourceLayout::ResolveSource:
			return D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE;
		case ResourceLayout::ResolveDestination:
			return D3D12_BARRIER_LAYOUT_RESOLVE_DEST;
		case ResourceLayout::Undefined:
			return D3D12_BARRIER_LAYOUT_UNDEFINED;
		default: [[unlikely]]
			assert(false && "Invalid layout");
			return D3D12_BARRIER_LAYOUT_COMMON;
		}
	}

	constexpr D3D12_CLEAR_VALUE ToClearValue(const ClearValue& clearValue, const DXGI_FORMAT format) noexcept
	{
		auto clear = D3D12_CLEAR_VALUE
		{
			.Format = format,
		};
		std::visit(Type::Overload
		{
			[&](const NoClear&) noexcept
			{
				clear.Format = DXGI_FORMAT_UNKNOWN;
			},
			[&](const Math::ColorRGBA<float>& color) noexcept
			{
				for (std::size_t i = 0uz; i < color.ChannelCount; ++i)
				{
					clear.Color[i] = color[i];
				}
			},
			[&](const DepthStencil& depthStencil) noexcept
			{
				clear.DepthStencil.Depth = depthStencil.depth;
				clear.DepthStencil.Stencil = depthStencil.stencil;
			}
		}, clearValue);

		return clear;
	}

	constexpr UINT16 GetArraySize(const D3D12_RESOURCE_DESC1& resourceDesc) noexcept
	{
		return resourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D ? 1u : resourceDesc.DepthOrArraySize;
	}

	constexpr UINT CalculateSubresource(const UINT16 mipIndex, const UINT16 arrayIndex, const UINT8 planeIndex, const UINT16 mipCount, const UINT16 arraySize) noexcept
	{
		return mipIndex + arrayIndex * mipCount + planeIndex * mipCount * arraySize;
	}

	constexpr D3D12_RESOURCE_DESC1 MakeResourceDesc(const TextureParams& params, const DXGI_FORMAT format) noexcept
	{
		return D3D12_RESOURCE_DESC1
		{
			.Dimension = ToResourceDimension(params.dimension),
			.Alignment = 0ull,
			.Width = params.size.X(),
			.Height = params.size.Y(),
			.DepthOrArraySize = GetDepthOrArraySize(params),
			.MipLevels = params.mipCount,
			.Format = format,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = ToNumber(params.sampleCount), .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = MakeResourceFlags(params.usage),
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
	}

	constexpr D3D12_RESOURCE_DIMENSION ToResourceDimension(const TextureDimension dimension) noexcept
	{
		switch (dimension)
		{
		case TextureDimension::Texture1D:
			return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
		case TextureDimension::Texture2D:
			return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		case TextureDimension::Texture3D:
			return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
		default: [[unlikely]]
			assert(false && "Invalid dimension.");
			return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		}
	}

	constexpr UINT16 GetDepthOrArraySize(const TextureParams& params) noexcept
	{
		return params.dimension == TextureDimension::Texture3D
			? static_cast<UINT16>(params.size.Z())
			: static_cast<UINT16>(params.arraySize);
	}

	constexpr D3D12_RESOURCE_FLAGS MakeResourceFlags(const TextureUsage usage) noexcept
	{
		auto flags = D3D12_RESOURCE_FLAG_NONE;
		if (usage == TextureUsage::DepthStencil)
		{
			flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE | D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		}
		else
		{
			if (Any(TextureUsage::UnorderedAccess, usage))
			{
				flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
			}
			if (Any(TextureUsage::RenderTarget, usage))
			{
				flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
			}
			if (Any(TextureUsage::DepthStencil, usage))
			{
				flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
			}
		}

		return flags;
	}

	constexpr D3D12_SHADER_RESOURCE_VIEW_DESC MakeSRVDesc(const TextureSRVParams& params, const DXGI_FORMAT format, 
		const std::uint8_t resourceMipCount, const std::uint16_t resourceArraySize) noexcept
	{
		auto viewDesc = D3D12_SHADER_RESOURCE_VIEW_DESC
		{
			.Format = format,
			.Shader4ComponentMapping = ToShaderMapping(params.mapping),
		};

		std::visit(Type::Overload
		{
			[&](const SingleSRVLayout& l) noexcept
			{
				switch (params.dimension)
				{
				case TextureViewDimension::Texture1D:
					viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
					viewDesc.Texture1D = D3D12_TEX1D_SRV
					{
						.MostDetailedMip = l.mipRange.mostDetailedMipIndex,
						.MipLevels = l.mipRange.mipCount.value_or(resourceMipCount - l.mipRange.mostDetailedMipIndex),
						.ResourceMinLODClamp = 0.f
					};
					break;
				case TextureViewDimension::Texture2D:
					viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
					viewDesc.Texture2D = D3D12_TEX2D_SRV
					{
						.MostDetailedMip = l.mipRange.mostDetailedMipIndex,
						.MipLevels = l.mipRange.mipCount.value_or(resourceMipCount - l.mipRange.mostDetailedMipIndex),
						.PlaneSlice = ToPlaneIndex(params.aspect),
						.ResourceMinLODClamp = 0.f
					};
					break;
				case TextureViewDimension::Texture3D:
					viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
					viewDesc.Texture3D = D3D12_TEX3D_SRV
					{
						.MostDetailedMip = l.mipRange.mostDetailedMipIndex,
						.MipLevels = l.mipRange.mipCount.value_or(resourceMipCount - l.mipRange.mostDetailedMipIndex),
						.ResourceMinLODClamp = 0.f
					};
					break;
				case TextureViewDimension::TextureCube:
					viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
					viewDesc.TextureCube = D3D12_TEXCUBE_SRV
					{
						.MostDetailedMip = l.mipRange.mostDetailedMipIndex,
						.MipLevels = l.mipRange.mipCount.value_or(resourceMipCount - l.mipRange.mostDetailedMipIndex),
						.ResourceMinLODClamp = 0.f
					};
					break;
				default: [[unlikely]]
					assert(false && "Invalid view dimension.");
					break;
				}
			},
			[&](const ArraySRVLayout& l) noexcept
			{
				switch (params.dimension)
				{
				case TextureViewDimension::Texture1D:
					viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
					viewDesc.Texture1DArray = D3D12_TEX1D_ARRAY_SRV
					{
						.MostDetailedMip = l.mipRange.mostDetailedMipIndex,
						.MipLevels = l.mipRange.mipCount.value_or(resourceMipCount - l.mipRange.mostDetailedMipIndex),
						.FirstArraySlice = l.arrayRange.firstArrayIndex,
						.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex),
						.ResourceMinLODClamp = 0.f
					};
					break;
				case TextureViewDimension::Texture2D:
					viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
					viewDesc.Texture2DArray = D3D12_TEX2D_ARRAY_SRV
					{
						.MostDetailedMip = l.mipRange.mostDetailedMipIndex,
						.MipLevels = l.mipRange.mipCount.value_or(resourceMipCount - l.mipRange.mostDetailedMipIndex),
						.FirstArraySlice = l.arrayRange.firstArrayIndex,
						.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex),
						.PlaneSlice = ToPlaneIndex(params.aspect),
						.ResourceMinLODClamp = 0.f
					};
					break;
				case TextureViewDimension::Texture3D:
					viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
					viewDesc.Texture3D = D3D12_TEX3D_SRV
					{
						.MostDetailedMip = l.mipRange.mostDetailedMipIndex,
						.MipLevels = l.mipRange.mipCount.value_or(resourceMipCount - l.mipRange.mostDetailedMipIndex),
						.ResourceMinLODClamp = 0.f
					};
					break;
				case TextureViewDimension::TextureCube:
					viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBEARRAY;
					viewDesc.TextureCubeArray = D3D12_TEXCUBE_ARRAY_SRV
					{
						.MostDetailedMip = l.mipRange.mostDetailedMipIndex,
						.MipLevels = l.mipRange.mipCount.value_or(resourceMipCount - l.mipRange.mostDetailedMipIndex),
						.First2DArrayFace = l.arrayRange.firstArrayIndex,
						.NumCubes = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex) / 6u,
						.ResourceMinLODClamp = 0.f
					};
					break;
				default: [[unlikely]]
					assert(false && "Invalid view dimension.");
					break;
				}
			},
			[&](const MultiSampleSRVLayout&) noexcept
			{
				viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;
				viewDesc.Texture2DMS = D3D12_TEX2DMS_SRV
				{
				};
			},
			[&](const MultiSampleArraySRVLayout& l) noexcept
			{
				viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMSARRAY;
				viewDesc.Texture2DMSArray = D3D12_TEX2DMS_ARRAY_SRV
				{
					.FirstArraySlice = l.arrayRange.firstArrayIndex,
					.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex)
				};
			}
		}, params.layout);

		return viewDesc;
	}

	constexpr D3D12_UNORDERED_ACCESS_VIEW_DESC MakeUAVDesc(const TextureUAVParams& params, const DXGI_FORMAT format, const std::uint16_t resourceArraySize) noexcept
	{
		auto viewDesc = D3D12_UNORDERED_ACCESS_VIEW_DESC
		{
			.Format = format
		};

		std::visit(Type::Overload
		{
			[&](const SingleUAVLayout& l) noexcept
			{
				switch (params.dimension)
				{
				case TextureDimension::Texture1D:
					viewDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE1D;
					viewDesc.Texture1D = D3D12_TEX1D_UAV
					{
						.MipSlice = l.mipIndex
					};
					break;
				case TextureDimension::Texture2D:
					viewDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
					viewDesc.Texture2D = D3D12_TEX2D_UAV
					{
						.MipSlice = l.mipIndex,
						.PlaneSlice = ToPlaneIndex(params.aspect)
					};
					break;
				case TextureDimension::Texture3D:
					viewDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
					viewDesc.Texture3D = D3D12_TEX3D_UAV
					{
						.MipSlice = l.mipIndex,
						.FirstWSlice = 0u,
						.WSize = std::numeric_limits<UINT>::max()
					};
					break;
				default: [[unlikely]]
					assert(false && "Invalid dimension");
					break;
				}
			},
			[&](const ArrayUAVLayout& l) noexcept
			{
				switch (params.dimension)
				{
				case TextureDimension::Texture1D:
					viewDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE1DARRAY;
					viewDesc.Texture1DArray = D3D12_TEX1D_ARRAY_UAV
					{
						.MipSlice = l.mipIndex,
						.FirstArraySlice = l.arrayRange.firstArrayIndex,
						.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex)
					};
					break;
				case TextureDimension::Texture2D:
					viewDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
					viewDesc.Texture2DArray = D3D12_TEX2D_ARRAY_UAV
					{
						.MipSlice = l.mipIndex,
						.FirstArraySlice = l.arrayRange.firstArrayIndex,
						.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex),
						.PlaneSlice = ToPlaneIndex(params.aspect)
					};
					break;
				case TextureDimension::Texture3D:
					viewDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
					viewDesc.Texture3D = D3D12_TEX3D_UAV
					{
						.MipSlice = l.mipIndex,
						.FirstWSlice = 0u,
						.WSize = std::numeric_limits<UINT>::max()
					};
					break;
				default: [[unlikely]]
					assert(false && "Invalid dimension");
					break;
				}
			}
		}, params.layout);

		return viewDesc;
	}

	constexpr D3D12_RENDER_TARGET_VIEW_DESC MakeRTVDesc(const RTVParams& params, const DXGI_FORMAT format, const std::uint16_t resourceArraySize) noexcept
	{
		auto viewDesc = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = format
		};
		
		std::visit(Type::Overload
		{
			[&](const SingleRTVLayout& l) noexcept
			{
				switch (params.dimension)
				{
				case TextureDimension::Texture1D:
					viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE1D;
					viewDesc.Texture1D = D3D12_TEX1D_RTV
					{
						.MipSlice = l.mipIndex
					};
					break;
				case TextureDimension::Texture2D:
					viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
					viewDesc.Texture2D = D3D12_TEX2D_RTV
					{
						.MipSlice = l.mipIndex,
						.PlaneSlice = ToPlaneIndex(Aspect::Color)
					};
					break;
				case TextureDimension::Texture3D:
					viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE3D;
					viewDesc.Texture3D = D3D12_TEX3D_RTV
					{
						.MipSlice = l.mipIndex,
						.FirstWSlice = 0u,
						.WSize = std::numeric_limits<UINT>::max()
					};
					break;
				default: [[unlikely]]
					assert(false && "Invalid dimension");
					break;
				}
			},
			[&](const ArrayRTVLayout& l) noexcept
			{
				switch (params.dimension)
				{
				case TextureDimension::Texture1D:
					viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE1DARRAY;
					viewDesc.Texture1DArray = D3D12_TEX1D_ARRAY_RTV
					{
						.MipSlice = l.mipIndex,
						.FirstArraySlice = l.arrayRange.firstArrayIndex,
						.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex)
					};
					break;
				case TextureDimension::Texture2D:
					viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
					viewDesc.Texture2DArray = D3D12_TEX2D_ARRAY_RTV
					{
						.MipSlice = l.mipIndex,
						.FirstArraySlice = l.arrayRange.firstArrayIndex,
						.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex),
						.PlaneSlice = ToPlaneIndex(Aspect::Color)
					};
					break;
				case TextureDimension::Texture3D:
					viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE3D;
					viewDesc.Texture3D = D3D12_TEX3D_RTV
					{
						.MipSlice = l.mipIndex,
						.FirstWSlice = 0u,
						.WSize = std::numeric_limits<UINT>::max()
					};
					break;
				default: [[unlikely]]
					assert(false && "Invalid dimension");
					break;
				}
			},
			[&](const MultiSampleRTVLayout&) noexcept
			{
				viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
				viewDesc.Texture2DMS = D3D12_TEX2DMS_RTV
				{
				};
			},
			[&](const MultiSampleArrayRTVLayout& l) noexcept
			{
				viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY;
				viewDesc.Texture2DMSArray = D3D12_TEX2DMS_ARRAY_RTV
				{
					.FirstArraySlice = l.arrayRange.firstArrayIndex,
					.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex)
				};
			}
		}, params.layout);

		return viewDesc;
	}

	constexpr D3D12_DEPTH_STENCIL_VIEW_DESC MakeDSVDesc(const DSVParams& params, const DXGI_FORMAT format, const std::uint16_t resourceArraySize) noexcept
	{
		auto viewDesc = D3D12_DEPTH_STENCIL_VIEW_DESC
		{
			.Format = format,
			.Flags = ToDSVFlags(params.flags)
		};

		std::visit(Type::Overload
		{
			[&](const SingleDSVLayout& l) noexcept
			{
				switch (params.dimension)
				{
				case TextureDimension::Texture1D:
					viewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE1D;
					viewDesc.Texture1D = D3D12_TEX1D_DSV
					{
						.MipSlice = l.mipIndex
					};
					break;
				case TextureDimension::Texture2D:
					viewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
					viewDesc.Texture2D = D3D12_TEX2D_DSV
					{
						.MipSlice = l.mipIndex
					};
					break;
				default: [[unlikely]]
					assert(false && "Invalid dimension");
					break;
				}
			},
			[&](const ArrayDSVLayout& l) noexcept
			{
				switch (params.dimension)
				{
				case TextureDimension::Texture1D:
					viewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE1DARRAY;
					viewDesc.Texture1DArray = D3D12_TEX1D_ARRAY_DSV
					{
						.MipSlice = l.mipIndex,
						.FirstArraySlice = l.arrayRange.firstArrayIndex,
						.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex)
					};
					break;
				case TextureDimension::Texture2D:
					viewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
					viewDesc.Texture2DArray = D3D12_TEX2D_ARRAY_DSV
					{
						.MipSlice = l.mipIndex,
						.FirstArraySlice = l.arrayRange.firstArrayIndex,
						.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex)
					};
					break;
				default: [[unlikely]]
					assert(false && "Invalid dimension");
					break;
				}
			},
			[&](const MultiSampleDSVLayout&) noexcept
			{
				viewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;
				viewDesc.Texture2DMS = D3D12_TEX2DMS_DSV
				{
				};
			},
			[&](const MultiSampleArrayDSVLayout& l) noexcept
			{
				viewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMSARRAY;
				viewDesc.Texture2DMSArray = D3D12_TEX2DMS_ARRAY_DSV
				{
					.FirstArraySlice = l.arrayRange.firstArrayIndex,
					.ArraySize = l.arrayRange.arrayCount.value_or(resourceArraySize - l.arrayRange.firstArrayIndex)
				};
			}
		}, params.layout);

		return viewDesc;
	}

	constexpr D3D12_DSV_FLAGS ToDSVFlags(const DSVFlag flags) noexcept
	{
		auto answer = D3D12_DSV_FLAG_NONE;
		if (Any(DSVFlag::DepthReadOnly, flags))
		{
			answer |= D3D12_DSV_FLAG_READ_ONLY_DEPTH;
		}
		if (Any(DSVFlag::StencilReadOnly, flags))
		{
			answer |= D3D12_DSV_FLAG_READ_ONLY_STENCIL;
		}

		return answer;
	}

	constexpr D3D12_SHADER_COMPONENT_MAPPING ToShaderMapping(const ComponentSwizzle swizzle) noexcept
	{
		switch (swizzle)
		{
		case ComponentSwizzle::Red:
			return D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_0;
		case ComponentSwizzle::Green:
			return D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_1;
		case ComponentSwizzle::Blue:
			return D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_2;
		case ComponentSwizzle::Alpha:
			return D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_3;
		case ComponentSwizzle::Zero:
			return D3D12_SHADER_COMPONENT_MAPPING_FORCE_VALUE_0;
		case ComponentSwizzle::One:
			return D3D12_SHADER_COMPONENT_MAPPING_FORCE_VALUE_1;
		default: [[unlikely]]
			assert(false && "Invalid swizzle.");
			return D3D12_SHADER_COMPONENT_MAPPING_FORCE_VALUE_0;
		}
	}

	constexpr UINT ToShaderMapping(const ComponentMapping mapping) noexcept
	{
		return D3D12_ENCODE_SHADER_4_COMPONENT_MAPPING(
			ToShaderMapping(mapping.red),
			ToShaderMapping(mapping.green),
			ToShaderMapping(mapping.blue),
			ToShaderMapping(mapping.alpha)
		);
	}

	constexpr D3D12_RESOLVE_MODE ToResolveMode(const ResolveMode mode) noexcept
	{
		switch (mode)
		{
		case ResolveMode::Average:
			return D3D12_RESOLVE_MODE_AVERAGE;
		case ResolveMode::Minimum:
			return D3D12_RESOLVE_MODE_MIN;
		case ResolveMode::Maximum:
			return D3D12_RESOLVE_MODE_MAX;
		default: [[unlikely]]
			assert(false && "Invalid resolve mode.");
			return D3D12_RESOLVE_MODE_AVERAGE;
		}
	}
}

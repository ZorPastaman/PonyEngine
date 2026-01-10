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
#include "PonyEngine/Render/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Engine;

import std;

import PonyEngine.Memory;
import PonyEngine.Meta;
import PonyEngine.RenderDevice.Ext;

import :DXGIFactory;
import :DXGITextureFormatMap;
import :D3D12Buffer;
import :D3D12ComputeCommandQueue;
import :D3D12CopyCommandQueue;
import :D3D12Device;
import :D3D12GraphicsCommandQueue;
import :D3D12Texture;
import :D3D12Utility;
import :EngineUtility;

export namespace PonyEngine::Render::Windows
{
	class D3D12Engine final
	{
	public:
		static constexpr std::string_view ApiName = D3D12Device::ApiName;
		static constexpr auto ApiVersion = D3D12Device::ApiVersion;

		[[nodiscard("Pure constructor")]]
		explicit D3D12Engine(IRenderDeviceContext& renderDevice);
		D3D12Engine(const D3D12Engine&) = delete;
		D3D12Engine(D3D12Engine&&) = delete;

		~D3D12Engine() noexcept = default;

		[[nodiscard("Pure function")]]
		std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferCreateInfo& createInfo);

		[[nodiscard("Pure function")]]
		TextureFormatFeature TextureFormatFeatures(TextureFormatId textureFormatId) const;
		[[nodiscard("Pure function")]]
		TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureCreateInfo& createInfo);

		[[nodiscard("Pure function")]]
		IGraphicsCommandQueue& GraphicsCommandQueue() noexcept;
		[[nodiscard("Pure function")]]
		IComputeCommandQueue& ComputeCommandQueue() noexcept;
		[[nodiscard("Pure function")]]
		ICopyCommandQueue& CopyCommandQueue() noexcept;

		D3D12Engine& operator =(const D3D12Engine&) = delete;
		D3D12Engine& operator =(D3D12Engine&&) = delete;

	private:
		IRenderDeviceContext* renderDevice;

		Memory::Arena arena;

		DXGITextureFormatMap textureFormatMap;

		DXGIFactory factory;
		D3D12Device device;

		D3D12GraphicsCommandQueue graphicsCommandQueue;
		D3D12ComputeCommandQueue computeCommandQueue;
		D3D12CopyCommandQueue copyCommandQueue;
	};
}

namespace PonyEngine::Render::Windows
{
	D3D12Engine::D3D12Engine(IRenderDeviceContext& renderDevice) :
		renderDevice{&renderDevice},
		arena(64uz, 64uz),
		textureFormatMap(*this->renderDevice),
		factory(*this->renderDevice),
		device(*this->renderDevice),
		graphicsCommandQueue(*this->renderDevice, device.Device(), D3D12_COMMAND_QUEUE_PRIORITY_HIGH),
		computeCommandQueue(*this->renderDevice, device.Device(), D3D12_COMMAND_QUEUE_PRIORITY_HIGH),
		copyCommandQueue(*this->renderDevice, device.Device(), D3D12_COMMAND_QUEUE_PRIORITY_HIGH)
	{
	}

	std::shared_ptr<IBuffer> D3D12Engine::CreateBuffer(const HeapType heapType, const BufferCreateInfo& createInfo)
	{
		const D3D12_HEAP_PROPERTIES heapProperties = ToHeapProperties(heapType);
		const D3D12_HEAP_FLAGS heapFlags = ToHeapFlags(createInfo.usage);
		const D3D12_RESOURCE_DESC1 resourceDesc = ToResourceDesc(createInfo);
		Platform::Windows::ComPtr<ID3D12Resource2> resource = device.CreateResource(heapProperties, heapFlags, resourceDesc);

		return std::make_shared<D3D12Buffer>(std::move(resource), createInfo.size, createInfo.usage);
	}

	TextureFormatFeature D3D12Engine::TextureFormatFeatures(const TextureFormatId textureFormatId) const
	{
		if (const std::size_t index = textureFormatMap.IndexOf(textureFormatId); index < textureFormatMap.Size())
		{
			const DXGI_FORMAT format = textureFormatMap.DXGIFormat(index);
			const D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport = device.GetFormatSupport(format);

			return ToTextureFormatFeature(formatSupport);
		}

		return TextureFormatFeature::None;
	}

	TextureSupportResponse D3D12Engine::TextureSupport(const TextureSupportRequest& request) const
	{
		const auto getSampleCountMask = [&](const DXGI_FORMAT format, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& formatSupport)
		{
			if ((request.dimension != TextureDimension::Texture2D && request.dimension != TextureDimension::TextureCube) ||
				Any(TextureUsage::UnorderedAccess, request.usage) || (formatSupport.Support1 & D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET) == D3D12_FORMAT_SUPPORT1_NONE)
			{
				return SampleCountMask::X1;
			}

			auto mask = SampleCountMask::None;
			for (UINT i = 1u; i <= std::min(ToNumber(SampleCount::Max), std::uint8_t{ D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT }); i <<= 1u)
			{
				if (device.GetSampleQualityCount(format, i) > 0u)
				{
					mask |= static_cast<SampleCountMask>(i);
				}
			}

			return mask;
		};

		if (!IsValidUsage(request.usage))
		{
			return TextureSupportResponse{};
		}

		if (const std::size_t index = textureFormatMap.IndexOf(request.format); index < textureFormatMap.Size())
		{
			const DXGI_FORMAT format = textureFormatMap.DXGIFormat(index);
			const D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport = device.GetFormatSupport(format);

			if (IsDepthStencilFormat(format))
			{
				if (!CheckDepthSupport(request, formatSupport))
				{
					return TextureSupportResponse{};
				}
			}
			else
			{
				if (!CheckColorSupport(request, formatSupport))
				{
					return TextureSupportResponse{};
				}
			}

			auto response = TextureSupportResponse{ .supported = true };

			switch (request.dimension)
			{
			case TextureDimension::Texture1D:
				response.maxSize = Math::Vector3<std::uint32_t>(D3D12_REQ_TEXTURE1D_U_DIMENSION, 1u, 1u);
				response.maxArraySize = D3D12_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION;
				response.sampleCounts = getSampleCountMask(format, formatSupport);
				break;
			case TextureDimension::Texture2D:
				response.maxSize = Math::Vector3<std::uint32_t>(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION, D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION, 1u);
				response.maxArraySize = D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION;
				response.sampleCounts = getSampleCountMask(format, formatSupport);
				break;
			case TextureDimension::Texture3D:
				response.maxSize = Math::Vector3<std::uint32_t>(D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION, D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION, D3D12_REQ_TEXTURE3D_U_V_OR_W_DIMENSION);
				response.maxArraySize = 1u;
				response.sampleCounts = getSampleCountMask(format, formatSupport);
				break;
			case TextureDimension::TextureCube:
				response.maxSize = Math::Vector3<std::uint32_t>(D3D12_REQ_TEXTURECUBE_DIMENSION, D3D12_REQ_TEXTURECUBE_DIMENSION, 1u);
				response.maxArraySize = D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION / 6;
				response.sampleCounts = getSampleCountMask(format, formatSupport);
				break;
			default:
				break;
			}

			return response;
		}

		return TextureSupportResponse{};
	}

	std::shared_ptr<ITexture> D3D12Engine::CreateTexture(const HeapType heapType, const TextureCreateInfo& createInfo)
	{
		switch (createInfo.dimension)
		{
		case TextureDimension::Texture1D:
			if (createInfo.size.Y() != 1u || createInfo.size.Z() != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid size");
			}
			break;
		case TextureDimension::Texture2D:
			if (createInfo.size.Z() != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid size");
			}
			break;
		case TextureDimension::Texture3D:
			if (createInfo.arraySize != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid array size");
			}
			break;
		case TextureDimension::TextureCube:
			if (createInfo.size.Z() != 1u) [[unlikely]]
			{
				throw std::invalid_argument("Invalid size");
			}
			if (createInfo.arraySize > D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION / 6) [[unlikely]]
			{
				throw std::invalid_argument("Invalid array size");
			}
			break;
		}

		const std::size_t formatIndex = textureFormatMap.IndexOf(createInfo.format);
		if (formatIndex >= textureFormatMap.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid texture format");
		}
		const DXGI_FORMAT format = textureFormatMap.DXGIFormat(formatIndex);

		arena.Free();
		auto castableFormats = Memory::Arena::Slice<DXGI_FORMAT>{};
		if (IsDepthStencilFormat(format))
		{
			if (createInfo.castableFormats.size() > 0uz) [[unlikely]]
			{
				throw std::invalid_argument("Invalid castable texture format");
			}

			if (Any(TextureUsage::ShaderResource, createInfo.usage))
			{
				const DXGI_FORMAT depthFormat = GetDepthViewFormat(format);
				const DXGI_FORMAT stencilFormat = GetStencilViewFormat(format);
				castableFormats = arena.Allocate<DXGI_FORMAT>(1uz + (stencilFormat != DXGI_FORMAT_UNKNOWN));
				const std::span<DXGI_FORMAT> formats = arena.Span(castableFormats);
				formats[stencilFormat != DXGI_FORMAT_UNKNOWN] = stencilFormat;
				formats[0] = depthFormat;
			}
		}
		else
		{
			castableFormats = arena.Allocate<DXGI_FORMAT>(createInfo.castableFormats.size());
			const std::span<DXGI_FORMAT> formats = arena.Span(castableFormats);
			for (std::size_t i = 0uz; i < formats.size(); ++i)
			{
				const std::size_t castableFormatIndex = textureFormatMap.IndexOf(createInfo.castableFormats[i]);
				if (castableFormatIndex >= textureFormatMap.Size()) [[unlikely]]
				{
					throw std::invalid_argument("Invalid texture format");
				}

				formats[i] = textureFormatMap.DXGIFormat(castableFormatIndex);
			}
		}

		const D3D12_HEAP_PROPERTIES heapProperties = ToHeapProperties(heapType);
		const D3D12_HEAP_FLAGS heapFlags = ToHeapFlags(createInfo.usage);
		const D3D12_RESOURCE_DESC1 resourceDesc = ToResourceDesc(createInfo, format);
		const D3D12_BARRIER_LAYOUT initialLayout = ToLayout(createInfo.initialLayout);
		const D3D12_CLEAR_VALUE clearValue = ToClearValue(createInfo.clearValue, format);
		Platform::Windows::ComPtr<ID3D12Resource2> resource = device.CreateResource(heapProperties, heapFlags,
			resourceDesc, initialLayout, clearValue, arena.Span(castableFormats));

		return std::make_shared<D3D12Texture>(std::move(resource), createInfo.format, createInfo.castableFormats, 
			createInfo.size, createInfo.mipCount, createInfo.arraySize, createInfo.dimension, createInfo.sampleCount, createInfo.usage);
	}

	IGraphicsCommandQueue& D3D12Engine::GraphicsCommandQueue() noexcept
	{
		return graphicsCommandQueue;
	}

	IComputeCommandQueue& D3D12Engine::ComputeCommandQueue() noexcept
	{
		return computeCommandQueue;
	}

	ICopyCommandQueue& D3D12Engine::CopyCommandQueue() noexcept
	{
		return copyCommandQueue;
	}
}

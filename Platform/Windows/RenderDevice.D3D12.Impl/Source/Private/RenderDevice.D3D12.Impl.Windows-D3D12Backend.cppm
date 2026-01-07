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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Backend;

import std;

import PonyEngine.RenderDevice.Ext;

import :DXGIFactory;
import :DXGITextureFormatMap;
import :D3D12Device;
import :D3D12Utility;
import :EngineUtility;

export namespace PonyEngine::Render::Windows
{
	class D3D12Backend final : public IBackend
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit D3D12Backend(IRenderDeviceContext& renderDevice);
		D3D12Backend(const D3D12Backend&) = delete;
		D3D12Backend(D3D12Backend&&) = delete;

		~D3D12Backend() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::string_view RenderApiName() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Meta::Version RenderApiVersion() const noexcept override;

		virtual void Activate() override;
		virtual void Deactivate() override;

		[[nodiscard("Pure function")]] 
		virtual TextureFormatFeature TextureFormatFeatures(TextureFormatId textureFormatId) const override;
		[[nodiscard("Pure function")]] 
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const override;

		D3D12Backend& operator =(const D3D12Backend&) = delete;
		D3D12Backend& operator =(D3D12Backend&&) = delete;

	private:
		IRenderDeviceContext* renderDevice;

		DXGITextureFormatMap textureFormatMap;

		std::unique_ptr<DXGIFactory> factory;
		std::unique_ptr<D3D12Device> device;
	};
}

namespace PonyEngine::Render::Windows
{
	D3D12Backend::D3D12Backend(IRenderDeviceContext& renderDevice) :
		renderDevice{&renderDevice},
		textureFormatMap(*this->renderDevice)
	{
	}

	std::string_view D3D12Backend::RenderApiName() const noexcept
	{
		return D3D12Device::ApiName;
	}

	Meta::Version D3D12Backend::RenderApiVersion() const noexcept
	{
		return D3D12Device::ApiVersion;
	}

	void D3D12Backend::Activate()
	{
		factory = std::make_unique<DXGIFactory>(*renderDevice);
		device = std::make_unique<D3D12Device>(*renderDevice);
	}

	void D3D12Backend::Deactivate()
	{
		device.reset();
		factory.reset();
	}

	TextureFormatFeature D3D12Backend::TextureFormatFeatures(const TextureFormatId textureFormatId) const
	{
		if (const std::size_t index = textureFormatMap.IndexOf(textureFormatId); index < textureFormatMap.Size())
		{
			const DXGI_FORMAT format = textureFormatMap.DXGIFormat(index);
			const D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport = device->GetFormatSupport(format);

			return FormatSupportToTextureFormatFeature(formatSupport);
		}

		return TextureFormatFeature::None;
	}

	TextureSupportResponse D3D12Backend::TextureSupport(const TextureSupportRequest& request) const
	{
		const auto getSampleCountMask = [&](const DXGI_FORMAT format, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& formatSupport)
		{
			if ((request.dimension != TextureDimension::Texture2D && request.dimension != TextureDimension::TextureCube) ||
				Any(TextureUsage::UnorderedAccess, request.usage) || (formatSupport.Support1 & D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET) == D3D12_FORMAT_SUPPORT1_NONE)
			{
				return SampleCountMask::X1;
			}

			auto mask = SampleCountMask::None;
			for (UINT i = 1u; i <= std::min(ToNumber(SampleCount::Max), std::uint8_t{D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT}); i <<= 1u)
			{
				if (device->GetSampleQualityCount(format, i) > 0u)
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
			const D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport = device->GetFormatSupport(format);

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

			auto response = TextureSupportResponse{.supported = true};

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
}

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

export module PonyEngine.Render.Direct3D12.Detail:DepthStencil;

import <memory>;
import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;

import PonyBase.Utility;

import PonyMath.Utility;

import PonyDebug.Log;

import :DescriptorHeap;
import :ObjectUtility;
import :RenderTargetParams;
import :IDepthStencilPrivate;
import :IDescriptorHeapManager;
import :ISubSystemContext;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 depth stencil.
	class DepthStencil final : public IDepthStencilPrivate
	{
	public:
		/// @brief Creates a @p DepthStencil.
		/// @param d3d12System Direct3D12 system context.
		[[nodiscard("Pure constructor")]]
		explicit DepthStencil(ISubSystemContext& d3d12System);
		[[nodiscard("Pure constructor")]]
		DepthStencil(const DepthStencil& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		DepthStencil(DepthStencil&& other) noexcept = default;

		~DepthStencil() noexcept;

		[[nodiscard("Pure function")]]
		virtual DXGI_FORMAT DsvFormat() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ID3D12Resource2& DepthStencilTexture() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ID3D12Resource2& DepthStencilTexture() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual D3D12_CPU_DESCRIPTOR_HANDLE DsvHandle() const noexcept override;

		/// @brief Sets the name to the depth stencil components.
		/// @param name Name.
		void Name(std::string_view name);

		DepthStencil& operator =(const DepthStencil& other) noexcept = default;
		DepthStencil& operator =(DepthStencil&& other) noexcept = default;

	private:
		static constexpr DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT; ///< Depth stencil format.

		ISubSystemContext* d3d12System; ///< Render system context.

		std::shared_ptr<Texture> depthStencilTexture; ///< Depth stencil buffer.
		std::shared_ptr<DescriptorHeap> dsvHeap; ///< Depth stencil view heap.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	DepthStencil::DepthStencil(ISubSystemContext& d3d12System) :
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire depth stencil buffer.");
		const IRenderTargetPrivate& renderTarget = this->d3d12System->RenderTargetPrivate();
		const PonyMath::Utility::Resolution<UINT>& resolution = renderTarget.ResolutionD3D12();
		const DXGI_SAMPLE_DESC sampleDesc = renderTarget.SampleDesc();
		depthStencilTexture = this->d3d12System->ResourceManager().CreateDepthStencil(resolution.Width(), resolution.Height(), DepthStencilFormat, sampleDesc, D3D12_DEPTH_STENCIL_VALUE{.Depth = D3D12_MAX_DEPTH, .Stencil = 0u});
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil buffer acquired.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create dsv descriptor heap.");
		dsvHeap = this->d3d12System->DescriptorHeapManager().CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1u, false);
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Dsv descriptor heap created.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create depth stencil handle.");
		const auto dsvDesc = D3D12_DEPTH_STENCIL_VIEW_DESC
		{
			.Format = DepthStencilFormat,
			.ViewDimension = sampleDesc.Count > 1u ? D3D12_DSV_DIMENSION_TEXTURE2DMS : D3D12_DSV_DIMENSION_TEXTURE2D,
			.Flags = D3D12_DSV_FLAG_NONE
		};
		this->d3d12System->Device().CreateDepthStencilView(&depthStencilTexture->Data(), &dsvDesc, dsvHeap->CpuHandle(0u));
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil handle created.");
	}

	DepthStencil::~DepthStencil() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy dsv descriptor heap.");
		dsvHeap.reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Dsv descriptor heap destroyed.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release depth stencil buffer.");
		depthStencilTexture.reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Depth stencil buffer released.");
	}

	DXGI_FORMAT DepthStencil::DsvFormat() const noexcept
	{
		return DepthStencilFormat;
	}

	ID3D12Resource2& DepthStencil::DepthStencilTexture() noexcept
	{
		return depthStencilTexture->Data();
	}

	const ID3D12Resource2& DepthStencil::DepthStencilTexture() const noexcept
	{
		return depthStencilTexture->Data();
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencil::DsvHandle() const noexcept
	{
		return dsvHeap->CpuHandle(0u);
	}

	void DepthStencil::Name(const std::string_view name)
	{
		constexpr std::string_view bufferName = " - Buffer";
		constexpr std::string_view heapName = " - ViewHeap";

		auto componentName = std::string();
		componentName.reserve(name.size() + heapName.size());

		componentName.append(name).append(bufferName);
		SetName(depthStencilTexture->Data(), componentName);

		componentName.erase();
		componentName.append(name).append(heapName);
		SetName(dsvHeap->Heap(), componentName);
	}
}

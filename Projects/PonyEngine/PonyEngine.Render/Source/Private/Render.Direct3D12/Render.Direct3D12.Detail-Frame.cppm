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

export module PonyEngine.Render.Direct3D12.Detail:Frame;

import <memory>;

import :DescriptorHeap;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	class Frame final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Frame(const std::shared_ptr<Texture>& renderTarget, const std::shared_ptr<Texture>& resolveTarget, const std::shared_ptr<Texture>& depthStencil,
			const std::shared_ptr<DescriptorHeap>& renderTargetHeap, const std::shared_ptr<DescriptorHeap>& renderTargetShaderHeap, const std::shared_ptr<DescriptorHeap>& depthStencilHeap) noexcept;
		Frame(const Frame&) = delete;
		Frame(Frame&&) = delete;

		~Frame() noexcept = default;

		[[nodiscard("Pure function")]]
		Texture& RenderTarget() noexcept;
		[[nodiscard("Pure function")]]
		const Texture& RenderTarget() const noexcept;

		[[nodiscard("Pure function")]]
		Texture* ResolveTarget() noexcept;
		[[nodiscard("Pure function")]]
		const Texture* ResolveTarget() const noexcept;

		[[nodiscard("Pure function")]]
		Texture& DepthStencil() noexcept;
		[[nodiscard("Pure function")]]
		const Texture& DepthStencil() const noexcept;

		[[nodiscard("Pure function")]]
		DescriptorHeap& RenderTargetShaderHeap() noexcept;
		[[nodiscard("Pure function")]]
		const DescriptorHeap& RenderTargetShaderHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetHandle() const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE RenderTargetShaderHandle() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilHandle() const noexcept;

		Frame& operator =(const Frame&) = delete;
		Frame& operator =(Frame&&) = delete;

	private:
		std::shared_ptr<Texture> renderTarget;
		std::shared_ptr<Texture> resolveTarget;
		std::shared_ptr<Texture> depthStencil;

		std::shared_ptr<DescriptorHeap> renderTargetHeap;
		std::shared_ptr<DescriptorHeap> renderTargetShaderHeap;
		std::shared_ptr<DescriptorHeap> depthStencilHeap;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Frame::Frame(const std::shared_ptr<Texture>& renderTarget, const std::shared_ptr<Texture>& resolveTarget, const std::shared_ptr<Texture>& depthStencil, const std::shared_ptr<DescriptorHeap>& renderTargetHeap,
		const std::shared_ptr<DescriptorHeap>& renderTargetShaderHeap, const std::shared_ptr<DescriptorHeap>& depthStencilHeap) noexcept :
		renderTarget(renderTarget),
		resolveTarget(resolveTarget),
		depthStencil(depthStencil),
		renderTargetHeap(renderTargetHeap),
		renderTargetShaderHeap(renderTargetShaderHeap),
		depthStencilHeap(depthStencilHeap)
	{
	}

	Texture& Frame::RenderTarget() noexcept
	{
		return *renderTarget;
	}

	const Texture& Frame::RenderTarget() const noexcept
	{
		return *renderTarget;
	}

	Texture* Frame::ResolveTarget() noexcept
	{
		return resolveTarget.get();
	}

	const Texture* Frame::ResolveTarget() const noexcept
	{
		return resolveTarget.get();
	}

	Texture& Frame::DepthStencil() noexcept
	{
		return *depthStencil;
	}

	const Texture& Frame::DepthStencil() const noexcept
	{
		return *depthStencil;
	}

	DescriptorHeap& Frame::RenderTargetShaderHeap() noexcept
	{
		return *renderTargetShaderHeap;
	}

	const DescriptorHeap& Frame::RenderTargetShaderHeap() const noexcept
	{
		return *renderTargetShaderHeap;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Frame::RenderTargetHandle() const noexcept
	{
		return renderTargetHeap->CpuHandle(0u);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE Frame::RenderTargetShaderHandle() const noexcept
	{
		return renderTargetShaderHeap->GpuHandle(0u);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Frame::DepthStencilHandle() const noexcept
	{
		return depthStencilHeap->CpuHandle(0u);
	}
}

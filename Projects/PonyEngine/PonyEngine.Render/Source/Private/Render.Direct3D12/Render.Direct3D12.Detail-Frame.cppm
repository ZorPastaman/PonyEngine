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
			const std::shared_ptr<DescriptorHeap>& rtvHeap, const std::shared_ptr<DescriptorHeap>& srvHeap, const std::shared_ptr<DescriptorHeap>& dsvHeap) noexcept;
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
		Texture& FinalTarget() noexcept;
		[[nodiscard("Pure function")]]
		const Texture& FinalTarget() const noexcept;

		[[nodiscard("Pure function")]]
		Texture& DepthStencil() noexcept;
		[[nodiscard("Pure function")]]
		const Texture& DepthStencil() const noexcept;

		[[nodiscard("Pure function")]]
		DescriptorHeap& SrvHeap() noexcept;
		[[nodiscard("Pure function")]]
		const DescriptorHeap& SrvHeap() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE RtvHandle() const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_GPU_DESCRIPTOR_HANDLE SrvHandle() const noexcept;

		[[nodiscard("Pure function")]]
		D3D12_CPU_DESCRIPTOR_HANDLE DsvHandle() const noexcept;

		void Name(std::string_view name);

		Frame& operator =(const Frame&) = delete;
		Frame& operator =(Frame&&) = delete;

	private:
		std::shared_ptr<Texture> renderTarget;
		std::shared_ptr<Texture> resolveTarget;
		std::shared_ptr<Texture> depthStencil;

		std::shared_ptr<DescriptorHeap> rtvHeap;
		std::shared_ptr<DescriptorHeap> srvHeap;
		std::shared_ptr<DescriptorHeap> dsvHeap;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Frame::Frame(const std::shared_ptr<Texture>& renderTarget, const std::shared_ptr<Texture>& resolveTarget, const std::shared_ptr<Texture>& depthStencil, const std::shared_ptr<DescriptorHeap>& rtvHeap,
		const std::shared_ptr<DescriptorHeap>& srvHeap, const std::shared_ptr<DescriptorHeap>& dsvHeap) noexcept :
		renderTarget(renderTarget),
		resolveTarget(resolveTarget),
		depthStencil(depthStencil),
		rtvHeap(rtvHeap),
		srvHeap(srvHeap),
		dsvHeap(dsvHeap)
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

	Texture& Frame::FinalTarget() noexcept
	{
		return resolveTarget ? *resolveTarget : *renderTarget;
	}

	const Texture& Frame::FinalTarget() const noexcept
	{
		return resolveTarget ? *resolveTarget : *renderTarget;
	}

	Texture& Frame::DepthStencil() noexcept
	{
		return *depthStencil;
	}

	const Texture& Frame::DepthStencil() const noexcept
	{
		return *depthStencil;
	}

	DescriptorHeap& Frame::SrvHeap() noexcept
	{
		return *srvHeap;
	}

	const DescriptorHeap& Frame::SrvHeap() const noexcept
	{
		return *srvHeap;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Frame::RtvHandle() const noexcept
	{
		return rtvHeap->CpuHandle(0u);
	}

	D3D12_GPU_DESCRIPTOR_HANDLE Frame::SrvHandle() const noexcept
	{
		return srvHeap->GpuHandle(0u);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE Frame::DsvHandle() const noexcept
	{
		return dsvHeap->CpuHandle(0u);
	}

	void Frame::Name(const std::string_view name)
	{
		constexpr std::string_view rtvName = "-RTV";
		constexpr std::string_view resolveName = "-Resolve";
		constexpr std::string_view srvName = "-SRV";
		constexpr std::string_view dsvName = "-DSV";

		auto componentName = std::string();
		componentName.reserve(name.size() + resolveName.size());

		componentName.append(name).append(rtvName);
		renderTarget->Name(componentName);
		rtvHeap->Name(componentName);

		componentName.erase();
		componentName.append(name).append(srvName);
		srvHeap->Name(componentName);

		componentName.erase();
		componentName.append(name).append(dsvName);
		depthStencil->Name(componentName);
		dsvHeap->Name(componentName);

		if (resolveTarget)
		{
			componentName.erase();
			componentName.append(name).append(resolveName);
			resolveTarget->Name(componentName);
		}
	}
}

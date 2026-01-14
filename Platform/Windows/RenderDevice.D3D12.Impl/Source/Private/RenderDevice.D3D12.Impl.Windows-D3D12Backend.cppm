/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Backend;

import std;

import PonyEngine.Meta;
import PonyEngine.RenderDevice.Ext;

import :D3D12Engine;

export namespace PonyEngine::Render::Windows
{
	class D3D12Backend final : public IBackend
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit D3D12Backend(IRenderDeviceContext& renderDevice) noexcept;
		D3D12Backend(const D3D12Backend&) = delete;
		D3D12Backend(D3D12Backend&&) = delete;

		~D3D12Backend() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::string_view RenderApiName() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Meta::Version RenderApiVersion() const noexcept override;

		virtual void Activate() override;
		virtual void Deactivate() override;

		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferParams& params) override;

		[[nodiscard("Pure function")]] 
		virtual TextureFormatFeature TextureFormatFeatures(TextureFormatId textureFormatId) const override;
		[[nodiscard("Pure function")]] 
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const override;
		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params) override;

		[[nodiscard("Pure function")]] 
		virtual IGraphicsCommandQueue& GraphicsCommandQueue() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const IGraphicsCommandQueue& GraphicsCommandQueue() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual IComputeCommandQueue& ComputeCommandQueue() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const IComputeCommandQueue& ComputeCommandQueue() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual ICopyCommandQueue& CopyCommandQueue() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const ICopyCommandQueue& CopyCommandQueue() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual struct SwapChainSupport SwapChainSupport() const override;
		[[nodiscard("Pure function")]]
		virtual bool IsSwapChainAlive() const override;
		[[nodiscard("Pure function")]] 
		virtual void CreateSwapChain(const SwapChainParams& params) override;
		virtual void DestroySwapChain() override;
		[[nodiscard("Pure function")]] 
		virtual std::uint8_t SwapChainBufferCount() const override;
		[[nodiscard("Pure function")]] 
		virtual std::uint8_t CurrentSwapChainBufferIndex() const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<ITexture> SwapChainBuffer(std::uint8_t bufferIndex) const override;
		virtual void PresentNextSwapChainBuffer() override;

		D3D12Backend& operator =(const D3D12Backend&) = delete;
		D3D12Backend& operator =(D3D12Backend&&) = delete;

	private:
		IRenderDeviceContext* renderDevice;

		std::unique_ptr<D3D12Engine> engine;
	};
}

namespace PonyEngine::Render::Windows
{
	D3D12Backend::D3D12Backend(IRenderDeviceContext& renderDevice) noexcept :
		renderDevice{&renderDevice}
	{
	}

	std::string_view D3D12Backend::RenderApiName() const noexcept
	{
		return D3D12Engine::ApiName;
	}

	Meta::Version D3D12Backend::RenderApiVersion() const noexcept
	{
		return D3D12Engine::ApiVersion;
	}

	void D3D12Backend::Activate()
	{
		engine = std::make_unique<D3D12Engine>(*renderDevice);
	}

	void D3D12Backend::Deactivate()
	{
		engine.reset();
	}

	std::shared_ptr<IBuffer> D3D12Backend::CreateBuffer(const HeapType heapType, const BufferParams& params)
	{
		return engine->CreateBuffer(heapType, params);
	}

	TextureFormatFeature D3D12Backend::TextureFormatFeatures(const TextureFormatId textureFormatId) const
	{
		return engine->TextureFormatFeatures(textureFormatId);
	}

	TextureSupportResponse D3D12Backend::TextureSupport(const TextureSupportRequest& request) const
	{
		return engine->TextureSupport(request);
	}

	std::shared_ptr<ITexture> D3D12Backend::CreateTexture(const HeapType heapType, const TextureParams& params)
	{
		return engine->CreateTexture(heapType, params);
	}

	IGraphicsCommandQueue& D3D12Backend::GraphicsCommandQueue() noexcept
	{
		return engine->GraphicsCommandQueue();
	}

	const IGraphicsCommandQueue& D3D12Backend::GraphicsCommandQueue() const noexcept
	{
		return engine->GraphicsCommandQueue();
	}

	IComputeCommandQueue& D3D12Backend::ComputeCommandQueue() noexcept
	{
		return engine->ComputeCommandQueue();
	}

	const IComputeCommandQueue& D3D12Backend::ComputeCommandQueue() const noexcept
	{
		return engine->ComputeCommandQueue();
	}

	ICopyCommandQueue& D3D12Backend::CopyCommandQueue() noexcept
	{
		return engine->CopyCommandQueue();
	}

	const ICopyCommandQueue& D3D12Backend::CopyCommandQueue() const noexcept
	{
		return engine->CopyCommandQueue();
	}

	struct SwapChainSupport D3D12Backend::SwapChainSupport() const
	{
		return engine->SwapChainSupport();
	}

	bool D3D12Backend::IsSwapChainAlive() const
	{
		return engine->IsSwapChainAlive();
	}

	void D3D12Backend::CreateSwapChain(const SwapChainParams& params)
	{
		engine->CreateSwapChain(params);
	}

	void D3D12Backend::DestroySwapChain()
	{
		engine->DestroySwapChain();
	}

	std::uint8_t D3D12Backend::SwapChainBufferCount() const
	{
		return engine->SwapChainBufferCount();
	}

	std::uint8_t D3D12Backend::CurrentSwapChainBufferIndex() const
	{
		return engine->CurrentSwapChainBufferIndex();
	}

	std::shared_ptr<ITexture> D3D12Backend::SwapChainBuffer(const std::uint8_t bufferIndex) const
	{
		return engine->SwapChainBuffer(bufferIndex);
	}

	void D3D12Backend::PresentNextSwapChainBuffer()
	{
		engine->PresentNextSwapChainBuffer();
	}
}

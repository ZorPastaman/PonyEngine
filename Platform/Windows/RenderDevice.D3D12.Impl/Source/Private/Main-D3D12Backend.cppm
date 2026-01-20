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

export namespace PonyEngine::RenderDevice::Windows
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

		[[nodiscard("Pure function")]] 
		virtual HeapTypeMask BufferHeapTypeSupport() const override;
		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferParams& params) override;

		[[nodiscard("Pure function")]] 
		virtual struct TextureFormatSupport TextureFormatSupport(TextureFormatId textureFormatId) const override;
		[[nodiscard("Pure function")]] 
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const override;
		[[nodiscard("Pure function")]] 
		virtual HeapTypeMask TextureHeapTypeSupport() const override;
		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params) override;

		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<IGraphicsCommandList> CreateGraphicsCommandList() override;
		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<IComputeCommandList> CreateComputeCommandList() override;
		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<ICopyCommandList> CreateCopyCommandList() override;
		virtual void Execute(std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync) override;
		virtual void Execute(std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync) override;
		virtual void Execute(std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync) override;

		[[nodiscard("Pure function")]] 
		virtual std::uint32_t GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const override;
		[[nodiscard("Pure function")]] 
		virtual std::uint32_t GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const override;
		virtual std::pair<std::uint64_t, std::uint64_t> GetCopyableFootprints(const TextureParams& params, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const override;
		virtual std::pair<std::uint64_t, std::uint64_t> GetCopyableFootprints(const ITexture& texture, std::uint64_t offset, const SubTextureRange& range,
			std::span<CopyableFootprint> footprints) const override;

		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<IFence> CreateFence() override;
		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<IWaiter> CreateWaiter() override;

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

namespace PonyEngine::RenderDevice::Windows
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

	HeapTypeMask D3D12Backend::BufferHeapTypeSupport() const
	{
		return engine->BufferHeapTypeSupport();
	}

	std::shared_ptr<IBuffer> D3D12Backend::CreateBuffer(const HeapType heapType, const BufferParams& params)
	{
		return engine->CreateBuffer(heapType, params);
	}

	struct TextureFormatSupport D3D12Backend::TextureFormatSupport(const TextureFormatId textureFormatId) const
	{
		return engine->TextureFormatSupport(textureFormatId);
	}

	TextureSupportResponse D3D12Backend::TextureSupport(const TextureSupportRequest& request) const
	{
		return engine->TextureSupport(request);
	}

	HeapTypeMask D3D12Backend::TextureHeapTypeSupport() const
	{
		return engine->TextureHeapTypeSupport();
	}

	std::shared_ptr<ITexture> D3D12Backend::CreateTexture(const HeapType heapType, const TextureParams& params)
	{
		return engine->CreateTexture(heapType, params);
	}

	std::shared_ptr<IGraphicsCommandList> D3D12Backend::CreateGraphicsCommandList()
	{
		return engine->CreateGraphicsCommandList();
	}

	std::shared_ptr<IComputeCommandList> D3D12Backend::CreateComputeCommandList()
	{
		return engine->CreateComputeCommandList();
	}

	std::shared_ptr<ICopyCommandList> D3D12Backend::CreateCopyCommandList()
	{
		return engine->CreateCopyCommandList();
	}

	void D3D12Backend::Execute(const std::span<const IGraphicsCommandList* const> commandLists, const QueueSync& sync)
	{
		engine->Execute(commandLists, sync);
	}

	void D3D12Backend::Execute(const std::span<const IComputeCommandList* const> commandLists, const QueueSync& sync)
	{
		engine->Execute(commandLists, sync);
	}

	void D3D12Backend::Execute(const std::span<const ICopyCommandList* const> commandLists, const QueueSync& sync)
	{
		engine->Execute(commandLists, sync);
	}

	std::uint32_t D3D12Backend::GetCopyableFootprintCount(const TextureParams& params, const SubTextureRange& range) const
	{
		return engine->GetCopyableFootprintCount(params, range);
	}

	std::uint32_t D3D12Backend::GetCopyableFootprintCount(const ITexture& texture, const SubTextureRange& range) const
	{
		return engine->GetCopyableFootprintCount(texture, range);
	}

	std::pair<std::uint64_t, std::uint64_t> D3D12Backend::GetCopyableFootprints(const TextureParams& params, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		return engine->GetCopyableFootprints(params, offset, range, footprints);
	}

	std::pair<std::uint64_t, std::uint64_t> D3D12Backend::GetCopyableFootprints(const ITexture& texture, const std::uint64_t offset, const SubTextureRange& range,
		const std::span<CopyableFootprint> footprints) const
	{
		return engine->GetCopyableFootprints(texture, offset, range, footprints);
	}

	std::shared_ptr<IFence> D3D12Backend::CreateFence()
	{
		return engine->CreateFence();
	}

	std::shared_ptr<IWaiter> D3D12Backend::CreateWaiter()
	{
		return engine->CreateWaiter();
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

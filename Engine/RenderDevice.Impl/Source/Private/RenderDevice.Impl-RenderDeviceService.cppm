/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.RenderDevice.Impl:RenderDeviceService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.Meta;
import PonyEngine.RenderDevice.Ext;

import :BackendContainer;

export namespace PonyEngine::Render
{
	class RenderDeviceService final : public Application::IService, public IRenderDeviceModuleContext, private IRenderDeviceService, private IRenderDeviceContext
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit RenderDeviceService(Application::IApplicationContext& application) noexcept;
		RenderDeviceService(const RenderDeviceService&) = delete;
		RenderDeviceService(RenderDeviceService&&) = delete;

		~RenderDeviceService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void AddInterfaces(Application::IServiceInterfaceAdder& adder) override;

		[[nodiscard("Must be used to remove")]]
		virtual BackendHandle AddBackend(const std::function<std::shared_ptr<IBackend>(IRenderDeviceContext&)>& factory) override;
		virtual void RemoveBackend(BackendHandle backendHandle) override;

		RenderDeviceService& operator =(const RenderDeviceService&) = delete;
		RenderDeviceService& operator =(RenderDeviceService&&) = delete;

	private:
		[[nodiscard("Pure function")]] 
		virtual std::size_t BackendCount() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view RenderApiName(std::size_t backendIndex) const override;
		[[nodiscard("Pure function")]] 
		virtual Meta::Version RenderApiVersion(std::size_t backendIndex) const override;
		[[nodiscard("Pure function")]] 
		virtual std::optional<std::size_t> ActiveBackend() const noexcept override;
		virtual void SwitchBackend(std::optional<std::size_t> backendIndex) override;

		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<IBuffer> CreateBuffer(HeapType heapType, const BufferParams& params) override;

		[[nodiscard("Wierd call")]] 
		virtual struct TextureFormatId TextureFormatId(std::string_view textureFormat) override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view TextureFormat(struct TextureFormatId textureFormatId) const override;
		[[nodiscard("Pure function")]] 
		virtual bool IsValid(struct TextureFormatId textureFormatId) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual TextureFormatFeature TextureFormatFeatures(struct TextureFormatId textureFormatId) const override;
		[[nodiscard("Pure function")]]
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const override;
		[[nodiscard("Wierd call")]] 
		virtual std::shared_ptr<ITexture> CreateTexture(HeapType heapType, const TextureParams& params) override;

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

		[[nodiscard("Pure function")]] 
		virtual Application::IApplicationContext& Application() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const Application::IApplicationContext& Application() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const Log::ILogger& Logger() const noexcept override;

		void ActivateBackend(std::size_t index);
		void DeactivateBackend(std::size_t index);

		[[nodiscard("Pure function")]]
		IBackend& GetCurrentBackend();
		[[nodiscard("Pure function")]]
		const IBackend& GetCurrentBackend() const;
		[[nodiscard("Pure function")]]
		IBackend& GetBackend(std::size_t index);
		[[nodiscard("Pure function")]]
		const IBackend& GetBackend(std::size_t index) const;

		Application::IApplicationContext* application;

		BackendContainer backends;
		std::optional<std::size_t> activeBackendIndex;

		std::unordered_map<struct TextureFormatId, std::string> textureFormatHashMap;

		BackendHandle nextBackendHandle;
	};
}

namespace PonyEngine::Render
{
	RenderDeviceService::RenderDeviceService(Application::IApplicationContext& application) noexcept :
		application{&application},
		nextBackendHandle{.id = 1u}
	{
	}

	RenderDeviceService::~RenderDeviceService() noexcept
	{
		if (activeBackendIndex)
		{
			DeactivateBackend(*activeBackendIndex);
		}

		if (backends.Size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Render backends weren't removed:");
			for (std::size_t i = 0uz; i < backends.Size(); ++i)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Backend handle: '0x{:X}'.", backends.Handle(i).id);
			}
		}
	}

	void RenderDeviceService::Begin()
	{
	}

	void RenderDeviceService::End()
	{
	}

	void RenderDeviceService::AddInterfaces(Application::IServiceInterfaceAdder& adder)
	{
		adder.AddInterface<IRenderDeviceService>(*this);
	}

	BackendHandle RenderDeviceService::AddBackend(const std::function<std::shared_ptr<IBackend>(IRenderDeviceContext&)>& factory)
	{
		if (!nextBackendHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more backend handles available");
		}
		if (application->FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Backends can be added only on start-up");
		}

		const std::shared_ptr<IBackend> backend = factory(*this);
		if (!backend) [[unlikely]]
		{
			throw std::invalid_argument("Backend is nullptr");
		}
		if (backends.IndexOf(*backend) < backends.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Backend has already been added");
		}

		const BackendHandle currentHandle = nextBackendHandle;
		backends.Add(currentHandle, backend);
		++nextBackendHandle.id;
		PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' backend added. Handle: '0x{:X}'.", typeid(*backend).name(), currentHandle.id);

		return currentHandle;
	}

	void RenderDeviceService::RemoveBackend(const BackendHandle backendHandle)
	{
		if (application->FlowState() != Application::FlowState::StartingUp && application->FlowState() != Application::FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Backend can be removed only on start-up or shut-down");
		}

		if (const std::size_t index = backends.IndexOf(backendHandle); index < backends.Size()) [[likely]]
		{
			if (index == activeBackendIndex)
			{
				SwitchBackend(std::nullopt);
			}

			const char* const backendName = typeid(backends.Backend(index)).name();
			backends.Remove(index);
			PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' backend removed. Handle: '0x{:X}'.", backendName, backendHandle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Backend not found");
		}
	}

	std::size_t RenderDeviceService::BackendCount() const noexcept
	{
		return backends.Size();
	}

	std::string_view RenderDeviceService::RenderApiName(const std::size_t backendIndex) const
	{
		return GetBackend(backendIndex).RenderApiName();
	}

	Meta::Version RenderDeviceService::RenderApiVersion(const std::size_t backendIndex) const
	{
		return GetBackend(backendIndex).RenderApiVersion();
	}

	std::optional<std::size_t> RenderDeviceService::ActiveBackend() const noexcept
	{
		return activeBackendIndex;
	}

	void RenderDeviceService::SwitchBackend(const std::optional<std::size_t> backendIndex)
	{
		if (backendIndex && backendIndex >= backends.Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

		if (activeBackendIndex)
		{
			try
			{
				DeactivateBackend(*activeBackendIndex);
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On deactivating '{}' backend.", typeid(backends.Backend(*activeBackendIndex)).name());
				throw;
			}
		}

		activeBackendIndex = std::nullopt;
		
		if (backendIndex)
		{
			try
			{
				ActivateBackend(*backendIndex);
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On activating '{}' backend.", typeid(backends.Backend(*backendIndex)).name());
				throw;
			}
		}

		activeBackendIndex = backendIndex;
	}

	std::shared_ptr<IBuffer> RenderDeviceService::CreateBuffer(const HeapType heapType, const BufferParams& params)
	{
		return GetCurrentBackend().CreateBuffer(heapType, params);
	}

	struct TextureFormatId RenderDeviceService::TextureFormatId(const std::string_view textureFormat)
	{
		const auto textureFormatId = Render::TextureFormatId{.hash = Hash::FNV1a64(textureFormat)};

		if (const auto position = textureFormatHashMap.find(textureFormatId); position != textureFormatHashMap.cend())
		{
			if (position->second != textureFormat)
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding new texture format. TextureFormat: '{}'; TextureFormatHash: '{}'.", textureFormat, textureFormatId.hash);
			textureFormatHashMap[textureFormatId] = textureFormat;
		}

		return textureFormatId;
	}

	std::string_view RenderDeviceService::TextureFormat(const struct TextureFormatId textureFormatId) const
	{
		if (const auto position = textureFormatHashMap.find(textureFormatId); position != textureFormatHashMap.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Invalid texture format ID");
	}

	bool RenderDeviceService::IsValid(const struct TextureFormatId textureFormatId) const noexcept
	{
		return textureFormatHashMap.contains(textureFormatId);
	}

	TextureFormatFeature RenderDeviceService::TextureFormatFeatures(const struct TextureFormatId textureFormatId) const
	{
		if (!IsValid(textureFormatId)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid format");
		}

		return GetCurrentBackend().TextureFormatFeatures(textureFormatId);
	}

	TextureSupportResponse RenderDeviceService::TextureSupport(const TextureSupportRequest& request) const
	{
		if (!IsValid(request.format)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid format");
		}

		return GetCurrentBackend().TextureSupport(request);
	}

	std::shared_ptr<ITexture> RenderDeviceService::CreateTexture(const HeapType heapType, const TextureParams& params)
	{
		return GetCurrentBackend().CreateTexture(heapType, params);
	}

	struct SwapChainSupport RenderDeviceService::SwapChainSupport() const
	{
		return GetCurrentBackend().SwapChainSupport();
	}

	bool RenderDeviceService::IsSwapChainAlive() const
	{
		return GetCurrentBackend().IsSwapChainAlive();
	}

	void RenderDeviceService::CreateSwapChain(const SwapChainParams& params)
	{
		return GetCurrentBackend().CreateSwapChain(params);
	}

	void RenderDeviceService::DestroySwapChain()
	{
		GetCurrentBackend().DestroySwapChain();
	}

	std::uint8_t RenderDeviceService::SwapChainBufferCount() const
	{
		return GetCurrentBackend().SwapChainBufferCount();
	}

	std::uint8_t RenderDeviceService::CurrentSwapChainBufferIndex() const
	{
		return GetCurrentBackend().CurrentSwapChainBufferIndex();
	}

	std::shared_ptr<ITexture> RenderDeviceService::SwapChainBuffer(const std::uint8_t bufferIndex) const
	{
		return GetCurrentBackend().SwapChainBuffer(bufferIndex);
	}

	void RenderDeviceService::PresentNextSwapChainBuffer()
	{
		GetCurrentBackend().PresentNextSwapChainBuffer();
	}

	Application::IApplicationContext& RenderDeviceService::Application() noexcept
	{
		return *application;
	}

	const Application::IApplicationContext& RenderDeviceService::Application() const noexcept
	{
		return *application;
	}

	Log::ILogger& RenderDeviceService::Logger() noexcept
	{
		return application->Logger();
	}

	const Log::ILogger& RenderDeviceService::Logger() const noexcept
	{
		return application->Logger();
	}

	void RenderDeviceService::ActivateBackend(const std::size_t index)
	{
		IBackend& backend = backends.Backend(index);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Activating '{}' backend...", typeid(backend).name());
		backend.Activate();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Activating '{}' backend done.", typeid(backend).name());
	}

	void RenderDeviceService::DeactivateBackend(const std::size_t index)
	{
		IBackend& backend = backends.Backend(index);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Deactivating '{}' backend...", typeid(backend).name());
		backend.Deactivate();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Deactivating '{}' backend done.", typeid(backend).name());
	}

	IBackend& RenderDeviceService::GetCurrentBackend()
	{
		if (!activeBackendIndex) [[unlikely]]
		{
			throw std::logic_error("No active backend");
		}

		return backends.Backend(*activeBackendIndex);
	}

	const IBackend& RenderDeviceService::GetCurrentBackend() const
	{
		if (!activeBackendIndex) [[unlikely]]
		{
			throw std::logic_error("No active backend");
		}

		return backends.Backend(*activeBackendIndex);
	}

	IBackend& RenderDeviceService::GetBackend(const std::size_t index)
	{
		if (index >= backends.Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

		return backends.Backend(index);
	}

	const IBackend& RenderDeviceService::GetBackend(const std::size_t index) const
	{
		if (index >= backends.Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

		return backends.Backend(index);
	}
}

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
import PonyEngine.Log;
import PonyEngine.Meta;
import PonyEngine.RenderDevice.Ext;

import :BackendContainer;
import :EmptyBackend;

export namespace PonyEngine::Render
{
	class RenderDeviceService final : public Application::IService, public IRenderDeviceModuleContext, private IRenderDeviceService, private IRenderDeviceContext
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit RenderDeviceService(Application::IApplicationContext& application);
		RenderDeviceService(const RenderDeviceService&) = delete;
		RenderDeviceService(RenderDeviceService&&) = delete;

		~RenderDeviceService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Must be used to remove")]]
		virtual BackendHandle AddBackend(const std::function<std::shared_ptr<IBackend>(IRenderDeviceModuleContext&)>& factory) override;
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
		virtual std::size_t ActiveBackend() const noexcept override;
		virtual void SwitchBackend(std::size_t backendIndex) override;

		[[nodiscard("Pure function")]] 
		virtual Application::IApplicationContext& Application() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const Application::IApplicationContext& Application() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const Log::ILogger& Logger() const noexcept override;

		BackendHandle AddBackend(const std::shared_ptr<IBackend>& backend);
		void RemoveBackend(std::size_t index) noexcept;

		void ActivateBackend(std::size_t index);
		void DeactivateBackend(std::size_t index);

		Application::IApplicationContext* application;

		BackendContainer backends;
		std::size_t activeBackendIndex;

		BackendHandle nextBackendHandle;
	};
}

namespace PonyEngine::Render
{
	RenderDeviceService::RenderDeviceService(Application::IApplicationContext& application) :
		application{&application},
		activeBackendIndex{0uz},
		nextBackendHandle{.id = 1u}
	{
		PONY_LOG(application.Logger(), Log::LogType::Info, "Creating '{}' backend...", typeid(EmptyBackend).name());
		const auto emptyBackend = std::make_shared<EmptyBackend>();
		PONY_LOG(application.Logger(), Log::LogType::Info, "Creating '{}' backend done.", typeid(EmptyBackend).name());
		AddBackend(emptyBackend);
	}

	RenderDeviceService::~RenderDeviceService() noexcept
	{
		if (activeBackendIndex != 0uz)
		{
			DeactivateBackend(activeBackendIndex);
		}
		
		RemoveBackend(0uz);

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

	BackendHandle RenderDeviceService::AddBackend(const std::function<std::shared_ptr<IBackend>(IRenderDeviceModuleContext&)>& factory)
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

		return AddBackend(backend);
	}

	void RenderDeviceService::RemoveBackend(const BackendHandle backendHandle)
	{
		if (application->FlowState() != Application::FlowState::StartingUp && application->FlowState() != Application::FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Backend can be removed only on start-up or shut-down");
		}

		if (const std::size_t index = backends.IndexOf(backendHandle); index < backends.Size()) [[likely]]
		{
			RemoveBackend(index);
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
		if (backendIndex >= backends.Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

		return backends.Backend(backendIndex).RenderApiName();
	}

	Meta::Version RenderDeviceService::RenderApiVersion(const std::size_t backendIndex) const
	{
		if (backendIndex >= backends.Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

		return backends.Backend(backendIndex).RenderApiVersion();
	}

	std::size_t RenderDeviceService::ActiveBackend() const noexcept
	{
		return activeBackendIndex;
	}

	void RenderDeviceService::SwitchBackend(const std::size_t backendIndex)
	{
		if (backendIndex >= backends.Size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

		if (activeBackendIndex != 0uz)
		{
			try
			{
				DeactivateBackend(activeBackendIndex);
				activeBackendIndex = 0uz;
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On deactivating '{}' backend.", typeid(backends.Backend(activeBackendIndex)).name());
				throw;
			}
		}
		
		try
		{
			ActivateBackend(backendIndex);
			activeBackendIndex = backendIndex;
		}
		catch (...)
		{
			PONY_LOG_X(application->Logger(), std::current_exception(), "On activating '{}' backend.", typeid(backends.Backend(backendIndex)).name());
			throw;
		}
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

	BackendHandle RenderDeviceService::AddBackend(const std::shared_ptr<IBackend>& backend)
	{
		const BackendHandle currentHandle = nextBackendHandle;
		backends.Add(currentHandle, backend);
		++nextBackendHandle.id;
		PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' backend added. Handle: '0x{:X}'.", typeid(*backend).name(), currentHandle.id);

		return currentHandle;
	}

	void RenderDeviceService::RemoveBackend(const std::size_t index) noexcept
	{
		const BackendHandle backendHandle = backends.Handle(index);
		const char* const backendName = typeid(backends.Backend(index)).name();
		backends.Remove(index);
		PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' backend removed. Handle: '0x{:X}'.", backendName, backendHandle.id);
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
}

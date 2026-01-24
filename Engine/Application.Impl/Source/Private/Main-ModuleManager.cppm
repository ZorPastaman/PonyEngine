/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Impl:ModuleManager;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;

import :ModuleDataContainer;

export namespace PonyEngine::Application
{
	/// @brief Module manager.
	class ModuleManager final : private IModuleContext
	{
	public:
		/// @brief Creates a module manager.
		/// @param application Application context.
		/// @param loggerModuleContext Logger module context.
		/// @param serviceModuleContext Service module context.
		[[nodiscard("Pure constructor")]]
		ModuleManager(IApplicationContext& application, ILoggerModuleContext& loggerModuleContext, IServiceModuleContext& serviceModuleContext);
		ModuleManager(const ModuleManager&) = delete;
		ModuleManager(ModuleManager&&) = delete;

		~ModuleManager() noexcept;

		ModuleManager& operator =(const ModuleManager&) = delete;
		ModuleManager& operator =(ModuleManager&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual ILoggerModuleContext& LoggerModuleContext() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const ILoggerModuleContext& LoggerModuleContext() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual IServiceModuleContext& ServiceModuleContext() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IServiceModuleContext& ServiceModuleContext() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual void* GetData(std::type_index type) const override;
		virtual ModuleDataHandle AddData(std::type_index type, const std::shared_ptr<void>& data) override;
		virtual void RemoveData(ModuleDataHandle handle) override;

		/// @brief Initializes the modules.
		/// @param lastModule Last module pointer.
		void Initialize(std::uintptr_t& lastModule);
		/// @brief Finalizes the modules.
		/// @param lastModule Last module pointer.
		void Finalize(std::uintptr_t lastModule) noexcept;

		IApplicationContext* application; ///< Application context.

		ILoggerModuleContext* loggerModuleContext; ///< Logger module context.
		IServiceModuleContext* serviceModuleContext; ///< Service module context.

		ModuleDataContainer dataContainer; ///< Data container.

		ModuleDataHandle nextDataHandle; ///< Next data handle.
	};
}

namespace PonyEngine::Application
{
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) IModule** FirstModule = nullptr; ///< Module begin pointer.
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) IModule** LastModule = nullptr; ///< Module end pointer.

	ModuleManager::ModuleManager(IApplicationContext& application, ILoggerModuleContext& loggerModuleContext, IServiceModuleContext& serviceModuleContext) :
		application{&application},
		loggerModuleContext{&loggerModuleContext},
		serviceModuleContext{&serviceModuleContext},
		nextDataHandle{.id = 1u}
	{
		std::uintptr_t lastModule = reinterpret_cast<std::uintptr_t>(&FirstModule);
		try
		{
			Initialize(lastModule);
		}
		catch (...)
		{
			Finalize(lastModule);
			throw;
		}
	}

	ModuleManager::~ModuleManager() noexcept
	{
		Finalize(reinterpret_cast<std::uintptr_t>(&LastModule) - sizeof(IModule**));

		if (dataContainer.Size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Data wasn't removed:");
			for (const std::type_index type : dataContainer.Types())
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Data of type: '{}'.", type.name());
			}
		}
	}

	Log::ILogger& ModuleManager::Logger() noexcept
	{
		return application->Logger();
	}

	const Log::ILogger& ModuleManager::Logger() const noexcept
	{
		return application->Logger();
	}

	ILoggerModuleContext& ModuleManager::LoggerModuleContext() noexcept
	{
		return *loggerModuleContext;
	}

	const ILoggerModuleContext& ModuleManager::LoggerModuleContext() const noexcept
	{
		return *loggerModuleContext;
	}

	IServiceModuleContext& ModuleManager::ServiceModuleContext() noexcept
	{
		return *serviceModuleContext;
	}

	const IServiceModuleContext& ModuleManager::ServiceModuleContext() const noexcept
	{
		return *serviceModuleContext;
	}

	void* ModuleManager::GetData(const std::type_index type) const
	{
		if (const std::size_t index = dataContainer.IndexOf(type); index < dataContainer.Size())
		{
			return dataContainer.Data(index);
		}

		return nullptr;
	}

	ModuleDataHandle ModuleManager::AddData(const std::type_index type, const std::shared_ptr<void>& data)
	{
#ifndef NDEBUG
		if (!nextDataHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more data handles available");
		}

		if (application->FlowState() != FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Data can be added only on start-up");
		}

		if (dataContainer.IndexOf(type) < dataContainer.Size()) [[unlikely]]
		{
			throw std::invalid_argument(std::format("Data of type '{}' has already been added", type.name()));
		}
#endif

		const ModuleDataHandle currentHandle = nextDataHandle;
		dataContainer.Add(currentHandle, type, data);
		++nextDataHandle.id;

		PONY_LOG(application->Logger(), Log::LogType::Info, "Data of type '{}' added to module context. Handle: '0x{:X}'.", type.name(), currentHandle.id);

		return currentHandle;
	}

	void ModuleManager::RemoveData(const ModuleDataHandle handle)
	{
#ifndef NDEBUG
		if (application->FlowState() != FlowState::StartingUp && application->FlowState() != FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Data can be removed only on start-up or shut-down");
		}
#endif

		if (const std::size_t index = dataContainer.IndexOf(handle); index < dataContainer.Size()) [[likely]]
		{
			const char* const typeName = dataContainer.Type(index).name();
			dataContainer.Remove(index);
			PONY_LOG(application->Logger(), Log::LogType::Info, "Data of type '{}' removed from module context. Handle: '0x{:X}'.", typeName, handle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Data not found");
		}
	}

	void ModuleManager::Initialize(std::uintptr_t& lastModule)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up modules...")

		for (std::uintptr_t current = reinterpret_cast<std::uintptr_t>(&FirstModule) + sizeof(IModule**); 
			current < reinterpret_cast<std::uintptr_t>(&LastModule); 
			current += sizeof(IModule**))
		{
			if (const auto modulePtr = *reinterpret_cast<IModule***>(current))
			{
				IModule* const module = *modulePtr;
#ifndef NDEBUG
				if (!module) [[unlikely]]
				{
					throw std::logic_error("Module is nullptr");
				}
#endif
				PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up '{}' module...", typeid(*&*module).name());
				try
				{
					module->StartUp(*this);
				}
				catch (...)
				{
					PONY_LOG_X(application->Logger(), std::current_exception(), "On starting up '{}' module.", typeid(*&*module).name());
					throw;
				}
				PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up '{}' module done.", typeid(*&*module).name());
				lastModule = current;
			}
		}

		PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up modules done.")
	}

	void ModuleManager::Finalize(const std::uintptr_t lastModule) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down modules...")

		for (std::uintptr_t current = lastModule; 
			current > reinterpret_cast<std::uintptr_t>(&FirstModule); 
			current -= sizeof(IModule**))
		{
			if (const auto modulePtr = *reinterpret_cast<IModule***>(current))
			{
				IModule* const module = *modulePtr;
				PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down '{}' module...", typeid(*&*module).name());
				try
				{
					module->ShutDown(*this);
				}
				catch (...)
				{
					PONY_LOG_X(application->Logger(), std::current_exception(), "On shutting down '{}' module.", typeid(*&*module).name());
				}
				PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down '{}' module done.", typeid(*&*module).name());
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down modules done.")
	}
}

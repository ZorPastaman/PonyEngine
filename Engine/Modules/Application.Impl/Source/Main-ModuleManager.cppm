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

import PonyEngine.Application;
import PonyEngine.Log;

import :ModuleDataContainer;

export namespace PonyEngine::Application
{
	/// @brief Module manager.
	class ModuleManager final : private IModuleContext
	{
	public:
		/// @brief Creates a module manager.
		/// @param application Application.
		/// @param loggerModuleContext Logger module context.
		/// @param serviceModuleContext Service module context.
		[[nodiscard("Pure constructor")]]
		ModuleManager(IApplication& application, ILoggerModuleContext& loggerModuleContext, IServiceModuleContext& serviceModuleContext);
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
		void Initialize();
		/// @brief Finalizes the modules.
		void Finalize() noexcept;

		IApplication* application; ///< Application.

		ILoggerModuleContext* loggerModuleContext; ///< Logger module context.
		IServiceModuleContext* serviceModuleContext; ///< Service module context.

		std::vector<IModule*> appModules; ///< Application modules.

		ModuleDataContainer dataContainer; ///< Data container.

		ModuleDataHandle nextDataHandle; ///< Next data handle.
	};
}

namespace PonyEngine::Application
{
	using ModuleInterface = IModule*(*)();

	PONY_NORMAL_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) ModuleInterface FirstModule = nullptr; ///< Module begin pointer.
	PONY_NORMAL_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) ModuleInterface LastModule = nullptr; ///< Module end pointer.

	ModuleManager::ModuleManager(IApplication& application, ILoggerModuleContext& loggerModuleContext, IServiceModuleContext& serviceModuleContext) :
		application{&application},
		loggerModuleContext{&loggerModuleContext},
		serviceModuleContext{&serviceModuleContext},
		nextDataHandle{.id = 1u}
	{
		try
		{
			Initialize();
		}
		catch (...)
		{
			Finalize();
			throw;
		}
	}

	ModuleManager::~ModuleManager() noexcept
	{
		Finalize();

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
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		if (const std::size_t index = dataContainer.IndexOf(type); index < dataContainer.Size())
		{
			return dataContainer.Data(index);
		}

		return nullptr;
	}

	ModuleDataHandle ModuleManager::AddData(const std::type_index type, const std::shared_ptr<void>& data)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

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
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

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

	void ModuleManager::Initialize()
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Getting modules...")
		for (std::uintptr_t current = reinterpret_cast<std::uintptr_t>(&FirstModule) + sizeof(ModuleInterface);
			current < reinterpret_cast<std::uintptr_t>(&LastModule);
			current += sizeof(ModuleInterface))
		{
			if (const auto moduleGetter = *reinterpret_cast<ModuleInterface*>(current))
			{
				IModule* const appModule = moduleGetter();
#ifndef NDEBUG
				if (!appModule) [[unlikely]]
				{
					throw std::logic_error("Module is nullptr");
				}
#endif
				appModules.push_back(appModule);
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Getting modules done.")

		PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up modules...")
		for (IModule* const appModule : appModules)
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up '{}' module...", typeid(*appModule).name());
			try
			{
				appModule->StartUp(*this);
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, std::current_exception(), "On starting up '{}' module.", typeid(*appModule).name());
				throw;
			}
			PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up '{}' module done.", typeid(*appModule).name());
		}

		PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up modules done.")
	}

	void ModuleManager::Finalize() noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down modules...")

		for (std::size_t i = appModules.size(); i-- > 0uz; )
		{
			IModule* const appModule = appModules[i];
			PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down '{}' module...", typeid(*appModule).name());
			try
			{
				appModule->ShutDown(*this);
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, std::current_exception(), "On shutting down '{}' module.", typeid(*appModule).name());
			}
			PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down '{}' module done.", typeid(*appModule).name());
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down modules done.")
	}
}

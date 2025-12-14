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
		[[nodiscard("Pure function")]]
		ModuleManager(IApplicationContext& application, ILoggerModuleContext& loggerModuleContext, IServiceModuleContext& serviceModuleContext);
		ModuleManager(const ModuleManager&) = delete;
		ModuleManager(ModuleManager&&) = delete;

		~ModuleManager() noexcept;

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

		ModuleManager& operator =(const ModuleManager&) = delete;
		ModuleManager& operator =(ModuleManager&&) = delete;

	private:
		/// @brief Initializes the modules.
		/// @param lastModule Last module pointer.
		void Initialize(std::uintptr_t& lastModule);
		/// @brief Finalizes the modules.
		/// @param lastModule Last module pointer.
		void Finalize(std::uintptr_t lastModule) noexcept;

		IApplicationContext* application; ///< Application context.

		ILoggerModuleContext* loggerModuleContext; ///< Logger module context.
		IServiceModuleContext* serviceModuleContext; ///< Service module context.

		// These vectors are synced by index.
		std::vector<ModuleDataHandle> dataHandles; ///< Data handles.
		std::vector<std::type_index> dataTypes; ///< Data types.
		std::vector<std::shared_ptr<void>> data; ///< Data.

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

		if (data.size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Data wasn't removed:");
			for (const std::type_index type : dataTypes)
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
		if (const auto position = std::ranges::find(dataTypes, type); position != dataTypes.cend())
		{
			return data[position - dataTypes.cbegin()].get();
		}

		return nullptr;
	}

	ModuleDataHandle ModuleManager::AddData(const std::type_index type, const std::shared_ptr<void>& data)
	{
		if (!nextDataHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more data handles available");
		}

		if (application->FlowState() != FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Data can be added only on start-up");
		}

		if (std::ranges::find(dataTypes, type) != dataTypes.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Type has already been added");
		}

		const ModuleDataHandle currentHandle = nextDataHandle;
		dataHandles.push_back(currentHandle);
		try
		{
			dataTypes.push_back(type);
			try
			{
				this->data.push_back(data);
			}
			catch (...)
			{
				dataTypes.pop_back();
				throw;
			}
		}
		catch (...)
		{
			dataHandles.pop_back();
			throw;
		}
		++nextDataHandle.id;

		PONY_LOG(application->Logger(), Log::LogType::Info, "Data of type '{}' added to module context. Handle: '0x{:X}'.", type.name(), currentHandle.id);

		return currentHandle;
	}

	void ModuleManager::RemoveData(const ModuleDataHandle handle)
	{
		if (application->FlowState() != FlowState::StartingUp && application->FlowState() != FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Data can be removed only on start-up or shut-down");
		}

		if (const auto position = std::find(dataHandles.crbegin(), dataHandles.crend(), handle); position != dataHandles.crend()) [[likely]]
		{
			const std::size_t index = std::distance(dataHandles.cbegin(), position.base()) - 1uz;
			const char* const typeName = dataTypes[index].name();
			data.erase(data.cbegin() + index);
			dataTypes.erase(dataTypes.cbegin() + index);
			dataHandles.erase(dataHandles.cbegin() + index);
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
				if (!module) [[unlikely]]
				{
					throw std::logic_error("Module is nullptr");
				}
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

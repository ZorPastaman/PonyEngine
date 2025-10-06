/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Log/Log.h"

export module PonyEngine.Application.Main:ModuleManager;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.Memory;

import :LoggerManager;
import :ServiceManager;

export namespace PonyEngine::Application
{
	/// @brief Module manager.
	class ModuleManager final
	{
	public:
		/// @brief Creates a module manager.
		/// @param application Application context.
		/// @param loggerManager Logger manager.
		/// @param serviceManager Service manager.
		[[nodiscard("Pure function")]]
		ModuleManager(IApplicationContext& application, LoggerManager& loggerManager, ServiceManager& serviceManager);
		ModuleManager(const ModuleManager&) = delete;
		ModuleManager(ModuleManager&&) = delete;

		~ModuleManager() noexcept;

		ModuleManager& operator =(const ModuleManager&) = delete;
		ModuleManager& operator =(ModuleManager&&) = delete;

	private:
		/// @brief Starting up module context.
		class StartingUpModuleContext final : public IModuleContext
		{
		public:
			/// @brief Creates a starting up module context.
			/// @param moduleManager Module manager.
			[[nodiscard("Pure constructor")]]
			explicit StartingUpModuleContext(ModuleManager& moduleManager) noexcept;
			StartingUpModuleContext(const StartingUpModuleContext&) = delete;
			StartingUpModuleContext(StartingUpModuleContext&&) = delete;

			~StartingUpModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const IApplicationContext& Application() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Log::ILogger& Logger() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual std::size_t DataCount(const std::type_info& type) const noexcept override;
			[[nodiscard("Pure function")]]
			virtual const std::shared_ptr<void>& GetData(const std::type_info& type, std::size_t index) const override;
			[[nodiscard("Pure function")]]
			virtual void AddData(const std::type_info& type, const std::shared_ptr<void>& data) override;

			[[nodiscard("Pure function")]]
			virtual void* FindService(const std::type_info& type) noexcept override;
			[[nodiscard("Pure function")]]
			virtual const void* FindService(const std::type_info& type) const noexcept override;
			virtual void AddService(const ServiceData& data) override;

			/// @brief Gets the current module.
			/// @return Current module.
			[[nodiscard("Pure function")]]
			const IModule* CurrentModule() const noexcept;
			/// @brief Sets the current module.
			/// @param module Current module.
			void CurrentModule(const IModule* module) noexcept;

			StartingUpModuleContext& operator =(const StartingUpModuleContext&) = delete;
			StartingUpModuleContext& operator =(StartingUpModuleContext&&) = delete;

		private:
			ModuleManager* moduleManager; ///< Module manager.

			std::unordered_map<std::type_index, std::vector<std::shared_ptr<void>>> dataMap; ///< Data map.
			const IModule* currentModule; ///< Current module.
		};

		/// @brief Shutting down module context.
		class ShuttingDownModuleContext final : public IModuleContext
		{
		public:
			/// @brief Creates a shutting down module context.
			/// @param moduleManager Module manager.
			[[nodiscard("Pure constructor")]]
			explicit ShuttingDownModuleContext(ModuleManager& moduleManager) noexcept;
			ShuttingDownModuleContext(const ShuttingDownModuleContext&) = delete;
			ShuttingDownModuleContext(ShuttingDownModuleContext&&) = delete;

			~ShuttingDownModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const IApplicationContext& Application() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual Log::ILogger& Logger() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Log::ILogger& Logger() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual std::size_t DataCount(const std::type_info& type) const noexcept override;
			[[nodiscard("Pure function")]]
			virtual const std::shared_ptr<void>& GetData(const std::type_info& type, std::size_t index) const override;
			[[nodiscard("Pure function")]]
			virtual void AddData(const std::type_info& type, const std::shared_ptr<void>& data) override;

			[[nodiscard("Pure function")]]
			virtual void* FindService(const std::type_info& type) noexcept override;
			[[nodiscard("Pure function")]]
			virtual const void* FindService(const std::type_info& type) const noexcept override;
			virtual void AddService(const ServiceData& data) override;

			ShuttingDownModuleContext& operator =(const ShuttingDownModuleContext&) = delete;
			ShuttingDownModuleContext& operator =(ShuttingDownModuleContext&&) = delete;

		private:
			ModuleManager* moduleManager; ///< Module manager.
		};

		/// @brief Initializes the modules.
		/// @param lastModule Last module pointer.
		void Initialize(std::uintptr_t& lastModule);
		/// @brief Finalizes the modules.
		/// @param lastModule Last module pointer.
		void Finalize(std::uintptr_t lastModule) noexcept;
		/// @brief Remove module services.
		/// @param module Module.
		void RemoveServices(const IModule* module) noexcept;

		IApplicationContext* application; ///< Application context.
		LoggerManager* loggerManager; ///< Logger manager.
		ServiceManager* serviceManager; ///< Service manager.

		std::unordered_map<const IModule*, std::vector<const IService*>> moduleServices; ///< Module to its services map.
	};
}

namespace PonyEngine::Application
{
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) IModule** FirstModule = nullptr; ///< Module begin pointer.
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) IModule** LastModule = nullptr; ///< Module end pointer.

	ModuleManager::ModuleManager(IApplicationContext& application, LoggerManager& loggerManager, ServiceManager& serviceManager) :
		application{&application},
		loggerManager{&loggerManager},
		serviceManager{&serviceManager}
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
	}

	ModuleManager::StartingUpModuleContext::StartingUpModuleContext(ModuleManager& moduleManager) noexcept :
		moduleManager{&moduleManager},
		currentModule{nullptr}
	{
	}

	IApplicationContext& ModuleManager::StartingUpModuleContext::Application() noexcept
	{
		return *moduleManager->application;
	}

	const IApplicationContext& ModuleManager::StartingUpModuleContext::Application() const noexcept
	{
		return *moduleManager->application;
	}

	Log::ILogger& ModuleManager::StartingUpModuleContext::Logger() noexcept
	{
		return moduleManager->application->Logger();
	}

	const Log::ILogger& ModuleManager::StartingUpModuleContext::Logger() const noexcept
	{
		return moduleManager->application->Logger();
	}

	std::size_t ModuleManager::StartingUpModuleContext::DataCount(const std::type_info& type) const noexcept
	{
		if (const auto position = dataMap.find(type); position != dataMap.end())
		{
			return position->second.size();
		}

		return 0uz;
	}

	const std::shared_ptr<void>& ModuleManager::StartingUpModuleContext::GetData(const std::type_info& type, const std::size_t index) const
	{
		if (const auto position = dataMap.find(type); position != dataMap.end()) [[likely]]
		{
			if (index < position->second.size()) [[likely]]
			{
				return position->second[index];
			}
		}

		throw std::invalid_argument("Incorrect data request.");
	}

	void ModuleManager::StartingUpModuleContext::AddData(const std::type_info& type, const std::shared_ptr<void>& data)
	{
		dataMap[type].push_back(data);
	}

	void* ModuleManager::StartingUpModuleContext::FindService(const std::type_info& type) noexcept
	{
		return moduleManager->serviceManager->FindService(type);
	}

	const void* ModuleManager::StartingUpModuleContext::FindService(const std::type_info& type) const noexcept
	{
		return moduleManager->serviceManager->FindService(type);
	}

	void ModuleManager::StartingUpModuleContext::AddService(const ServiceData& data)
	{
		moduleManager->serviceManager->AddService(data);
		const IService* const service = data.service.index() == 0 ? std::get<0>(data.service).get() : std::get<1>(data.service).get();

		try
		{
			moduleManager->moduleServices[currentModule].push_back(service);
		}
		catch (...)
		{
			moduleManager->serviceManager->RemoveService(moduleManager->serviceManager->IndexOf(service).value());
			throw;
		}

		for (const Memory::TypedPtr<>& interface : data.publicInterfaces)
		{
			if (interface.Type() == typeid(Log::ILogger)) [[unlikely]]
			{
				moduleManager->loggerManager->Logger(static_cast<Log::ILogger*>(interface.Get()));
			}
		}
	}

	const IModule* ModuleManager::StartingUpModuleContext::CurrentModule() const noexcept
	{
		return currentModule;
	}

	void ModuleManager::StartingUpModuleContext::CurrentModule(const IModule* module) noexcept
	{
		currentModule = module;
	}

	ModuleManager::ShuttingDownModuleContext::ShuttingDownModuleContext(ModuleManager& moduleManager) noexcept :
		moduleManager{&moduleManager}
	{
	}

	IApplicationContext& ModuleManager::ShuttingDownModuleContext::Application() noexcept
	{
		return *moduleManager->application;
	}

	const IApplicationContext& ModuleManager::ShuttingDownModuleContext::Application() const noexcept
	{
		return *moduleManager->application;
	}

	Log::ILogger& ModuleManager::ShuttingDownModuleContext::Logger() noexcept
	{
		return moduleManager->application->Logger();
	}

	const Log::ILogger& ModuleManager::ShuttingDownModuleContext::Logger() const noexcept
	{
		return moduleManager->application->Logger();
	}

	std::size_t ModuleManager::ShuttingDownModuleContext::DataCount(const std::type_info& type) const noexcept
	{
		return 0uz;
	}

	const std::shared_ptr<void>& ModuleManager::ShuttingDownModuleContext::GetData(const std::type_info& type, const std::size_t index) const
	{
		throw std::logic_error("Invalid operation");
	}

	void ModuleManager::ShuttingDownModuleContext::AddData(const std::type_info& type, const std::shared_ptr<void>& data)
	{
		throw std::logic_error("Invalid operation");
	}

	void* ModuleManager::ShuttingDownModuleContext::FindService(const std::type_info& type) noexcept
	{
		return moduleManager->serviceManager->FindService(type);
	}

	const void* ModuleManager::ShuttingDownModuleContext::FindService(const std::type_info& type) const noexcept
	{
		return moduleManager->serviceManager->FindService(type);
	}

	void ModuleManager::ShuttingDownModuleContext::AddService(const ServiceData& data)
	{
		throw std::logic_error("Invalid operation");
	}

	void ModuleManager::Initialize(std::uintptr_t& lastModule)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up modules...")
		auto moduleContext = StartingUpModuleContext(*this);

		for (std::uintptr_t current = reinterpret_cast<std::uintptr_t>(&FirstModule) + sizeof(IModule**); 
			current < reinterpret_cast<std::uintptr_t>(&LastModule); 
			current += sizeof(IModule**))
		{
			if (const auto modulePtr = *reinterpret_cast<IModule***>(current))
			{
				IModule* const module = *modulePtr;
				assert(module && "The module is nullptr.");
				PONY_LOG(application->Logger(), Log::LogType::Info, "Starting up '{}' module...", typeid(*&*module).name());
				moduleContext.CurrentModule(module);
				try
				{
					module->StartUp(moduleContext);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On starting up '{}' module.", typeid(*&*module).name());
					throw;
				}
				catch (...)
				{
					PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on starting up '{}' module.", typeid(*&*module).name());
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
		const auto moduleContext = ShuttingDownModuleContext(*this);

		for (std::uintptr_t current = lastModule; 
			current > reinterpret_cast<std::uintptr_t>(&FirstModule); 
			current -= sizeof(IModule**))
		{
			if (const auto modulePtr = *reinterpret_cast<IModule***>(current))
			{
				IModule* const module = *modulePtr;
				PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down '{}' module...", typeid(*&*module).name());
				RemoveServices(module);
				try
				{
					module->ShutDown(moduleContext);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(application->Logger(), e, "On shutting down '{}' module.", typeid(*&*module).name());
				}
				catch (...)
				{
					PONY_LOG(application->Logger(), Log::LogType::Exception, "Unknown exception on shutting down '{}' module.", typeid(*&*module).name());
				}
				PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down '{}' module done.", typeid(*&*module).name());
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Shutting down modules done.")
	}

	void ModuleManager::RemoveServices(const IModule* const module) noexcept
	{
		const auto position = moduleServices.find(module);
		if (position == moduleServices.cend())
		{
			return;
		}

		PONY_LOG(application->Logger(), Log::LogType::Info, "Removing module services...");
		for (const IService* const service : position->second)
		{
			const std::size_t serviceIndex = serviceManager->IndexOf(service).value();
			for (const Memory::TypedPtr<>& interface : serviceManager->Service(serviceIndex).publicInterfaces)
			{
				if (interface.Type() == typeid(Log::ILogger)) [[unlikely]]
				{
					loggerManager->Logger(nullptr);
				}
			}
			serviceManager->RemoveService(serviceIndex);
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Removing module services done.");
	}
}

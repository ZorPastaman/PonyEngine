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
#include "PonyEngine/Macro/Text.h"

export module PonyEngine.Application.Impl:App;

import std;

import PonyEngine.Application;
import PonyEngine.Container;
import PonyEngine.Log;

import :EmptyLogger;
import :IdentityUtility;
import :PathUtility;

export namespace PonyEngine::Application
{
	class App final : public IApplication
	{
	public:
		[[nodiscard("Pure constructor")]]
		App(std::span<const std::string_view> commandLine, const std::filesystem::path& executableFile, const std::filesystem::path& localDataDirectory,
			const std::filesystem::path& userDataDirectory, const std::filesystem::path& tempDataDirectory);
		App(const App&) = delete;
		App(App&&) = delete;

		~App() noexcept;

		[[nodiscard("Pure function")]] 
		virtual std::string_view EngineName() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Meta::Version EngineVersion() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view EngineTitle() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::string_view CompanyName() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view ProjectName() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Meta::Version ProjectVersion() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view CompanyTitle() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view ProjectTitle() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& ExecutableFile() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& ExecutableDirectory() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& RootDirectory() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& LocalDataDirectory() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& UserDataDirectory() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& TempDataDirectory() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::thread::id MainThreadID() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::string_view> CommandLine() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual void* FindInterface(std::type_index type) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual FlowInfo Flow() const noexcept override;
		virtual void Stop(int exitCode) override;

		[[nodiscard("Pure function")]] 
		virtual std::uint64_t FrameCount() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::time_point<std::chrono::steady_clock> StartTimePoint() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::time_point<std::chrono::steady_clock> PrevFrameTimePoint() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::time_point<std::chrono::steady_clock> FrameTimePoint() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::time_point<std::chrono::steady_clock> NowTimePoint() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::nanoseconds PrevFrameTime() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::nanoseconds FrameTime() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::nanoseconds NowTime() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::nanoseconds DeltaTime() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::nanoseconds TargetFrameTime() const noexcept override;
		virtual void TargetFrameTime(std::chrono::nanoseconds frameTime) noexcept override;

		[[nodiscard("Pure function")]] 
		virtual TempBuffer AcquireTempBuffer(std::size_t requiredSize, std::size_t requiredAlignment) override;
		virtual void ReleaseTempBuffer(TempBuffer tempBuffer) noexcept override;

		void Initialize();
		void Finalize() noexcept;
		void Begin();
		void End() noexcept;
		int Run();

		[[nodiscard("Pure function")]]
		bool HasLogger() const noexcept;
		void SetLogger(Log::ILogger& logger);
		void UnsetLogger(const Log::ILogger& logger);

		void AddService(IService& service);
		void RemoveService(IService& service);

		void AddInterface(std::type_index type, void* interface);
		template<typename T>
		void AddInterface(T& interface);
		void RemoveInterface(std::type_index type, const void* interface);
		template<typename T>
		void RemoveInterface(T& interface);

		void AddTickable(ITickable& tickable, std::int32_t order);
		void RemoveTickable(ITickable& tickable, std::int32_t order);

		App& operator =(const App&) = delete;
		App& operator =(App&) = delete;

	private:
		using Buffer = std::vector<std::byte, Container::AlignedAllocator<std::byte>>; ///< Buffer type.
		using ModuleInterface = IModule*(*)();

		PONY_EARLY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) static inline ModuleInterface firstEarlyModule = nullptr; ///< Early module begin pointer.
		PONY_EARLY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) static inline ModuleInterface lastEarlyModule = nullptr; ///< Early module end pointer.
		PONY_NORMAL_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) static inline ModuleInterface firstNormalModule = nullptr; ///< Normal module begin pointer.
		PONY_NORMAL_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) static inline ModuleInterface lastNormalModule = nullptr; ///< Normal module end pointer.
		PONY_LATE_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) static inline ModuleInterface firstLateModule = nullptr; ///< Late module begin pointer.
		PONY_LATE_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) static inline ModuleInterface lastLateModule = nullptr; ///< Late module end pointer.

		/// @brief Temp buffer cache.
		struct TempBufferCache final
		{
			std::stack<Buffer> bufferCache; ///< Buffer cache.
			std::unordered_map<const std::byte*, Buffer> usedBuffers; ///< Buffers that are in use now.
		};

		class ModuleContext final : public IModuleContext
		{
		public:
			[[nodiscard("Pure constructor")]]
			explicit ModuleContext(App& application) noexcept;
			ModuleContext(const ModuleContext&) = delete;
			ModuleContext(ModuleContext&&) = delete;

			~ModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual IApplication& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const IApplication& Application() const noexcept override;

			[[nodiscard("Pure function")]]
			virtual bool HasLogger() const noexcept override;
			virtual void SetLogger(Log::ILogger& logger) override;
			virtual void UnsetLogger(Log::ILogger& logger) override;

			virtual void AddService(IService& service) override;
			virtual void RemoveService(IService& service) override;

			virtual void AddInterface(std::type_index type, void* interface) override;
			virtual void RemoveInterface(std::type_index type, void* interface) override;

			virtual void AddTickable(ITickable& tickable, std::int32_t order) override;
			virtual void RemoveTickable(ITickable& tickable, std::int32_t order) override;

			ModuleContext& operator =(const ModuleContext&) = delete;
			ModuleContext& operator =(ModuleContext&&) = delete;

		private:
			App* application;
		};

		struct FrameInfo final
		{
			std::chrono::time_point<std::chrono::steady_clock> prevFrameTimePoint;
			std::chrono::time_point<std::chrono::steady_clock> thisFrameTimePoint;
		};

		void Initialize(std::size_t& earlyCount, std::size_t& normalCount, std::size_t& lateCount);
		void Finalize(std::size_t earlyCount, std::size_t normalCount, std::size_t lateCount) noexcept;

		void Begin(std::size_t& count);
		void End(std::size_t count) noexcept;

		[[nodiscard("Pure function")]]
		static TempBufferCache& GetCache();
		/// @brief Gets a suitable buffer.
		/// @param cache Buffer cache.
		/// @param requiredAlignment Required alignment.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		Buffer GetBuffer(TempBufferCache& cache, std::size_t requiredAlignment) const;

		void GetModules(ModuleInterface firstModule, ModuleInterface lastModule, std::vector<IModule*>& modules) const;
		void StartUpModules(std::span<IModule* const> modules, std::size_t& count, ModuleContext& context) const;
		void ShutDownModules(std::span<IModule* const> modules, std::size_t count, ModuleContext& context) const noexcept;

		[[nodiscard("Pure function")]]
		FrameInfo ThisFrameInfo() const noexcept;

		std::thread::id mainThreadId;
		std::span<const std::string_view> commandLine;

		std::filesystem::path executableFile; ///< Path to the executable.
		std::filesystem::path executableDirectory; ///< Executable directory.
		std::filesystem::path rootDirectory; ///< Root directory.
		std::filesystem::path localDataDirectory; ///< Local data directory.
		std::filesystem::path userDataDirectory; ///< User data directory.
		std::filesystem::path tempDataDirectory; ///< Temporal data directory.

		EmptyLogger emptyLogger;
		Log::ILogger* logger;

		std::atomic<FlowInfo> flow;

		std::atomic<std::uint64_t> frameCount;
		std::chrono::time_point<std::chrono::steady_clock> startTimePoint;
		std::array<FrameInfo, 2> frameInfos;
		std::atomic<std::chrono::nanoseconds> targetFrameTime;

		std::vector<IService*> services;
		std::unordered_map<std::type_index, void*> interfaces; ///< Interfaces.
		std::vector<std::pair<ITickable*, std::int32_t>> tickables; ///< Tickables.

		std::vector<IModule*> earlyModules;
		std::vector<IModule*> normalModules;
		std::vector<IModule*> lateModules;

		static_assert(std::atomic<std::uint64_t>::is_always_lock_free, "Uint64 is not lock-free");
		static_assert(std::atomic<FlowInfo>::is_always_lock_free, "FlowInfo is not lock-free");
		static_assert(std::atomic<std::chrono::nanoseconds>::is_always_lock_free, "std::chrono::nanoseconds is not lock-free");
	};
}

namespace PonyEngine::Application
{
	App::App(const std::span<const std::string_view> commandLine, const std::filesystem::path& executableFile, const std::filesystem::path& localDataDirectory,
		const std::filesystem::path& userDataDirectory, const std::filesystem::path& tempDataDirectory) :
		mainThreadId(std::this_thread::get_id()),
		commandLine(commandLine),
		executableFile(executableFile),
		executableDirectory(this->executableFile.parent_path()),
		rootDirectory((this->executableDirectory / PONY_STRINGIFY_VALUE(PONY_ENGINE_ROOT_PATH)).lexically_normal()),
		localDataDirectory(localDataDirectory),
		userDataDirectory(userDataDirectory),
		tempDataDirectory(tempDataDirectory),
		logger{&emptyLogger},
		flow(FlowInfo{.exitCode = 0, .flowState = FlowState::NotInitialized}),
		frameCount(0ull),
		startTimePoint(NowTimePoint()),
		frameInfos{FrameInfo{.prevFrameTimePoint = startTimePoint, .thisFrameTimePoint = startTimePoint}, FrameInfo{.prevFrameTimePoint = startTimePoint, .thisFrameTimePoint = startTimePoint}},
		targetFrameTime(std::chrono::nanoseconds(0))
	{
	}

	std::string_view App::EngineName() const noexcept
	{
		return Application::EngineName();
	}

	Meta::Version App::EngineVersion() const noexcept
	{
		return Application::EngineVersion();
	}

	std::string_view App::EngineTitle() const noexcept
	{
		return Application::EngineTitle();
	}

	std::string_view App::CompanyName() const noexcept
	{
		return Application::CompanyName();
	}

	std::string_view App::ProjectName() const noexcept
	{
		return Application::ProjectName();
	}

	Meta::Version App::ProjectVersion() const noexcept
	{
		return Application::ProjectVersion();
	}

	std::string_view App::CompanyTitle() const noexcept
	{
		return Application::CompanyTitle();
	}

	std::string_view App::ProjectTitle() const noexcept
	{
		return Application::ProjectTitle();
	}

	const std::filesystem::path& App::ExecutableFile() const noexcept
	{
		return executableFile;
	}

	const std::filesystem::path& App::ExecutableDirectory() const noexcept
	{
		return executableDirectory;
	}

	const std::filesystem::path& App::RootDirectory() const noexcept
	{
		return rootDirectory;
	}

	const std::filesystem::path& App::LocalDataDirectory() const noexcept
	{
		return localDataDirectory;
	}

	const std::filesystem::path& App::UserDataDirectory() const noexcept
	{
		return userDataDirectory;
	}

	const std::filesystem::path& App::TempDataDirectory() const noexcept
	{
		return tempDataDirectory;
	}

	std::thread::id App::MainThreadID() const noexcept
	{
		return mainThreadId;
	}

	std::span<const std::string_view> App::CommandLine() const noexcept
	{
		return commandLine;
	}

	Log::ILogger& App::Logger() const noexcept
	{
		return *logger;
	}

	void* App::FindInterface(const std::type_index type) const noexcept
	{
		if (const auto position = interfaces.find(type); position != interfaces.cend()) [[likely]]
		{
			return position->second;
		}

		return nullptr;
	}

	FlowInfo App::Flow() const noexcept
	{
		return flow.load(std::memory_order::relaxed);
	}

	void App::Stop(const int exitCode)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		FlowInfo currentFlow = flow.load(std::memory_order::relaxed);
		if (currentFlow.flowState == FlowState::Running && flow.compare_exchange_strong(currentFlow, FlowInfo{.exitCode = exitCode, .flowState = FlowState::Stopped}, std::memory_order::relaxed))
		{
			PONY_LOG(Logger(), Log::LogType::Info, "Application stopped. Exit code: '{}'.", exitCode);
		}
		else
		{
			if (currentFlow.flowState == FlowState::Stopped) [[likely]]
			{
				PONY_LOG(Logger(), Log::LogType::Debug, "Tried to stop already stopped application. Ignoring.");
			}
			else [[unlikely]]
			{
				PONY_LOG(Logger(), Log::LogType::Warning, "Tried to stop application in inappropriate state. Ignoring. Current flow state: '{}'.", currentFlow.flowState);
			}
		}
	}

	std::uint64_t App::FrameCount() const noexcept
	{
		return frameCount.load(std::memory_order::relaxed);
	}

	std::chrono::time_point<std::chrono::steady_clock> App::StartTimePoint() const noexcept
	{
		return startTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> App::PrevFrameTimePoint() const noexcept
	{
		return ThisFrameInfo().prevFrameTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> App::FrameTimePoint() const noexcept
	{
		return ThisFrameInfo().thisFrameTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> App::NowTimePoint() const noexcept
	{
		return std::chrono::steady_clock::now();
	}

	std::chrono::nanoseconds App::PrevFrameTime() const noexcept
	{
		return PrevFrameTimePoint() - startTimePoint;
	}

	std::chrono::nanoseconds App::FrameTime() const noexcept
	{
		return FrameTimePoint() - startTimePoint;
	}

	std::chrono::nanoseconds App::NowTime() const noexcept
	{
		return NowTimePoint() - startTimePoint;
	}

	std::chrono::nanoseconds App::DeltaTime() const noexcept
	{
		const FrameInfo info = ThisFrameInfo();
		return info.thisFrameTimePoint - info.prevFrameTimePoint;
	}

	std::chrono::nanoseconds App::TargetFrameTime() const noexcept
	{
		return targetFrameTime.load(std::memory_order::relaxed);
	}

	void App::TargetFrameTime(const std::chrono::nanoseconds frameTime) noexcept
	{
		targetFrameTime.store(frameTime, std::memory_order::relaxed);
	}

	TempBuffer App::AcquireTempBuffer(const std::size_t requiredSize, const std::size_t requiredAlignment)
	{
		PONY_LOG(Logger(), Log::LogType::Verbose, "Acquiring temp buffer... Size: '{}'; Alignment: '{}'.", requiredSize, requiredAlignment);

		if (requiredAlignment < alignof(std::max_align_t) || !std::has_single_bit(requiredAlignment)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid alignment");
		}

		TempBufferCache& cache = GetCache();
		Buffer buffer = GetBuffer(cache, requiredAlignment);
		if (const std::size_t size = std::max(requiredSize, 1024uz); buffer.size() < size) [[unlikely]]
		{
			PONY_LOG(Logger(), Log::LogType::Debug, "Growing temp buffer.");
			buffer.resize(size);
		}

		const auto tempBuffer = TempBuffer{.buffer = std::span(buffer.data(), buffer.size())};
		cache.usedBuffers.emplace(buffer.data(), std::move(buffer));

		PONY_LOG(Logger(), Log::LogType::Verbose, "Acquiring temp buffer done. Buffer: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(tempBuffer.buffer.data()));

		return tempBuffer;
	}

	void App::ReleaseTempBuffer(const TempBuffer tempBuffer) noexcept
	{
		PONY_LOG(Logger(), Log::LogType::Verbose, "Releasing temp buffer... Buffer: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(tempBuffer.buffer.data()));

		TempBufferCache& cache = GetCache();
		const auto position = cache.usedBuffers.find(tempBuffer.buffer.data());
		if (position == cache.usedBuffers.cend()) [[unlikely]]
		{
			PONY_LOG(Logger(), Log::LogType::Fatal, "TempBuffer memory corruption detected. Terminating.");
			std::terminate();
		}

		try
		{
			Buffer buffer = std::move(position->second);
			cache.usedBuffers.erase(position);
			cache.bufferCache.push(std::move(buffer));
		}
		catch (...)
		{
			PONY_LOG(Logger(), Log::LogType::Error, std::current_exception(), "On moving temp buffer from used to cache.");
		}

		PONY_LOG(Logger(), Log::LogType::Verbose, "Releasing temp buffer done.");
	}

	void App::Initialize()
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		PONY_LOG(Logger(), Log::LogType::Info, "Starting up application...");

		std::size_t earlyCount = 0uz;
		std::size_t normalCount = 0uz;
		std::size_t lateCount = 0uz;
		try
		{
			Initialize(earlyCount, normalCount, lateCount);
		}
		catch (...)
		{
			Finalize(earlyCount, normalCount, lateCount);
			throw;
		}

		PONY_LOG(Logger(), Log::LogType::Info, "Starting up application done.");
		PONY_LOG(Logger(), Log::LogType::Info, "{} {}", EngineName(), EngineVersion());
		PONY_LOG(Logger(), Log::LogType::Info, "Main thread: '{}'.", mainThreadId);
		PONY_LOG(Logger(), Log::LogType::Info, "Executable file: '{}'; Executable directory: '{}'; Root directory: '{}'.",
			executableFile.string(), executableDirectory.string(), rootDirectory.string());
		PONY_LOG(Logger(), Log::LogType::Info, "Local data directory: '{}'; User data directory: '{}'; Temp data directory: '{}'.",
			localDataDirectory.string(), userDataDirectory.string(), tempDataDirectory.string());
	}

	void App::Finalize() noexcept
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		PONY_LOG(Logger(), Log::LogType::Info, "Shutting down application...");
		Finalize(earlyModules.size(), normalModules.size(), lateModules.size());
		PONY_LOG(Logger(), Log::LogType::Info, "Shutting down application done.");
	}

	void App::Begin()
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		std::size_t count = 0uz;
		try
		{
			Begin(count);
		}
		catch (...)
		{
			End(count);
			throw;
		}
	}

	void App::End() noexcept
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");
		End(services.size());
	}

	bool App::HasLogger() const noexcept
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return logger != &emptyLogger;
	}

	void App::SetLogger(Log::ILogger& logger)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (HasLogger()) [[unlikely]]
		{
			throw std::logic_error("Logger was already added");
		}
#endif

		this->logger = &logger;
	}

	void App::UnsetLogger(const Log::ILogger& logger)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (this->logger != &logger) [[unlikely]]
		{
			throw std::logic_error("Another logger is set");
		}
#endif

		this->logger = &emptyLogger;
	}

	void App::AddService(IService& service)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (Flow().flowState > FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Invalid flow state");
		}

		if (std::ranges::find(services, &service) != services.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Service was already added");
		}
#endif

		PONY_LOG(Logger(), Log::LogType::Info, "Adding service. Service: '{}'.", typeid(service).name());
		services.push_back(&service);
	}

	void App::RemoveService(IService& service)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (const FlowState flowState = Flow().flowState; flowState > FlowState::StartingUp && flowState < FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Invalid flow state");
		}
#endif

		PONY_LOG(Logger(), Log::LogType::Info, "Removing service. Service: '{}'.", typeid(service).name());
		if (const auto position = std::ranges::find(services, &service); position != services.cend()) [[likely]]
		{
			services.erase(position);
		}
#ifndef NDEBUG
		else [[unlikely]]
		{
			throw std::invalid_argument("Service wasn't added");
		}
#endif
	}

	void App::AddInterface(const std::type_index type, void* const interface)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (Flow().flowState > FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Invalid flow state");
		}
#endif

		PONY_LOG(Logger(), Log::LogType::Info, "Adding interface. Type: '{}'; Address: '0x{:X}'.", type.name(), reinterpret_cast<std::uintptr_t>(interface));
		const auto [iterator, added] = interfaces.try_emplace(type, interface);
#ifndef NDEBUG
		if (!added) [[unlikely]]
		{
			throw std::invalid_argument("Interface is already added");
		}
#endif
	}

	template<typename T>
	void App::AddInterface(T& interface)
	{
		AddInterface(typeid(T), &interface);
	}

	void App::RemoveInterface(const std::type_index type, const void* const interface)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (const FlowState flowState = Flow().flowState; flowState > FlowState::StartingUp && flowState < FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Invalid flow state");
		}
#endif

		PONY_LOG(Logger(), Log::LogType::Info, "Removing interface. Type: '{}'; Address: '0x{:X}'.", type.name(), reinterpret_cast<std::uintptr_t>(interface));
		if (const auto position = interfaces.find(type); position != interfaces.cend() && position->second == interface) [[likely]]
		{
			interfaces.erase(position);
		}
#ifndef NDEBUG
		else [[unlikely]]
		{
			throw std::invalid_argument("Interface wasn't added");
		}
#endif
	}

	template<typename T>
	void App::RemoveInterface(T& interface)
	{
		RemoveInterface(typeid(T), &interface);
	}

	void App::AddTickable(ITickable& tickable, const std::int32_t order)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (Flow().flowState > FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Invalid flow state");
		}
#endif

		PONY_LOG(Logger(), Log::LogType::Info, "Adding tickable. Tickable: '{}'; Order: '{}'.", typeid(tickable).name(), order);
		tickables.emplace_back(&tickable, order);
	}

	void App::RemoveTickable(ITickable& tickable, const std::int32_t order)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (const FlowState flowState = Flow().flowState; flowState > FlowState::StartingUp && flowState < FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Invalid flow state");
		}
#endif

		PONY_LOG(Logger(), Log::LogType::Info, "Removing tickable. Tickable: '{}'; Order: '{}'.", typeid(tickable).name(), order);
		if (const auto position = std::ranges::find(tickables, std::pair(&tickable, order)); position != tickables.cend()) [[likely]]
		{
			tickables.erase(position);
		}
#ifndef NDEBUG
		else [[unlikely]]
		{
			throw std::invalid_argument("Tickable wasn't added");
		}
#endif
	}

	App::ModuleContext::ModuleContext(App& application) noexcept :
		application{&application}
	{
	}

	IApplication& App::ModuleContext::Application() noexcept
	{
		return *application;
	}

	const IApplication& App::ModuleContext::Application() const noexcept
	{
		return *application;
	}

	bool App::ModuleContext::HasLogger() const noexcept
	{
		return application->HasLogger();
	}

	void App::ModuleContext::SetLogger(Log::ILogger& logger)
	{
		application->SetLogger(logger);
	}

	void App::ModuleContext::UnsetLogger(Log::ILogger& logger)
	{
		application->UnsetLogger(logger);
	}

	void App::ModuleContext::AddService(IService& service)
	{
		application->AddService(service);
	}

	void App::ModuleContext::RemoveService(IService& service)
	{
		application->RemoveService(service);
	}

	void App::ModuleContext::AddInterface(const std::type_index type, void* const interface)
	{
		application->AddInterface(type, interface);
	}

	void App::ModuleContext::RemoveInterface(const std::type_index type, void* const interface)
	{
		application->RemoveInterface(type, interface);
	}

	void App::ModuleContext::AddTickable(ITickable& tickable, const std::int32_t order)
	{
		application->AddTickable(tickable, order);
	}

	void App::ModuleContext::RemoveTickable(ITickable& tickable, const std::int32_t order)
	{
		application->RemoveTickable(tickable, order);
	}

	void App::Initialize(std::size_t& earlyCount, std::size_t& normalCount, std::size_t& lateCount)
	{
		const FlowInfo currentFlow = flow.load(std::memory_order::relaxed);
		assert(currentFlow.flowState == FlowState::NotInitialized && "Invalid state.");
		flow.store(FlowInfo{.exitCode = currentFlow.exitCode, .flowState = FlowState::StartingUp}, std::memory_order::relaxed);

		auto context = ModuleContext(*this);

		PONY_LOG(Logger(), Log::LogType::Info, "Getting early modules...");
		GetModules(firstEarlyModule, lastEarlyModule, earlyModules);
		PONY_LOG(Logger(), Log::LogType::Info, "Getting early modules done.");
		PONY_LOG(Logger(), Log::LogType::Info, "Starting up early modules...");
		StartUpModules(earlyModules, earlyCount, context);
		PONY_LOG(Logger(), Log::LogType::Info, "Starting up early modules done.");
		PONY_LOG(Logger(), Log::LogType::Info, "Getting normal modules...");
		GetModules(firstNormalModule, lastNormalModule, normalModules);
		PONY_LOG(Logger(), Log::LogType::Info, "Getting normal modules done.");
		PONY_LOG(Logger(), Log::LogType::Info, "Starting up normal modules...");
		StartUpModules(normalModules, normalCount, context);
		PONY_LOG(Logger(), Log::LogType::Info, "Starting up normal modules done.");
		PONY_LOG(Logger(), Log::LogType::Info, "Getting late modules...");
		GetModules(firstLateModule, lastLateModule, lateModules);
		PONY_LOG(Logger(), Log::LogType::Info, "Getting late modules done.");
		PONY_LOG(Logger(), Log::LogType::Info, "Starting up late modules...");
		StartUpModules(lateModules, lateCount, context);
		PONY_LOG(Logger(), Log::LogType::Info, "Starting up late modules done.");

		flow.store(FlowInfo{.exitCode = currentFlow.exitCode, .flowState = FlowState::Beginning}, std::memory_order::relaxed);
	}

	void App::Finalize(const std::size_t earlyCount, const std::size_t normalCount, const std::size_t lateCount) noexcept
	{
		const FlowInfo currentFlow = flow.load(std::memory_order::relaxed);
		assert(currentFlow.flowState <= FlowState::Ending && "Invalid state.");
		flow.store(FlowInfo{.exitCode = currentFlow.exitCode, .flowState = FlowState::ShuttingDown}, std::memory_order::relaxed);
		
		auto context = ModuleContext(*this);

		PONY_LOG(Logger(), Log::LogType::Info, "Shutting down late modules...");
		ShutDownModules(lateModules, lateCount, context);
		PONY_LOG(Logger(), Log::LogType::Info, "Shutting down late modules done.");
		PONY_LOG(Logger(), Log::LogType::Info, "Shutting down normal modules...");
		ShutDownModules(normalModules, normalCount, context);
		PONY_LOG(Logger(), Log::LogType::Info, "Shutting down normal modules done.");
		PONY_LOG(Logger(), Log::LogType::Info, "Shutting down early modules...");
		ShutDownModules(earlyModules, earlyCount, context);
		PONY_LOG(Logger(), Log::LogType::Info, "Shutting down early modules done.");

		flow.store(FlowInfo{.exitCode = currentFlow.exitCode, .flowState = FlowState::Finalized}, std::memory_order::relaxed);
	}

	void App::Begin(std::size_t& count)
	{
		const FlowInfo currentFlow = flow.load(std::memory_order::relaxed);
		assert(currentFlow.flowState == FlowState::Beginning && "Invalid state.");
		flow.store(FlowInfo{.exitCode = currentFlow.exitCode, .flowState = FlowState::Beginning}, std::memory_order::relaxed);

		PONY_LOG(Logger(), Log::LogType::Info, "Beginning services...");
		for (IService* const service : services)
		{
			PONY_LOG(Logger(), Log::LogType::Info, "Beginning service... Service: '{}'.", typeid(*service).name());
			service->Begin();
			PONY_LOG(Logger(), Log::LogType::Info, "Beginning service done. Service: '{}'.", typeid(*service).name());
			++count;
		}
		PONY_LOG(Logger(), Log::LogType::Info, "Beginning services done.");

		PONY_LOG(Logger(), Log::LogType::Info, "Sorting tickables...");
		std::ranges::sort(tickables, std::less<std::int32_t>(), &std::pair<ITickable*, std::int32_t>::second);
		PONY_LOG(Logger(), Log::LogType::Info, "Sorting tickables done.");
		PONY_LOG(Logger(), Log::LogType::Debug, "Tickables order:");
		for (const auto [tickable, order] : tickables)
		{
			PONY_LOG(Logger(), Log::LogType::Debug, "{} : {}", typeid(*tickable).name(), order);
		}
		for (std::size_t i = 1uz; i < tickables.size(); ++i)
		{
			PONY_LOG_IF(tickables[i].second == tickables[i - 1uz].second, Logger(), Log::LogType::Warning,
				"Tickables '{}' and '{}' have the same order: '{}'.", typeid(*tickables[i].first).name(),
				typeid(*tickables[i - 1uz].first).name(), tickables[i].second);
		}
		PONY_LOG(Logger(), Log::LogType::Debug, "Tickables order end.");

		flow.store(FlowInfo{.exitCode = currentFlow.exitCode, .flowState = FlowState::Running}, std::memory_order::relaxed);
	}

	void App::End(const std::size_t count) noexcept
	{
		const FlowInfo currentFlow = flow.load(std::memory_order::relaxed);
		assert(currentFlow.flowState <= FlowState::Ending && "Invalid state.");
		flow.store(FlowInfo{.exitCode = currentFlow.exitCode, .flowState = FlowState::Ending}, std::memory_order::relaxed);

		PONY_LOG(Logger(), Log::LogType::Info, "Ending services...");
		for (std::size_t i = count; i-- > 0uz; )
		{
			IService* const service = services[i];

			try
			{
				PONY_LOG(Logger(), Log::LogType::Info, "Ending service... Service: '{}'.", typeid(*service).name());
				service->End();
				PONY_LOG(Logger(), Log::LogType::Info, "Ending service done. Service: '{}'.", typeid(*service).name());
			}
			catch (...)
			{
				PONY_LOG(Logger(), Log::LogType::Error, std::current_exception(), "On ending service. Service: '{}'.", typeid(*service).name());
			}
		}
		PONY_LOG(Logger(), Log::LogType::Info, "Ending services done.");

		flow.store(FlowInfo{ .exitCode = currentFlow.exitCode, .flowState = FlowState::ShuttingDown}, std::memory_order::relaxed);
	}

	App::TempBufferCache& App::GetCache()
	{
		thread_local auto cache = std::make_unique<TempBufferCache>();
		return *cache;
	}

	App::Buffer App::GetBuffer(TempBufferCache& cache, const std::size_t requiredAlignment) const
	{
		if (cache.bufferCache.empty()) [[unlikely]]
		{
			PONY_LOG(Logger(), Log::LogType::Debug, "Creating new temp buffer.");
			return Buffer(Container::AlignedAllocator<std::byte>(requiredAlignment));
		}

		Buffer buffer = std::move(cache.bufferCache.top());
		cache.bufferCache.pop();

		if (buffer.get_allocator().Alignment() < requiredAlignment) [[unlikely]]
		{
			PONY_LOG(Logger(), Log::LogType::Debug, "Realigning temp buffer.");
			buffer = Buffer(Container::AlignedAllocator<std::byte>(requiredAlignment));
		}

		return buffer;
	}

	void App::GetModules(const ModuleInterface firstModule, const ModuleInterface lastModule, std::vector<IModule*>& modules) const
	{
		for (std::uintptr_t current = reinterpret_cast<std::uintptr_t>(&firstModule) + sizeof(ModuleInterface);
			current < reinterpret_cast<std::uintptr_t>(&lastModule);
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
				PONY_LOG(Logger(), Log::LogType::Info, "Gotten module: '{}'.", typeid(*appModule).name());
				modules.push_back(appModule);
			}
		}
	}

	void App::StartUpModules(const std::span<IModule* const> modules, std::size_t& count, ModuleContext& context) const
	{
		for (IModule* const appModule : modules)
		{
			PONY_LOG(Logger(), Log::LogType::Info, "Starting up '{}' module...", typeid(*appModule).name());
			try
			{
				appModule->StartUp(context);
			}
			catch (...)
			{
				PONY_LOG(Logger(), Log::LogType::Error, std::current_exception(), "On starting up '{}' module.", typeid(*appModule).name());
				throw;
			}
			PONY_LOG(Logger(), Log::LogType::Info, "Starting up '{}' module done.", typeid(*appModule).name());
		}
	}

	void App::ShutDownModules(const std::span<IModule* const> modules, const std::size_t count, ModuleContext& context) const noexcept
	{
		for (std::size_t i = modules.size(); i-- > 0uz; )
		{
			IModule* const appModule = modules[i];
			PONY_LOG(Logger(), Log::LogType::Info, "Shutting down '{}' module...", typeid(*appModule).name());
			try
			{
				appModule->ShutDown(context);
			}
			catch (...)
			{
				PONY_LOG(Logger(), Log::LogType::Error, std::current_exception(), "On shutting down '{}' module.", typeid(*appModule).name());
			}
			PONY_LOG(Logger(), Log::LogType::Info, "Shutting down '{}' module done.", typeid(*appModule).name());
		}
	}

	App::FrameInfo App::ThisFrameInfo() const noexcept
	{
		return frameInfos[FrameCount() % frameInfos.size()];
	}
}

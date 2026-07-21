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
import PonyEngine.Format;
import PonyEngine.Log;

import :IdentityUtility;
import :PathUtility;

export namespace PonyEngine::Application
{
	/// @brief Application.
	/// @note The user must control the flow in a correct way. This class doesn't enforce it.
	class App final : public IApplication
	{
	public:
		/// @brief Creates an application.
		/// @param commandLine Command line.
		/// @param executableFile Executable file path.
		/// @param localDataDirectory Local data directory.
		/// @param userDataDirectory User data directory.
		/// @param tempDataDirectory Temporary data directory.
		[[nodiscard("Pure constructor")]]
		App(std::span<const std::string_view> commandLine, const std::filesystem::path& executableFile, const std::filesystem::path& localDataDirectory,
			const std::filesystem::path& userDataDirectory, const std::filesystem::path& tempDataDirectory);
		App(const App&) = delete;
		App(App&&) = delete;

		~App() noexcept = default;

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
		virtual std::optional<int> ExitCode() const override;
		virtual void Stop(int exitCode = 0) override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t FrameCount() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> StartTimePoint() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> PrevFrameTimePoint() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> ThisFrameTimePoint() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> NowTimePoint() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds PrevFrameTime() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds ThisFrameTime() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds NowTime() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds DeltaTime() const override;
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds TargetFrameTime() const override;
		virtual void TargetFrameTime(std::chrono::nanoseconds frameTime) override;

		[[nodiscard("Pure function")]] 
		virtual void* FindInterface(std::type_index type) const override;

		[[nodiscard("Pure function")]] 
		virtual TempBuffer AcquireTempBuffer(std::size_t requiredSize, std::size_t requiredAlignment) override;
		virtual void ReleaseTempBuffer(TempBuffer tempBuffer) noexcept override;

		/// @brief Initializes early modules.
		void InitializeEarly();
		/// @brief Finalizes early modules.
		void FinalizeEarly() noexcept;
		/// @brief Initializes normal modules.
		void InitializeNormal();
		/// @brief Finalizes normal modules.
		void FinalizeNormal() noexcept;
		/// @brief Initializes late modules.
		void InitializeLate();
		/// @brief Finalizes late modules.
		void FinalizeLate() noexcept;
		/// @brief Begins the main loop.
		void Begin();
		/// @brief Ends the main loop.
		void End() noexcept;
		/// @brief Begins a next frame.
		void BeginFrame();
		/// @brief Ends a current frame.
		void EndFrame();
		/// @brief Ticks a current frame.
		void Tick();

		/// @brief Tries to find an interface.
		/// @tparam T Interface type.
		/// @return Interface or nullptr if not found.
		/// @note Must be called on a main thread.
		template<typename T>
		T* FindInterface() const;
		/// @brief Adds the interface.
		/// @param type Interface type.
		/// @param interface Interface. Mustn't be nullptr.
		/// @note Must be called on a main thread.
		void AddInterface(std::type_index type, void* interface);
		/// @brief Adds the interface.
		/// @tparam T Interface type.
		/// @param interface Interface.
		/// @note Must be called on a main thread.
		template<typename T>
		void AddInterface(T& interface);
		/// @brief Removes the interface.
		/// @param type Interface type. Must be previously added.
		/// @param interface Interface.
		void RemoveInterface(std::type_index type, const void* interface);
		/// @brief Removes the interface.
		/// @tparam T Interface type. Must be previously added.
		/// @param interface Interface.
		template<typename T>
		void RemoveInterface(T& interface);

		/// @brief Adds the tickable.
		/// @param tickable Tickable.
		/// @param tickableOrder Tickable order.
		void AddTickable(ITickable& tickable, const TickableOrder& tickableOrder);
		/// @brief Removes the tickable.
		/// @param tickable Tickable. Must be previously added.
		/// @param tickableOrder Tickable order.
		void RemoveTickable(ITickable& tickable, const TickableOrder& tickableOrder);

		/// @brief Gets the log service.
		/// @return Log service.
		[[nodiscard("Pure function")]]
		const Log::ILogService* LogService() const noexcept;
		/// @brief Logs basic application info.
		void LogBasicInfo() const noexcept;

		/// @brief Gets the interfaces.
		/// @return Interfaces.
		[[nodiscard("Pure function")]]
		const std::unordered_map<std::type_index, void*>& Interfaces() const noexcept;
		/// @brief Gets the tickables.
		/// @return Tickables.
		[[nodiscard("Pure function")]]
		std::span<const std::pair<ITickable*, TickableOrder>> Tickables() const noexcept;

		App& operator =(const App&) = delete;
		App& operator =(App&) = delete;

	private:
		using Buffer = std::vector<std::byte, Container::AlignedAllocator<std::byte>>; ///< Buffer type.
		using ModuleGetter = IModule*(*)(); ///< Module getter function.

		PONY_EARLY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) static inline ModuleGetter firstEarlyModule = nullptr; ///< Early module begin pointer.
		PONY_EARLY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) static inline ModuleGetter lastEarlyModule = nullptr; ///< Early module end pointer.
		PONY_NORMAL_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) static inline ModuleGetter firstNormalModule = nullptr; ///< Normal module begin pointer.
		PONY_NORMAL_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) static inline ModuleGetter lastNormalModule = nullptr; ///< Normal module end pointer.
		PONY_LATE_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) static inline ModuleGetter firstLateModule = nullptr; ///< Late module begin pointer.
		PONY_LATE_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) static inline ModuleGetter lastLateModule = nullptr; ///< Late module end pointer.

		/// @brief Temp buffer cache.
		struct TempBufferCache final
		{
			std::stack<Buffer> bufferCache; ///< Buffer cache.
			std::unordered_map<const std::byte*, Buffer> usedBuffers; ///< Buffers that are in use now.
		};

		/// @brief Module context that is used during start-up.
		class StartUpModuleContext final : public IModuleContext
		{
		public:
			/// @brief Creates a module context.
			/// @param application Application.
			[[nodiscard("Pure constructor")]]
			explicit StartUpModuleContext(App& application) noexcept;
			StartUpModuleContext(const StartUpModuleContext&) = delete;
			StartUpModuleContext(StartUpModuleContext&&) = delete;

			~StartUpModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual IApplication& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const IApplication& Application() const noexcept override;

			virtual void AddInterface(std::type_index type, void* interface) override;
			virtual void RemoveInterface(std::type_index type, void* interface) override;

			virtual void AddTickable(ITickable& tickable, const TickableOrder& tickOrder) override;
			virtual void RemoveTickable(ITickable& tickable, const TickableOrder& tickOrder) override;

			StartUpModuleContext& operator =(const StartUpModuleContext&) = delete;
			StartUpModuleContext& operator =(StartUpModuleContext&&) = delete;

		private:
			App* application; ///< Application.
		};

		/// @brief Module context that is used during shut-down.
		class ShutDownModuleContext final : public IModuleContext
		{
		public:
			/// @brief Creates a module context.
			/// @param application Application.
			[[nodiscard("Pure constructor")]]
			explicit ShutDownModuleContext(App& application) noexcept;
			ShutDownModuleContext(const ShutDownModuleContext&) = delete;
			ShutDownModuleContext(ShutDownModuleContext&&) = delete;

			~ShutDownModuleContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual IApplication& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const IApplication& Application() const noexcept override;

			virtual void AddInterface(std::type_index type, void* interface) override;
			virtual void RemoveInterface(std::type_index type, void* interface) override;

			virtual void AddTickable(ITickable& tickable, const TickableOrder& tickOrder) override;
			virtual void RemoveTickable(ITickable& tickable, const TickableOrder& tickOrder) override;

			ShutDownModuleContext& operator =(const ShutDownModuleContext&) = delete;
			ShutDownModuleContext& operator =(ShutDownModuleContext&&) = delete;

		private:
			App* application; ///< Application.
		};

		/// @brief Make a single string out of the command line arguments.
		/// @return Command line string. It starts with a space.
		[[nodiscard("Pure function")]]
		std::string MakeCommandLineString() const;

		/// @brief Gets modules.
		/// @param firstModule First module getter.
		/// @param lastModule Last module getter.
		/// @param modules Module list to add to.
		void GetModules(ModuleGetter firstModule, ModuleGetter lastModule, std::vector<IModule*>& modules) const;
		/// @brief Starts up the modules.
		/// @param modules Modules to start-up.
		/// @param count How many modules are started-up.
		void StartUpModules(std::span<IModule* const> modules, std::size_t& count);
		/// @brief Shuts down the modules.
		/// @param modules Modules to shut down.
		/// @param count How many modules to shut down.
		void ShutDownModules(std::span<IModule* const> modules, std::size_t count) noexcept;

		/// @brief Updates the list of begin tickables.
		void UpdateBeginTickables();
		/// @brief Updates the list of tick tickables.
		void UpdateTickTickables();
		/// @brief Updates the tickables.
		/// @param targetTickables Target tickable list.
		/// @param tickableOrderGetter Tickable order getter.
		void UpdateTickables(std::vector<ITickable*>& targetTickables, const std::function<std::optional<std::int32_t>(const TickableOrder&)>& tickableOrderGetter);
		/// @brief Logs the tickable list.
		/// @param tickables Tickable list to log.
		void LogTickableList(std::span<const ITickable* const> tickables) const noexcept;

		/// @brief Begins the tickables.
		/// @param count How many tickables were begun.
		void Begin(std::size_t& count) const;
		/// @brief Ends the tickables.
		/// @param count How many tickables to end.
		void End(std::size_t count) noexcept;

		/// @brief Gets a temp buffer cache for this thread.
		/// @return Temp buffer cache.
		[[nodiscard("Pure function")]]
		static TempBufferCache& GetCache();
		/// @brief Gets a suitable buffer.
		/// @param cache Buffer cache.
		/// @param requiredAlignment Required alignment.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		Buffer GetBuffer(TempBufferCache& cache, std::size_t requiredAlignment) const;

		std::thread::id mainThreadId; ///< Main thread ID. It's a thread on which this class was created.
		std::span<const std::string_view> commandLine; ///< Command line.

		std::filesystem::path executableFile; ///< Path to the executable.
		std::filesystem::path executableDirectory; ///< Executable directory.
		std::filesystem::path rootDirectory; ///< Root directory.
		std::filesystem::path localDataDirectory; ///< Local data directory.
		std::filesystem::path userDataDirectory; ///< User data directory.
		std::filesystem::path tempDataDirectory; ///< Temporal data directory.

		std::optional<int> exitCode; ///< Exit code.
		std::uint64_t frameCount; ///< Frame count.
		std::chrono::time_point<std::chrono::steady_clock> startTimePoint; ///< Start time point.
		std::chrono::time_point<std::chrono::steady_clock> prevFrameTimePoint; ///< Previous frame time point.
		std::chrono::time_point<std::chrono::steady_clock> thisFrameTimePoint; ///< This frame time point.
		std::chrono::nanoseconds targetFrameTime; ///< Target frame time. It's the minimum time that must pass between frame begins.

		std::vector<IModule*> earlyModules; ///< Early modules.
		std::vector<IModule*> normalModules; ///< Normal modules.
		std::vector<IModule*> lateModules; ///< Late modules.

		Log::ILogService* logService; ///< Log service.

		std::unordered_map<std::type_index, void*> interfaces; ///< Interfaces.
		std::vector<std::pair<ITickable*, TickableOrder>> tickables; ///< Tickables.
		std::vector<ITickable*> beginTickables; ///< Tickables with Begin() and End() functions.
		std::vector<ITickable*> tickTickables; ///< Tickables with Tick() function.
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
		exitCode(std::nullopt),
		frameCount{0ull},
		startTimePoint(NowTimePoint()),
		prevFrameTimePoint(startTimePoint),
		thisFrameTimePoint(startTimePoint),
		targetFrameTime(std::chrono::nanoseconds(0)),
		logService{nullptr}
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

	std::optional<int> App::ExitCode() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return exitCode;
	}

	void App::Stop(const int exitCode)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		if (this->exitCode)
		{
			PONY_LOG(logService, Log::LogType::Debug, "Tried to stop already stopped application. Ignoring.");
		}
		else
		{
			this->exitCode = exitCode;
			PONY_LOG(logService, Log::LogType::Info, "Application stopped. Exit code: '{}'.", *this->exitCode);
		}
	}

	std::uint64_t App::FrameCount() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return frameCount;
	}

	std::chrono::time_point<std::chrono::steady_clock> App::StartTimePoint() const noexcept
	{
		return startTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> App::PrevFrameTimePoint() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return prevFrameTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> App::ThisFrameTimePoint() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return thisFrameTimePoint;
	}

	std::chrono::time_point<std::chrono::steady_clock> App::NowTimePoint() const noexcept
	{
		return std::chrono::steady_clock::now();
	}

	std::chrono::nanoseconds App::PrevFrameTime() const
	{
		return PrevFrameTimePoint() - startTimePoint;
	}

	std::chrono::nanoseconds App::ThisFrameTime() const
	{
		return ThisFrameTimePoint() - startTimePoint;
	}

	std::chrono::nanoseconds App::NowTime() const noexcept
	{
		return NowTimePoint() - startTimePoint;
	}

	std::chrono::nanoseconds App::DeltaTime() const
	{
		return ThisFrameTimePoint() - PrevFrameTimePoint();
	}

	std::chrono::nanoseconds App::TargetFrameTime() const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		return targetFrameTime;
	}

	void App::TargetFrameTime(const std::chrono::nanoseconds frameTime)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		targetFrameTime = std::max(frameTime, std::chrono::nanoseconds(0));

		PONY_LOG(logService, Log::LogType::Info, "Target frame time changed to: '{}'.", targetFrameTime);
	}

	void* App::FindInterface(const std::type_index type) const
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		if (const auto position = interfaces.find(type); position != interfaces.cend()) [[likely]]
		{
			return position->second;
		}

		return nullptr;
	}

	TempBuffer App::AcquireTempBuffer(const std::size_t requiredSize, const std::size_t requiredAlignment)
	{
		PONY_LOG(logService, Log::LogType::Verbose, "Acquiring temp buffer... Size: '{}'; Alignment: '{}'.", requiredSize, requiredAlignment);

		if (requiredAlignment < alignof(std::max_align_t) || !std::has_single_bit(requiredAlignment)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid alignment");
		}

		TempBufferCache& cache = GetCache();
		Buffer buffer = GetBuffer(cache, requiredAlignment);
		if (const std::size_t size = std::max(requiredSize, 1024uz); buffer.size() < size) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Debug, "Growing temp buffer.");
			buffer.resize(size);
		}

		const auto tempBuffer = TempBuffer{.buffer = std::span(buffer.data(), buffer.size())};
		cache.usedBuffers.emplace(buffer.data(), std::move(buffer));

		PONY_LOG(logService, Log::LogType::Verbose, "Acquiring temp buffer done. Buffer: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(tempBuffer.buffer.data()));

		return tempBuffer;
	}

	void App::ReleaseTempBuffer(const TempBuffer tempBuffer) noexcept
	{
		PONY_LOG(logService, Log::LogType::Verbose, "Releasing temp buffer... Buffer: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(tempBuffer.buffer.data()));

		TempBufferCache& cache = GetCache();
		const auto position = cache.usedBuffers.find(tempBuffer.buffer.data());
		if (position == cache.usedBuffers.cend()) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Fatal, "TempBuffer memory corruption detected. Terminating.");
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
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On moving temp buffer from used to cache.");
		}

		PONY_LOG(logService, Log::LogType::Verbose, "Releasing temp buffer done.");
	}

	void App::InitializeEarly()
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		PONY_LOG(logService, Log::LogType::Info, "Initializing early modules...");

		std::size_t count = 0uz;
		try
		{
			PONY_LOG(logService, Log::LogType::Info, "Getting early modules...");
			GetModules(firstEarlyModule, lastEarlyModule, earlyModules);
			PONY_LOG(logService, Log::LogType::Info, "Getting early modules done.");
			PONY_LOG(logService, Log::LogType::Info, "Starting up early modules...");
			StartUpModules(earlyModules, count);
			PONY_LOG(logService, Log::LogType::Info, "Starting up early modules done.");
		}
		catch (...)
		{
			ShutDownModules(earlyModules, count);
			throw;
		}

		PONY_LOG(logService, Log::LogType::Info, "Initializing early modules done.");

		logService = FindInterface<Log::ILogService>();
		LogBasicInfo();
	}

	void App::FinalizeEarly() noexcept
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		logService = nullptr;

		PONY_LOG(logService, Log::LogType::Info, "Shutting down early modules...");
		ShutDownModules(earlyModules, earlyModules.size());
		PONY_LOG(logService, Log::LogType::Info, "Shutting down early modules done.");
	}

	void App::InitializeNormal()
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		PONY_LOG(logService, Log::LogType::Info, "Initializing normal modules...");

		std::size_t count = 0uz;
		try
		{
			PONY_LOG(logService, Log::LogType::Info, "Getting normal modules...");
			GetModules(firstNormalModule, lastNormalModule, normalModules);
			PONY_LOG(logService, Log::LogType::Info, "Getting normal modules done.");
			PONY_LOG(logService, Log::LogType::Info, "Starting up normal modules...");
			StartUpModules(normalModules, count);
			PONY_LOG(logService, Log::LogType::Info, "Starting up normal modules done.");
		}
		catch (...)
		{
			ShutDownModules(normalModules, count);
			throw;
		}

		PONY_LOG(logService, Log::LogType::Info, "Initializing normal modules done.");
	}

	void App::FinalizeNormal() noexcept
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		PONY_LOG(logService, Log::LogType::Info, "Shutting down normal modules...");
		ShutDownModules(normalModules, normalModules.size());
		PONY_LOG(logService, Log::LogType::Info, "Shutting down normal modules done.");
	}

	void App::InitializeLate()
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		PONY_LOG(logService, Log::LogType::Info, "Initializing late modules...");

		std::size_t count = 0uz;
		try
		{
			PONY_LOG(logService, Log::LogType::Info, "Getting late modules...");
			GetModules(firstLateModule, lastLateModule, lateModules);
			PONY_LOG(logService, Log::LogType::Info, "Getting late modules done.");
			PONY_LOG(logService, Log::LogType::Info, "Starting up late modules...");
			StartUpModules(lateModules, count);
			PONY_LOG(logService, Log::LogType::Info, "Starting up late modules done.");
		}
		catch (...)
		{
			ShutDownModules(lateModules, count);
			throw;
		}

		PONY_LOG(logService, Log::LogType::Info, "Initializing late modules done.");
	}

	void App::FinalizeLate() noexcept
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		PONY_LOG(logService, Log::LogType::Info, "Shutting down late modules...");
		ShutDownModules(lateModules, lateModules.size());
		PONY_LOG(logService, Log::LogType::Info, "Shutting down late modules done.");
	}

	void App::Begin()
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");

		tickables.shrink_to_fit();
		UpdateBeginTickables();
		UpdateTickTickables();

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

		End(beginTickables.size());
	}

	void App::BeginFrame()
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");
		assert(!exitCode && "The exit code is set.");

		++frameCount;

		prevFrameTimePoint = thisFrameTimePoint;
		std::chrono::time_point<std::chrono::steady_clock> now;
		do
		{
			now = NowTimePoint();
		} while (now - prevFrameTimePoint < targetFrameTime);
		thisFrameTimePoint = now;

		PONY_LOG(logService, Log::LogType::Verbose, "New frame began. Frame: '{}'; Time point: '{}'.", frameCount, thisFrameTimePoint.time_since_epoch());
	}

	void App::EndFrame()
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");
	}

	void App::Tick()
	{
		assert(std::this_thread::get_id() == mainThreadId && "Wrong thread.");
		assert(!exitCode && "The exit code is set.");

		PONY_LOG(logService, Log::LogType::Verbose, "Ticking tickables...");
		for (ITickable* const tickable : tickTickables)
		{
			PONY_LOG(logService, Log::LogType::Verbose, "Ticking '{}'...", typeid(*tickable).name());
			tickable->Tick();
			PONY_LOG(logService, Log::LogType::Verbose, "Ticking '{}' done.", typeid(*tickable).name());
		}
		PONY_LOG(logService, Log::LogType::Verbose, "Ticking tickables done.");
	}

	void App::AddInterface(const std::type_index type, void* const interface)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		PONY_LOG(logService, Log::LogType::Info, "Adding interface. Type: '{}'; Address: '0x{:X}'.", type.name(), reinterpret_cast<std::uintptr_t>(interface));
		const auto [iterator, added] = interfaces.try_emplace(type, interface);
#ifndef NDEBUG
		if (!added) [[unlikely]]
		{
			throw std::invalid_argument("Interface is already added");
		}
#endif
	}

	template<typename T>
	T* App::FindInterface() const
	{
		return static_cast<T*>(FindInterface(typeid(T)));
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
#endif

		PONY_LOG(logService, Log::LogType::Info, "Removing interface. Type: '{}'; Address: '0x{:X}'.", type.name(), reinterpret_cast<std::uintptr_t>(interface));
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

	void App::AddTickable(ITickable& tickable, const TickableOrder& tickableOrder)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		PONY_LOG(logService, Log::LogType::Info, "Adding tickable. Tickable: '{}'; Begin order: '{}'; Tick order: '{}'.", typeid(tickable).name(), 
			tickableOrder.beginOrder, tickableOrder.tickOrder);
		tickables.emplace_back(&tickable, tickableOrder);
	}

	void App::RemoveTickable(ITickable& tickable, const TickableOrder& tickableOrder)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != mainThreadId) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		PONY_LOG(logService, Log::LogType::Info, "Removing tickable. Tickable: '{}'; Begin order: '{}'; Tick order: '{}'.", typeid(tickable).name(),
			tickableOrder.beginOrder, tickableOrder.tickOrder);
		if (const auto position = std::ranges::find(tickables, std::pair(&tickable, tickableOrder)); position != tickables.cend()) [[likely]]
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

	const Log::ILogService* App::LogService() const noexcept
	{
		return logService;
	}

	void App::LogBasicInfo() const noexcept
	{
		try
		{
			PONY_LOG(logService, Log::LogType::Info, "{} v{}", EngineTitle(), EngineVersion());
			PONY_LOG(logService, Log::LogType::Info, "{} v{}", ProjectTitle(), ProjectVersion());
			PONY_LOG(logService, Log::LogType::Info, "Main thread ID: '{}'.", mainThreadId);
			PONY_LOG(logService, Log::LogType::Info, "Command line:{}", MakeCommandLineString());

			PONY_LOG(logService, Log::LogType::Info, "Executable path: '{}'; Executable directory: '{}'; Root directory: '{}'.",
				executableFile.string(), executableDirectory.string(), rootDirectory.string());
			PONY_LOG(logService, Log::LogType::Info, "Local data directory: '{}'; User data directory: '{}'; Temp data directory: '{}'.",
				localDataDirectory.string(), userDataDirectory.string(), tempDataDirectory.string());
			PONY_LOG(logService, Log::LogType::Info, "Working directory: '{}'.", std::filesystem::current_path().string());

			PONY_LOG(logService, Log::LogType::Info, "Engine start time point: '{}'.", startTimePoint.time_since_epoch());
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On logging basic info.");
			// Strange but it's ok to ignore.
		}
	}

	const std::unordered_map<std::type_index, void*>& App::Interfaces() const noexcept
	{
		return interfaces;
	}

	std::span<const std::pair<ITickable*, TickableOrder>> App::Tickables() const noexcept
	{
		return tickables;
	}

	App::StartUpModuleContext::StartUpModuleContext(App& application) noexcept :
		application{&application}
	{
	}

	IApplication& App::StartUpModuleContext::Application() noexcept
	{
		return *application;
	}

	const IApplication& App::StartUpModuleContext::Application() const noexcept
	{
		return *application;
	}

	void App::StartUpModuleContext::AddInterface(const std::type_index type, void* const interface)
	{
		application->AddInterface(type, interface);
	}

	void App::StartUpModuleContext::RemoveInterface(const std::type_index type, void* const interface)
	{
		application->RemoveInterface(type, interface);
	}

	void App::StartUpModuleContext::AddTickable(ITickable& tickable, const TickableOrder& tickOrder)
	{
		application->AddTickable(tickable, tickOrder);
	}

	void App::StartUpModuleContext::RemoveTickable(ITickable& tickable, const TickableOrder& tickOrder)
	{
		application->RemoveTickable(tickable, tickOrder);
	}

	App::ShutDownModuleContext::ShutDownModuleContext(App& application) noexcept :
		application{&application}
	{
	}

	IApplication& App::ShutDownModuleContext::Application() noexcept
	{
		return *application;
	}

	const IApplication& App::ShutDownModuleContext::Application() const noexcept
	{
		return *application;
	}

	void App::ShutDownModuleContext::AddInterface(const std::type_index type, void* const interface)
	{
		throw std::logic_error("Can't add interface during shut-down");
	}

	void App::ShutDownModuleContext::RemoveInterface(const std::type_index type, void* const interface)
	{
		application->RemoveInterface(type, interface);
	}

	void App::ShutDownModuleContext::AddTickable(ITickable& tickable, const TickableOrder& tickOrder)
	{
		throw std::logic_error("Can't add tickable during shut-down");
	}

	void App::ShutDownModuleContext::RemoveTickable(ITickable& tickable, const TickableOrder& tickOrder)
	{
		application->RemoveTickable(tickable, tickOrder);
	}

	std::string App::MakeCommandLineString() const
	{
		std::string commandLineString;
		for (const std::string_view command : commandLine)
		{
			const bool hasSpaces = command.find(' ') != std::string_view::npos;

			commandLineString += ' ';
			if (hasSpaces)
			{
				commandLineString += '"';
			}
			commandLineString += command;
			if (hasSpaces)
			{
				commandLineString += '"';
			}
		}

		return commandLineString;
	}

	void App::GetModules(const ModuleGetter firstModule, const ModuleGetter lastModule, std::vector<IModule*>& modules) const
	{
		for (std::uintptr_t current = reinterpret_cast<std::uintptr_t>(&firstModule) + sizeof(ModuleGetter);
			current < reinterpret_cast<std::uintptr_t>(&lastModule);
			current += sizeof(ModuleGetter))
		{
			if (const auto moduleGetter = *reinterpret_cast<ModuleGetter*>(current))
			{
				IModule* const appModule = moduleGetter();
#ifndef NDEBUG
				if (!appModule) [[unlikely]]
				{
					throw std::logic_error("Module is nullptr");
				}
#endif
				PONY_LOG(logService, Log::LogType::Info, "Gotten module: '{}'.", typeid(*appModule).name());
				modules.push_back(appModule);
			}
		}

		modules.shrink_to_fit();
	}

	void App::StartUpModules(const std::span<IModule* const> modules, std::size_t& count)
	{
		for (auto context = StartUpModuleContext(*this); IModule* const appModule : modules)
		{
			PONY_LOG(logService, Log::LogType::Info, "Starting up '{}' module...", typeid(*appModule).name());
			try
			{
				appModule->StartUp(context);
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On starting up '{}' module.", typeid(*appModule).name());
				throw;
			}
			PONY_LOG(logService, Log::LogType::Info, "Starting up '{}' module done.", typeid(*appModule).name());
		}
	}

	void App::ShutDownModules(const std::span<IModule* const> modules, const std::size_t count) noexcept
	{
		auto context = ShutDownModuleContext(*this);
		for (std::size_t i = modules.size(); i-- > 0uz; )
		{
			IModule* const appModule = modules[i];
			PONY_LOG(logService, Log::LogType::Info, "Shutting down '{}' module...", typeid(*appModule).name());
			try
			{
				appModule->ShutDown(context);
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On shutting down '{}' module.", typeid(*appModule).name());
			}
			PONY_LOG(logService, Log::LogType::Info, "Shutting down '{}' module done.", typeid(*appModule).name());
		}
	}

	void App::UpdateBeginTickables()
	{
		PONY_LOG(logService, Log::LogType::Info, "Updating begin order...");
		UpdateTickables(beginTickables, [](const TickableOrder& order) { return order.beginOrder; });
		PONY_LOG(logService, Log::LogType::Info, "Updating begin order done. Order:");
		LogTickableList(beginTickables);
	}

	void App::UpdateTickTickables()
	{
		PONY_LOG(logService, Log::LogType::Info, "Updating tick order...");
		UpdateTickables(tickTickables, [](const TickableOrder& order) { return order.tickOrder; });
		PONY_LOG(logService, Log::LogType::Info, "Updating tick order done. Order:");
		LogTickableList(tickTickables);
	}

	void App::UpdateTickables(std::vector<ITickable*>& targetTickables, const std::function<std::optional<std::int32_t>(const TickableOrder&)>& tickableOrderGetter)
	{
		auto indices = std::vector<std::size_t>();
		indices.reserve(tickables.size());
		for (std::size_t i = 0uz; i < tickables.size(); ++i)
		{
			if (tickableOrderGetter(tickables[i].second))
			{
				indices.push_back(i);
			}
		}

		std::ranges::sort(indices, [&](const std::size_t lhs, const std::size_t rhs)
		{
			return *tickableOrderGetter(tickables[lhs].second) < *tickableOrderGetter(tickables[rhs].second);
		});

		for (std::size_t i = 1uz; i < indices.size(); ++i)
		{
			const auto [tickableLhs, orderLhs] = tickables[indices[i]];
			const auto [tickableRhs, orderRhs] = tickables[indices[i - 1uz]];
			const std::int32_t orderNumberLhs = *tickableOrderGetter(orderLhs);
			const std::int32_t orderNumberRhs = *tickableOrderGetter(orderRhs);

			PONY_LOG_IF(orderNumberLhs == orderNumberRhs, logService, Log::LogType::Warning,
				"Tickables '{}' and '{}' have the same order: '{}'.", typeid(*tickableLhs).name(), typeid(*tickableRhs).name(), orderNumberLhs);
		}

		targetTickables.clear();
		targetTickables.reserve(indices.size());
		for (const std::size_t i : indices)
		{
			targetTickables.push_back(tickables[i].first);
		}
	}

	void App::LogTickableList(const std::span<const ITickable* const> tickables) const noexcept
	{
		for (const ITickable* const tickable : tickables)
		{
			PONY_LOG(logService, Log::LogType::Info, "{}", typeid(*tickable).name());
		}
	}

	void App::Begin(std::size_t& count) const
	{
		PONY_LOG(logService, Log::LogType::Info, "Beginning tickables...")

		for (ITickable* const tickable : beginTickables)
		{
			try
			{
				PONY_LOG(logService, Log::LogType::Info, "Beginning '{}'...", typeid(*tickable).name());
				tickable->Begin();
				PONY_LOG(logService, Log::LogType::Info, "Beginning '{}' done.", typeid(*tickable).name());
				++count;
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On beginning tickable '{}'.", typeid(*tickable).name());
				throw;
			}
		}

		PONY_LOG(logService, Log::LogType::Info, "Beginning tickables done.")
	}

	void App::End(const std::size_t count) noexcept
	{
		PONY_LOG(logService, Log::LogType::Info, "Ending tickables...")

		for (std::size_t i = count; i-- > 0uz; )
		{
			ITickable* const tickable = beginTickables[i];

			try
			{
				tickable->End();
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On ending tickable '{}'.", typeid(*tickable).name());
			}
		}

		PONY_LOG(logService, Log::LogType::Info, "Ending tickables done.")

		beginTickables.clear();
		tickTickables.clear();
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
			PONY_LOG(logService, Log::LogType::Debug, "Creating new temp buffer.");
			return Buffer(Container::AlignedAllocator<std::byte>(requiredAlignment));
		}

		Buffer buffer = std::move(cache.bufferCache.top());
		cache.bufferCache.pop();

		if (buffer.get_allocator().Alignment() < requiredAlignment) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Debug, "Realigning temp buffer.");
			buffer = Buffer(Container::AlignedAllocator<std::byte>(requiredAlignment));
		}

		return buffer;
	}
}

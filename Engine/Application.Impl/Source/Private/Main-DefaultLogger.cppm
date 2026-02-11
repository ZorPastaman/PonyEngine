/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Impl:DefaultLogger;

import std;

import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Default logger that writes everything to a console if it's enabled.
	class DefaultLogger : public Log::ILogger
	{
	public:
		DefaultLogger(const DefaultLogger&) = delete;
		DefaultLogger(DefaultLogger&&) = delete;

		virtual ~DefaultLogger() noexcept = default;

		virtual void Log(Log::LogType logType, std::string_view message) const noexcept override final;
		virtual void Log(Log::LogType logType, std::string_view message, const std::stacktrace& stacktrace) const noexcept override final;
		virtual void Log(Log::LogType logType, std::string_view format, std::format_args formatArgs) const noexcept override final;
		virtual void Log(Log::LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override final;

		virtual void Log(const std::exception_ptr& exception) const noexcept override final;
		virtual void Log(const std::exception_ptr& exception, std::string_view message) const noexcept override final;
		virtual void Log(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) const noexcept override final;
		virtual void Log(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept override final;
		virtual void Log(const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept override final;
		virtual void Log(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override final;

		DefaultLogger& operator =(const DefaultLogger&) = delete;
		DefaultLogger& operator =(DefaultLogger&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		DefaultLogger() noexcept = default;

		/// @brief Logs to a console.
		/// @param logType Log type.
		/// @param message Log message.
		virtual void LogToConsole(Log::LogType logType, std::string_view message) const noexcept = 0;

	private:
		/// @brief Logs to a console.
		/// @param logType Log type.
		/// @param message Log message.
		void LogInternal(Log::LogType logType, std::string_view message) const noexcept;

		static constexpr std::string_view AllocationError = "Log message allocation failed."; ///< Allocation error message.
		static constexpr std::string_view UnknownException = "Unknown exception."; ///< Unknown exception without a new line text.
		static constexpr std::string_view NullptrException = "Nullptr exception."; ///< Nullptr exception text.

		static inline thread_local std::string stringTemp; ///< Temporal string.
		mutable std::mutex logMutex; ///< Log mutex.
	};
}

namespace PonyEngine::Application
{
	void DefaultLogger::Log(const Log::LogType logType, const std::string_view message) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			stringTemp.clear();
			std::format_to(std::back_inserter(stringTemp), "{}: {}\n", logType, message);
			LogInternal(logType, stringTemp);
		}
		catch (...)
		{
			LogInternal(logType, AllocationError);
		}
#endif
	}

	void DefaultLogger::Log(const Log::LogType logType, const std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			stringTemp.clear();
			std::format_to(std::back_inserter(stringTemp), "{}: {}\n{}\n", logType, message, stacktrace);
			LogToConsole(logType, stringTemp);
		}
		catch (...)
		{
			LogInternal(logType, AllocationError);
		}
#endif
	}

	void DefaultLogger::Log(const Log::LogType logType, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			stringTemp.clear();
			std::format_to(std::back_inserter(stringTemp), "{}: ", logType);
			std::vformat_to(std::back_inserter(stringTemp), format, formatArgs);
			stringTemp.push_back('\n');
			LogToConsole(logType, stringTemp);
		}
		catch (...)
		{
			LogInternal(logType, AllocationError);
		}
#endif
	}

	void DefaultLogger::Log(const Log::LogType logType, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			stringTemp.clear();
			std::format_to(std::back_inserter(stringTemp), "{}: ", logType);
			std::vformat_to(std::back_inserter(stringTemp), format, formatArgs);
			std::format_to(std::back_inserter(stringTemp), "\n{}\n", stacktrace);
			LogToConsole(logType, stringTemp);
		}
		catch (...)
		{
			LogInternal(logType, AllocationError);
		}
#endif
	}

	void DefaultLogger::Log(const std::exception_ptr& exception) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			if (!exception) [[unlikely]]
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {}\n", Log::LogType::Exception, NullptrException);
				LogToConsole(Log::LogType::Exception, stringTemp);
				return;
			}

			try
			{
				std::rethrow_exception(exception);
			}
			catch (const std::exception& e)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {}\n", Log::LogType::Exception, e.what());
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
			catch (...)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {}\n", Log::LogType::Exception, UnknownException);
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
		}
		catch (...)
		{
			LogInternal(Log::LogType::Exception, AllocationError);
		}
#endif
	}

	void DefaultLogger::Log(const std::exception_ptr& exception, std::string_view message) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			if (!exception) [[unlikely]]
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - {}\n", Log::LogType::Exception, NullptrException, message);
				LogToConsole(Log::LogType::Exception, stringTemp);
				return;
			}

			try
			{
				std::rethrow_exception(exception);
			}
			catch (const std::exception& e)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - {}\n", Log::LogType::Exception, e.what(), message);
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
			catch (...)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - {}\n", Log::LogType::Exception, UnknownException, message);
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
		}
		catch (...)
		{
			LogInternal(Log::LogType::Exception, AllocationError);
		}
#endif
	}

	void DefaultLogger::Log(const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			if (!exception) [[unlikely]]
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - ", Log::LogType::Exception, NullptrException);
				std::vformat_to(std::back_inserter(stringTemp), format, formatArgs);
				stringTemp.push_back('\n');
				LogToConsole(Log::LogType::Exception, stringTemp);
				return;
			}

			try
			{
				std::rethrow_exception(exception);
			}
			catch (const std::exception& e)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - ", Log::LogType::Exception, e.what());
				std::vformat_to(std::back_inserter(stringTemp), format, formatArgs);
				stringTemp.push_back('\n');
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
			catch (...)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - ", Log::LogType::Exception, UnknownException);
				std::vformat_to(std::back_inserter(stringTemp), format, formatArgs);
				stringTemp.push_back('\n');
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
		}
		catch (...)
		{
			LogInternal(Log::LogType::Exception, AllocationError);
		}
#endif
	}

	void DefaultLogger::Log(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			if (!exception) [[unlikely]]
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {}\n{}\n", Log::LogType::Exception, NullptrException, stacktrace);
				LogToConsole(Log::LogType::Exception, stringTemp);
				return;
			}

			try
			{
				std::rethrow_exception(exception);
			}
			catch (const std::exception& e)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {}\n{}\n", Log::LogType::Exception, e.what(), stacktrace);
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
			catch (...)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {}\n{}\n", Log::LogType::Exception, UnknownException, stacktrace);
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
		}
		catch (...)
		{
			LogInternal(Log::LogType::Exception, AllocationError);
		}
#endif
	}

	void DefaultLogger::Log(const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			if (!exception) [[unlikely]]
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - {}\n{}\n", Log::LogType::Exception, NullptrException, message, stacktrace);
				LogToConsole(Log::LogType::Exception, stringTemp);
				return;
			}

			try
			{
				std::rethrow_exception(exception);
			}
			catch (const std::exception& e)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - {}\n{}\n", Log::LogType::Exception, e.what(), message, stacktrace);
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
			catch (...)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - {}\n{}\n", Log::LogType::Exception, UnknownException, message, stacktrace);
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
		}
		catch (...)
		{
			LogInternal(Log::LogType::Exception, AllocationError);
		}
#endif
	}

	void DefaultLogger::Log(const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept
	{
#if PONY_ENGINE_DEFAULT_LOGGER
		try
		{
			if (!exception) [[unlikely]]
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - ", Log::LogType::Exception, NullptrException);
				std::vformat_to(std::back_inserter(stringTemp), format, formatArgs);
				std::format_to(std::back_inserter(stringTemp), "\n{}\n", stacktrace);
				LogToConsole(Log::LogType::Exception, stringTemp);
				return;
			}

			try
			{
				std::rethrow_exception(exception);
			}
			catch (const std::exception& e)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - ", Log::LogType::Exception, e.what());
				std::vformat_to(std::back_inserter(stringTemp), format, formatArgs);
				std::format_to(std::back_inserter(stringTemp), "\n{}\n", stacktrace);
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
			catch (...)
			{
				stringTemp.clear();
				std::format_to(std::back_inserter(stringTemp), "{}: {} - ", Log::LogType::Exception, UnknownException);
				std::vformat_to(std::back_inserter(stringTemp), format, formatArgs);
				std::format_to(std::back_inserter(stringTemp), "\n{}\n", stacktrace);
				LogToConsole(Log::LogType::Exception, stringTemp);
			}
		}
		catch (...)
		{
			LogInternal(Log::LogType::Exception, AllocationError);
		}
#endif
	}

	void DefaultLogger::LogInternal(const Log::LogType logType, const std::string_view message) const noexcept
	{
		const auto lock = std::lock_guard(logMutex);
		LogToConsole(logType, message);
	}
}

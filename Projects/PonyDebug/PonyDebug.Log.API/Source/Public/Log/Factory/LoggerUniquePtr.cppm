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

export module PonyDebug.Log.Factory:LoggerUniquePtr;

import <concepts>;
import <memory>;
import <utility>;

import :ILoggerDestroyer;

namespace PonyDebug::Log
{
	/// @brief Logger deleter.
	class LoggerDeleter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		LoggerDeleter() noexcept = default;
		/// @brief Creates a @p LoggerDeleter.
		/// @param loggerDestroyer Logger destroyer to use.
		[[nodiscard("Pure constructor")]]
		explicit LoggerDeleter(ILoggerDestroyer& loggerDestroyer) noexcept;
		[[nodiscard("Pure constructor")]]
		LoggerDeleter(const LoggerDeleter& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		LoggerDeleter(LoggerDeleter&& other) noexcept = default;

		~LoggerDeleter() noexcept = default;

		/// @brief Checks the logger compatibility.
		/// @param logger Logger.
		/// @return @a True if it's compatible; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsCompatible(ILogger* logger) const noexcept;

		/// @brief Destroys the @p logger.
		/// @param logger Logger to destroy.
		void operator ()(ILogger* logger) const noexcept;

		LoggerDeleter& operator =(const LoggerDeleter& other) noexcept = default;
		LoggerDeleter& operator =(LoggerDeleter&& other) noexcept = default;

	private:
		ILoggerDestroyer* loggerDestroyer; ///< Logger destroyer.
	};
}

export namespace PonyDebug::Log
{
	/// @brief Logger concept.
	template<typename T>
	concept LoggerType = std::convertible_to<T*, ILogger*>;

	/// @brief Logger unique pointer.
	/// @tparam T Logger type.
	template<LoggerType T>
	class LoggerUniquePtr final // TODO: Add tests
	{
	public:
		/// @brief Creates an empty @p LoggerUniquePtr.
		[[nodiscard("Pure constructor")]]
		LoggerUniquePtr() noexcept = default;
		/// @brief Creates a @p LoggerUniquePtr.
		/// @param logger Logger.
		/// @param loggerDestroyer Logger destroyer. Must be compatible with the @p logger.
		[[nodiscard("Pure constructor")]]
		LoggerUniquePtr(T& logger, ILoggerDestroyer& loggerDestroyer) noexcept;
		LoggerUniquePtr(const LoggerUniquePtr&) = delete;
		[[nodiscard("Pure constructor")]]
		LoggerUniquePtr(LoggerUniquePtr&& other) noexcept = default;
		/// @brief Move constructor with a conversion of the logger type.
		/// @tparam U Source type.
		/// @param other Source.
		template<LoggerType U> [[nodiscard("Pure constructor")]]
		explicit LoggerUniquePtr(LoggerUniquePtr<U>&& other) noexcept requires (std::convertible_to<U*, T*>);

		~LoggerUniquePtr() noexcept = default;

		/// @brief Gets a logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		T* Get() const noexcept;
		/// @brief Destroys the logger.
		void Reset() noexcept;

		/// @brief @a True if the pointer isn't nullptr; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		/// @brief Gets a logger reference.
		/// @return Logger reference.
		[[nodiscard("Pure operator")]]
		T& operator *() const noexcept;
		/// @brief Gets a logger pointer.
		/// @return Logger pointer.
		[[nodiscard("Pure operator")]]
		T* operator ->() const noexcept;

		LoggerUniquePtr& operator =(const LoggerUniquePtr&) = delete;
		LoggerUniquePtr& operator =(LoggerUniquePtr&& other) noexcept = default;
		/// @brief Move assignment with a conversion of logger type.
		/// @tparam U Source type.
		/// @param other Source.
		/// @return This.
		template<LoggerType U>
		LoggerUniquePtr& operator =(LoggerUniquePtr<U>&& other) noexcept requires (std::convertible_to<U*, T*>);

	private:
		std::unique_ptr<T, LoggerDeleter> pointer; ///< Unique_ptr.

		template<LoggerType U>
		friend class LoggerUniquePtr;
	};
}

namespace PonyDebug::Log
{
	LoggerDeleter::LoggerDeleter(ILoggerDestroyer& loggerDestroyer) noexcept :
		loggerDestroyer{&loggerDestroyer}
	{
	}

	bool LoggerDeleter::IsCompatible(ILogger* const logger) const noexcept
	{
		return !loggerDestroyer || loggerDestroyer->IsCompatible(logger);
	}

	void LoggerDeleter::operator ()(ILogger* const logger) const noexcept
	{
		if (loggerDestroyer)
		{
			loggerDestroyer->Destroy(logger);
		}
	}

	template<LoggerType T>
	LoggerUniquePtr<T>::LoggerUniquePtr(T& logger, ILoggerDestroyer& loggerDestroyer) noexcept :
		pointer(&logger, LoggerDeleter(loggerDestroyer))
	{
		assert(!pointer || pointer.get_deleter().IsCompatible(pointer.get()) && "The logger isn't compatible with the destroyer.");
	}

	template<LoggerType T>
	template<LoggerType U>
	LoggerUniquePtr<T>::LoggerUniquePtr(LoggerUniquePtr<U>&& other) noexcept requires (std::convertible_to<U*, T*>) :
		pointer(std::move(other.pointer))
	{
	}

	template<LoggerType T>
	T* LoggerUniquePtr<T>::Get() const noexcept
	{
		return pointer.get();
	}

	template<LoggerType T>
	void LoggerUniquePtr<T>::Reset() noexcept
	{
		pointer.reset();
	}

	template<LoggerType T>
	LoggerUniquePtr<T>::operator bool() const noexcept
	{
		return static_cast<bool>(pointer);
	}

	template<LoggerType T>
	T& LoggerUniquePtr<T>::operator *() const noexcept
	{
		return *pointer;
	}

	template<LoggerType T>
	T* LoggerUniquePtr<T>::operator ->() const noexcept
	{
		return pointer.get();
	}

	template<LoggerType T>
	template<LoggerType U>
	LoggerUniquePtr<T>& LoggerUniquePtr<T>::operator =(LoggerUniquePtr<U>&& other) noexcept requires (std::convertible_to<U*, T*>)
	{
		pointer = std::move(other.pointer);

		return *this;
	}
}

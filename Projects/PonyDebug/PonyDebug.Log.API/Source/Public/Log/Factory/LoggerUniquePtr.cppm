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
	/// @brief Logger unique pointer.
	/// @tparam T Logger type.
	template<std::derived_from<ILogger> T>
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
		template<std::derived_from<T> U> [[nodiscard("Pure constructor")]]
		explicit LoggerUniquePtr(LoggerUniquePtr<U>&& other) noexcept;

		~LoggerUniquePtr() noexcept = default;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		T* Get() const noexcept;
		/// @brief Destroys the logger.
		void Reset() noexcept;

		/// @brief @a True if the pointer isn't nullptr; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		/// @brief Gets the logger reference.
		/// @return Logger reference.
		[[nodiscard("Pure operator")]]
		T& operator *() const noexcept;
		/// @brief Gets the logger pointer.
		/// @return Logger pointer.
		[[nodiscard("Pure operator")]]
		T* operator ->() const noexcept;

		LoggerUniquePtr& operator =(const LoggerUniquePtr&) = delete;
		LoggerUniquePtr& operator =(LoggerUniquePtr&& other) noexcept = default;
		/// @brief Move assignment with a conversion of logger type.
		/// @tparam U Source type.
		/// @param other Source.
		/// @return This.
		template<std::derived_from<T> U>
		LoggerUniquePtr& operator =(LoggerUniquePtr<U>&& other) noexcept;

	private:
		std::unique_ptr<T, LoggerDeleter> pointer; ///< Unique_ptr.

		template<std::derived_from<ILogger> U>
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

	template<std::derived_from<ILogger> T>
	LoggerUniquePtr<T>::LoggerUniquePtr(T& logger, ILoggerDestroyer& loggerDestroyer) noexcept :
		pointer(&logger, LoggerDeleter(loggerDestroyer))
	{
		assert(pointer.get_deleter().IsCompatible(pointer.get()) && "The logger isn't compatible with the destroyer.");
	}

	template<std::derived_from<ILogger> T>
	template<std::derived_from<T> U>
	LoggerUniquePtr<T>::LoggerUniquePtr(LoggerUniquePtr<U>&& other) noexcept :
		pointer(std::move(other.pointer))
	{
	}

	template<std::derived_from<ILogger> T>
	T* LoggerUniquePtr<T>::Get() const noexcept
	{
		return pointer.get();
	}

	template<std::derived_from<ILogger> T>
	void LoggerUniquePtr<T>::Reset() noexcept
	{
		pointer.reset();
	}

	template<std::derived_from<ILogger> T>
	LoggerUniquePtr<T>::operator bool() const noexcept
	{
		return static_cast<bool>(pointer);
	}

	template<std::derived_from<ILogger> T>
	T& LoggerUniquePtr<T>::operator *() const noexcept
	{
		return *pointer;
	}

	template<std::derived_from<ILogger> T>
	T* LoggerUniquePtr<T>::operator ->() const noexcept
	{
		return pointer.get();
	}

	template<std::derived_from<ILogger> T>
	template<std::derived_from<T> U>
	LoggerUniquePtr<T>& LoggerUniquePtr<T>::operator =(LoggerUniquePtr<U>&& other) noexcept
	{
		pointer = std::move(other.pointer);

		return *this;
	}
}

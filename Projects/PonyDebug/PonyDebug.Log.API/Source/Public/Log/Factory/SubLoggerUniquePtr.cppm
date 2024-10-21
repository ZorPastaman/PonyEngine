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

export module PonyDebug.Log.Factory:SubLoggerUniquePtr;

import <concepts>;
import <memory>;
import <utility>;

import PonyDebug.Log;

import :ISubLoggerDestroyer;

namespace PonyDebug::Log
{
	/// @brief Sub-logger deleter.
	class SubLoggerDeleter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		SubLoggerDeleter() noexcept = default;
		/// @brief Creates a @p SubLoggerDeleter.
		/// @param subLoggerDestroyer Logger destroyer to use.
		[[nodiscard("Pure constructor")]]
		explicit SubLoggerDeleter(ISubLoggerDestroyer& subLoggerDestroyer) noexcept;
		[[nodiscard("Pure constructor")]]
		SubLoggerDeleter(const SubLoggerDeleter& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		SubLoggerDeleter(SubLoggerDeleter&& other) noexcept = default;

		~SubLoggerDeleter() noexcept = default;

		/// @brief Checks the sub-logger compatibility.
		/// @param subLogger Sub-logger.
		/// @return @a True if it's compatible; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsCompatible(ISubLogger* subLogger) const noexcept;

		/// @brief Destroys the @p subLogger.
		/// @param subLogger Sub-logger to destroy.
		void operator ()(ISubLogger* subLogger) const noexcept;

		SubLoggerDeleter& operator =(const SubLoggerDeleter& other) noexcept = default;
		SubLoggerDeleter& operator =(SubLoggerDeleter&& other) noexcept = default;

	private:
		ISubLoggerDestroyer* subLoggerDestroyer; ///< Sub-logger destroyer.
	};
}

export namespace PonyDebug::Log
{
	/// @brief Sub-logger concept.
	/// @tparam T Sub-logger type.
	template<typename T>
	concept SubLoggerType = std::convertible_to<T*, ISubLogger*>;

	/// @brief Sub-logger unique pointer.
	/// @tparam T Sub-logger type.
	template<SubLoggerType T>
	class SubLoggerUniquePtr final // TODO: Add tests
	{
	public:
		/// @brief Creates an empty @p SubLoggerUniquePtr.
		[[nodiscard("Pure constructor")]]
		SubLoggerUniquePtr() noexcept = default;
		/// @brief Creates a @p SubLoggerUniquePtr.
		/// @param subLogger Sub-logger.
		/// @param subLoggerDestroyer Sub-logger destroyer. Must be compatible with the @p subLogger.
		[[nodiscard("Pure constructor")]]
		SubLoggerUniquePtr(T& subLogger, ISubLoggerDestroyer& subLoggerDestroyer) noexcept;
		SubLoggerUniquePtr(const SubLoggerUniquePtr&) = delete;
		[[nodiscard("Pure constructor")]]
		SubLoggerUniquePtr(SubLoggerUniquePtr&& other) noexcept = default;
		/// @brief Move constructor with a conversion of the sub-logger type.
		/// @tparam U Source type.
		/// @param other Source.
		template<SubLoggerType U> [[nodiscard("Pure constructor")]]
		explicit SubLoggerUniquePtr(SubLoggerUniquePtr<U>&& other) noexcept requires (std::convertible_to<U*, T*>);

		/// @brief Destroys the pointed sub-logger if it's not nullptr.
		~SubLoggerUniquePtr() noexcept = default;

		/// @brief Gets a sub-logger.
		/// @return Sub-logger.
		[[nodiscard("Pure function")]]
		T* Get() const noexcept;
		/// @brief Destroys the sub-logger.
		void Reset() noexcept;

		/// @brief @a True if the pointer isn't nullptr; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		/// @brief Gets a sub-logger reference.
		/// @return Sub-logger reference.
		[[nodiscard("Pure operator")]]
		T& operator *() const noexcept;
		/// @brief Gets a sub-logger pointer.
		/// @return Sub-logger pointer.
		[[nodiscard("Pure operator")]]
		T* operator ->() const noexcept;

		SubLoggerUniquePtr& operator =(const SubLoggerUniquePtr&) = delete;
		SubLoggerUniquePtr& operator =(SubLoggerUniquePtr&& other) noexcept = default;
		/// @brief Move assignment with a conversion of sub-logger type.
		/// @tparam U Source type.
		/// @param other Source.
		/// @return This.
		template<SubLoggerType U>
		SubLoggerUniquePtr& operator =(SubLoggerUniquePtr<U>&& other) noexcept requires (std::convertible_to<U*, T*>);

	private:
		std::unique_ptr<T, SubLoggerDeleter> pointer; ///< Unique_ptr.

		template<SubLoggerType U>
		friend class SubLoggerUniquePtr;
	};
}

namespace PonyDebug::Log
{
	SubLoggerDeleter::SubLoggerDeleter(ISubLoggerDestroyer& subLoggerDestroyer) noexcept :
		subLoggerDestroyer{&subLoggerDestroyer}
	{
	}

	bool SubLoggerDeleter::IsCompatible(ISubLogger* const subLogger) const noexcept
	{
		return !subLoggerDestroyer || subLoggerDestroyer->IsCompatible(subLogger);
	}

	void SubLoggerDeleter::operator ()(ISubLogger* const subLogger) const noexcept
	{
		if (subLoggerDestroyer)
		{
			subLoggerDestroyer->Destroy(subLogger);
		}
	}

	template<SubLoggerType T>
	SubLoggerUniquePtr<T>::SubLoggerUniquePtr(T& subLogger, ISubLoggerDestroyer& subLoggerDestroyer) noexcept :
		pointer(&subLogger, SubLoggerDeleter(subLoggerDestroyer))
	{
		assert(!pointer || pointer.get_deleter().IsCompatible(pointer.get()) && "The sub-logger isn't compatible with the destroyer.");
	}

	template<SubLoggerType T>
	template<SubLoggerType U>
	SubLoggerUniquePtr<T>::SubLoggerUniquePtr(SubLoggerUniquePtr<U>&& other) noexcept requires (std::convertible_to<U*, T*>) :
		pointer(std::move(other.pointer))
	{
	}

	template<SubLoggerType T>
	T* SubLoggerUniquePtr<T>::Get() const noexcept
	{
		return pointer.get();
	}

	template<SubLoggerType T>
	void SubLoggerUniquePtr<T>::Reset() noexcept
	{
		pointer.reset();
	}

	template<SubLoggerType T>
	SubLoggerUniquePtr<T>::operator bool() const noexcept
	{
		return static_cast<bool>(pointer);
	}

	template<SubLoggerType T>
	T& SubLoggerUniquePtr<T>::operator *() const noexcept
	{
		return *pointer;
	}

	template<SubLoggerType T>
	T* SubLoggerUniquePtr<T>::operator ->() const noexcept
	{
		return pointer.get();
	}

	template<SubLoggerType T>
	template<SubLoggerType U>
	SubLoggerUniquePtr<T>& SubLoggerUniquePtr<T>::operator =(SubLoggerUniquePtr<U>&& other) noexcept requires (std::convertible_to<U*, T*>)
	{
		pointer = std::move(other.pointer);

		return *this;
	}
}

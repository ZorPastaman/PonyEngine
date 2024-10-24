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

export module PonyEngine.Core.Factory:SystemUniquePtr;

import <concepts>;
import <memory>;
import <utility>;

import PonyEngine.Core;

import :ISystemDestroyer;

namespace PonyEngine::Core
{
	/// @brief System deleter.
	class SystemDeleter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		SystemDeleter() noexcept = default;
		/// @brief Creates a @p SystemDeleter.
		/// @param destroyer System destroyer to use.
		[[nodiscard("Pure constructor")]]
		explicit SystemDeleter(ISystemDestroyer& destroyer) noexcept;
		[[nodiscard("Pure constructor")]]
		SystemDeleter(const SystemDeleter& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		SystemDeleter(SystemDeleter&& other) noexcept = default;

		~SystemDeleter() noexcept = default;

		/// @brief Checks if the destroyer is compatible with the @p system.
		/// @param system Target system.
		/// @return @a True if it's compatible; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsCompatible(IEngineSystem* system) const noexcept;

		/// @brief Deletes the @p system.
		/// @param system System to delete.
		void operator ()(IEngineSystem* system) const noexcept;

		SystemDeleter& operator =(const SystemDeleter& other) noexcept = default;
		SystemDeleter& operator =(SystemDeleter&& other) noexcept = default;

	private:
		ISystemDestroyer* destroyer; ///< System destroyer.
	};
}

export namespace PonyEngine::Core
{
	/// @brief System unique pointer.
	/// @tparam T System type.
	template<std::derived_from<IEngineSystem> T>
	class SystemUniquePtr final // TODO: Add tests
	{
	public:
		/// @brief Creates an empty @p SystemUniquePtr.
		[[nodiscard("Pure constructor")]]
		SystemUniquePtr() noexcept = default;
		/// @brief Creates a @p SystemUniquePtr.
		/// @param system System.
		/// @param systemDestroyer System destroyer.
		[[nodiscard("Pure constructor")]]
		SystemUniquePtr(T& system, ISystemDestroyer& systemDestroyer) noexcept;
		SystemUniquePtr(const SystemUniquePtr&) = delete;
		[[nodiscard("Pure constructor")]]
		SystemUniquePtr(SystemUniquePtr&& other) noexcept = default;
		/// @brief Creates a @p SystemUniquePtr with a type conversion.
		/// @tparam U Source type.
		/// @param other Source.
		template<std::derived_from<T> U>
		explicit SystemUniquePtr(SystemUniquePtr<U>&& other) noexcept;

		~SystemUniquePtr() noexcept = default;

		/// @brief Gets the system.
		/// @return System.
		[[nodiscard("Pure function")]]
		T* Get() const noexcept;
		/// @brief Destroys the system.
		void Reset() noexcept;

		/// @brief @a True if the pointer isn't nullptr; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		/// @brief Gets the system reference.
		/// @return System reference.
		[[nodiscard("Pure operator")]]
		T& operator *() const noexcept;
		/// @brief Gets the system pointer.
		/// @return System pointer.
		[[nodiscard("Pure operator")]]
		T* operator ->() const noexcept;

		SystemUniquePtr& operator =(const SystemUniquePtr&) = delete;
		SystemUniquePtr& operator =(SystemUniquePtr&& other) noexcept = default;
		/// @brief Assigns with a type conversion.
		/// @tparam U Source type.
		/// @param other Source.
		/// @return @a This.
		template<std::derived_from<T> U>
		SystemUniquePtr& operator =(SystemUniquePtr<U>&& other) noexcept;

	private:
		std::unique_ptr<T, SystemDeleter> pointer; ///< System pointer.

		template<std::derived_from<IEngineSystem> U>
		friend class SystemUniquePtr;
	};
}

namespace PonyEngine::Core
{
	SystemDeleter::SystemDeleter(ISystemDestroyer& destroyer) noexcept :
		destroyer{&destroyer}
	{
	}

	bool SystemDeleter::IsCompatible(IEngineSystem* const system) const noexcept
	{
		return !destroyer || destroyer->IsCompatible(system);
	}

	void SystemDeleter::operator ()(IEngineSystem* const system) const noexcept
	{
		if (destroyer)
		{
			destroyer->Destroy(system);
		}
	}

	template<std::derived_from<IEngineSystem> T>
	SystemUniquePtr<T>::SystemUniquePtr(T& system, ISystemDestroyer& systemDestroyer) noexcept :
		pointer(&system, SystemDeleter(systemDestroyer))
	{
		assert(pointer.get_deleter().IsCompatible(pointer.get()) && "The system isn't compatible with the destroyer.");
	}

	template<std::derived_from<IEngineSystem> T>
	template<std::derived_from<T> U>
	SystemUniquePtr<T>::SystemUniquePtr(SystemUniquePtr<U>&& other) noexcept :
		pointer(std::move(other.pointer))
	{
	}

	template<std::derived_from<IEngineSystem> T>
	T* SystemUniquePtr<T>::Get() const noexcept
	{
		return pointer.get();
	}

	template<std::derived_from<IEngineSystem> T>
	void SystemUniquePtr<T>::Reset() noexcept
	{
		pointer.reset();
	}

	template<std::derived_from<IEngineSystem> T>
	SystemUniquePtr<T>::operator bool() const noexcept
	{
		return static_cast<bool>(pointer);
	}

	template<std::derived_from<IEngineSystem> T>
	T& SystemUniquePtr<T>::operator *() const noexcept
	{
		return *pointer;
	}

	template<std::derived_from<IEngineSystem> T>
	T* SystemUniquePtr<T>::operator ->() const noexcept
	{
		return pointer.get();
	}

	template<std::derived_from<IEngineSystem> T>
	template<std::derived_from<T> U>
	SystemUniquePtr<T>& SystemUniquePtr<T>::operator =(SystemUniquePtr<U>&& other) noexcept
	{
		pointer = std::move(other);

		return *this;
	}
}

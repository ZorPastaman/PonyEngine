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

export module PonyEngine.Core.Factory:SystemFactoryUniquePtr;

import <concepts>;
import <memory>;
import <utility>;

import :ISystemFactory;
import :ISystemFactoryDestroyer;

namespace PonyEngine::Core
{
	/// @brief System factory deleter.
	class SystemFactoryDeleter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		SystemFactoryDeleter() noexcept = default;
		/// @brief Creates a @p SystemFactoryDeleter.
		/// @param factoryDestroyer System factory destroyer to use.
		[[nodiscard("Pure constructor")]]
		explicit SystemFactoryDeleter(ISystemFactoryDestroyer& factoryDestroyer) noexcept;
		[[nodiscard("Pure constructor")]]
		SystemFactoryDeleter(const SystemFactoryDeleter& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		SystemFactoryDeleter(SystemFactoryDeleter&& other) noexcept = default;

		~SystemFactoryDeleter() noexcept = default;

		/// @brief Checks the system factory compatibility.
		/// @param factory System factory.
		/// @return @a True if it's compatible; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsCompatible(ISystemFactory* factory) const noexcept;

		/// @brief Deletes the @p factory.
		/// @param factory System factory to delete.
		void operator ()(ISystemFactory* factory) const noexcept;

		SystemFactoryDeleter& operator =(const SystemFactoryDeleter& other) noexcept = default;
		SystemFactoryDeleter& operator =(SystemFactoryDeleter&& other) noexcept = default;

	private:
		ISystemFactoryDestroyer* factoryDestroyer; ///< System factory destroyer.
	};
}

export namespace PonyEngine::Core
{
	/// @brief System factory unique pointer.
	/// @tparam T System factory type.
	template<std::derived_from<ISystemFactory> T>
	class SystemFactoryUniquePtr final // TODO: Add tests
	{
	public:
		/// @brief Creates an empty @p SystemFactoryUniquePtr.
		[[nodiscard("Pure constructor")]]
		SystemFactoryUniquePtr() noexcept = default;
		/// @brief Creates a @p SystemFactoryUniquePtr.
		/// @param factory System factory.
		/// @param factoryDestroyer System factory destroyer.
		[[nodiscard("Pure constructor")]]
		SystemFactoryUniquePtr(T& factory, ISystemFactoryDestroyer& factoryDestroyer) noexcept;
		SystemFactoryUniquePtr(const SystemFactoryUniquePtr&) = delete;
		[[nodiscard("Pure constructor")]]
		SystemFactoryUniquePtr(SystemFactoryUniquePtr&& other) noexcept = default;
		/// @brief Creates a @p SystemFactoryUniquePtr with a type conversion.
		/// @tparam U Source type.
		/// @param other Source.
		template<std::derived_from<T> U> [[nodiscard("Pure constructor")]]
		explicit SystemFactoryUniquePtr(SystemFactoryUniquePtr<U>&& other) noexcept;

		~SystemFactoryUniquePtr() noexcept = default;

		/// @brief Gets the system factory.
		/// @return System factory.
		[[nodiscard("Pure function")]]
		T* Get() const noexcept;
		/// @brief Destroys the system factory.
		void Reset() noexcept;

		/// @brief @a True if the system factory isn't nullptr; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		/// @brief Gets a system factory reference.
		/// @return System factory reference.
		[[nodiscard("Pure operator")]]
		T& operator *() const noexcept;
		/// @brief Gets a system factory pointer.
		/// @return System factory pointer.
		[[nodiscard("Pure operator")]]
		T* operator ->() const noexcept;

		SystemFactoryUniquePtr& operator =(const SystemFactoryUniquePtr&) = delete;
		SystemFactoryUniquePtr& operator =(SystemFactoryUniquePtr&&) noexcept = default;
		/// @brief Assigns with a type conversion.
		/// @tparam U Source type.
		/// @param other Source.
		/// @return @a This.
		template<std::derived_from<T> U>
		SystemFactoryUniquePtr& operator =(SystemFactoryUniquePtr<U>&& other) noexcept;

	private:
		std::unique_ptr<T, SystemFactoryDeleter> pointer; ///< System factory pointer.

		template<std::derived_from<ISystemFactory> U>
		friend class SystemFactoryUniquePtr;
	};
}

namespace PonyEngine::Core
{
	SystemFactoryDeleter::SystemFactoryDeleter(ISystemFactoryDestroyer& factoryDestroyer) noexcept :
		factoryDestroyer{&factoryDestroyer}
	{
	}

	bool SystemFactoryDeleter::IsCompatible(ISystemFactory* const factory) const noexcept
	{
		return !factoryDestroyer || factoryDestroyer->IsCompatible(factory);
	}

	void SystemFactoryDeleter::operator ()(ISystemFactory* const factory) const noexcept
	{
		if (factoryDestroyer)
		{
			factoryDestroyer->Destroy(factory);
		}
	}

	template<std::derived_from<ISystemFactory> T>
	SystemFactoryUniquePtr<T>::SystemFactoryUniquePtr(T& factory, ISystemFactoryDestroyer& factoryDestroyer) noexcept :
		pointer(&factory, SystemFactoryDeleter(factoryDestroyer))
	{
		assert(pointer.get_deleter().IsCompatible(pointer.get()) && "The system factory isn't compatible with the system factory destroyer.");
	}

	template<std::derived_from<ISystemFactory> T>
	template<std::derived_from<T> U>
	SystemFactoryUniquePtr<T>::SystemFactoryUniquePtr(SystemFactoryUniquePtr<U>&& other) noexcept :
		pointer(std::move(other.pointer))
	{
	}

	template<std::derived_from<ISystemFactory> T>
	T* SystemFactoryUniquePtr<T>::Get() const noexcept
	{
		return pointer.get();
	}

	template<std::derived_from<ISystemFactory> T>
	void SystemFactoryUniquePtr<T>::Reset() noexcept
	{
		pointer.reset();
	}

	template<std::derived_from<ISystemFactory> T>
	SystemFactoryUniquePtr<T>::operator bool() const noexcept
	{
		return static_cast<bool>(pointer);
	}

	template<std::derived_from<ISystemFactory> T>
	T& SystemFactoryUniquePtr<T>::operator *() const noexcept
	{
		return *pointer;
	}

	template<std::derived_from<ISystemFactory> T>
	T* SystemFactoryUniquePtr<T>::operator ->() const noexcept
	{
		return pointer.get();
	}

	template<std::derived_from<ISystemFactory> T>
	template<std::derived_from<T> U>
	SystemFactoryUniquePtr<T>& SystemFactoryUniquePtr<T>::operator =(SystemFactoryUniquePtr<U>&& other) noexcept
	{
		pointer = std::move(other.pointer);

		return *this;
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <objbase.h>

export module PonyEngine.Platform.WinCore:ComPtr;

import std;

export namespace PonyEngine::Platform::WinCore
{
	/// @brief Smart pointer to manipulate COM objects.
	/// @tparam T Object type.
	//template<std::derived_from<IUnknown> T>
	//class ComPtr;

	/// @brief Smart pointer to manipulate COM objects.
	/// @tparam T Object type.
	template<std::derived_from<IUnknown> T>
	class ComPtr final
	{
	public:
		using ValueType = T; ///< Object type.

		/// @brief Creates a nullptr COM pointer.
		[[nodiscard("Pure constructor")]]
		ComPtr() noexcept;
		/// @brief Creates a nullptr COM pointer.
		[[nodiscard("Pure constructor")]]
		ComPtr(std::nullptr_t) noexcept;
		/// @brief Creates a COM pointer.
		/// @param pointer COM object.
		[[nodiscard("Pure constructor")]]
		explicit ComPtr(T* pointer) noexcept;
		[[nodiscard("Pure constructor")]]
		ComPtr(const ComPtr& other) noexcept;
		[[nodiscard("Pure constructor")]]
		ComPtr(ComPtr&& other) noexcept;
		template<std::derived_from<T> U> [[nodiscard("Pure constructor")]]
		ComPtr(const ComPtr<U>& other) noexcept;
		template<std::derived_from<T> U> [[nodiscard("Pure constructor")]]
		ComPtr(ComPtr<U>&& other) noexcept;

		~ComPtr() noexcept;

		/// @brief Gets the current object.
		/// @return Current object.
		[[nodiscard("Pure function")]]
		T* Get() const noexcept;
		/// @brief Gets the internal pointer.
		/// @return Internal pointer.
		/// @note If you write to the returned pointer, it can be dangerous 'cause there will be no correct release of the previous value.
		[[nodiscard("Pure function")]]
		T** GetAddress() noexcept;
		/// @brief Gets the internal pointer.
		/// @return Internal pointer.
		[[nodiscard("Pure function")]]
		T* const* GetAddress() const noexcept;
		/// @brief Releases the current object and gets the internal pointer.
		/// @return Internal pointer.
		T** ReleaseAndGetAddress() noexcept;
		/// @brief Resets the COM pointer with a new value.
		/// @param newPointer COM object to set.
		void Reset(T* newPointer = nullptr) noexcept;

		/// @brief Tries to cast the COM object to another type.
		/// @tparam U Target type.
		/// @param target Target COM pointer.
		/// @return Cast result.
		template<std::derived_from<IUnknown> U>
		HRESULT As(ComPtr<U>& target) const noexcept;

		/// @brief Swaps the COM objects.
		/// @param other Other COM pointer to swap objects with.
		void Swap(ComPtr& other) noexcept;

		/// @brief Gets the current object reference.
		/// @return Current object reference.
		/// @note If the current pointer is nullptr, it's UB.
		[[nodiscard("Pure operator")]]
		T& operator *() const noexcept;
		/// @brief Gets the current object.
		/// @return Current object.
		[[nodiscard("Pure operator")]]
		T* operator ->() const noexcept;

		/// @brief Checks if the current object is valid.
		/// @return @a True if it's a valid object; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		ComPtr& operator =(const ComPtr& other) noexcept;
		ComPtr& operator =(ComPtr&& other) noexcept;
		template<std::derived_from<T> U>
		ComPtr& operator =(const ComPtr<U>& other) noexcept;
		template<std::derived_from<T> U>
		ComPtr& operator =(ComPtr<U>&& other) noexcept;

		template<std::derived_from<IUnknown> U> [[nodiscard("Pure operator")]]
		bool operator ==(const ComPtr<U>& other) const noexcept;

	private:
		/// @brief Increments a ref count of the current object if it's not nullptr.
		/// @return New ref count.
		ULONG AddRef() noexcept;
		/// @brief Decrements a ref count of the current object if it's not nullptr.
		/// @return New ref count.
		ULONG Release() noexcept;

		T* pointer; ///< COM object.

		template<std::derived_from<IUnknown> U>
		friend class ComPtr;
	};
}

namespace PonyEngine::Platform::WinCore
{
	template<std::derived_from<IUnknown> T>
	ComPtr<T>::ComPtr() noexcept :
		pointer{nullptr}
	{
	}

	template<std::derived_from<IUnknown> T>
	ComPtr<T>::ComPtr(std::nullptr_t) noexcept :
		ComPtr()
	{
	}

	template<std::derived_from<IUnknown> T>
	ComPtr<T>::ComPtr(T* const pointer) noexcept :
		pointer{pointer}
	{
		AddRef();
	}

	template<std::derived_from<IUnknown> T>
	ComPtr<T>::ComPtr(const ComPtr& other) noexcept :
		ComPtr(other.pointer)
	{
	}

	template<std::derived_from<IUnknown> T>
	ComPtr<T>::ComPtr(ComPtr&& other) noexcept :
		pointer{nullptr}
	{
		Swap(other);
	}

	template<std::derived_from<IUnknown> T>
	template<std::derived_from<T> U>
	ComPtr<T>::ComPtr(const ComPtr<U>& other) noexcept :
		ComPtr(other.pointer)
	{
	}

	template<std::derived_from<IUnknown> T>
	template<std::derived_from<T> U>
	ComPtr<T>::ComPtr(ComPtr<U>&& other) noexcept :
		pointer{other.pointer}
	{
		other.pointer = nullptr;
	}

	template<std::derived_from<IUnknown> T>
	ComPtr<T>::~ComPtr() noexcept
	{
		Release();
	}

	template<std::derived_from<IUnknown> T>
	T* ComPtr<T>::Get() const noexcept
	{
		return pointer;
	}

	template<std::derived_from<IUnknown> T>
	T** ComPtr<T>::GetAddress() noexcept
	{
		return &pointer;
	}

	template<std::derived_from<IUnknown> T>
	T* const* ComPtr<T>::GetAddress() const noexcept
	{
		return &pointer;
	}

	template<std::derived_from<IUnknown> T>
	T** ComPtr<T>::ReleaseAndGetAddress() noexcept
	{
		Release();
		return &pointer;
	}

	template<std::derived_from<IUnknown> T>
	void ComPtr<T>::Reset(T* const newPointer) noexcept
	{
		if (pointer != newPointer)
		{
			Release();
			pointer = newPointer;
			AddRef();
		}
	}

	template<std::derived_from<IUnknown> T>
	template<std::derived_from<IUnknown> U>
	HRESULT ComPtr<T>::As(ComPtr<U>& target) const noexcept
	{
		if (!pointer)
		{
			return E_POINTER;
		}

		ComPtr<U> temp;
		const HRESULT result = pointer->QueryInterface(temp.GetAddress());

		if (SUCCEEDED(result))
		{
			target.Swap(temp);
		}

		return result;
	}

	template<std::derived_from<IUnknown> T>
	void ComPtr<T>::Swap(ComPtr& other) noexcept
	{
		std::swap(pointer, other.pointer);
	}

	template<std::derived_from<IUnknown> T>
	T& ComPtr<T>::operator *() const noexcept
	{
		return *pointer;
	}

	template<std::derived_from<IUnknown> T>
	T* ComPtr<T>::operator ->() const noexcept
	{
		return pointer;
	}

	template<std::derived_from<IUnknown> T>
	ComPtr<T>::operator bool() const noexcept
	{
		return pointer;
	}

	template<std::derived_from<IUnknown> T>
	ComPtr<T>& ComPtr<T>::operator =(const ComPtr& other) noexcept
	{
		Reset(other.pointer);
		return *this;
	}

	template<std::derived_from<IUnknown> T>
	ComPtr<T>& ComPtr<T>::operator =(ComPtr&& other) noexcept
	{
		Release();
		Swap(other);

		return *this;
	}

	template<std::derived_from<IUnknown> T>
	template<std::derived_from<T> U>
	ComPtr<T>& ComPtr<T>::operator =(const ComPtr<U>& other) noexcept
	{
		Reset(other.pointer);
		return *this;
	}

	template<std::derived_from<IUnknown> T>
	template<std::derived_from<T> U>
	ComPtr<T>& ComPtr<T>::operator =(ComPtr<U>&& other) noexcept
	{
		Release();
		pointer = other.pointer;
		other.pointer = nullptr;

		return *this;
	}

	template<std::derived_from<IUnknown> T>
	template<std::derived_from<IUnknown> U>
	bool ComPtr<T>::operator ==(const ComPtr<U>& other) const noexcept
	{
		return pointer == other.pointer;
	}

	template<std::derived_from<IUnknown> T>
	ULONG ComPtr<T>::AddRef() noexcept
	{
		if (pointer)
		{
			return pointer->AddRef();
		}

		return 0ul;
	}

	template<std::derived_from<IUnknown> T>
	ULONG ComPtr<T>::Release() noexcept
	{
		if (pointer)
		{
			T* const temp = pointer;
			pointer = nullptr;
			return temp->Release();
		}

		return 0ul;
	}
}

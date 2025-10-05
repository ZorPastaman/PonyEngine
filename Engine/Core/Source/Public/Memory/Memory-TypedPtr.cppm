/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Memory:TypedPtr;

import std;

import :Mutability;

export namespace PonyEngine::Memory
{
	/// @brief Void pointer with type information.
	/// @tparam ValueMutability Value mutability.
	template<Mutability ValueMutability = Mutability::None>
	class TypedPtr final
	{
	public:
		/// @brief Pointer value type.
		using ValueType = std::conditional_t<ValueMutability == Mutability::All, const volatile void,
			std::conditional_t<ValueMutability == Mutability::Constant, const void,
			std::conditional_t<ValueMutability == Mutability::Volatile, volatile void,
			void>>>;

		/// @brief Creates a nullptr pointer.
		[[nodiscard("Pure constructor")]]
		TypedPtr() noexcept;
		/// @brief Creates a pointer.
		/// @tparam T Object type.
		/// @param ptr Object pointer.
		/// @note It must satisfy the mutability of the pointer.
		template<typename T> [[nodiscard("Pure constructor")]]
		explicit TypedPtr(T* ptr) noexcept;
		[[nodiscard("Pure constructor")]]
		TypedPtr(const TypedPtr& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		TypedPtr(TypedPtr&& other) noexcept = default;

		~TypedPtr() noexcept = default;

		/// @brief Gets the type.
		/// @return Type.
		[[nodiscard("Pure function")]]
		const std::type_info& Type() const noexcept;
		/// @brief Gets the pointer.
		/// @return Pointer.
		[[nodiscard("Pure function")]]
		ValueType* Get() const noexcept;

		/// @brief Checks if the pointer points to an object.
		/// @return @a True if the pointer point to an object; @a false if it's nullptr.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		TypedPtr& operator =(const TypedPtr& other) noexcept = default;
		TypedPtr& operator =(TypedPtr&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const TypedPtr& other) const noexcept = default;

	private:
		const std::type_info* type; ///< Pointer type.
		ValueType* ptr; ///< Pointer.
	};
}

namespace PonyEngine::Memory
{
	template<Mutability ValueMutability>
	TypedPtr<ValueMutability>::TypedPtr() noexcept :
		type{&typeid(std::nullptr_t)},
		ptr{nullptr}
	{
	}

	template<Mutability ValueMutability>
	template<typename T>
	TypedPtr<ValueMutability>::TypedPtr(T* const ptr) noexcept :
		type{&typeid(T)},
		ptr{ptr}
	{
	}

	template<Mutability ValueMutability>
	const std::type_info& TypedPtr<ValueMutability>::Type() const noexcept
	{
		return *type;
	}

	template<Mutability ValueMutability>
	TypedPtr<ValueMutability>::ValueType* TypedPtr<ValueMutability>::Get() const noexcept
	{
		return ptr;
	}

	template<Mutability ValueMutability>
	TypedPtr<ValueMutability>::operator bool() const noexcept
	{
		return ptr;
	}
}

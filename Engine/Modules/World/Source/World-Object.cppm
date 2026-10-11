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

export module PonyEngine.World:Object;

import std;

export namespace PonyEngine::World
{
	/// @brief World object.
	/// @details It's a type-erased wrapper over std::shared_ptr.
	class Object final
	{
	public:
		/// @brief Creates an empty object.
		[[nodiscard("Pure constructor")]]
		Object() noexcept;
		/// @brief Creates an empty object.
		[[nodiscard("Pure constructor")]]
		Object(std::nullptr_t) noexcept;
		/// @brief Creates an object.
		/// @tparam T Data type.
		/// @param data Data.
		template<typename T> [[nodiscard("Pure constructor")]]
		explicit Object(std::shared_ptr<T> data) noexcept;
		[[nodiscard("Pure constructor")]]
		Object(const Object& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Object(Object&& other) noexcept = default;

		~Object() noexcept = default;

		/// @brief Gets the data.
		/// @return Data.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<const void>& Data() const noexcept;
		/// @brief Gets the data pointer.
		/// @return Data pointer.
		[[nodiscard("Pure function")]]
		const void* Pointer() const noexcept;
		/// @brief Gets the type.
		/// @return Type.
		[[nodiscard("Pure function")]]
		std::type_index Type() const noexcept;
		/// @brief Checks if the data is const.
		/// @return @a True if it's const; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsConst() const noexcept;

		/// @brief Checks if the object is castable to the requested pointer.
		/// @tparam T Target type of a pointer.
		/// @return @a True if it's castable; @a false otherwise.
		template<typename T> [[nodiscard("Pure function")]]
		bool IsCastable() const noexcept;
		/// @brief Checks if the object is castable to the requested pointer.
		/// @param type Pointer type.
		/// @param isConst Is the pointer const?
		/// @return @a True if it's castable; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsCastable(std::type_index type, bool isConst) const noexcept;

		/// @brief Checks if the object has a data.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasData() const noexcept;
		/// @brief Gets a data pointer.
		/// @tparam T Data type. Must be equal to the data type or void. Non-const types may be used only with non-const data.
		/// @return Data pointer.
		template<typename T> [[nodiscard("Pure function")]]
		T* Get() const noexcept;
		/// @brief Gets a shared data pointer.
		/// @tparam T Data type. Must be equal to the data type or void. Non-const types may be used only with non-const data.
		/// @return Shared data pointer.
		template<typename T> [[nodiscard("Pure function")]]
		std::shared_ptr<T> GetShared() const noexcept;

		/// @brief Resets the object.
		void Reset() noexcept;
		/// @brief Resets the object.
		/// @tparam T Data type.
		/// @param data Data.
		template<typename T>
		void Reset(std::shared_ptr<T> data) noexcept;

		/// @brief Checks if the object has a data.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		Object& operator =(const Object& other) noexcept = default;
		Object& operator =(Object&& other) noexcept = default;

	private:
		/// @brief Validates the requested data type.
		/// @tparam T Requested data type.
		template<typename T>
		void Validate();

		/// @brief Gets the intermediate cast type.
		/// @tparam T Target type.
		template<typename T>
		using Intermediate = std::conditional_t<std::is_const_v<T>, const void, void>;

		std::shared_ptr<const void> data; ///< Data.
		std::type_index type; ///< Data type.
		bool isConst; ///< Is the data const?
	};
}

namespace PonyEngine::World
{
	Object::Object() noexcept :
		type(typeid(void)),
		isConst{false}
	{
	}

	Object::Object(std::nullptr_t) noexcept :
		Object()
	{
	}

	template<typename T>
	Object::Object(std::shared_ptr<T> data) noexcept :
		data(std::move(data)),
		type(typeid(T)),
		isConst(std::is_const_v<T>)
	{
	}

	const std::shared_ptr<const void>& Object::Data() const noexcept
	{
		return data;
	}

	const void* Object::Pointer() const noexcept
	{
		return data.get();
	}

	std::type_index Object::Type() const noexcept
	{
		return type;
	}

	bool Object::IsConst() const noexcept
	{
		return isConst;
	}

	template<typename T>
	bool Object::IsCastable() const noexcept
	{
		if constexpr (!std::is_void_v<T>)
		{
			if (typeid(T) != type)
			{
				return false;
			}
		}
		if constexpr (!std::is_const_v<T>)
		{
			if (isConst)
			{
				return false;
			}
		}

		return true;
	}

	bool Object::IsCastable(const std::type_index type, const bool isConst) const noexcept
	{
		if (type != typeid(void) && type != this->type)
		{
			return false;
		}
		if (!isConst && this->isConst)
		{
			return false;
		}

		return true;
	}

	bool Object::HasData() const noexcept
	{
		return static_cast<bool>(data);
	}

	template<typename T>
	T* Object::Get() const noexcept
	{
		Validate<T>();

		const auto ptr = const_cast<Intermediate<T>*>(data.get());
		return static_cast<T*>(ptr);
	}

	template<typename T>
	std::shared_ptr<T> Object::GetShared() const noexcept
	{
		Validate<T>();

		auto ptr = std::const_pointer_cast<Intermediate<T>>(data);
		return std::static_pointer_cast<T>(std::move(ptr));
	}

	void Object::Reset() noexcept
	{
		*this = Object();
	}

	template<typename T>
	void Object::Reset(std::shared_ptr<T> data) noexcept
	{
		*this = Object(std::move(data));
	}

	Object::operator bool() const noexcept
	{
		return static_cast<bool>(data);
	}

	template<typename T>
	void Object::Validate()
	{
		if constexpr (!std::is_void_v<T>)
		{
			assert(typeid(T) == type && "Invalid type.");
		}
		if constexpr (!std::is_const_v<T>)
		{
			assert(!isConst && "Object is const.");
		}
	}
}

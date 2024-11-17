/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyBase.Memory:UniquePointer;

import <concepts>;
import <type_traits>;
import <utility>;

namespace PonyBase::Memory // TODO: Remove file
{
	/// @brief Object owner.
	///	@details It deletes an owned object on its destruction.
	class Owner
	{
	public:
		Owner(const Owner&) = delete;

		/// @brief Deletes the owned object.
		virtual ~Owner() noexcept = 0;

		Owner& operator =(const Owner&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		Owner() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Owner(Owner&& other) noexcept = default;

		Owner& operator =(Owner&& other) noexcept = default;
	};

	/// @brief Standard object owner.
	/// @tparam T Object type.
	template<std::destructible T>
	class StandardOwner final : public Owner
	{
	public:
		/// @brief Creates an object and a @p StandardOwner.
		/// @tparam Args Object constructor argument types.
		/// @param args Object constructor arguments.
		template<typename... Args> [[nodiscard("Pure constructor")]]
		explicit StandardOwner(Args&&... args) noexcept requires (std::is_constructible_v<T, Args...>);
		StandardOwner(const StandardOwner&) = delete;
		/// @brief Move constructor.
		/// @param other Source.
		[[nodiscard("Pure constructor")]]
		StandardOwner(StandardOwner&& other) noexcept;

		/// @brief Deletes the owned object.
		virtual ~StandardOwner() noexcept override;

		/// @brief Gets the owned object.
		/// @return Owned object.
		[[nodiscard("Pure function")]]
		T* Get() const noexcept;

		StandardOwner& operator =(const StandardOwner&) = delete;
		/// @brief Move assignment.
		/// @param other Source.
		/// @return @a This.
		StandardOwner& operator =(StandardOwner&& other) noexcept;

	private:
		T* object; ///< Owned object.
	};
}

export namespace PonyBase::Memory
{
	/// @brief Unique pointer.
	/// @tparam T Object type.
	template<typename T>
	class UniquePointer final
	{
	public:
		/// @brief Creates an empty @p UniquePointer.
		[[nodiscard("Pure constructor")]]
		UniquePointer() noexcept = default;
		UniquePointer(const UniquePointer&) = delete;
		/// @brief Move constructor.
		/// @param other Source.
		[[nodiscard("Pure constructor")]]
		UniquePointer(UniquePointer&& other) noexcept;
		/// @brief Move constructor with a type cast.
		/// @tparam U Source type.
		/// @param other Source.
		template<std::derived_from<T> U> [[nodiscard("Pure constructor")]]
		explicit UniquePointer(UniquePointer<U>&& other) noexcept;

		/// @brief Deletes the object.
		~UniquePointer() noexcept;

		/// @brief Creates an object and a @p UniquePointer.
		/// @tparam Args Object constructor argument types.
		/// @param args Object constructor arguments.
		/// @return Created @p UniquePointer.
		template<typename... Args> [[nodiscard("Pure constructor")]]
		static UniquePointer Create(Args&&... args) requires (std::destructible<T>&& std::is_constructible_v<T, Args...>);

		/// @brief Gets the object.
		/// @return Object.
		T* Get() const noexcept;
		/// @brief Deletes the object and resets the pointer to a default value.
		void Reset() noexcept;

		/// @brief Checks if the pointer has a live object.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		/// @brief Gets the object.
		/// @return Object.
		[[nodiscard("Pure operator")]]
		T& operator *() const noexcept;
		/// @brief Gets the object.
		/// @return Object.
		[[nodiscard("Pure operator")]]
		T* operator ->() const noexcept;

		UniquePointer& operator =(const UniquePointer&) = delete;
		/// @brief Move assignment.
		/// @param other Source.
		/// @return @a This.
		UniquePointer& operator =(UniquePointer&& other) noexcept;
		/// @brief Move assignment with a type cast.
		/// @tparam U Source type.
		/// @param other Source.
		/// @return @a This.
		template<std::derived_from<T> U>
		UniquePointer& operator =(UniquePointer<U>&& other) noexcept;

	private:
		/// @brief Creates a @p UniquePointer that points to the @p standardOwner object.
		/// @tparam U Object type.
		/// @param standardOwner Standard owner. Mustn't be nullptr.
		template<std::destructible U> [[nodiscard("Pure constructor")]]
		explicit UniquePointer(const StandardOwner<U>& standardOwner) noexcept requires (std::derived_from<U, T>);

		T* object; ///< Object.
		const Owner* owner; ///< Object owner.

		template<typename U>
		friend class UniquePointer;
	};
}

namespace PonyBase::Memory
{
	Owner::~Owner() noexcept
	{
	}

	template<std::destructible T>
	template<typename ... Args>
	StandardOwner<T>::StandardOwner(Args&&... args) noexcept requires (std::is_constructible_v<T, Args...>) :
		object{new T(std::forward<Args>(args)...)}
	{
	}

	template<std::destructible T>
	StandardOwner<T>::StandardOwner(StandardOwner&& other) noexcept :
		object{other.object}
	{
		other.object = nullptr;
	}

	template<std::destructible T>
	StandardOwner<T>::~StandardOwner() noexcept
	{
		delete object;
	}

	template<std::destructible T>
	T* StandardOwner<T>::Get() const noexcept
	{
		return object;
	}

	template<std::destructible T>
	StandardOwner<T>& StandardOwner<T>::operator =(StandardOwner&& other) noexcept
	{
		delete object;
		object = other.object;
		other.object = nullptr;

		return *this;
	}

	template<typename T>
	UniquePointer<T>::UniquePointer(UniquePointer&& other) noexcept :
		object{other.object},
		owner{other.owner}
	{
		other.object = nullptr;
		other.owner = nullptr;
	}

	template<typename T>
	template<std::derived_from<T> U>
	UniquePointer<T>::UniquePointer(UniquePointer<U>&& other) noexcept :
		object{other.object},
		owner{other.owner}
	{
		other.object = nullptr;
		other.owner = nullptr;
	}

	template<typename T>
	UniquePointer<T>::~UniquePointer() noexcept
	{
		Reset();
	}

	template<typename T>
	template<typename... Args>
	UniquePointer<T> UniquePointer<T>::Create(Args&&... args) requires (std::destructible<T> && std::is_constructible_v<T, Args...>)
	{
		const StandardOwner<T>* const owner = new StandardOwner<T>(std::forward<Args>(args)...);

		return UniquePointer(*owner);
	}

	template<typename T>
	T* UniquePointer<T>::Get() const noexcept
	{
		return object;
	}

	template<typename T>
	void UniquePointer<T>::Reset() noexcept
	{
		delete owner;
		object = nullptr;
		owner = nullptr;
	}

	template<typename T>
	UniquePointer<T>::operator bool() const noexcept
	{
		return object;
	}

	template<typename T>
	T& UniquePointer<T>::operator *() const noexcept
	{
		return *object;
	}

	template<typename T>
	T* UniquePointer<T>::operator ->() const noexcept
	{
		return object;
	}

	template<typename T>
	UniquePointer<T>& UniquePointer<T>::operator =(UniquePointer&& other) noexcept
	{
		delete owner;
		object = other.object;
		owner = other.owner;
		other.object = nullptr;
		other.owner = nullptr;

		return *this;
	}

	template<typename T>
	template<std::derived_from<T> U>
	UniquePointer<T>& UniquePointer<T>::operator =(UniquePointer<U>&& other) noexcept
	{
		delete owner;
		object = other.object;
		owner = other.owner;
		other.object = nullptr;
		other.owner = nullptr;

		return *this;
	}

	template<typename T>
	template<std::destructible U>
	UniquePointer<T>::UniquePointer(const StandardOwner<U>& standardOwner) noexcept requires (std::derived_from<U, T>) :
		object{standardOwner.Get()},
		owner{&standardOwner}
	{
	}
}

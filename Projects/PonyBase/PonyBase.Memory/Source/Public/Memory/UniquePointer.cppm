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

namespace PonyBase::Memory
{
	class Owner
	{
	public:
		Owner(const Owner&) = delete;

		virtual ~Owner() noexcept = 0;

		Owner& operator =(const Owner&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		Owner() noexcept = default;
		[[nodiscard("Pure constructor")]]
		Owner(Owner&& other) noexcept = default;

		Owner& operator =(Owner&& other) noexcept = default;
	};

	template<typename T>
	class StandardOwner final : public Owner
	{
	public:
		template<typename... Args> [[nodiscard("Pure constructor")]]
		explicit StandardOwner(Args&&... args) requires (std::is_constructible_v<T, Args...>);
		StandardOwner(const StandardOwner&) = delete;
		[[nodiscard("Pure constructor")]]
		StandardOwner(StandardOwner&& other) noexcept;

		virtual ~StandardOwner() noexcept override;

		[[nodiscard("Pure function")]]
		T* Get() const noexcept;

		StandardOwner& operator =(const StandardOwner&) = delete;
		StandardOwner& operator =(StandardOwner&& other) noexcept;

	private:
		T* object;
	};
}

export namespace PonyBase::Memory
{
	template<typename T>
	class UniquePointer final // TODO: Add docs and tests
	{
	public:
		template<typename... Args> [[nodiscard("Pure constructor")]]
		explicit UniquePointer(Args&&... args) requires (std::is_constructible_v<T, Args...>);
		UniquePointer(const UniquePointer&) = delete;
		[[nodiscard("Pure constructor")]]
		UniquePointer(UniquePointer&& other) noexcept;
		template<std::derived_from<T> U> [[nodiscard("Pure constructor")]]
		explicit UniquePointer(UniquePointer<U>&& other) noexcept;

		~UniquePointer() noexcept;

		T* Get() const noexcept;
		void Reset() noexcept;

		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		[[nodiscard("Pure operator")]]
		T& operator *() const noexcept;
		[[nodiscard("Pure operator")]]
		T* operator ->() const noexcept;

		UniquePointer& operator =(const UniquePointer&) = delete;
		UniquePointer& operator =(UniquePointer&& other) noexcept;
		template<std::derived_from<T> U>
		UniquePointer& operator =(UniquePointer<U>&& other) noexcept;

	private:
		[[nodiscard("Pure constructor")]]
		explicit UniquePointer(const StandardOwner<T>* standardOwner) noexcept;

		T* pointer;
		const Owner* owner;

		template<typename U>
		friend class UniquePointer;
	};
}

namespace PonyBase::Memory
{
	Owner::~Owner() noexcept
	{
	}

	template<typename T>
	template<typename... Args>
	StandardOwner<T>::StandardOwner(Args&&... args) requires (std::is_constructible_v<T, Args...>) :
		object(new T(std::forward<Args>(args)...))
	{
	}

	template<typename T>
	StandardOwner<T>::StandardOwner(StandardOwner&& other) noexcept :
		object{other.object}
	{
		other.object = nullptr;
	}

	template<typename T>
	StandardOwner<T>::~StandardOwner() noexcept
	{
		delete object;
	}

	template<typename T>
	T* StandardOwner<T>::Get() const noexcept
	{
		return object;
	}

	template<typename T>
	StandardOwner<T>& StandardOwner<T>::operator =(StandardOwner&& other) noexcept
	{
		delete object;
		object = other.object;
		other.object = nullptr;

		return *this;
	}

	template<typename T>
	template<typename... Args>
	UniquePointer<T>::UniquePointer(Args&&... args) requires (std::is_constructible_v<T, Args...>) :
		UniquePointer(new StandardOwner<T>(std::forward<Args>(args)...))
	{
	}

	template<typename T>
	UniquePointer<T>::UniquePointer(UniquePointer&& other) noexcept :
		pointer{other.pointer},
		owner{other.owner}
	{
		other.pointer = nullptr;
		other.owner = nullptr;
	}

	template<typename T>
	template<std::derived_from<T> U>
	UniquePointer<T>::UniquePointer(UniquePointer<U>&& other) noexcept :
		pointer{other.pointer},
		owner{other.owner}
	{
		other.pointer = nullptr;
		other.owner = nullptr;
	}

	template<typename T>
	UniquePointer<T>::~UniquePointer() noexcept
	{
		delete owner;
	}

	template<typename T>
	T* UniquePointer<T>::Get() const noexcept
	{
		return pointer;
	}

	template<typename T>
	void UniquePointer<T>::Reset() noexcept
	{
		delete owner;
		pointer = nullptr;
		owner = nullptr;
	}

	template<typename T>
	UniquePointer<T>::operator bool() const noexcept
	{
		return pointer;
	}

	template<typename T>
	T& UniquePointer<T>::operator *() const noexcept
	{
		return *pointer;
	}

	template<typename T>
	T* UniquePointer<T>::operator ->() const noexcept
	{
		return pointer;
	}

	template<typename T>
	UniquePointer<T>& UniquePointer<T>::operator =(UniquePointer&& other) noexcept
	{
		delete owner;
		pointer = other.pointer;
		owner = other.owner;
		other.pointer = nullptr;
		other.owner = nullptr;

		return *this;
	}

	template<typename T>
	template<std::derived_from<T> U>
	UniquePointer<T>& UniquePointer<T>::operator =(UniquePointer<U>&& other) noexcept
	{
		delete owner;
		pointer = other.pointer;
		owner = other.owner;
		other.pointer = nullptr;
		other.owner = nullptr;

		return *this;
	}

	template<typename T>
	UniquePointer<T>::UniquePointer(const StandardOwner<T>* standardOwner) noexcept :
		pointer{standardOwner->Get()},
		owner{standardOwner}
	{
	}
}

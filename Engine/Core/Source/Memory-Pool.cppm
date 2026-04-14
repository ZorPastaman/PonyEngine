/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Memory:Pool;

import std;

export namespace PonyEngine::Memory
{
	/// @brief Pool memory.
	/// @tparam T Object type.
	template<typename T>
	class Pool final
	{
	public:
		/// @brief Pool object. It returns an object to a pool automatically when out of scope.
		/// @note The object must be destroyed before its pool is destroyed.
		class Object final
		{
		public:
			Object(const Object&) = delete;
			[[nodiscard("Pure constructor")]]
			Object(Object&& other) noexcept;

			~Object() noexcept;

			/// @brief Gets a pointer to the object.
			/// @return Object pointer.
			[[nodiscard("Pure function")]]
			T* Get() const noexcept;

			/// @brief Gets a reference to the object.
			/// @return Object reference.
			[[nodiscard("Pure operator")]]
			T& operator *() const noexcept;
			/// @brief Gets a pointer to the object.
			/// @return Object pointer.
			[[nodiscard("Pure operator")]]
			T* operator ->() const noexcept;

			/// @brief Check if the object is alive.
			/// @return @a True if it's alive; @a false otherwise.
			[[nodiscard("Pure operator")]]
			explicit operator bool() const noexcept;

			Object& operator =(const Object&) = delete;
			Object& operator =(Object&& other) noexcept;

		private:
			/// @brief Creates a pool object.
			/// @param object Object.
			/// @param pool Pool
			[[nodiscard("Pure constructor")]]
			Object(T& object, Pool& pool) noexcept;

			T* object; ///< Object.
			Pool* pool; ///< Pool.

			friend Pool;
		};

		/// @brief Creates a pool.
		/// @param create Create function.
		/// @param acquire Acquire callback.
		/// @param release Release callback.
		/// @param utility Utility function. It's used to determine what object to delete on reaching a max size.
		/// @param maxSize Max size. It affects only inactive objects.
		[[nodiscard("Pure constructor")]]
		Pool(const std::function<std::unique_ptr<T, std::function<void(T*)>>()>& create, const std::function<void(T&)>& acquire, const std::function<void(T&)>& release,
			const std::function<std::uint64_t(const T&)>& utility, std::size_t maxSize);
		Pool(const Pool&) = delete;
		Pool(Pool&&) = delete;

		~Pool() noexcept = default;

		/// @brief Acquires an object.
		/// @return Object.
		/// @note When it's not needed anymore, call @p Release().
		[[nodiscard("Wierd call")]]
		T& Acquire();
		/// @brief Releases a previously acquired object.
		/// @param object Object to release.
		void Release(const T& object);
		/// @brief Acquires an object and returns it in a wrapper that automatically releases it when out of scope.
		/// @return Object.
		[[nodiscard("Wierd call")]]
		Object Lease();

		/// @brief Gets the inactive object max count.
		/// @return Max size.
		[[nodiscard("Pure function")]]
		std::size_t MaxSize() const noexcept;
		/// @brief Gets a current active object count.
		/// @return Active object count.
		[[nodiscard("Pure function")]]
		std::size_t ActiveCount() const noexcept;
		/// @brief Gets an inactive object count.
		/// @return Inactive object count.
		[[nodiscard("Pure function")]]
		std::size_t InactiveCount() const noexcept;

		Pool& operator =(const Pool&) = delete;
		Pool& operator =(Pool&&) = delete;

	private:
		/// @brief Takes an object from the inactive pool.
		/// @return Object.
		[[nodiscard("Wierd call")]]
		std::unique_ptr<T, std::function<void(T*)>> GetFromInactive();
		/// @brief Puts the object into the inactive pool.
		/// @param object Object.
		void PutIntoInactive(std::unique_ptr<T, std::function<void(T*)>>&& object);

		std::function<std::unique_ptr<T, std::function<void(T*)>>()> create; ///< Create function.
		std::function<void(T&)> acquire; ///< Acquire function.
		std::function<void(T&)> release; ///< Release function.
		std::function<std::uint64_t(const T&)> utility; ///< Utility function.

		std::size_t maxSize; ///< Inactive max size.

		std::vector<std::unique_ptr<T, std::function<void(T*)>>> inactive; ///< Inactive objects.
		std::vector<std::unique_ptr<T, std::function<void(T*)>>> active; ///< Active objects.
	};
}

namespace PonyEngine::Memory
{
	template<typename T>
	Pool<T>::Object::Object(Object&& other) noexcept : 
		object{other.object}, 
		pool{other.pool}
	{
		other.object = nullptr;
		other.pool = nullptr;
	}

	template<typename T>
	Pool<T>::Object::~Object() noexcept
	{
		if (object)
		{
			pool->Release(*object);
		}
	}

	template<typename T>
	T* Pool<T>::Object::Get() const noexcept
	{
		return object;
	}

	template<typename T>
	T& Pool<T>::Object::operator *() const noexcept
	{
		return *object;
	}

	template<typename T>
	T* Pool<T>::Object::operator ->() const noexcept
	{
		return object;
	}

	template<typename T>
	Pool<T>::Object::operator bool() const noexcept
	{
		return object;
	}

	template<typename T>
	Pool<T>::Object& Pool<T>::Object::operator =(Object&& other) noexcept
	{
		if (object)
		{
			pool->Release(*object);
		}

		object = other.object;
		pool = other.pool;

		other.object = nullptr;
		other.pool = nullptr;

		return *this;
	}

	template<typename T>
	Pool<T>::Object::Object(T& object, Pool& pool) noexcept : 
		object{&object}, 
		pool{&pool}
	{
	}

	template<typename T>
	Pool<T>::Pool(const std::function<std::unique_ptr<T, std::function<void(T*)>>()>& create, const std::function<void(T&)>& acquire,
		const std::function<void(T&)>& release, const std::function<std::uint64_t(const T&)>& utility, const std::size_t maxSize) :
		create(create),
		acquire(acquire),
		release(release),
		utility(utility),
		maxSize{std::max(maxSize, 1uz)}
	{
	}

	template<typename T>
	T& Pool<T>::Acquire()
	{
		std::unique_ptr<T, std::function<void(T*)>> acquired = inactive.empty() ? create() : GetFromInactive();
		T& ref = *acquired;
		acquire(ref);
		active.push_back(std::move(acquired));

		return ref;
	}

	template<typename T>
	void Pool<T>::Release(const T& object)
	{
		if (const auto position = std::ranges::find_if(active, [&](const std::unique_ptr<T, std::function<void(T*)>>& p){ return p.get() == &object; });
			position != active.cend()) [[likely]]
		{
			std::unique_ptr<T, std::function<void(T*)>> released = std::move(*position);
			active.erase(position);
			release(*released);
			PutIntoInactive(std::move(released));
		}
		else
		{
			throw std::invalid_argument("The object does not belong to this pool");
		}
	}

	template<typename T>
	Pool<T>::Object Pool<T>::Lease()
	{
		return Object(Acquire(), *this);
	}

	template<typename T>
	std::size_t Pool<T>::MaxSize() const noexcept
	{
		return maxSize;
	}

	template<typename T>
	std::size_t Pool<T>::ActiveCount() const noexcept
	{
		return active.size();
	}

	template<typename T>
	std::size_t Pool<T>::InactiveCount() const noexcept
	{
		return inactive.size();
	}

	template<typename T>
	std::unique_ptr<T, std::function<void(T*)>> Pool<T>::GetFromInactive()
	{
		std::unique_ptr<T, std::function<void(T*)>> object = std::move(inactive.back());
		inactive.pop_back();

		return object;
	}

	template<typename T>
	void Pool<T>::PutIntoInactive(std::unique_ptr<T, std::function<void(T*)>>&& object)
	{
		if (inactive.size() < maxSize)
		{
			inactive.push_back(std::move(object));
		}
		else
		{
			const std::uint64_t objectUtility = utility(*object);
			const auto position = std::ranges::find_if(inactive, [&](const std::unique_ptr<T, std::function<void(T*)>>& p) { return utility(*p) < objectUtility; });
			if (position != inactive.cend())
			{
				inactive.erase(position);
				inactive.push_back(std::move(object));
			}
		}
	}
}

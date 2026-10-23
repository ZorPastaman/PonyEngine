/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Utility:ScopeGuard;

import std;

export namespace PonyEngine::Utility
{
	/// @brief Concept that is satisfied if the @p F is a function with the signature void() noexcept.
	/// @tparam F Type to check.
	template<typename F>
	concept ScopeGuardFunc = requires(F& func)
	{
		{ func() } noexcept -> std::same_as<void>;
	};

	/// @brief Scope guard flag.
	/// @details It allows to release multiple scope guards with one release call.
	class ScopeGuardFlag final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ScopeGuardFlag() noexcept;
		ScopeGuardFlag(const ScopeGuardFlag&) = delete;
		ScopeGuardFlag(ScopeGuardFlag&&) = delete;

		~ScopeGuardFlag() noexcept = default;

		/// @brief Checks if the flag is active.
		/// @return @a True if it's active; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsActive() const noexcept;
		/// @brief Releases the flag.
		void Release() noexcept;

		ScopeGuardFlag& operator =(const ScopeGuardFlag&) = delete;
		ScopeGuardFlag& operator =(ScopeGuardFlag&&) = delete;

	private:
		bool isActive; ///< Is the flag active?
	};

	/// @brief Scope guard.
	/// @details Executes a function on destruction if it's not released.
	/// @tparam F Function type.
	template<ScopeGuardFunc F>
	class ScopeGuard final
	{
	public:
		/// @brief Creates a scope guard.
		/// @param func Function to execute.
		[[nodiscard("Pure constructor")]]
		explicit ScopeGuard(F func) noexcept;
		/// @brief Creates a scope guard.
		/// @param func Function to execute.
		/// @param flag Scope guard flag. The guard will execute the function only if the flag is active.
		[[nodiscard("Pure constructor")]]
		ScopeGuard(F func, const ScopeGuardFlag& flag) noexcept;
		ScopeGuard(const ScopeGuard&) = delete;
		ScopeGuard(ScopeGuard&&) = delete;

		~ScopeGuard() noexcept;

		/// @brief Gets the function.
		/// @return Function.
		[[nodiscard("Pure function")]]
		const F& Function() const noexcept;
		/// @brief Gets the flag.
		/// @return Flag.
		[[nodiscard("Pure function")]]
		const ScopeGuardFlag* Flag() const noexcept;
		/// @brief Checks if the guard is active.
		/// @return @a True if it's active; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsActive() const noexcept;
		/// @brief Releases the guard.
		void Release() noexcept;
		/// @brief Removes the flag.
		void Detach() noexcept;

		ScopeGuard& operator =(const ScopeGuard&) = delete;
		ScopeGuard& operator =(ScopeGuard&&) = delete;

	private:
		F func; ///< Function to execute on destruction.
		const ScopeGuardFlag* flag; ///< Guard flag.
		bool isActive; ///< Is the guard active?
	};
}

namespace PonyEngine::Utility
{
	ScopeGuardFlag::ScopeGuardFlag() noexcept :
		isActive{true}
	{
	}

	bool ScopeGuardFlag::IsActive() const noexcept
	{
		return isActive;
	}

	void ScopeGuardFlag::Release() noexcept
	{
		isActive = false;
	}

	template<ScopeGuardFunc F>
	ScopeGuard<F>::ScopeGuard(F func) noexcept :
		func(std::move(func)),
		flag{nullptr},
		isActive{true}
	{
	}

	template<ScopeGuardFunc F>
	ScopeGuard<F>::ScopeGuard(F func, const ScopeGuardFlag& flag) noexcept :
		func(std::move(func)),
		flag{&flag},
		isActive{true}
	{
	}

	template<ScopeGuardFunc F>
	ScopeGuard<F>::~ScopeGuard() noexcept
	{
		if (isActive && (!flag || flag->IsActive()))
		{
			std::invoke(func);
		}
	}

	template<ScopeGuardFunc F>
	const F& ScopeGuard<F>::Function() const noexcept
	{
		return func;
	}

	template<ScopeGuardFunc F>
	const ScopeGuardFlag* ScopeGuard<F>::Flag() const noexcept
	{
		return flag;
	}

	template<ScopeGuardFunc F>
	bool ScopeGuard<F>::IsActive() const noexcept
	{
		return isActive;
	}

	template<ScopeGuardFunc F>
	void ScopeGuard<F>::Release() noexcept
	{
		isActive = false;
	}

	template<ScopeGuardFunc F>
	void ScopeGuard<F>::Detach() noexcept
	{
		flag = nullptr;
	}
}

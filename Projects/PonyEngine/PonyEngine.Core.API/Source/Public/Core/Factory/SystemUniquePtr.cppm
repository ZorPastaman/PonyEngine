/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:SystemUniquePtr;

import <memory>;

import PonyEngine.Core;

import :ISystemDestroyer;

export namespace PonyEngine::Core
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

		/// @brief Gets the system destroyer.
		/// @return System destroyer.
		[[nodiscard("Pure function")]]
		ISystemDestroyer* SystemDestroyer() const noexcept;

		/// @brief Deletes the @p system.
		/// @param system System to delete.
		void operator ()(ISystem* system) const noexcept;

		SystemDeleter& operator =(const SystemDeleter& other) noexcept = default;
		SystemDeleter& operator =(SystemDeleter&& other) noexcept = default;

	private:
		ISystemDestroyer* destroyer; ///< System destroyer.
	};

	using SystemUniquePtr = std::unique_ptr<ISystem, SystemDeleter>; ///< System unique_ptr typedef.
}

namespace PonyEngine::Core
{
	SystemDeleter::SystemDeleter(ISystemDestroyer& destroyer) noexcept :
		destroyer{&destroyer}
	{
	}

	ISystemDestroyer* SystemDeleter::SystemDestroyer() const noexcept
	{
		return destroyer;
	}

	void SystemDeleter::operator ()(ISystem* const system) const noexcept
	{
		if (destroyer)
		{
			destroyer->Destroy(system);
		}
	}
}

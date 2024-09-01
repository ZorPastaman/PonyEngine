/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:SystemFactoryUniquePtr;

import <memory>;

import :ISystemFactoryDestroyer;

export namespace PonyEngine::Core
{
	/// @brief System factory deleter.
	class SystemFactoryDeleter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		SystemFactoryDeleter() noexcept = default;
		/// @brief Creates a @p SystemFactoryDeleter.
		/// @param destroyer System factory destroyer to use.
		[[nodiscard("Pure constructor")]]
		explicit SystemFactoryDeleter(ISystemFactoryDestroyer& destroyer) noexcept;
		[[nodiscard("Pure constructor")]]
		SystemFactoryDeleter(const SystemFactoryDeleter& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		SystemFactoryDeleter(SystemFactoryDeleter&& other) noexcept = default;

		~SystemFactoryDeleter() noexcept = default;

		/// @brief Gets the system factory destroyer.
		/// @return System factory destroyer.
		[[nodiscard("Pure function")]]
		ISystemFactoryDestroyer* SystemFactoryDestroyer() const noexcept;

		/// @brief Deletes the @p factory.
		/// @param factory System factory to delete.
		void operator ()(ISystemFactory* factory) const noexcept;

		SystemFactoryDeleter& operator =(const SystemFactoryDeleter& other) noexcept = default;
		SystemFactoryDeleter& operator =(SystemFactoryDeleter&& other) noexcept = default;

	private:
		ISystemFactoryDestroyer* destroyer; ///< System factory destroyer.
	};

	using SystemFactoryUniquePtr = std::unique_ptr<ISystemFactory, SystemFactoryDeleter>; ///< System factory unique_ptr typedef.
}

namespace PonyEngine::Core
{
	SystemFactoryDeleter::SystemFactoryDeleter(ISystemFactoryDestroyer& destroyer) noexcept :
		destroyer{&destroyer}
	{
	}

	ISystemFactoryDestroyer* SystemFactoryDeleter::SystemFactoryDestroyer() const noexcept
	{
		return destroyer;
	}

	void SystemFactoryDeleter::operator ()(ISystemFactory* const factory) const noexcept
	{
		if (destroyer) [[likely]]
		{
			destroyer->Destroy(factory);
		}
	}
}

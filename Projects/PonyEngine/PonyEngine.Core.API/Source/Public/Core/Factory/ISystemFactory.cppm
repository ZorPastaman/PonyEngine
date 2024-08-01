/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:ISystemFactory;

import <memory>;

import PonyEngine.Core;

import :SystemDeleter;

export namespace PonyEngine::Core
{
	using SystemUniquePtr = std::unique_ptr<ISystem, SystemDeleter>;

	/// @brief System factory.
	class ISystemFactory
	{
	public:
		ISystemFactory(const ISystemFactory&) = delete;
		ISystemFactory(ISystemFactory&&) = delete;

		/// @brief Creates a system.
		/// @param engine Engine that owns the system.
		/// @return Created system.
		[[nodiscard("Pure function")]]
		virtual SystemUniquePtr Create(IEngine& engine) = 0;

		/// @brief Gets the system factory name.
		/// @return System factory name.
		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept = 0;

		/// @brief Gets the system static name.
		/// @return System static name.
		[[nodiscard("Pure function")]]
		virtual const char* GetSystemName() const noexcept = 0;

		ISystemFactory& operator =(const ISystemFactory&) = delete;
		ISystemFactory& operator =(ISystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure function")]]
		ISystemFactory() noexcept = default;

		~ISystemFactory() noexcept = default;
	};
}

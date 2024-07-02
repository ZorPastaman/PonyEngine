/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factories:ISystemFactory;

import <utility>;

import PonyEngine.Core;
import PonyEngine.Utility;

import :ObjectInterfaces;

export namespace PonyEngine::Core
{
	/// @brief System factory.
	class ISystemFactory : public Utility::INamed
	{
	public:
		// TODO: return std::unique_ptr with a custom deleter.
		// TODO: add special return type to create to avoid std::pair.

		/// @brief Creates a system.
		/// @param engine Engine that owns the system.
		/// @return Created system and its public interfaces.
		[[nodiscard("Pure function")]]
		virtual std::pair<ISystem*, ObjectInterfaces> Create(IEngine& engine) = 0;
		/// @brief Destroys a previously created system.
		/// @param system System to destroy.
		virtual void Destroy(ISystem* system) noexcept = 0;

		/// @brief Gets a system name.
		/// @return System name.
		[[nodiscard("Pure function")]]
		virtual const char* GetSystemName() const noexcept = 0;

	protected:
		~ISystemFactory() noexcept = default;
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factories:ISystemFactory;

import PonyEngine.Utility;

import :SystemInfo;

export namespace PonyEngine::Core
{
	/// @brief System factory.
	class ISystemFactory : public Utility::INamed
	{
	public:
		/// @brief Creates a system.
		/// @param engine Engine that owns the system.
		/// @return Created system info.
		[[nodiscard("Pure function")]]
		virtual SystemInfo Create(IEngine& engine) = 0;

		/// @brief Gets a system static name.
		/// @return System static name.
		[[nodiscard("Pure function")]]
		virtual const char* GetSystemName() const noexcept = 0;

	protected:
		~ISystemFactory() noexcept = default;
	};
}

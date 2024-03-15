/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Factories:ISubLoggerFactory;

import PonyEngine.Core;
import PonyEngine.Debug.Log;

namespace PonyEngine::Debug::Log
{
	/// @brief Sub-logger factory.
	export class ISubLoggerFactory
	{
	public:
		/// @brief Creates a sub-logger.
		/// @param engine Engine that owns the sub-logger.
		/// @return Created sub-logger.
		[[nodiscard("Pure function")]]
		virtual ISubLogger* Create(Core::IEngine& engine) = 0;
		/// @brief Destroys a previously created sub-logger.
		/// @param subLogger Sub-logger to destroy.
		virtual void Destroy(ISubLogger* subLogger) noexcept = 0;

		/// @brief Gets a sub-logger name.
		/// @return Sub-logger name.
		virtual const char* GetSubLoggerName() const noexcept = 0;

	protected:
		inline virtual ~ISubLoggerFactory() noexcept = default;
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factories:IServiceFactory;

import PonyEngine.Core;

namespace PonyEngine::Core
{
	/// @brief Service factory.
	export class IServiceFactory
	{
	public:
		/// @brief Creates a service.
		/// @param engine Engine that owns the service.
		/// @return Created service.
		[[nodiscard("Pure function")]]
		virtual IService* Create(IEngine& engine) = 0;
		/// @brief Destroys a previously created service.
		/// @param service Service to destroy.
		virtual void Destroy(IService* service) noexcept = 0;

		virtual const char* GetServiceName() const noexcept = 0;

	protected:
		inline virtual ~IServiceFactory() noexcept = default;
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:ISystemFactory;

import <typeinfo>;

import :IEngineContext;
import :SystemData;
import :SystemParams;

export namespace PonyEngine::Core
{
	/// @brief System factory.
	class ISystemFactory
	{
	public:
		ISystemFactory(const ISystemFactory&) = delete;
		ISystemFactory(ISystemFactory&&) = delete;

		/// @brief Creates a system.
		/// @param engine Engine context.
		/// @param params System parameters.
		/// @return Created system data.
		[[nodiscard("Pure function")]]
		virtual SystemData Create(IEngineContext& engine, const SystemParams& params) = 0;

		/// @brief Gets a system type.
		/// @return System type.
		[[nodiscard("Pure function")]]
		virtual const std::type_info& SystemType() const noexcept = 0;

		ISystemFactory& operator =(const ISystemFactory&) = delete;
		ISystemFactory& operator =(ISystemFactory&&) = delete;

	protected:
		[[nodiscard("Pure function")]]
		ISystemFactory() noexcept = default;

		~ISystemFactory() noexcept = default;
	};
}

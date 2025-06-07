/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <memory>
#include <string_view>

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Core:IFactory;

export namespace PonyEngine::Core
{
	/// @brief Factory.
	/// @tparam T Factory output type.
	template<typename T>
	class IFactory // TODO: Move to another module
	{
		INTERFACE_BODY(IFactory)

		/// @brief Creates an object.
		/// @return Created object.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<T> Create() = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
	};
}

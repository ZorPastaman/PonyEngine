/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Resource:IResourceRequest;

import std;

import :IResourceRequestResult;
import :ResourceRequestStatus;
import :ResourceID;

export namespace PonyEngine::Resource
{
	/// @brief Resource request.
	class IResourceRequest
	{
		PONY_INTERFACE_BODY(IResourceRequest)

		/// @brief Gets a resource ID.
		/// @return Resource ID.
		/// @note The function is always valid to call.
		[[nodiscard("Pure function")]]
		virtual ResourceID ResourceID() const noexcept = 0;
		/// @brief Checks whether the resource is of type @p type.
		/// @param type The resource type to check against.
		/// @return @a true if the resource is of the specified type; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsTypeOf(std::type_index type) const noexcept;
		/// @brief Checks whether the resource is of types @p types.
		/// @param types The resource types to check against.
		/// @return @a true if the resource is of the specified types; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsTypeOf(std::span<const std::type_index> types) const noexcept = 0;
		/// @brief Checks whether the resource is of types @p Args.
		/// @tparam Args The resource types to check against.
		/// @return @a true if the resource is of the specified types; @a false otherwise.
		template<typename... Args> [[nodiscard("Pure function")]]
		bool IsTypeOf() const noexcept;
		
		/// @brief Gets the request status.
		/// @return Request status.
		[[nodiscard("Pure function")]]
		virtual ResourceRequestStatus Status() const noexcept = 0;
		/// @brief Gets a result of the request.
		/// @return Request result.
		/// @not It's valid to call it only if the request status is success.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<const IResourceRequestResult> Result() const = 0;
		/// @brief Gets an exception that occured during the request execution.
		/// @return Exception.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const = 0;

		/// @brief Cancels the request.
		virtual void Cancel() = 0;

		/// @brief Makes the thread sleep till the request is completed with success or failure or cancel.
		virtual void Wait() const noexcept = 0;
	};
}

namespace PonyEngine::Resource
{
	bool IResourceRequest::IsTypeOf(const std::type_index type) const noexcept
	{
		return IsTypeOf(std::span(&type, 1uz));
	}

	template<typename... Args>
	bool IResourceRequest::IsTypeOf() const noexcept
	{
		return IsTypeOf(std::array<std::type_index, sizeof...(Args)>{typeid(Args)...});
	}
}

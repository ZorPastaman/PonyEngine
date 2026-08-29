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

import PonyEngine.Async;

import :ResourceID;

export namespace PonyEngine::Resource
{
	/// @brief Resource request.
	class IResourceRequest : public Async::IRequest
	{
		PONY_INTERFACE_BODY(IResourceRequest)

		/// @brief Gets a resource ID.
		/// @return Resource ID.
		/// @note The function is always valid to call.
		[[nodiscard("Pure function")]]
		virtual ResourceID ResourceID() const noexcept = 0;
		/// @brief Checks whether the resource has an interface of type @p type.
		/// @param type Interface type to check against.
		/// @return @a True if the resource has an interface of the specified type; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasInterface(std::type_index type) const noexcept;
		/// @brief Checks whether the resource has interfaces of types @p types.
		/// @param types Interface types to check against.
		/// @return @a True if the resource has an interface of the specified type; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool HasInterfaces(std::span<const std::type_index> types) const noexcept = 0;
		/// @brief Checks whether the resource has interfaces of types @p Args.
		/// @tparam Args Interface types to check against.
		/// @return @a True if the resource has an interface of the specified type; @a false otherwise.
		template<typename... Args> [[nodiscard("Pure function")]]
		bool HasInterfaces() const noexcept;

		/// @brief Gets a resource.
		/// @param type Resource type. Must be one of the resource types.
		/// @return Resource.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<const void> Resource(std::type_index type) const = 0;
		/// @brief Gets a resource.
		/// @tparam T Resource type. Must be one of the resource types.
		/// @return Resource.
		template<typename T> [[nodiscard("Pure function")]]
		std::shared_ptr<const T> Resource() const;
		/// @brief Gets an exception that occured during the request execution.
		/// @return Exception.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const = 0;
	};
}

namespace PonyEngine::Resource
{
	bool IResourceRequest::HasInterface(const std::type_index type) const noexcept
	{
		return HasInterfaces(std::span(&type, 1uz));
	}

	template<typename... Args>
	bool IResourceRequest::HasInterfaces() const noexcept
	{
		return HasInterfaces(std::array<std::type_index, sizeof...(Args)>{typeid(Args)...});
	}

	template<typename T>
	std::shared_ptr<const T> IResourceRequest::Resource() const
	{
		return std::static_pointer_cast<const T>(Resource(typeid(T)));
	}
}

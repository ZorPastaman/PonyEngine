/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Resource.Ext:ILoadableDataAccess;

import std;

import PonyEngine.Async;

export namespace PonyEngine::Resource
{
	/// @brief Load parameters.
	struct LoadParams final
	{
		std::span<std::byte> buffer; ///< Target buffer.
		std::size_t offset = 0uz; ///< Read offset.
	};

	/// @brief Loadable data access request.
	class ILoadableDataAccessRequest : public Async::IRequest
	{
		PONY_INTERFACE_BODY(ILoadableDataAccessRequest)

		/// @brief Gets the request parameters.
		/// @return Request parameters.
		[[nodiscard("Pure function")]]
		virtual const LoadParams& Params() const noexcept = 0;

		/// @brief Gets how many bytes were transferred.
		/// @return Transferred byte count.
		/// @note It's valid to call it only if the request status is success.
		[[nodiscard("Pure function")]]
		virtual std::size_t ByteCount() const = 0;
		/// @brief Gets an exception that occured during the request execution.
		/// @return Exception.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const = 0;
	};

	/// @brief Loadable data access.
	class ILoadableDataAccess
	{
		PONY_INTERFACE_BODY(ILoadableDataAccess)

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;

		/// @brief Makes a load request.
		/// @param params Load parameters.
		/// @param callback Callback. Can be nullptr. It will be called on the caller thread or on an io thread. It may be called before the function returns.
		/// @return Load request. Must be destroyed before the access.
		/// @note The access, request, buffer and callback must be kept alive till the finish of the operation.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadableDataAccessRequest> Load(const LoadParams& params, 
			std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback = nullptr) = 0;
	};
}

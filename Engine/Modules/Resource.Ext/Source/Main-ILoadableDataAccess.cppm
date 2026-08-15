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
#include "PonyEngine/Type/Enum.h"

export module PonyEngine.Resource.Ext:ILoadableDataAccess;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Request status.
	enum class LoadableRequestStatus : std::uint8_t
	{
		Pending, ///< A request is still in progress.
		Success, ///< A request finished with a success.
		Failure, ///< A request finished with a failure.
		Canceled ///< A request was canceled.
	};

	/// @brief Loadable data access request.
	class ILoadableDataAccessRequest
	{
		PONY_INTERFACE_BODY(ILoadableDataAccessRequest)

		/// @brief Gets the request status.
		/// @return Request status.
		[[nodiscard("Pure function")]]
		virtual LoadableRequestStatus Status() const noexcept = 0;
		/// @brief Gets an exception that occured during the request execution.
		/// @return Exception.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const = 0;

		/// @brief Cancels the request.
		/// @note The cancel is not immediate, it may take some time to cancel the operation.
		///       And because of it, the request may complete event if you requested a cancel.
		virtual void Cancel() = 0;

		/// @brief Makes the thread sleep till the request is completed with success or failure or cancel.
		virtual void Wait() const noexcept = 0;
	};

	/// @brief Loadable data access request observer.
	class ILoadableDataAccessRequestObserver
	{
		PONY_INTERFACE_BODY(ILoadableDataAccessRequestObserver)

		/// @brief Invoked on a success.
		virtual void OnSuccess() noexcept = 0;
		/// @brief Invoked on a failure.
		/// @param exception Exception.
		virtual void OnFailure(const std::exception_ptr& exception) noexcept = 0;
		/// @brief Invoked on cancel.
		virtual void OnCancel() noexcept = 0;
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
		/// @param buffer Data buffer. Must be valid till the end of the operation.
		/// @param offset Read offset.
		/// @param observer Observer. Can be nullptr. Must be valid till the end of the operation.
		/// @return Load request.
		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadableDataAccessRequest> Load(std::span<std::byte> buffer, std::size_t offset, ILoadableDataAccessRequestObserver* observer = nullptr) = 0;
	};
}

namespace PonyEngine::Resource
{
	/// @brief Request status names.
	constexpr std::array<std::string_view, 4> LoadableRequestStatusNames
	{
		"Pending",
		"Success",
		"Failure",
		"Canceled"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::Resource::LoadableRequestStatus, PonyEngine::Resource::LoadableRequestStatusNames)
}

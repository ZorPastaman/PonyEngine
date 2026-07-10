/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.File.Impl:RequestVariant;

import std;

import PonyEngine.File;
import PonyEngine.Type;

import :ReadRequest;
import :WriteRequest;

export namespace PonyEngine::File
{
	/// @brief Wrapper that holds a variant of read and write requests.
	class RequestVariant final
	{
	public:
		/// @brief Creates a read request.
		/// @param params Read parameters.
		/// @param callback Request callback.
		[[nodiscard("Pure constructor")]]
		RequestVariant(const ReadParams& params, const std::function<void(const IReadRequest&)>& callback) noexcept;
		/// @brief Creates a write request.
		/// @param params Write parameters.
		/// @param callback Request callback.
		[[nodiscard("Pure constructor")]]
		RequestVariant(const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) noexcept;
		RequestVariant(const RequestVariant&) = delete;
		RequestVariant(RequestVariant&&) = delete;

		~RequestVariant() noexcept = default;

		/// @brief Checks if it's a read request.
		/// @return @a True if it's a read request; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsRead() const noexcept;
		/// @brief Checks if it's a write request.
		/// @return @a True if it's a write request; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsWrite() const noexcept;

		/// @brief Gets the read request.
		/// @return Read request.
		[[nodiscard("Pure function")]]
		ReadRequest& Read() noexcept;
		/// @brief Gets the read request.
		/// @return Read request.
		[[nodiscard("Pure function")]]
		const ReadRequest& Read() const noexcept;
		/// @brief Gets the write request.
		/// @return Write request.
		[[nodiscard("Pure function")]]
		WriteRequest& Write() noexcept;
		/// @brief Gets the write request.
		/// @return Write request.
		[[nodiscard("Pure function")]]
		const WriteRequest& Write() const noexcept;

		/// @brief Sets the status to success.
		/// @param byteCount Transferred byte count.
		void SetSuccess(std::size_t byteCount) noexcept;
		/// @brief Sets the status to failure.
		/// @param exception Exception that occured during the request execution.
		void SetFailed(const std::exception_ptr& exception) noexcept;

		RequestVariant& operator =(const RequestVariant&) = delete;
		RequestVariant& operator =(RequestVariant&&) = delete;

	private:
		std::variant<ReadRequest, WriteRequest> request; ///< Read/write request.
	};
}

namespace PonyEngine::File
{
	RequestVariant::RequestVariant(const ReadParams& params, const std::function<void(const IReadRequest&)>& callback) noexcept :
		request(std::in_place_type<ReadRequest>, params, callback)
	{
	}

	RequestVariant::RequestVariant(const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) noexcept :
		request(std::in_place_type<WriteRequest>, params, callback)
	{
	}

	bool RequestVariant::IsRead() const noexcept
	{
		return std::holds_alternative<ReadRequest>(request);
	}

	bool RequestVariant::IsWrite() const noexcept
	{
		return std::holds_alternative<WriteRequest>(request);
	}

	ReadRequest& RequestVariant::Read() noexcept
	{
		return std::get<ReadRequest>(request);
	}

	const ReadRequest& RequestVariant::Read() const noexcept
	{
		return std::get<ReadRequest>(request);
	}

	WriteRequest& RequestVariant::Write() noexcept
	{
		return std::get<WriteRequest>(request);
	}

	const WriteRequest& RequestVariant::Write() const noexcept
	{
		return std::get<WriteRequest>(request);
	}

	void RequestVariant::SetSuccess(const std::size_t byteCount) noexcept
	{
		std::visit(Type::Overload
		{
			[&](ReadRequest& readRequest)
			{
				readRequest.SetSuccess(byteCount);
			},
			[&](WriteRequest& writeRequest)
			{
				writeRequest.SetSuccess(byteCount);
			}
		}, request);
	}

	void RequestVariant::SetFailed(const std::exception_ptr& exception) noexcept
	{
		std::visit(Type::Overload
		{
			[&](ReadRequest& readRequest)
			{
				readRequest.SetFailure(exception);
			},
			[&](WriteRequest& writeRequest)
			{
				writeRequest.SetFailure(exception);
			}
		}, request);
	}
}

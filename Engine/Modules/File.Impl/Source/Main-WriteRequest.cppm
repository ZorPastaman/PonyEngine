/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.File.Impl:WriteRequest;

import std;

import PonyEngine.File;

import :IRequestController;
import :Request;

export namespace PonyEngine::File
{
	/// @brief Write request.
	class WriteRequest final : public IWriteRequest
	{
	public:
		/// @brief Creates a write request.
		/// @param controller Request controller.
		/// @param params Write parameters.
		[[nodiscard("Pure constructor")]]
		WriteRequest(IRequestController& controller, const WriteParams& params) noexcept;
		WriteRequest(const WriteRequest&) = delete;
		WriteRequest(WriteRequest&&) = delete;

		~WriteRequest() noexcept;

		[[nodiscard("Pure function")]]
		virtual const WriteParams& Params() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::size_t ByteCount() const override;
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		virtual void AddObserver(IWriteObserver& observer) const override;
		virtual void RemoveObserver(IWriteObserver& observer) const override;

		/// @brief Sets the status to success.
		/// @param byteCount Transferred byte count.
		void SetSuccess(std::size_t byteCount) noexcept;
		/// @brief Sets the status to failure.
		/// @param exception Exception that occured during the request execution.
		void SetFailure(const std::exception_ptr& exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		WriteRequest& operator =(const WriteRequest&) = delete;
		WriteRequest& operator =(WriteRequest&&) = delete;

	private:
		/// @brief Calls observers.
		void Observe() noexcept;

		IRequestController* controller; ///< Request controller.
		WriteParams params; ///< Write parameters.
		Request request; ///< Write request.

		mutable std::vector<IWriteObserver*> observers; ///< Observers.
		bool observerCalled; ///< Were observers called?
		mutable std::mutex observerMutex; ///< Observer mutex.
	};
}

namespace PonyEngine::File
{
	WriteRequest::WriteRequest(IRequestController& controller, const WriteParams& params) noexcept :
		controller{ &controller },
		params(params),
		observerCalled{ false }
	{
	}

	WriteRequest::~WriteRequest() noexcept
	{
		assert(observers.empty() && "Observers weren't removed.");
	}

	const WriteParams& WriteRequest::Params() const noexcept
	{
		return params;
	}

	RequestStatus WriteRequest::Status() const noexcept
	{
		return request.Status();
	}

	std::size_t WriteRequest::ByteCount() const
	{
		return request.ByteCount();
	}

	const std::exception_ptr& WriteRequest::Exception() const
	{
		return request.Exception();
	}

	void WriteRequest::Cancel()
	{
		controller->Cancel();
	}

	void WriteRequest::Wait() const noexcept
	{
		request.Wait();
	}

	void WriteRequest::AddObserver(IWriteObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);
		observers.push_back(&observer);

		if (observerCalled)
		{
			observer.OnStatusChanged(*this);
		}
	}

	void WriteRequest::RemoveObserver(IWriteObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);

		if (const auto position = std::ranges::find(observers, &observer); position != observers.cend()) [[likely]]
		{
			observers.erase(position);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Observer wasn't added");
		}
	}

	void WriteRequest::SetSuccess(const std::size_t byteCount) noexcept
	{
		request.SetSuccess(byteCount);
		Observe();
	}

	void WriteRequest::SetFailure(const std::exception_ptr& exception) noexcept
	{
		request.SetFailed(exception);
		Observe();
	}

	void WriteRequest::SetCanceled() noexcept
	{
		request.SetCanceled();
		Observe();
	}

	void WriteRequest::Observe() noexcept
	{
		const auto lock = std::lock_guard(observerMutex);

		for (IWriteObserver* const observer : observers)
		{
			observer->OnStatusChanged(*this);
		}

		observerCalled = true;
	}
}

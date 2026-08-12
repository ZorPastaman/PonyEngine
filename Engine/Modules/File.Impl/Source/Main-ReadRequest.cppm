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

export module PonyEngine.File.Impl:ReadRequest;

import std;

import PonyEngine.File;

import :IRequestController;
import :Request;

export namespace PonyEngine::File
{
	/// @brief Read request.
	class ReadRequest final : public IReadRequest
	{
	public:
		/// @brief Creates a read request.
		/// @param controller Request controller.
		/// @param params Read parameters.
		[[nodiscard("Pure constructor")]]
		ReadRequest(IRequestController& controller, const ReadParams& params) noexcept;
		ReadRequest(const ReadRequest&) = delete;
		ReadRequest(ReadRequest&&) = delete;

		~ReadRequest() noexcept;

		[[nodiscard("Pure function")]] 
		virtual const ReadParams& Params() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t ByteCount() const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		virtual void AddObserver(IReadObserver& observer) const override;
		virtual void RemoveObserver(IReadObserver& observer) const override;

		/// @brief Sets the status to success.
		/// @param byteCount Transferred byte count.
		void SetSuccess(std::size_t byteCount) noexcept;
		/// @brief Sets the status to failure.
		/// @param exception Exception that occured during the request execution.
		void SetFailure(const std::exception_ptr& exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		ReadRequest& operator =(const ReadRequest&) = delete;
		ReadRequest& operator =(ReadRequest&&) = delete;

	private:
		/// @brief Calls observers.
		void Observe() noexcept;

		IRequestController* controller; ///< Request controller.
		ReadParams params; ///< Read parameters.
		Request request; ///< Read request.

		mutable std::vector<IReadObserver*> observers; ///< Observers.
		bool observerCalled; ///< Were observers called?
		mutable std::mutex observerMutex; ///< Observer mutex.
	};
}

namespace PonyEngine::File
{
	ReadRequest::ReadRequest(IRequestController& controller, const ReadParams& params) noexcept :
		controller{&controller},
		params(params),
		observerCalled{false}
	{
	}

	ReadRequest::~ReadRequest() noexcept
	{
		assert(observers.empty() && "Observers weren't removed.");
	}

	const ReadParams& ReadRequest::Params() const noexcept
	{
		return params;
	}

	RequestStatus ReadRequest::Status() const noexcept
	{
		return request.Status();
	}

	std::size_t ReadRequest::ByteCount() const
	{
		return request.ByteCount();
	}

	const std::exception_ptr& ReadRequest::Exception() const
	{
		return request.Exception();
	}

	void ReadRequest::Cancel()
	{
		controller->Cancel();
	}

	void ReadRequest::Wait() const noexcept
	{
		request.Wait();
	}

	void ReadRequest::AddObserver(IReadObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);
		observers.push_back(&observer);

		if (observerCalled)
		{
			observer.OnStatusChanged(*this);
		}
	}

	void ReadRequest::RemoveObserver(IReadObserver& observer) const
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

	void ReadRequest::SetSuccess(const std::size_t byteCount) noexcept
	{
		request.SetSuccess(byteCount);
		Observe();
	}

	void ReadRequest::SetFailure(const std::exception_ptr& exception) noexcept
	{
		request.SetFailed(exception);
		Observe();
	}

	void ReadRequest::SetCanceled() noexcept
	{
		request.SetCanceled();
		Observe();
	}

	void ReadRequest::Observe() noexcept
	{
		const auto lock = std::lock_guard(observerMutex);

		for (IReadObserver* const observer : observers)
		{
			observer->OnStatusChanged(*this);
		}

		observerCalled = true;
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application:ScopedTempBuffer;

import :IApplication;
import :TempBuffer;

export namespace PonyEngine::Application
{
	class ScopedTempBuffer final
	{
	public:
		/// @brief Creates an empty scoped temporary buffer.
		[[nodiscard("Pure constructor")]]
		ScopedTempBuffer() noexcept;
		/// @brief Creates a scoped temporary buffer.
		/// @param application Application.
		/// @param requiredSize Required size.
		/// @param requiredAlignment Required alignment. Must be a valid alignment value and at least alignof(std::max_align_t).
		/// @note Each thread has its own pool of buffers.
		/// @note The buffer must be destroyed on the same thread it was acquired.
		[[nodiscard("Pure constructor")]]
		ScopedTempBuffer(IApplication& application, std::size_t requiredSize, std::size_t requiredAlignment = alignof(std::max_align_t));
		ScopedTempBuffer(const ScopedTempBuffer&) = delete;
		[[nodiscard("Pure constructor")]]
		ScopedTempBuffer(ScopedTempBuffer&& other) noexcept;

		~ScopedTempBuffer() noexcept;

		/// @brief Releases the temporary buffer.
		void Release() noexcept;
		/// @brief Forgets the temporary buffer.
		void Forget() noexcept;

		/// @brief Gets the buffer.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		const std::span<std::byte>* Get() const noexcept;
		/// @brief Gets the temp buffer.
		/// @return Temp buffer.
		[[nodiscard("Pure function")]]
		const TempBuffer& Buffer() const noexcept;
		/// @brief Gets the application.
		/// @return Application.
		[[nodiscard("Pure function")]]
		IApplication* Application() const noexcept;

		/// @brief Checks if it has a valid buffer.
		[[nodiscard("Pure operator")]]
		explicit operator bool() const noexcept;

		[[nodiscard("Pure operator")]]
		const std::span<std::byte>& operator *() const noexcept;
		[[nodiscard("Pure operator")]]
		const std::span<std::byte>* operator ->() const noexcept;

		ScopedTempBuffer& operator =(const ScopedTempBuffer&) = delete;
		ScopedTempBuffer& operator =(ScopedTempBuffer&& other) noexcept;

	private:
		TempBuffer buffer; ///< Temporary buffer.
		IApplication* application; ///< Application.
	};
}

namespace PonyEngine::Application
{
	ScopedTempBuffer::ScopedTempBuffer() noexcept :
		application{nullptr}
	{
	}

	ScopedTempBuffer::ScopedTempBuffer(IApplication& application, const std::size_t requiredSize, const std::size_t requiredAlignment) :
		buffer(application.AcquireTempBuffer(requiredSize, requiredAlignment)),
		application{&application}
	{
	}

	ScopedTempBuffer::ScopedTempBuffer(ScopedTempBuffer&& other) noexcept :
		buffer(other.buffer),
		application{other.application}
	{
		other.Forget();
	}

	ScopedTempBuffer::~ScopedTempBuffer() noexcept
	{
		Release();
	}

	void ScopedTempBuffer::Release() noexcept
	{
		if (application)
		{
			application->ReleaseTempBuffer(buffer);
			Forget();
		}
	}

	void ScopedTempBuffer::Forget() noexcept
	{
		buffer = TempBuffer{};
		application = nullptr;
	}

	const std::span<std::byte>* ScopedTempBuffer::Get() const noexcept
	{
		return application ? &buffer.buffer : nullptr;
	}

	const TempBuffer& ScopedTempBuffer::Buffer() const noexcept
	{
		return buffer;
	}

	IApplication* ScopedTempBuffer::Application() const noexcept
	{
		return application;
	}

	ScopedTempBuffer::operator bool() const noexcept
	{
		return application;
	}

	const std::span<std::byte>& ScopedTempBuffer::operator *() const noexcept
	{
		return *Get();
	}

	const std::span<std::byte>* ScopedTempBuffer::operator ->() const noexcept
	{
		return Get();
	}

	ScopedTempBuffer& ScopedTempBuffer::operator =(ScopedTempBuffer&& other) noexcept
	{
		Release();
		buffer = other.buffer;
		application = other.application;
		other.Forget();

		return *this;
	}
}

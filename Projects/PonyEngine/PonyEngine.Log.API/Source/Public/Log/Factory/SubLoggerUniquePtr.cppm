/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Factory:SubLoggerUniquePtr;

import <memory>;

import :ISubLoggerDestroyer;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger deleter.
	class SubLoggerDeleter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		SubLoggerDeleter() noexcept = default;
		/// @brief Creates a @p SubLoggerDeleter.
		/// @param subLoggerDestroyer Logger destroyer to use.
		[[nodiscard("Pure constructor")]]
		explicit SubLoggerDeleter(ISubLoggerDestroyer& subLoggerDestroyer) noexcept;
		[[nodiscard("Pure constructor")]]
		SubLoggerDeleter(const SubLoggerDeleter& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		SubLoggerDeleter(SubLoggerDeleter&& other) noexcept = default;

		~SubLoggerDeleter() noexcept = default;

		/// @brief Gets the sub-logger destroyer.
		/// @return Sub-logger destroyer.
		[[nodiscard("Pure function")]]
		ISubLoggerDestroyer* SubLoggerDestroyer() const noexcept;

		/// @brief Destroys the @p subLogger.
		/// @param subLogger Sub-logger to destroy.
		void operator ()(ISubLogger* subLogger) const noexcept;

		SubLoggerDeleter& operator =(const SubLoggerDeleter& other) noexcept = default;
		SubLoggerDeleter& operator =(SubLoggerDeleter&& other) noexcept = default;

	private:
		ISubLoggerDestroyer* subLoggerDestroyer;
	};

	using SubLoggerUniquePtr = std::unique_ptr<ISubLogger, SubLoggerDeleter>; ///< Sub-logger unique_ptr typedef.
}

namespace PonyEngine::Log
{
	SubLoggerDeleter::SubLoggerDeleter(ISubLoggerDestroyer& subLoggerDestroyer) noexcept :
		subLoggerDestroyer{&subLoggerDestroyer}
	{
	}

	ISubLoggerDestroyer* SubLoggerDeleter::SubLoggerDestroyer() const noexcept
	{
		return subLoggerDestroyer;
	}

	void SubLoggerDeleter::operator ()(ISubLogger* const subLogger) const noexcept
	{
		if (subLoggerDestroyer)
		{
			subLoggerDestroyer->Destroy(subLogger);
		}
	}

}

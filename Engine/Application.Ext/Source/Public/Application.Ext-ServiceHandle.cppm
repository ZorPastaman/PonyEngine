/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Ext:ServiceHandle;

export namespace PonyEngine::Application
{
	/// @brief Service handle.
	struct ServiceHandle final
	{
		/// @brief Is the handle valid?
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsValid() const noexcept;

		const void* id = nullptr; ///< ID. It's used only by the owner.
	};
}

namespace PonyEngine::Application
{
	bool ServiceHandle::IsValid() const noexcept
	{
		return id;
	}
}

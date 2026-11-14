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

export module PonyEngine.Display:IDisplayService;

import :DisplayHandle;
import :DisplayInfo;

export namespace PonyEngine::Display
{
	/// @brief Display service.
	class IDisplayService
	{
		PONY_INTERFACE_BODY(IDisplayService)

		/// @brief Gets a display count.
		/// @return Display count.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::size_t DisplayCount() const noexcept = 0;
		/// @brief Gets a display handle.
		/// @param index Display index. Must be less than @p DisplayCount().
		/// @return Display handle.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual DisplayHandle Display(std::size_t index) const noexcept = 0;
		/// @brief Checks if the display handle is valid.
		/// @param displayHandle Display handle.
		/// @return @a True if it's valid; @a false otherwise.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual bool IsValid(DisplayHandle displayHandle) const noexcept = 0;
		/// @brief Checks if a display is connected.
		/// @param displayHandle Display handle. Must be valid.
		/// @return @a True if it's connected; @a false otherwise.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual bool IsConnected(DisplayHandle displayHandle) const noexcept =0;
		/// @brief Gets a display info.
		/// @param displayHandle Display handle. Must be valid.
		/// @return Display info.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual DisplayInfo DisplayInfo(DisplayHandle displayHandle) const noexcept = 0;
	};
}

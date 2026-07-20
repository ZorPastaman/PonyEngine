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
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Windows:IResourceProvider;

export namespace PonyEngine::Application::Windows
{
	/// @brief WinAPI resource provider.
	class IResourceProvider
	{
		PONY_INTERFACE_BODY(IResourceProvider)

		/// @brief Gets a main icon.
		/// @return Main icon. May be nullptr.
		/// @note Must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual HICON MainIcon() const = 0;

		// TODO: Add other functions later.
	};
}

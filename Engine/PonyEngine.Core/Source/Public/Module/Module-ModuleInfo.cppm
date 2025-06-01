/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <string_view>

export module PonyEngine.Module:ModuleInfo;

export namespace PonyEngine::Module
{
	/// @brief Module initializer function.
	using ModuleInitializer = void(*)();

	/// @brief Module info.
	struct ModuleInfo final
	{
		ModuleInitializer initializer = nullptr; ///< Module initializer.
		const std::string_view name; ///< Module name.
	};
}

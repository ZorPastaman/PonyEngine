/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <string_view>

#include "PonyEngine/Utility/Compiler.h"

import PonyEngine.Core;

namespace PonyEngine::Log::Core
{
	/// @brief Logger module.
	class PONY_DLL_EXPORT LoggerModule final : public PonyEngine::Core::IModule
	{
	public:
		virtual void StartUp(PonyEngine::Core::IModuleContext& context) override;
		virtual void ShutDown(const PonyEngine::Core::IModuleContext& context) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
	};
}

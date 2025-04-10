/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:LogicBlend;

import :LogicOperation;

export namespace PonyEngine::Render
{
	/// @brief Logic blend.
	struct LogicBlend final
	{
		LogicOperation operation = LogicOperation::Noop; ///< Logic blend operation.

		[[nodiscard("Pure operator")]]
		bool operator ==(const LogicBlend& other) const noexcept = default;
	};
}

/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:OpaqueBlend;

export namespace PonyEngine::Render
{
	/// @brief Opaque blend.
	struct OpaqueBlend final
	{
		[[nodiscard("Pure operator")]]
		bool operator ==(const OpaqueBlend& other) const noexcept = default;
	};
}

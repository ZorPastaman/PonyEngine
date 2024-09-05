/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Render/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12:Direct3D12SubSystem;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 sys-system.
	class Direct3D12SubSystem final
	{
	public:
	private:
#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> d3D12Debug;
#endif
	};
}

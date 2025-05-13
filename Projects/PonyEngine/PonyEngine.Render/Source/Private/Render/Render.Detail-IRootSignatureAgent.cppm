/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Detail:IRootSignatureAgent;

import :RootSignature;

export namespace PonyEngine::Render
{
	/// @brief Root signature agent.
	class IRootSignatureAgent
	{
		INTERFACE_BODY(IRootSignatureAgent)

		/// @brief Creates a GPU root signature.
		/// @param rootSignature CPU root signature.
		virtual void Create(const RootSignature& rootSignature) = 0;
		/// @brief Destroys a GPU root signature.
		/// @param rootSignature CPU root signature.
		virtual void Destroy(const RootSignature& rootSignature) = 0;
		/// @brief Updates a GPU root signature.
		/// @param rootSignature CPU root signature.
		virtual void Update(const RootSignature& rootSignature) = 0;
	};
}

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

export module PonyEngine.Render:IRootSignatureManager;

import <memory>;

import :IRootSignature;

import :RootSignatureParams;

export namespace PonyEngine::Render
{
	/// @brief Root signature manager.
	class IRootSignatureManager
	{
		INTERFACE_BODY(IRootSignatureManager)

		/// @brief Creates a root signature.
		/// @param params Root signature parameters.
		/// @return Root signature.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IRootSignature> CreateRootSignature(const RootSignatureParams& params) = 0;
	};
}
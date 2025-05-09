/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Detail:RootSignatureManager;

import <memory>;
import <stdexcept>;

import PonyBase.Utility;

import PonyEngine.Render;

import :Shader;

export namespace PonyEngine::Render
{
	class RootSignatureManager final : public IRootSignatureManager
	{
	public:
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IRootSignature> CreateRootSignature(const RootSignatureParams& params) override;
	};
}

namespace PonyEngine::Render
{
	std::shared_ptr<IRootSignature> RootSignatureManager::CreateRootSignature(const RootSignatureParams& params)
	{
		const auto shader = std::dynamic_pointer_cast<const Shader>(params.shader);
		if (!shader) [[unlikely]]
		{
			throw std::invalid_argument("Shader is nullptr.");
		}
	}
}

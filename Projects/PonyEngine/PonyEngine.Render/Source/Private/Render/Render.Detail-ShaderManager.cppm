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

export module PonyEngine.Render.Detail:ShaderManager;

import <cstddef>;
import <filesystem>;
import <fstream>;
import <memory>;
import <stdexcept>;
import <utility>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render;

import :IRenderSystemContext;
import :Shader;

export namespace PonyEngine::Render
{
	/// @brief Shader manager.
	class ShaderManager final : public IShaderManager
	{
	public:
		/// @brief Creates a shader manager.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constructor")]]
		explicit ShaderManager(IRenderSystemContext& renderSystem) noexcept;
		ShaderManager(const ShaderManager&) = delete;
		ShaderManager(ShaderManager&&) = delete;

		~ShaderManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IShader> CreateShader(const ShaderParams& params) override;

		/// @brief Cleans out dead shaders.
		void Clean() noexcept;

		ShaderManager& operator =(const ShaderManager&) = delete;
		ShaderManager& operator =(ShaderManager&&) = delete;

	private:
		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<std::pair<std::shared_ptr<Shader>, std::filesystem::path>> shaders; ///< Shaders.
	};
}

namespace PonyEngine::Render
{
	ShaderManager::ShaderManager(IRenderSystemContext& renderSystem) noexcept :
		renderSystem{&renderSystem}
	{
	}

	std::shared_ptr<IShader> ShaderManager::CreateShader(const ShaderParams& params)
	{
		for (const auto& [shader, path] : shaders) // TODO: Remake with resource system.
		{
			if (path == params.shaderPath)
			{
				return shader;
			}
		}

		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Read shader file.");
		auto stream = std::ifstream(params.shaderPath, std::ios::binary | std::ios::ate);
		if (!stream.is_open())
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to open shader file at '{}'.", params.shaderPath));
		}
		const std::size_t size = stream.tellg();
		stream.seekg(std::ios::beg);

		auto data = PonyBase::Container::Buffer(sizeof(char), size);
		if (!stream.read(reinterpret_cast<char*>(data.Data()), size))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to read shader file at '{}'.", params.shaderPath));
		}
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Info, "Shader file read.");

		const auto shader = std::make_shared<Shader>(std::move(data), params.name);
		shaders.push_back(std::pair(shader, params.shaderPath));

		return shader;
	}

	void ShaderManager::Clean() noexcept
	{
		for (std::size_t i = shaders.size(); i-- > 0; )
		{
			if (shaders[i].first.use_count() <= 1L)
			{
				shaders.erase(shaders.cbegin() + i);
			}
		}
	}
}

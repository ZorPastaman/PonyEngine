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

export module PonyEngine.Render.Direct3D12.Detail:ShaderManager;

import <memory>;
import <vector>;

import :IShaderManager;
import :ISubSystemContext;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	class ShaderManager final : public IShaderManager
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit ShaderManager(ISubSystemContext& d3d12System) noexcept;
		ShaderManager(const ShaderManager&) = delete;
		ShaderManager(ShaderManager&&) = delete;

		~ShaderManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Shader> CreateShader(std::string_view shaderPath) override;

		void Clean() noexcept;

		ShaderManager& operator =(const ShaderManager&) = delete;
		ShaderManager& operator =(ShaderManager&&) = delete;

	private:
		void Add(const std::shared_ptr<Shader>& shader, std::string_view shaderPath);
		void Remove(std::size_t index) noexcept;

		ISubSystemContext* d3d12System;

		std::vector<std::shared_ptr<Shader>> shaders;
		std::vector<std::string> shaderPaths;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	ShaderManager::ShaderManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Shader> ShaderManager::CreateShader(const std::string_view shaderPath)
	{
		for (std::size_t i = 0; i < shaderPaths.size(); ++i)
		{
			if (shaderPaths[i] == shaderPath)
			{
				return shaders[i];
			}
		}

		const std::string path = std::format("{}.cso", shaderPath);
		auto stream = std::ifstream(path, std::ios::binary | std::ios::ate);
		if (!stream.is_open())
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to open shader file at '{}'.", path));
		}
		const std::size_t size = stream.tellg();
		stream.seekg(std::ios::beg);

		auto data = PonyBase::Container::Buffer(static_cast<std::uint32_t>(sizeof(char)), static_cast<std::uint32_t>(size));
		if (!stream.read(reinterpret_cast<char*>(data.Data()), size))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to read shader file at '{}'.", path));
		}

		const auto shader = std::make_shared<Shader>(data);
		Add(shader, shaderPath);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Shader created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(shader.get()));

		return shader;
	}

	void ShaderManager::Clean() noexcept
	{
		for (std::size_t i = shaders.size(); i-- > 0; )
		{
			if (shaders[i].use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy shader at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(shaders[i].get()));
				Remove(i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Shader destroyed.");
			}
		}
	}

	void ShaderManager::Add(const std::shared_ptr<Shader>& shader, const std::string_view shaderPath)
	{
		const std::size_t currentSize = shaders.size();

		try
		{
			shaders.push_back(shader);
			shaderPaths.push_back(std::string(shaderPath));
		}
		catch (...)
		{
			shaders.resize(currentSize);
			shaderPaths.resize(currentSize);

			throw;
		}
	}

	void ShaderManager::Remove(const std::size_t index) noexcept
	{
		shaders.erase(shaders.cbegin() + index);
		shaderPaths.erase(shaderPaths.cbegin() + index);
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12:Direct3D12Shader;

import <cstddef>;
import <format>;
import <fstream>;
import <stdexcept>;
import <vector>;

import PonyBase.StringUtility;

export namespace PonyEngine::Render
{
	class Direct3D12Shader final // TODO: code here is too generic. So, maybe, it's better to make a generic class.
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12Shader(const char* shaderName);
		[[nodiscard("Pure constructor")]]
		Direct3D12Shader(const Direct3D12Shader& other) = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Shader(Direct3D12Shader&& other) noexcept = default;

		~Direct3D12Shader() noexcept = default;

		[[nodiscard("Pure function")]]
		const void* Data() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		Direct3D12Shader& operator =(const Direct3D12Shader& other) = default;
		Direct3D12Shader& operator =(Direct3D12Shader&& other) noexcept = default;

	private:
		std::vector<char> data;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Shader::Direct3D12Shader(const char* const shaderName)
	{
		const std::string path = std::format("{}.cso", shaderName);
		auto stream = std::ifstream(path, std::ios::binary | std::ios::ate);
		if (!stream.is_open())
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to open Direct3D 12 shader file at '{}'.", path));
		}
		const std::size_t size = stream.tellg();
		stream.seekg(std::ios::beg);

		data = std::vector<char>(size);
		if (!stream.read(data.data(), size))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to read Direct3D 12 shader file at '{}'.", path));
		}
	}

	const void* Direct3D12Shader::Data() const noexcept
	{
		return data.data();
	}

	std::size_t Direct3D12Shader::Size() const noexcept
	{
		return data.size();
	}
}

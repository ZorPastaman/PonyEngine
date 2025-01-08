/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Shader;

import <cstddef>;
import <format>;
import <fstream>;
import <stdexcept>;
import <string>;
import <string_view>;
import <vector>;

import PonyBase.Utility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 shader.
	class Shader final
	{
	public:
		/// @brief Creates a @p Shader.
		/// @param shaderName Shader name.
		[[nodiscard("Pure constructor")]]
		explicit Shader(std::string_view shaderName);
		[[nodiscard("Pure constructor")]]
		Shader(const Shader& other) = default;
		[[nodiscard("Pure constructor")]]
		Shader(Shader&& other) noexcept = default;

		~Shader() noexcept = default;

		/// @brief Gets the shader byte code.
		/// @return Shader byte code.
		[[nodiscard("Pure function")]]
		const char* Data() const noexcept;
		/// @brief Gets the shader byte code size.
		/// @return Shader byte code size in bytes.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;
		[[nodiscard("Pure function")]]
		D3D12_SHADER_BYTECODE ByteCode() const noexcept;

		Shader& operator =(const Shader& other) = default;
		Shader& operator =(Shader&& other) noexcept = default;

	private:
		std::vector<char> data; ///< Shader byte code.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Shader::Shader(const std::string_view shaderName)
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

	const char* Shader::Data() const noexcept
	{
		return data.data();
	}

	std::size_t Shader::Size() const noexcept
	{
		return data.size();
	}

	D3D12_SHADER_BYTECODE Shader::ByteCode() const noexcept
	{
		return D3D12_SHADER_BYTECODE{.pShaderBytecode = Data(), .BytecodeLength = Size()};
	}
}

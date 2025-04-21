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

import PonyBase.Container;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 shader.
	class Shader final
	{
	public:
		/// @brief Creates a shader.
		/// @param data Shader data.
		[[nodiscard("Pure constructor")]]
		explicit Shader(const PonyBase::Container::Buffer& data);
		[[nodiscard("Pure constructor")]]
		Shader(const Shader& other) = default;
		[[nodiscard("Pure constructor")]]
		Shader(Shader&& other) noexcept = default;

		~Shader() noexcept = default;

		/// @brief Gets the shader byte code.
		/// @return Shader byte code.
		[[nodiscard("Pure function")]]
		const std::byte* Data() const noexcept;
		/// @brief Gets the shader byte code size.
		/// @return Shader byte code size in bytes.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;
		/// @brief Gets the shader byte code.
		/// @return Shader byte code.
		[[nodiscard("Pure function")]]
		D3D12_SHADER_BYTECODE ByteCode() const noexcept;

		Shader& operator =(const Shader& other) = default;
		Shader& operator =(Shader&& other) noexcept = default;

	private:
		PonyBase::Container::Buffer data; ///< Shader byte code.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Shader::Shader(const PonyBase::Container::Buffer& data) :
		data(data)
	{
	}

	const std::byte* Shader::Data() const noexcept
	{
		return data.Data();
	}

	std::size_t Shader::Size() const noexcept
	{
		return data.Size();
	}

	D3D12_SHADER_BYTECODE Shader::ByteCode() const noexcept
	{
		return D3D12_SHADER_BYTECODE{.pShaderBytecode = Data(), .BytecodeLength = static_cast<SIZE_T>(Size())};
	}
}

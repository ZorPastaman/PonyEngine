/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:Shader;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class Shader final : public IShader
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Shader(std::span<const std::byte> byteCode);
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;

		~Shader() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> ByteCode() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		D3D12_SHADER_BYTECODE ShaderByteCode() const noexcept;

		Shader& operator =(const Shader&) = delete;
		Shader& operator =(Shader&&) = delete;

	private:
		std::vector<std::byte> byteCode;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Shader::Shader(const std::span<const std::byte> byteCode) :
		byteCode(byteCode.cbegin(), byteCode.cend())
	{
	}

	std::span<const std::byte> Shader::ByteCode() const noexcept
	{
		return byteCode;
	}

	std::string_view Shader::Name() const noexcept
	{
		return name;
	}

	void Shader::Name(const std::string_view name)
	{
		this->name = name;
	}

	D3D12_SHADER_BYTECODE Shader::ShaderByteCode() const noexcept
	{
		return D3D12_SHADER_BYTECODE{.pShaderBytecode = byteCode.data(), .BytecodeLength = static_cast<SIZE_T>(byteCode.size())};
	}
}

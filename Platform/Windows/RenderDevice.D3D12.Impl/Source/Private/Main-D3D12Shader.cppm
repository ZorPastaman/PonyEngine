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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Shader;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12Shader final : public IShader
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit D3D12Shader(std::span<const std::byte> byteCode);
		D3D12Shader(const D3D12Shader&) = delete;
		D3D12Shader(D3D12Shader&&) = delete;

		~D3D12Shader() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> ByteCode() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		D3D12_SHADER_BYTECODE ShaderByteCode() const noexcept;

		D3D12Shader& operator =(const D3D12Shader&) = delete;
		D3D12Shader& operator =(D3D12Shader&&) = delete;

	private:
		std::vector<std::byte> byteCode;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12Shader::D3D12Shader(const std::span<const std::byte> byteCode) :
		byteCode(byteCode.cbegin(), byteCode.cend())
	{
	}

	std::span<const std::byte> D3D12Shader::ByteCode() const noexcept
	{
		return byteCode;
	}

	std::string_view D3D12Shader::Name() const noexcept
	{
		return name;
	}

	void D3D12Shader::Name(const std::string_view name)
	{
		this->name = name;
	}

	D3D12_SHADER_BYTECODE D3D12Shader::ShaderByteCode() const noexcept
	{
		return D3D12_SHADER_BYTECODE{.pShaderBytecode = byteCode.data(), .BytecodeLength = static_cast<SIZE_T>(byteCode.size())};
	}
}

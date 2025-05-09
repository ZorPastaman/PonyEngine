/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:Shader;

import <cstddef>;
import <span>;
import <string>;
import <string_view>;
import <utility>;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	/// @brief Shader.
	class Shader final : public IShader
	{
	public:
		/// @brief Creates a shader.
		/// @param data Shader data.
		/// @param name Shader name.
		[[nodiscard("Pure contructor")]]
		Shader(PonyBase::Container::Buffer&& data, std::string_view name) noexcept;
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;

		~Shader() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> ByteCode() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		Shader& operator =(const Shader&) = delete;
		Shader& operator =(Shader&&) = delete;

	private:
		PonyBase::Container::Buffer data; ///< Shader data.

		std::string name; ///< Shader name.
	};
}

namespace PonyEngine::Render
{
	Shader::Shader(PonyBase::Container::Buffer&& data, const std::string_view name) noexcept :
		data(std::move(data)),
		name(name)
	{
	}

	std::span<const std::byte> Shader::ByteCode() const noexcept
	{
		return data.Span();
	}

	std::string_view Shader::Name() const noexcept
	{
		return name;
	}

	void Shader::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
	}
}

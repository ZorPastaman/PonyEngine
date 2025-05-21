/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:Attachment;

import <cstdint>;
import <string>;
import <string_view>;

import PonyMath.Utility;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	/// @brief Attachment.
	class Attachment final : public IAttachment
	{
	public:
		/// @brief Creates an attachment.
		/// @param format Texture format.
		/// @param size Texture resolution.
		/// @param sampleCount Sample count.
		[[nodiscard("Pure constructor")]]
		Attachment(TextureFormat format, const PonyMath::Utility::Resolution<std::uint32_t>& size, std::uint8_t sampleCount) noexcept;
		[[nodiscard("Pure constructor")]]
		Attachment(const Attachment&) = delete;
		[[nodiscard("Pure constructor")]]
		Attachment(Attachment&&) = delete;

		~Attachment() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual TextureFormat Format() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Utility::Resolution<std::uint32_t>& Size() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint8_t SampleCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		Attachment& operator =(const Attachment&) = delete;
		Attachment& operator =(Attachment&&) = delete;

	private:
		TextureFormat format; ///< Texture format.
		std::uint8_t sampleCount; ///< Sample count.
		PonyMath::Utility::Resolution<std::uint32_t> size; ///< Texture resolution.
		std::string_view name; ///< Texture name.
	};
}

namespace PonyEngine::Render
{
	Attachment::Attachment(const TextureFormat format, const PonyMath::Utility::Resolution<std::uint32_t>& size, const std::uint8_t sampleCount) noexcept :
		format{format},
		sampleCount{sampleCount},
		size(size)
	{
	}

	TextureFormat Attachment::Format() const noexcept
	{
		return format;
	}

	const PonyMath::Utility::Resolution<std::uint32_t>& Attachment::Size() const noexcept
	{
		return size;
	}

	std::uint8_t Attachment::SampleCount() const noexcept
	{
		return sampleCount;
	}

	std::string_view Attachment::Name() const noexcept
	{
		return name;
	}

	void Attachment::Name(const std::string_view name)
	{
		this->name = name;
	}
}

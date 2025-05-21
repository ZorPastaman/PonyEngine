/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:Material;

import <cstdint>;
import <memory>;
import <span>;
import <string>;
import <string_view>;
import <vector>;

import PonyEngine.Render;

import :BufferData;

export namespace PonyEngine::Render
{
	/// @brief Material.
	class Material final : public IMaterial
	{
	public:
		/// @brief Creates a material.
		/// @param params Material parameters.
		[[nodiscard("Pure constructor")]]
		explicit Material(const MaterialParams& params);
		Material(const Material&) = delete;
		Material(Material&&) = delete;

		~Material() noexcept = default;

		Material& operator =(const Material&) = delete;
		Material& operator =(Material&&) = delete;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IPipelineState>& PipelineState() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindDataTypeIndex(std::string_view dataType) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view DataType(std::uint32_t dataTypeIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataTypeCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;
		virtual void Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::span<const std::byte> data) override;
		[[nodiscard("Pure function")]]
		virtual std::size_t DataSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;
		[[nodiscard("Pure function")]] virtual std::uint32_t
		DataCount(std::uint32_t dataTypeIndex) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex) const noexcept override;
		virtual void Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex, std::span<const std::byte> element) override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t ElementSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t ElementCount(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept override;

		virtual std::uint32_t CreateData(std::string_view textureType, std::span<const PonyBase::Container::BufferParams> dataParams) override;
		virtual void DestroyData(std::uint32_t dataTypeIndex) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindTextureTypeIndex(std::string_view textureType) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureType(std::uint32_t textureTypeIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t TextureTypeCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const ITexture>& Texture(std::uint32_t textureTypeIndex, std::uint32_t textureIndex) const noexcept override;
		virtual void Texture(std::uint32_t textureTypeIndex, std::uint32_t textureIndex, const std::shared_ptr<const ITexture>& texture) override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t TextureCount(std::uint32_t textureTypeIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		std::uint32_t TextureCount() const noexcept;

		virtual std::uint32_t CreateTextureSet(std::string_view textureType, std::uint32_t textureCount) override;
		virtual void DestroyTextureSet(std::uint32_t textureTypeIndex) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

	private:
		std::shared_ptr<const IPipelineState> pipelineState; ///< Pipeline state.

		BufferData bufferData; ///< Buffer data.

		std::vector<std::string> textureTypes; ///< Texture types.
		std::vector<std::vector<std::shared_ptr<const ITexture>>> textures; ///< Textures.

		std::string name; ///< Material name.
	};
}

namespace PonyEngine::Render
{
	Material::Material(const MaterialParams& params) :
		pipelineState(params.pipelineState),
		bufferData(params.data),
		name(params.name)
	{
		std::size_t textureCount = 0;
		for (const auto& [dataType, textureSet] : params.textures)
		{
			if (textureSet.size() == 0) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Texture set of type '{}' is empty.", dataType));
			}
			textureCount += textureSet.size();
		}
		if (textureCount > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Texture count exceeds std::uint32_t max value.");
		}

		textureTypes.reserve(params.textures.size());
		textures.reserve(params.textures.size());
		for (const auto& [textureType, textureSet] : params.textures)
		{
			textureTypes.push_back(textureType);
			textures.push_back(textureSet);
		}
	}

	const std::shared_ptr<const IPipelineState>& Material::PipelineState() const noexcept
	{
		return pipelineState;
	}

	std::optional<std::uint32_t> Material::FindDataTypeIndex(const std::string_view dataType) const noexcept
	{
		return bufferData.DataTypeIndex(dataType);
	}

	std::string_view Material::DataType(const std::uint32_t dataTypeIndex) const noexcept
	{
		return bufferData.DataType(dataTypeIndex);
	}

	std::uint32_t Material::DataTypeCount() const noexcept
	{
		return bufferData.DataTypeCount();
	}

	std::span<const std::byte> Material::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.GetData(dataTypeIndex, dataIndex);
	}

	void Material::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::span<const std::byte> data)
	{
		bufferData.SetData(dataTypeIndex, dataIndex, data);
	}

	std::size_t Material::DataSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.DataSize(dataTypeIndex, dataIndex);
	}

	std::uint32_t Material::DataCount(const std::uint32_t dataTypeIndex) const noexcept
	{
		return bufferData.DataCount(dataTypeIndex);
	}

	std::span<const std::byte> Material::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex) const noexcept
	{
		return bufferData.GetData(dataTypeIndex, dataIndex, elementIndex);
	}

	void Material::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex, const std::span<const std::byte> element)
	{
		bufferData.SetData(dataTypeIndex, dataIndex, elementIndex, element);
	}

	std::uint32_t Material::ElementSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.ElementSize(dataTypeIndex, dataIndex);
	}

	std::uint32_t Material::ElementCount(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return bufferData.ElementCount(dataTypeIndex, dataIndex);
	}

	std::uint32_t Material::CreateData(const std::string_view textureType, const std::span<const PonyBase::Container::BufferParams> dataParams)
	{
		return bufferData.Create(textureType, dataParams);
	}

	void Material::DestroyData(const std::uint32_t dataTypeIndex) noexcept
	{
		bufferData.Destroy(dataTypeIndex);
	}

	std::optional<std::uint32_t> Material::FindTextureTypeIndex(const std::string_view textureType) const noexcept
	{
		for (std::uint32_t i = 0; i < TextureTypeCount(); ++i)
		{
			if (textureTypes[i] == textureType)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	std::string_view Material::TextureType(const std::uint32_t textureTypeIndex) const noexcept
	{
		return textureTypes[textureTypeIndex];
	}

	std::uint32_t Material::TextureTypeCount() const noexcept
	{
		return static_cast<std::uint32_t>(textureTypes.size());
	}

	const std::shared_ptr<const ITexture>& Material::Texture(const std::uint32_t textureTypeIndex, const std::uint32_t textureIndex) const noexcept
	{
		return textures[textureTypeIndex][textureIndex];
	}

	void Material::Texture(const std::uint32_t textureTypeIndex, const std::uint32_t textureIndex, const std::shared_ptr<const ITexture>& texture)
	{
		textures[textureTypeIndex][textureIndex] = texture;
	}

	std::uint32_t Material::TextureCount(const std::uint32_t textureTypeIndex) const noexcept
	{
		return static_cast<std::uint32_t>(textures[textureTypeIndex].size());
	}

	std::uint32_t Material::TextureCount() const noexcept
	{
		std::uint32_t count = 0u;
		for (std::uint32_t i = 0; i < TextureTypeCount(); ++i)
		{
			count += TextureCount(i);
		}

		return count;
	}

	std::uint32_t Material::CreateTextureSet(const std::string_view textureType, const std::uint32_t textureCount)
	{
		if (textureCount == 0) [[unlikely]]
		{
			throw std::invalid_argument("Texture count is zero.");
		}
		if (TextureCount() + textureCount > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Texture count exceeds std::uint32_t max value.");
		}

		if (FindTextureTypeIndex(textureType)) [[unlikely]]
		{
			throw std::invalid_argument("Such texture type already exists.");
		}

		const std::size_t currentSize = textureTypes.size();
		try
		{
			textureTypes.push_back(std::string(textureType));
			textures.push_back(std::vector<std::shared_ptr<const ITexture>>(textureCount));
		}
		catch (...)
		{
			textureTypes.resize(currentSize);
			textures.resize(currentSize);

			throw;
		}

		return static_cast<std::uint32_t>(currentSize);
	}

	void Material::DestroyTextureSet(const std::uint32_t textureTypeIndex) noexcept
	{
		textureTypes.erase(textureTypes.cbegin() + textureTypeIndex);
		textures.erase(textures.cbegin() + textureTypeIndex);
	}

	std::string_view Material::Name() const noexcept
	{
		return name;
	}

	void Material::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
	}
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Core:Material;

import <cstdint>;
import <memory>;
import <span>;
import <string>;
import <string_view>;
import <vector>;

import PonyEngine.Render;

import :Buffer;
import :BufferDirtyFlag;

export namespace PonyEngine::Render::Core
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
		virtual const IBuffer& Buffer() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindTextureTypeIndex(std::string_view textureType) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureType(std::uint32_t textureTypeIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t TextureTypeCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const ITexture>& Texture(std::uint32_t textureTypeIndex) const noexcept override;
		virtual void Texture(std::uint32_t textureTypeIndex, const std::shared_ptr<const ITexture>& texture) override;

		virtual std::uint32_t CreateTextureSlot(std::string_view textureType) override;
		virtual void DestroyTextureSlot(std::uint32_t textureTypeIndex) noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the dirty flags.
		/// @return Dirty flags.
		[[nodiscard("Pure function")]]
		BufferDirtyFlag DirtyFlags() const noexcept;
		/// @brief Resets the dirty flags.
		void ResetDirty() noexcept;

	private:
		std::shared_ptr<const IPipelineState> pipelineState; ///< Pipeline state.

		class Buffer buffer; ///< Buffer data.

		std::vector<std::string> textureTypes; ///< Texture types.
		std::vector<std::shared_ptr<const ITexture>> textures; ///< Textures.

		std::string name; ///< Material name.

		BufferDirtyFlag dirtyFlags; ///< Dirty flags.
	};
}

namespace PonyEngine::Render::Core
{
	Material::Material(const MaterialParams& params) :
		pipelineState(params.pipelineState),
		buffer(params.data),
		name(params.name),
		dirtyFlags{BufferDirtyFlag::All}
	{
		std::size_t textureCount = 0;
		for (const auto& [dataType, texture] : params.textures)
		{
			++textureCount;

			if (params.data.contains(dataType)) [[unlikely]]
			{
				throw std::invalid_argument(PonyBase::Utility::SafeFormat("Data type name '{}' is used in both data and textures.", dataType));
			}
		}
		if (textureCount > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Texture count exceeds std::uint32_t max value."); // TODO: Check for overall count textures + buffers. And make it a universal container.
		}

		textureTypes.reserve(params.textures.size());
		textures.reserve(params.textures.size());
		for (const auto& [textureType, texture] : params.textures)
		{
			textureTypes.push_back(textureType);
			textures.push_back(texture);
		}
	}

	const std::shared_ptr<const IPipelineState>& Material::PipelineState() const noexcept
	{
		return pipelineState;
	}

	std::optional<std::uint32_t> Material::FindDataTypeIndex(const std::string_view dataType) const noexcept
	{
		return buffer.DataTypeIndex(dataType);
	}

	std::string_view Material::DataType(const std::uint32_t dataTypeIndex) const noexcept
	{
		return buffer.DataType(dataTypeIndex);
	}

	std::uint32_t Material::DataTypeCount() const noexcept
	{
		return buffer.DataTypeCount();
	}

	std::span<const std::byte> Material::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return buffer.Data(dataTypeIndex, dataIndex);
	}

	void Material::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::span<const std::byte> data)
	{
		buffer.Data(dataTypeIndex, dataIndex, data);
		dirtyFlags |= BufferDirtyFlag::Data;
	}

	std::size_t Material::DataSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return buffer.DataSize(dataTypeIndex, dataIndex);
	}

	std::uint32_t Material::DataCount(const std::uint32_t dataTypeIndex) const noexcept
	{
		return buffer.DataCount(dataTypeIndex);
	}

	std::span<const std::byte> Material::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex) const noexcept
	{
		return buffer.Element(dataTypeIndex, dataIndex, elementIndex);
	}

	void Material::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex, const std::span<const std::byte> element)
	{
		buffer.Element(dataTypeIndex, dataIndex, elementIndex, element);
		dirtyFlags |= BufferDirtyFlag::Data;
	}

	std::uint32_t Material::ElementSize(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return buffer.ElementSize(dataTypeIndex, dataIndex);
	}

	std::uint32_t Material::ElementCount(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const noexcept
	{
		return buffer.ElementCount(dataTypeIndex, dataIndex);
	}

	std::uint32_t Material::CreateData(const std::string_view textureType, const std::span<const PonyBase::Container::BufferParams> dataParams)
	{
		if (FindTextureTypeIndex(textureType)) [[unlikely]]
		{
			throw std::invalid_argument("Type is already used in textures.");
		}

		const std::uint32_t answer = buffer.Create(textureType, dataParams);
		dirtyFlags |= BufferDirtyFlag::DataStructure;

		return answer;
	}

	void Material::DestroyData(const std::uint32_t dataTypeIndex) noexcept
	{
		buffer.Destroy(dataTypeIndex);
		dirtyFlags |= BufferDirtyFlag::DataStructure;
	}

	const IBuffer& Material::Buffer() const noexcept
	{
		return buffer;
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

	const std::shared_ptr<const ITexture>& Material::Texture(const std::uint32_t textureTypeIndex) const noexcept
	{
		return textures[textureTypeIndex];
	}

	void Material::Texture(const std::uint32_t textureTypeIndex, const std::shared_ptr<const ITexture>& texture)
	{
		textures[textureTypeIndex] = texture;
	}

	std::uint32_t Material::CreateTextureSlot(const std::string_view textureType)
	{
		if (TextureTypeCount() + 1 > std::numeric_limits<std::uint32_t>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Texture count exceeds std::uint32_t max value.");
		}

		if (FindDataTypeIndex(textureType)) [[unlikely]]
		{
			throw std::invalid_argument("Type is already used in data.");
		}
		if (FindTextureTypeIndex(textureType)) [[unlikely]]
		{
			throw std::invalid_argument("Such texture type already exists.");
		}

		const std::size_t currentSize = textureTypes.size();
		try
		{
			textureTypes.push_back(std::string(textureType));
			textures.push_back(std::shared_ptr<const ITexture>());
		}
		catch (...)
		{
			textureTypes.resize(currentSize);
			textures.resize(currentSize);

			throw;
		}

		return static_cast<std::uint32_t>(currentSize);
	}

	void Material::DestroyTextureSlot(const std::uint32_t textureTypeIndex) noexcept
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
		buffer.Name(name);
		dirtyFlags |= BufferDirtyFlag::Name;
	}

	BufferDirtyFlag Material::DirtyFlags() const noexcept
	{
		return dirtyFlags;
	}

	void Material::ResetDirty() noexcept
	{
		dirtyFlags = BufferDirtyFlag::None;
	}
}

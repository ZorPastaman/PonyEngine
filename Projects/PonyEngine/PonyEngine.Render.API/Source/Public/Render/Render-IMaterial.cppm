/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render:IMaterial;

import <cstddef>;
import <cstdint>;
import <memory>;
import <optional>;
import <span>;
import <stdexcept>;
import <string_view>;

import PonyBase.Container;

import :IBuffer;
import :IPipelineState;
import :ITexture;

export namespace PonyEngine::Render
{
	/// @brief Material.
	class IMaterial
	{
		INTERFACE_BODY(IMaterial)

		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IPipelineState>& PipelineState() const noexcept = 0;

		/// @brief Tries to find a data type index by the @p dataType.
		/// @param dataType Data type.
		/// @return Data type index if it's found; std::nullopt otherwise.
		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindDataTypeIndex(std::string_view dataType) const noexcept = 0;
		/// @brief Gets a data type.
		/// @param dataTypeIndex Data type index.
		/// @return Data type.
		[[nodiscard("Pure function")]]
		virtual std::string_view DataType(std::uint32_t dataTypeIndex) const noexcept = 0;
		/// @brief Gets a data type count.
		/// @return Data type count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataTypeCount() const noexcept = 0;

		/// @brief Gets a data.
		/// @details It gets a whole buffer.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept = 0;
		/// @brief Gets a data.
		/// @details It gets a whole buffer.
		/// @tparam T Data type. Its size must be an element size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<const T> Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const;
		/// @brief Sets a data.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param data Data to set. Must be the same size as a whole buffer.
		virtual void Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::span<const std::byte> data) = 0;
		/// @brief Sets a data.
		/// @tparam T Data type. its size must be an element size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param data Data to set. Its size must be the same as an element count of a target buffer.
		template<typename T>
		void Data(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::span<const T> data);
		/// @brief Gets a buffer size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Data size.
		[[nodiscard("Pure function")]]
		virtual std::size_t DataSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept = 0;
		/// @brief Gets a data count.
		/// @param dataTypeIndex Data type index.
		/// @return Data count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t DataCount(std::uint32_t dataTypeIndex) const noexcept = 0;

		/// @brief Gets an element.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @return Element.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex) const noexcept = 0;
		/// @brief Gets an element.
		/// @tparam T Element type. Must be the same size as a buffer element size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @return Element.
		template<typename T> [[nodiscard("Pure function")]]
		const T& Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex) const;
		/// @brief Sets an element.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @param element Element to set. Must be the same size as a buffer element size.
		virtual void Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex, std::span<const std::byte> element) = 0;
		/// @brief Sets an element.
		/// @tparam T Element type. Must be the same size as a buffer element size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @param elementIndex Element index.
		/// @param element Element.
		template<typename T>
		void Element(std::uint32_t dataTypeIndex, std::uint32_t dataIndex, std::uint32_t elementIndex, const T& element);
		/// @brief Gets an element size.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Element size.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t ElementSize(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept = 0;
		/// @brief Gets an element count.
		/// @param dataTypeIndex Data type index.
		/// @param dataIndex Data index.
		/// @return Element count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t ElementCount(std::uint32_t dataTypeIndex, std::uint32_t dataIndex) const noexcept = 0;

		/// @brief Creates a data.
		/// @note Throws if the data or texture set with same type already exist.
		/// @param textureType Data type.
		/// @param dataParams Data params. Use stride as an element size and count as an element count.
		/// @return Data type index.
		virtual std::uint32_t CreateData(std::string_view textureType, std::span<const PonyBase::Container::BufferParams> dataParams) = 0;
		/// @brief Destroys a data.
		/// @param dataTypeIndex Type index of a data to destroy.
		virtual void DestroyData(std::uint32_t dataTypeIndex) noexcept = 0;

		/// @brief Gets the buffer.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		virtual const IBuffer& Buffer() const noexcept = 0;

		/// @brief Tries to find a texture type index by the @p textureType.
		/// @param textureType Texture type.
		/// @return Texture type index if it's found; std::nullopt otherwise.
		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindTextureTypeIndex(std::string_view textureType) const noexcept = 0;
		/// @brief Gets a texture type.
		/// @param textureTypeIndex Texture type index.
		/// @return Texture type.
		[[nodiscard("Pure function")]]
		virtual std::string_view TextureType(std::uint32_t textureTypeIndex) const noexcept = 0;
		/// @brief Gets a texture type count.
		/// @return Texture type count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t TextureTypeCount() const noexcept = 0;

		/// @brief Gets a texture.
		/// @param textureTypeIndex Texture type index.
		/// @return Texture.
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const ITexture>& Texture(std::uint32_t textureTypeIndex) const noexcept = 0;
		/// @brief Sets a texture.
		/// @param textureTypeIndex Texture type index.
		/// @param texture Texture to set.
		virtual void Texture(std::uint32_t textureTypeIndex, const std::shared_ptr<const ITexture>& texture) = 0;

		/// @brief Creates a texture set.
		/// @note Throws if the data or texture set with same type already exist.
		/// @param textureType Texture type.
		/// @return Texture type index.
		virtual std::uint32_t CreateTextureSlot(std::string_view textureType) = 0;
		/// @brief Destroys a texture set.
		/// @param textureTypeIndex Type index of a texture set to destroy.
		virtual void DestroyTextureSlot(std::uint32_t textureTypeIndex) noexcept = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}

namespace PonyEngine::Render
{
	template <typename T>
	std::span<const T> IMaterial::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex) const
	{
		if (sizeof(T) != ElementSize(dataTypeIndex, dataIndex)) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		const std::span<const std::byte> span = Data(dataTypeIndex, dataIndex);

		return std::span<const T>(reinterpret_cast<const T*>(span.data()), span.size() / sizeof(T));
	}

	template <typename T>
	void IMaterial::Data(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::span<const T> data)
	{
		if (sizeof(T) != ElementSize(dataTypeIndex, dataIndex)) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		Data(dataTypeIndex, dataIndex, std::span<const std::byte>(reinterpret_cast<const std::byte*>(data.data()), data.size() * sizeof(T)));
	}

	template <typename T>
	const T& IMaterial::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex) const
	{
		if (sizeof(T) != ElementSize(dataTypeIndex, dataIndex)) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		const std::span<const std::byte> span = Element(dataTypeIndex, dataIndex, elementIndex);

		return *reinterpret_cast<const T*>(span.data());
	}

	template <typename T>
	void IMaterial::Element(const std::uint32_t dataTypeIndex, const std::uint32_t dataIndex, const std::uint32_t elementIndex, const T& element)
	{
		if (sizeof(T) != ElementSize(dataTypeIndex, dataIndex)) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		Element(dataTypeIndex, dataIndex, elementIndex, std::span(reinterpret_cast<const std::byte*>(&element), sizeof(T)));
	}
}

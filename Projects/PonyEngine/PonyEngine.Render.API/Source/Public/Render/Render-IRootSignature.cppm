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

export module PonyEngine.Render:IRootSignature;

import <cstdint>;
import <optional>;
import <string_view>;

import :IShader;

export namespace PonyEngine::Render
{
	/// @brief Root signature.
	class IRootSignature
	{
		INTERFACE_BODY(IRootSignature)

		/// @brief Get the root signature shader.
		/// @return Root signature shader.
		[[nodiscard("Pure function")]]
		virtual const IShader& Shader() const noexcept = 0;

		/// @brief Tries to find a slot index by the @p slotName.
		/// @param slotName Slot name.
		/// @return Slot index if it's found; std::nullopt otherwise.
		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindSlotIndex(std::string_view slotName) const noexcept = 0;
		/// @brief Gets a slot name by the @p slotIndex.
		/// @param slotIndex Slot index.
		/// @return Slot name.
		[[nodiscard("Pure function")]]
		virtual std::string_view SlotName(std::uint32_t slotIndex) const noexcept = 0;
		/// @brief Gets a slot count.
		/// @return Slot count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t SlotCount() const noexcept = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}

/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Core:RootSignature;

import <cstdint>;
import <memory>;
import <optional>;
import <string>;
import <string_view>;
import <utility>;
import <vector>;

import PonyEngine.Render;

import :RootSignatureDirtyFlag;
import :Shader;

export namespace PonyEngine::Render
{
	/// @brief Root signature shader.
	class RootSignature final : public IRootSignature
	{
	public:
		/// @brief Creates a root signature.
		/// @param params Root signature parameters.
		[[nodiscard("Pure constructor")]]
		explicit RootSignature(const RootSignatureParams& params);
		RootSignature(const RootSignature&) = delete;
		RootSignature(RootSignature&&) = delete;

		~RootSignature() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IShader>& Shader() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindSlotIndex(std::string_view slotName) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view SlotName(std::uint32_t slotIndex) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t SlotCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the dirty flags.
		/// @return Dirty flags.
		[[nodiscard("Pure function")]]
		RootSignatureDirtyFlag DirtyFlags() const noexcept;
		[[nodiscard("Pure function")]]
		/// @brief Resets the dirty flags.
		void ResetDirty() noexcept;

		RootSignature& operator =(const RootSignature&) = delete;
		RootSignature& operator =(RootSignature&&) = delete;

	private:
		std::shared_ptr<const IShader> shader; ///< Root signature shader.
		std::vector<std::string> slots; ///< Root signature slots.

		std::string name; ///< Root signature name.

		RootSignatureDirtyFlag dirtyFlags; ///< Dirty flags.
	};
}

namespace PonyEngine::Render
{
	RootSignature::RootSignature(const RootSignatureParams& params) :
		shader(params.shader),
		slots(params.slots),
		name(params.name),
		dirtyFlags{RootSignatureDirtyFlag::All}
	{
	}

	const std::shared_ptr<const IShader>& RootSignature::Shader() const noexcept
	{
		return shader;
	}

	std::optional<std::uint32_t> RootSignature::FindSlotIndex(const std::string_view slotName) const noexcept
	{
		for (std::size_t i = 0; i < slots.size(); ++i)
		{
			if (slots[i] == slotName)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	std::string_view RootSignature::SlotName(const std::uint32_t slotIndex) const noexcept
	{
		return slots[slotIndex];
	}

	std::uint32_t RootSignature::SlotCount() const noexcept
	{
		return slots.size();
	}

	std::string_view RootSignature::Name() const noexcept
	{
		return name;
	}

	void RootSignature::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
		dirtyFlags |= RootSignatureDirtyFlag::Name;
	}

	RootSignatureDirtyFlag RootSignature::DirtyFlags() const noexcept
	{
		return dirtyFlags;
	}

	void RootSignature::ResetDirty() noexcept
	{
		dirtyFlags = RootSignatureDirtyFlag::None;
	}
}

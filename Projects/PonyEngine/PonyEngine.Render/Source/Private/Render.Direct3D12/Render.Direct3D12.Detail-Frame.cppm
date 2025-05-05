/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Frame;

import <algorithm>;
import <memory>;
import <optional>;
import <string>;
import <string_view>;
import <unordered_map>;
import <utility>;

import :Attachment;
import :DescriptorHeap;
import :Texture;
import :View;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Frame buffer.
	class Frame final
	{
	public:
		/// @brief Creates a frame.
		/// @note The @p heaps must have all the views that the @p handles have.
		/// @note The @p heaps must have descriptor heaps that point only to the @p textures.
		/// @param textures Textures.
		/// @param heaps Heaps.
		/// @param handles Handles.
		[[nodiscard("Pure constructor")]]
		Frame(const std::unordered_map<Attachment, std::shared_ptr<Texture>>& textures, 
			const std::unordered_map<View, std::shared_ptr<DescriptorHeap>>& heaps, const std::unordered_map<View, std::uint32_t>& handles);
		/// @brief Creates a frame.
		/// @note The @p heaps must have all the views that the @p handles have.
		/// @note The @p heaps must have descriptor heaps that point only to the @p textures.
		/// @param textures Textures.
		/// @param heaps Heaps.
		/// @param handles Handles.
		[[nodiscard("Pure constructor")]]
		Frame(std::unordered_map<Attachment, std::shared_ptr<Texture>>&& textures,
			std::unordered_map<View, std::shared_ptr<DescriptorHeap>>&& heaps, std::unordered_map<View, std::uint32_t>&& handles) noexcept;
		[[nodiscard("Pure constructor")]]
		Frame(const Frame& other) = default;
		[[nodiscard("Pure constructor")]]
		Frame(Frame&& other) noexcept = default;

		~Frame() noexcept = default;

		/// @brief Tries to find a texture by the @p attachment.
		/// @param attachment Attachment.
		/// @return Texture; nullptr if such a texture isn't found.
		[[nodiscard("Pure function")]]
		Texture* FindTexture(Attachment attachment) noexcept;
		/// @brief Tries to find a texture by the @p attachment.
		/// @param attachment Attachment.
		/// @return Texture; nullptr if such a texture isn't found.
		[[nodiscard("Pure function")]]
		const Texture* FindTexture(Attachment attachment) const noexcept;

		/// @brief Tries to find a heap that has a descriptor for the @p view.
		/// @param view View.
		/// @return Descriptor heap; nullptr if such a heap isn't found.
		[[nodiscard("Pure function")]]
		DescriptorHeap* FindHeap(View view) noexcept;
		/// @brief Tries to find a heap that has a descriptor for the @p view.
		/// @param view View.
		/// @return Descriptor heap; nullptr if such a heap isn't found.
		[[nodiscard("Pure function")]]
		const DescriptorHeap* FindHeap(View view) const noexcept;

		/// @brief Tries to find a cpu handle by the @p view.
		/// @param view View.
		/// @return Handle; std::nullopt if such a handle isn't found.
		[[nodiscard("Pure function")]]
		std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> FindCpuHandle(View view) const noexcept;
		/// @brief Tries to find a gpu handle by the @p view.
		/// @param view View.
		/// @return Handle; std::nullopt if such a handle isn't found.
		[[nodiscard("Pure function")]]
		std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> FindGpuHandle(View view) const noexcept;

		/// @brief Sets the name.
		/// @param name Name to set.
		void Name(std::string_view name);

		Frame& operator =(const Frame& other) = default;
		Frame& operator =(Frame&& other) noexcept = default;

	private:
		std::unordered_map<Attachment, std::shared_ptr<Texture>> textures; ///< Textures.
		std::unordered_map<View, std::shared_ptr<DescriptorHeap>> heaps; ///< Heaps.
		std::unordered_map<View, std::uint32_t> handles; ///< Handle indices.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Frame::Frame(const std::unordered_map<Attachment, std::shared_ptr<Texture>>& textures,
		const std::unordered_map<View, std::shared_ptr<DescriptorHeap>>& heaps, const std::unordered_map<View, std::uint32_t>& handles) :
		textures(textures),
		heaps(heaps),
		handles(handles)
	{
		assert(std::ranges::find_if(this->textures, [](const std::pair<Attachment, std::shared_ptr<Texture>>& p) { return !p.second; }) == this->textures.cend() && "At least one of the textures is nullptr.");
		assert(std::ranges::find_if(this->heaps, [](const std::pair<View, std::shared_ptr<DescriptorHeap>>& p) { return !p.second; }) == this->heaps.cend() && "At least one of the heaps is nullptr.");
		assert(std::ranges::find_if(this->handles, [&](const std::pair<View, std::uint32_t>& p) { return !this->heaps.contains(p.first) || p.second >= this->heaps.find(p.first)->second->HandleCount(); }) == this->handles.cend() && "No heap for a handle is found.");
	}

	Frame::Frame(std::unordered_map<Attachment, std::shared_ptr<Texture>>&& textures,
		std::unordered_map<View, std::shared_ptr<DescriptorHeap>>&& heaps, std::unordered_map<View, std::uint32_t>&& handles) noexcept :
		textures(std::move(textures)),
		heaps(std::move(heaps)),
		handles(std::move(handles))
	{
		assert(std::ranges::find_if(this->textures, [](const std::pair<Attachment, std::shared_ptr<Texture>>& p) { return !p.second; }) == this->textures.cend() && "At least one of the textures is nullptr.");
		assert(std::ranges::find_if(this->heaps, [](const std::pair<View, std::shared_ptr<DescriptorHeap>>& p) { return !p.second; }) == this->heaps.cend() && "At least one of the heaps is nullptr.");
		assert(std::ranges::find_if(this->handles, [&](const std::pair<View, std::uint32_t>& p) { return !this->heaps.contains(p.first) || p.second >= this->heaps.find(p.first)->second->HandleCount(); }) == this->handles.cend() && "No heap for a handle is found.");
	}

	Texture* Frame::FindTexture(const Attachment attachment) noexcept
	{
		if (const auto position = textures.find(attachment); position != textures.cend())
		{
			return position->second.get();
		}

		return nullptr;
	}

	const Texture* Frame::FindTexture(const Attachment attachment) const noexcept
	{
		if (const auto position = textures.find(attachment); position != textures.cend())
		{
			return position->second.get();
		}

		return nullptr;
	}

	DescriptorHeap* Frame::FindHeap(const View view) noexcept
	{
		if (const auto position = heaps.find(view); position != heaps.cend())
		{
			return position->second.get();
		}

		return nullptr;
	}

	const DescriptorHeap* Frame::FindHeap(const View view) const noexcept
	{
		if (const auto position = heaps.find(view); position != heaps.cend())
		{
			return position->second.get();
		}

		return nullptr;
	}

	std::optional<D3D12_CPU_DESCRIPTOR_HANDLE> Frame::FindCpuHandle(const View view) const noexcept
	{
		if (const DescriptorHeap* const heap = FindHeap(view))
		{
			if (const auto position = handles.find(view); position != handles.cend())
			{
				return heap->CpuHandle(position->second);
			}
		}

		return std::nullopt;
	}

	std::optional<D3D12_GPU_DESCRIPTOR_HANDLE> Frame::FindGpuHandle(const View view) const noexcept
	{
		if (const DescriptorHeap* const heap = FindHeap(view))
		{
			if (const auto position = handles.find(view); position != handles.cend())
			{
				return heap->GpuHandle(position->second);
			}
		}

		return std::nullopt;
	}

	void Frame::Name(const std::string_view name)
	{
		auto componentName = std::string();
		componentName.reserve(name.size() + 32);

		for (const auto& [attachment, texture] : textures)
		{
			componentName.clear();
			componentName.append(name).append("-").append(ToString(attachment));
			texture->Name(componentName);
		}

		for (const auto& [view, heap] : heaps)
		{
			componentName.clear();
			componentName.append(name).append("-").append(ToString(view));
			heap->Name(componentName);
		}
	}
}

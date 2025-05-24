/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:TextureManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <utility>;
import <vector>;

import PonyEngine.Render;

import :Buffer;
import :FormatUtility;
import :HeapType;
import :IResourceManager;
import :ISubSystemContext;
import :ITextureManager;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	class TextureManager final : public ITextureManager
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit TextureManager(ISubSystemContext& d3d12System) noexcept;
		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;

		~TextureManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Texture> CreateTexture(const std::shared_ptr<const Render::Texture>& texture) override;

		void Tick();

		void Clean() noexcept;

		TextureManager& operator =(const TextureManager&) = delete;
		TextureManager& operator =(TextureManager&&) = delete;

	private:
		class TextureObserver final : public ITextureObserver
		{
		public:
			[[nodiscard("Pure constructor")]]
			TextureObserver() noexcept;
			TextureObserver(const TextureObserver&) = delete;
			TextureObserver(TextureObserver&&) = delete;

			~TextureObserver() noexcept = default;

			virtual void OnTextureChanged() noexcept override;

			[[nodiscard("Pure function")]]
			bool TextureChanged() const noexcept;

			void Reset() noexcept;

			TextureObserver& operator =(const TextureObserver&) = delete;
			TextureObserver& operator =(TextureObserver&&) = delete;

		private:
			bool textureChanged;
		};

		[[nodiscard("Pure function")]]
		std::shared_ptr<Texture> CreateTexture(const Render::Texture& source) const;
		[[nodiscard("Pure function")]]
		std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> CreateTextureBuffer(const Render::Texture& source) const;

		void UpdateTexture(Texture& texture, const Render::Texture& source, const TextureObserver& observer);

		void Add(const std::shared_ptr<Texture>& texture, const std::shared_ptr<const Render::Texture>& source);
		void Remove(std::size_t index) noexcept;

		ISubSystemContext* d3d12System;

		std::vector<std::shared_ptr<Texture>> textures;
		std::vector<std::shared_ptr<const Render::Texture>> sources;
		std::vector<std::unique_ptr<TextureObserver>> observers;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	TextureManager::TextureObserver::TextureObserver() noexcept :
		textureChanged{true}
	{
	}

	void TextureManager::TextureObserver::OnTextureChanged() noexcept
	{
		textureChanged = true;
	}

	bool TextureManager::TextureObserver::TextureChanged() const noexcept
	{
		return textureChanged;
	}

	void TextureManager::TextureObserver::Reset() noexcept
	{
		textureChanged = false;
	}

	TextureManager::TextureManager(ISubSystemContext& d3d12System) noexcept :
		d3d12System{&d3d12System}
	{
	}

	std::shared_ptr<Texture> TextureManager::CreateTexture(const std::shared_ptr<const Render::Texture>& texture)
	{
		if (!texture) [[unlikely]]
		{
			throw std::invalid_argument("Texture is nullptr.");
		}

		for (std::size_t i = 0; i < sources.size(); ++i)
		{
			if (sources[i] == texture)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Texture reused at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(textures[i].get()));
				return textures[i];
			}
		}

		const std::shared_ptr<Texture> renderTexture = CreateTexture(*texture);
		Add(renderTexture, texture);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Texture acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(renderTexture.get()));

		return renderTexture;
	}

	void TextureManager::Tick()
	{
		for (std::size_t i = 0; i < textures.size(); ++i)
		{
			Texture& texture = *textures[i];
			const Render::Texture& source = *sources[i];
			TextureObserver& observer = *observers[i];

			UpdateTexture(texture, source, observer);

			observer.Reset();
		}
	}

	void TextureManager::Clean() noexcept
	{
		for (std::size_t i = textures.size(); i-- > 0; )
		{
			if (const std::shared_ptr<Texture>& texture = textures[i]; texture.use_count() <= 1L)
			{
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release texture at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(texture.get()));
				Remove(i);
				PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Texture released.");
			}
		}
	}

	std::shared_ptr<Texture> TextureManager::CreateTexture(const Render::Texture& source) const
	{
		switch (source.Dimension())
		{
		case TextureDimension::Texture1D:
			return d3d12System->ResourceManager().CreateTexture1D(source.Width(), GetD3D12Format(source.Format()),
				DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}, HeapType::Default);
		case TextureDimension::Texture2D:
			return d3d12System->ResourceManager().CreateTexture2D(source.Width(), source.Height(), GetD3D12Format(source.Format()),
				DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}, HeapType::Default);
		case TextureDimension::Texture3D:
			return d3d12System->ResourceManager().CreateTexture3D(source.Width(), source.Height(), source.Depth(), GetD3D12Format(source.Format()),
				DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}, HeapType::Default);
		default: [[unlikely]]
			throw std::invalid_argument("Unsupported texture dimension.");
		}
	}

	std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> TextureManager::CreateTextureBuffer(const Render::Texture& source) const
	{
		switch (source.Dimension())
		{
		case TextureDimension::Texture1D:
			return d3d12System->ResourceManager().CreateTextureBuffer1D(source.Width(), GetD3D12Format(source.Format()), 
				DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}, HeapType::Upload);
		case TextureDimension::Texture2D:
			return d3d12System->ResourceManager().CreateTextureBuffer2D(source.Width(), source.Height(), GetD3D12Format(source.Format()),
				DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}, HeapType::Upload);
		case TextureDimension::Texture3D:
			return d3d12System->ResourceManager().CreateTextureBuffer3D(source.Width(), source.Height(), source.Depth(), GetD3D12Format(source.Format()),
				DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}, HeapType::Upload);
		default: [[unlikely]]
			throw std::invalid_argument("Unsupported texture dimension.");
		}
	}

	void TextureManager::UpdateTexture(Texture& texture, const Render::Texture& source, const TextureObserver& observer)
	{
		if (!observer.TextureChanged()) [[likely]]
		{
			return;
		}

		const auto [uploadBuffer, footprint] = CreateTextureBuffer(source);
		uploadBuffer->SetData(source.Data(), footprint);

		d3d12System->CopyPipeline().AddCopyTask(*uploadBuffer, texture, footprint, 0u, 0u, 0u, 0u);
	}

	void TextureManager::Add(const std::shared_ptr<Texture>& texture, const std::shared_ptr<const Render::Texture>& source)
	{
		const std::size_t currentSize = textures.size();

		try
		{
			textures.push_back(texture);
			sources.push_back(source);
			observers.push_back(std::make_unique<TextureObserver>());
			source->AddObserver(*observers.back());
		}
		catch (...)
		{
			textures.resize(currentSize);
			sources.resize(currentSize);
			observers.resize(currentSize);

			throw;
		}
	}

	void TextureManager::Remove(const std::size_t index) noexcept
	{
		sources[index]->RemoveObserver(*observers[index]);

		textures.erase(textures.cbegin() + index);
		sources.erase(sources.cbegin() + index);
		observers.erase(observers.cbegin() + index);
	}
}

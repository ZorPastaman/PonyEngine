/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Impl:EmptyBackend;

import std;

import PonyEngine.RenderDevice.Ext;

export namespace PonyEngine::Render
{
	class EmptyBackend final : public IBackend
	{
	public:
		[[nodiscard("Pure constructor")]]
		EmptyBackend() noexcept = default;
		EmptyBackend(const EmptyBackend&) = delete;
		EmptyBackend(EmptyBackend&&) = delete;

		~EmptyBackend() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::string_view RenderApiName() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Meta::Version RenderApiVersion() const noexcept override;

		virtual void Activate() noexcept override;
		virtual void Deactivate() noexcept override;

		[[nodiscard("Pure function")]] 
		virtual TextureFormatFeature TextureFormatFeatures(TextureFormatId textureFormatId) const override;
		[[nodiscard("Pure function")]] 
		virtual TextureSupportResponse TextureSupport(const TextureSupportRequest& request) const override;

		EmptyBackend& operator =(const EmptyBackend&) = delete;
		EmptyBackend& operator =(EmptyBackend&&) = delete;
	};
}

namespace PonyEngine::Render
{
	std::string_view EmptyBackend::RenderApiName() const noexcept
	{
		return RenderAPI::Empty;
	}

	Meta::Version EmptyBackend::RenderApiVersion() const noexcept
	{
		return Meta::Version();
	}

	void EmptyBackend::Activate() noexcept
	{
	}

	void EmptyBackend::Deactivate() noexcept
	{
	}

	TextureFormatFeature EmptyBackend::TextureFormatFeatures(const TextureFormatId textureFormatId) const
	{
		return TextureFormatFeature::None;
	}

	TextureSupportResponse EmptyBackend::TextureSupport(const TextureSupportRequest& request) const
	{
		return TextureSupportResponse{};
	}
}

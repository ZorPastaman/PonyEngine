/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Text.Impl:TextLoaderModule;

import std;

import PonyEngine.Application;
import PonyEngine.Resource.Ext;

import :TextLoader;

export namespace PonyEngine::Resource::Text
{
	/// @brief Text loader module.
	class TextLoaderModule final : public Application::IModule
	{
	public:
		[[nodiscard("Pure constructor")]]
		TextLoaderModule() noexcept = default;
		TextLoaderModule(const TextLoaderModule&) = delete;
		TextLoaderModule(TextLoaderModule&&) = delete;

		~TextLoaderModule() noexcept = default;

		virtual void StartUp(Application::IModuleContext& context) override;
		virtual void ShutDown(Application::IModuleContext& context) override;

		TextLoaderModule& operator =(const TextLoaderModule&) = delete;
		TextLoaderModule& operator =(TextLoaderModule&&) = delete;

	private:
		static constexpr std::string_view TextResourceType = "PonyText"; ///< Text resource type.

		std::unique_ptr<TextLoader> textLoader; ///< Text loader.
	};
}

namespace PonyEngine::Resource::Text
{
	void TextLoaderModule::StartUp(Application::IModuleContext& context)
	{
		IResourceHub& resourceHub = context.Application().GetInterface<IResourceHub>();
		const ResourceType textResourceType = resourceHub.MakeResourceType(TextResourceType);

		textLoader = std::make_unique<TextLoader>();
		try
		{
			resourceHub.RegisterLoader(*textLoader, std::span(&textResourceType, 1uz));
		}
		catch (...)
		{
			textLoader.reset();
			throw;
		}
	}

	void TextLoaderModule::ShutDown(Application::IModuleContext& context)
	{
		IResourceHub& resourceHub = context.Application().GetInterface<IResourceHub>();
		resourceHub.UnregisterLoader(*textLoader);
		textLoader.reset();
	}
}

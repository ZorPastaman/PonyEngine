/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Path.Main.Windows:PathServiceFactory;

import std;

import PonyEngine.Application;
import PonyEngine.Path.Extension.Windows;
import PonyEngine.Path.Main;
import PonyEngine.Platform.Windows;

export namespace PonyEngine::Path::Windows
{
	/// @brief Path service factory.
	class PathServiceFactory final : public Path::PathServiceFactory
	{
	public:
		/// @brief Creates a path service factory.
		/// @param context Module context.
		[[nodiscard("Pure constuctor")]]
		explicit PathServiceFactory(Application::IModuleContext& context) noexcept;
		PathServiceFactory(const PathServiceFactory&) = delete;
		PathServiceFactory(PathServiceFactory&&) = delete;

		virtual ~PathServiceFactory() noexcept override = default;

		PathServiceFactory& operator =(const PathServiceFactory&) = delete;
		PathServiceFactory& operator =(PathServiceFactory&&) = delete;

	protected:
		[[nodiscard("Pure function")]]
		virtual std::filesystem::path GetExecutablePath() const override;
	};
}

namespace PonyEngine::Path::Windows
{
	PathServiceFactory::PathServiceFactory(Application::IModuleContext& context) noexcept :
		Path::PathServiceFactory(context)
	{
	}

	std::filesystem::path PathServiceFactory::GetExecutablePath() const
	{
		return GetModulePath(nullptr);
	}
}

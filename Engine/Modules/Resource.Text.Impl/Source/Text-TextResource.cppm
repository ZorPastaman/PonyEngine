/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Text.Impl:TextResource;

import std;

export namespace PonyEngine::Resource::Text
{
	/// @brief Text resource.
	class TextResource final
	{
	public:
		/// @brief Creates a text resource.
		/// @param textData Text data.
		/// @param textView Text view. Must reference a string that is kept alive by the @p textData.
		[[nodiscard("Pure constructor")]]
		TextResource(std::shared_ptr<const void> textData, std::string_view textView) noexcept;
		[[nodiscard("Pure constructor")]]
		TextResource(const TextResource& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		TextResource(TextResource&& other) noexcept = default;

		~TextResource() noexcept = default;

		/// @brief Gets the view.
		/// @return View.
		[[nodiscard("Pure function")]]
		const std::string_view& View() const noexcept;

		TextResource& operator =(const TextResource& other) noexcept = default;
		TextResource& operator =(TextResource&& other) noexcept = default;

	private:
		std::shared_ptr<const void> textData; ///< Text data.
		std::string_view textView; ///< Text view.
	};
}

namespace PonyEngine::Resource::Text
{
	TextResource::TextResource(std::shared_ptr<const void> textData, const std::string_view textView) noexcept :
		textData(std::move(textData)),
		textView(textView)
	{
	}

	const std::string_view& TextResource::View() const noexcept
	{
		return textView;
	}
}

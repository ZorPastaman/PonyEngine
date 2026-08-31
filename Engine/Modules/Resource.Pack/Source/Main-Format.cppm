/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack:Format;

import std;

export namespace PonyEngine::Resource::Pack
{
	constexpr std::string_view PackManifestExtension = ".prpm"; ///< Pack manifest file extension.
	constexpr std::string_view PackDataExtension = ".prpd"; ///< Pack data file extension.
	constexpr std::string_view MagicWord = "PonyEngineRPM"; ///< Pack manifest magic word.
}

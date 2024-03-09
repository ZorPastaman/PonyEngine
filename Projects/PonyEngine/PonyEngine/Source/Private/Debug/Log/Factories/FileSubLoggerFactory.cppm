/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Factories.Implementation:FileSubLoggerFactory;

import <filesystem>;

import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Debug.Log.Factories;

namespace PonyEngine::Debug::Log
{
	export class FileSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		FileSubLoggerFactory() = default;
		~FileSubLoggerFactory() = default;

		[[nodiscard("Pure function")]]
		virtual ISubLogger* Create(Core::IEngine& engine) override;
		virtual void Destroy(ISubLogger* subLogger) override;

	private:
		std::filesystem::path m_path = "Log.log";
	};

	ISubLogger* FileSubLoggerFactory::Create(Core::IEngine& engine)
	{
		return new FileSubLogger(m_path);
	}

	void FileSubLoggerFactory::Destroy(ISubLogger* subLogger)
	{
		delete static_cast<FileSubLogger*>(subLogger);
	}
}

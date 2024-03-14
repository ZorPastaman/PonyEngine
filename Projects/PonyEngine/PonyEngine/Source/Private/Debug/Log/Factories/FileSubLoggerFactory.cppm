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

export module PonyEngine.Debug.Log.Factories.Implementation:FileSubLoggerFactory;

import <filesystem>;

import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Debug.Log.Factories;

namespace PonyEngine::Debug::Log
{
	export class FileSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		inline FileSubLoggerFactory();
		inline FileSubLoggerFactory(const std::filesystem::path& path);
		inline FileSubLoggerFactory(const FileSubLoggerFactory& other) = default;
		inline FileSubLoggerFactory(FileSubLoggerFactory&& other) = default;

		inline ~FileSubLoggerFactory() = default;

		[[nodiscard("Pure function")]]
		virtual ISubLogger* Create(Core::IEngine& engine) override;
		virtual void Destroy(ISubLogger* subLogger) noexcept override;

		virtual const char* GetSubLoggerName() const noexcept override;

		inline std::filesystem::path GetPath() const;
		inline void SetPath(const std::filesystem::path& path);

		inline FileSubLoggerFactory& operator =(const FileSubLoggerFactory& other) = default;
		inline FileSubLoggerFactory& operator =(FileSubLoggerFactory&& other) = default;

	private:
		std::filesystem::path m_path;
	};

	FileSubLoggerFactory::FileSubLoggerFactory() :
		m_path("Log.log")
	{
	}

	FileSubLoggerFactory::FileSubLoggerFactory(const std::filesystem::path& path) :
		m_path(path)
	{
	}

	ISubLogger* FileSubLoggerFactory::Create(Core::IEngine&)
	{
		return new FileSubLogger(m_path);
	}

	void FileSubLoggerFactory::Destroy(ISubLogger* subLogger) noexcept
	{
		assert((dynamic_cast<FileSubLogger*>(subLogger) != nullptr));
		delete static_cast<FileSubLogger*>(subLogger);
	}

	const char* FileSubLoggerFactory::GetSubLoggerName() const noexcept
	{
		return FileSubLogger::Name;
	}

	inline std::filesystem::path FileSubLoggerFactory::GetPath() const
	{
		return m_path;
	}

	inline void FileSubLoggerFactory::SetPath(const std::filesystem::path& path)
	{
		m_path = path;
	}
}

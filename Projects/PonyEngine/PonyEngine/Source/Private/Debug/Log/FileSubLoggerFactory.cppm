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

export module PonyEngine.Debug.Log.Implementation:FileSubLoggerFactory;

import <filesystem>;

import PonyEngine.Debug.Log.Factories;

import :FileSubLogger;

namespace PonyEngine::Debug::Log
{
	/// @brief File sub-logger factory.
	export class FileSubLoggerFactory final : public ISubLoggerFactory
	{
	public:
		/// @brief Creates a @p FileSubLoggerFactory with the default log file path, Log.log.
		[[nodiscard("Pure constructor")]]
		inline FileSubLoggerFactory();
		/// @brief Creates a @p FileSubLoggerFactory with the @p path.
		/// @param path Log file path.
		[[nodiscard("Pure constructor")]]
		inline FileSubLoggerFactory(const std::filesystem::path& path);
		[[nodiscard("Pure constructor")]]
		inline FileSubLoggerFactory(const FileSubLoggerFactory& other) = default;
		[[nodiscard("Pure constructor")]]
		inline FileSubLoggerFactory(FileSubLoggerFactory&& other) = default;

		inline virtual ~FileSubLoggerFactory() noexcept = default;

		[[nodiscard("Pure function")]]
		inline virtual ISubLogger* Create(Core::IEngine& engine) override;
		inline virtual void Destroy(ISubLogger* subLogger) noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual const char* GetSubLoggerName() const noexcept override;

		/// @brief Gets a log file path of the next @p FileSubLogger.
		/// @return Log file path of the next @p FileSubLogger.
		[[nodiscard("Pure function")]]
		inline std::filesystem::path GetPath() const;
		/// @brief Sets a log file path of the next @p FileSubLogger.
		/// @param path Log file path of the next @p FileSubLogger.
		inline void SetPath(const std::filesystem::path& path);

		inline FileSubLoggerFactory& operator =(const FileSubLoggerFactory& other) = default;
		inline FileSubLoggerFactory& operator =(FileSubLoggerFactory&& other) = default;

	private:
		std::filesystem::path m_path; /// @brief Log file path of the next @p FileSubLogger.
	};

	FileSubLoggerFactory::FileSubLoggerFactory() :
		m_path("Log.log")
	{
	}

	FileSubLoggerFactory::FileSubLoggerFactory(const std::filesystem::path& path) :
		m_path(path)
	{
	}

	inline ISubLogger* FileSubLoggerFactory::Create(Core::IEngine&)
	{
		return new FileSubLogger(m_path);
	}

	inline void FileSubLoggerFactory::Destroy(ISubLogger* const subLogger) noexcept
	{
		assert((dynamic_cast<FileSubLogger*>(subLogger) != nullptr));
		delete static_cast<FileSubLogger*>(subLogger);
	}

	inline const char* FileSubLoggerFactory::GetSubLoggerName() const noexcept
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

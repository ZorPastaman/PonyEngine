/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Detail:EngineLogger;

import <exception>;
import <string_view>;

import PonyDebug.Log;

import PonyEngine.Core;

export namespace PonyEngine::Core
{
	/// @brief Engine logger wrapper.
	class EngineLogger final : public PonyDebug::Log::ILogger
	{
	public:
		/// @brief Creates an @p EngineLogger.
		/// @param engine Engine context.
		/// @param externalLogger External logger.
		[[nodiscard("Pure constructor")]]
		EngineLogger(IEngineContext& engine, PonyDebug::Log::ILogger& externalLogger) noexcept;
		EngineLogger(const EngineLogger&) = delete;
		EngineLogger(EngineLogger&&) = delete;

		~EngineLogger() noexcept = default;

		virtual void Log(PonyDebug::Log::LogType logType, const PonyDebug::Log::LogInput& logInput) noexcept override;
		virtual void LogException(const ::std::exception& exception, const PonyDebug::Log::LogInput& logInput) noexcept override;

		virtual void AddSubLogger(PonyDebug::Log::ISubLogger& subLogger) override;
		virtual void RemoveSubLogger(PonyDebug::Log::ISubLogger& subLogger) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		EngineLogger& operator =(const EngineLogger&) = delete;
		EngineLogger& operator =(EngineLogger&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Core::EngineLogger"; ///< Class name.

	private:
		/// @brief Converts the @p logInput to an engine log input.
		/// @param logInput Log input to convert.
		/// @return Engine log input.
		[[nodiscard("Pure function")]]
		PonyDebug::Log::LogInput ConvertToEngineLogInput(const PonyDebug::Log::LogInput& logInput) const noexcept;

		IEngineContext* engine; ///< Engine.
		PonyDebug::Log::ILogger* externalLogger; ///< External logger.
	};
}

namespace PonyEngine::Core
{
	EngineLogger::EngineLogger(IEngineContext& engine, PonyDebug::Log::ILogger& externalLogger) noexcept :
		engine{&engine},
		externalLogger{&externalLogger}
	{
	}

	void EngineLogger::Log(const PonyDebug::Log::LogType logType, const PonyDebug::Log::LogInput& logInput) noexcept
	{
		const PonyDebug::Log::LogInput engineLogInput = ConvertToEngineLogInput(logInput);
		externalLogger->Log(logType, engineLogInput);
	}

	void EngineLogger::LogException(const std::exception& exception, const PonyDebug::Log::LogInput& logInput) noexcept
	{
		const PonyDebug::Log::LogInput engineLogInput = ConvertToEngineLogInput(logInput);
		externalLogger->LogException(exception, engineLogInput);
	}

	void EngineLogger::AddSubLogger(PonyDebug::Log::ISubLogger& subLogger)
	{
		externalLogger->AddSubLogger(subLogger);
	}

	void EngineLogger::RemoveSubLogger(PonyDebug::Log::ISubLogger& subLogger)
	{
		externalLogger->RemoveSubLogger(subLogger);
	}

	std::string_view EngineLogger::Name() const noexcept
	{
		return StaticName;
	}

	PonyDebug::Log::LogInput EngineLogger::ConvertToEngineLogInput(const PonyDebug::Log::LogInput& logInput) const noexcept
	{
		PonyDebug::Log::LogInput engineLogInput = logInput;
		engineLogInput.frameCount = engine->FrameCount();

		return engineLogInput;
	}
}

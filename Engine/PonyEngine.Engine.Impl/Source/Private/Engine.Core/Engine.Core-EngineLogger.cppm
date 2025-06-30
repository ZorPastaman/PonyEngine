/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Engine.Core:EngineLogger;

import std;

import PonyEngine.Application;
import PonyEngine.Engine.Ext;
import PonyEngine.Log;

export namespace PonyEngine::Engine
{
	/// @brief Engine logger wrapper.
	class EngineLogger final : public Log::ILogger
	{
	public:
		/// @brief Creates an @p EngineLogger.
		/// @param engine Engine context.
		[[nodiscard("Pure constructor")]]
		explicit EngineLogger(IEngineContext& engine) noexcept;
		EngineLogger(const EngineLogger&) = delete;
		EngineLogger(EngineLogger&&) = delete;

		~EngineLogger() noexcept = default;

		virtual void Log(Log::LogType logType, const Log::LogInput& logInput) const noexcept override;
		virtual void Log(const std::exception& exception, const Log::LogInput& logInput) const noexcept override;

		EngineLogger& operator =(const EngineLogger&) = delete;
		EngineLogger& operator =(EngineLogger&&) = delete;

	private:
		/// @brief Converts the @p logInput to an engine log input.
		/// @param logInput Log input to convert.
		/// @return Engine log input.
		[[nodiscard("Pure function")]]
		Log::LogInput ConvertToEngineLogInput(const Log::LogInput& logInput) const noexcept;

		IEngineContext* engine; ///< Engine.
	};
}

namespace PonyEngine::Engine
{
	EngineLogger::EngineLogger(IEngineContext& engine) noexcept :
		engine{&engine}
	{
	}

	void EngineLogger::Log(const Log::LogType logType, const Log::LogInput& logInput) const noexcept
	{
		const Log::LogInput engineLogInput = ConvertToEngineLogInput(logInput);
		engine->Application().Logger().Log(logType, engineLogInput);
	}

	void EngineLogger::Log(const std::exception& exception, const Log::LogInput& logInput) const noexcept
	{
		const Log::LogInput engineLogInput = ConvertToEngineLogInput(logInput);
		engine->Application().Logger().Log(exception, engineLogInput);
	}

	Log::LogInput EngineLogger::ConvertToEngineLogInput(const Log::LogInput& logInput) const noexcept
	{
		Log::LogInput engineLogInput = logInput;
		engineLogInput.frameCount = engine->FrameCount();

		return engineLogInput;
	}
}

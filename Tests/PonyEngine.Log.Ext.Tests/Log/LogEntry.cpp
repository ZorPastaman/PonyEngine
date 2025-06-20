/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>

import std;

import PonyEngine.Log.Extension;

TEST_CASE("LogEntry: basic", "[Log][LogEntry]")
{
	const auto tp = std::chrono::system_clock::now();
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(std::string_view(), nullptr, nullptr, tp, std::nullopt, lt);

	REQUIRE(logEntry.Message().empty());
	REQUIRE_FALSE(logEntry.Stacktrace());
	REQUIRE_FALSE(logEntry.Exception());
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE_FALSE(logEntry.FrameCount().has_value());
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, tp));
}

TEST_CASE("LogEntry: frame", "[Log][LogEntry]")
{
	const auto tp = std::chrono::system_clock::now();
	constexpr std::uint64_t frame = 42;
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(std::string_view(), nullptr, nullptr, tp, frame, lt);

	REQUIRE(logEntry.Message().empty());
	REQUIRE_FALSE(logEntry.Stacktrace());
	REQUIRE_FALSE(logEntry.Exception());
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE(logEntry.FrameCount() == frame);
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, tp, frame));
}

TEST_CASE("LogEntry: exception", "[Log][LogEntry]")
{
	const auto tp = std::chrono::system_clock::now();
	const auto e = std::logic_error("Test!");
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(std::string_view(), nullptr, &e, tp, std::nullopt, lt);

	REQUIRE(logEntry.Message().empty());
	REQUIRE_FALSE(logEntry.Stacktrace());
	REQUIRE(logEntry.Exception() == &e);
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE_FALSE(logEntry.FrameCount().has_value());
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, e.what(), tp));
}

TEST_CASE("LogEntry: exception, frame", "[Log][LogEntry]")
{
	const auto tp = std::chrono::system_clock::now();
	const auto e = std::logic_error("Test!");
	constexpr std::uint64_t f = 42;
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(std::string_view(), nullptr, &e, tp, f, lt);

	REQUIRE(logEntry.Message().empty());
	REQUIRE_FALSE(logEntry.Stacktrace());
	REQUIRE(logEntry.Exception() == &e);
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE(logEntry.FrameCount() == f);
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, e.what(), tp, f));
}

TEST_CASE("LogEntry: stacktrace", "[Log][LogEntry]")
{
	const auto tp = std::chrono::system_clock::now();
	const auto s = std::stacktrace::current();
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(std::string_view(), &s, nullptr, tp, std::nullopt, lt);

	REQUIRE(logEntry.Message().empty());
	REQUIRE(logEntry.Stacktrace() == &s);
	REQUIRE_FALSE(logEntry.Exception());
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE_FALSE(logEntry.FrameCount().has_value());
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, tp, s));
}

TEST_CASE("LogEntry: stacktrace, frame", "[Log][LogEntry]")
{
	const auto tp = std::chrono::system_clock::now();
	const auto s = std::stacktrace::current();
	constexpr std::uint64_t f = 42;
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(std::string_view(), &s, nullptr, tp, f, lt);

	REQUIRE(logEntry.Message().empty());
	REQUIRE(logEntry.Stacktrace() == &s);
	REQUIRE_FALSE(logEntry.Exception());
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE(logEntry.FrameCount() == f);
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, tp, f, s));
}

TEST_CASE("LogEntry: stacktrace, exception", "[Log][LogEntry]")
{
	const auto tp = std::chrono::system_clock::now();
	const auto e = std::logic_error("Test!");
	const auto s = std::stacktrace::current();
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(std::string_view(), &s, &e, tp, std::nullopt, lt);

	REQUIRE(logEntry.Message().empty());
	REQUIRE(logEntry.Stacktrace() == &s);
	REQUIRE(logEntry.Exception() == &e);
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE_FALSE(logEntry.FrameCount().has_value());
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, e.what(), tp, s));
}

TEST_CASE("LogEntry: stacktrace, exception, frame", "[Log][LogEntry]")
{
	const auto tp = std::chrono::system_clock::now();
	const auto e = std::logic_error("Test!");
	const auto s = std::stacktrace::current();
	constexpr std::uint64_t f = 42;
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(std::string_view(), &s, &e, tp, f, lt);

	REQUIRE(logEntry.Message().empty());
	REQUIRE(logEntry.Stacktrace() == &s);
	REQUIRE(logEntry.Exception() == &e);
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE(logEntry.FrameCount() == f);
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, e.what(), tp, f, s));
}

TEST_CASE("LogEntry: message, frame", "[Log][LogEntry]")
{
	constexpr std::string_view m = "Message";
	const auto tp = std::chrono::system_clock::now();
	constexpr std::uint64_t frame = 42;
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(m, nullptr, nullptr, tp, frame, lt);

	REQUIRE(logEntry.Message() == m);
	REQUIRE_FALSE(logEntry.Stacktrace());
	REQUIRE_FALSE(logEntry.Exception());
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE(logEntry.FrameCount() == frame);
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, m, tp, frame));
}

TEST_CASE("LogEntry: message, exception", "[Log][LogEntry]")
{
	constexpr std::string_view m = "Message";
	const auto tp = std::chrono::system_clock::now();
	const auto e = std::logic_error("Test!");
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(m, nullptr, &e, tp, std::nullopt, lt);

	REQUIRE(logEntry.Message() == m);
	REQUIRE_FALSE(logEntry.Stacktrace());
	REQUIRE(logEntry.Exception() == &e);
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE_FALSE(logEntry.FrameCount().has_value());
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, e.what(), m, tp));
}

TEST_CASE("LogEntry: message, exception, frame", "[Log][LogEntry]")
{
	constexpr std::string_view m = "Message";
	const auto tp = std::chrono::system_clock::now();
	const auto e = std::logic_error("Test!");
	constexpr std::uint64_t f = 42;
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(m, nullptr, &e, tp, f, lt);

	REQUIRE(logEntry.Message() == m);
	REQUIRE_FALSE(logEntry.Stacktrace());
	REQUIRE(logEntry.Exception() == &e);
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE(logEntry.FrameCount() == f);
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, e.what(), m, tp, f));
}

TEST_CASE("LogEntry: message, stacktrace, message", "[Log][LogEntry]")
{
	constexpr std::string_view m = "Message";
	const auto tp = std::chrono::system_clock::now();
	const auto s = std::stacktrace::current();
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(m, &s, nullptr, tp, std::nullopt, lt);

	REQUIRE(logEntry.Message() == m);
	REQUIRE(logEntry.Stacktrace() == &s);
	REQUIRE_FALSE(logEntry.Exception());
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE_FALSE(logEntry.FrameCount().has_value());
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, m, tp, s));
}

TEST_CASE("LogEntry: message, stacktrace, frame", "[Log][LogEntry]")
{
	constexpr std::string_view m = "Message";
	const auto tp = std::chrono::system_clock::now();
	const auto s = std::stacktrace::current();
	constexpr std::uint64_t f = 42;
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(m, &s, nullptr, tp, f, lt);

	REQUIRE(logEntry.Message() == m);
	REQUIRE(logEntry.Stacktrace() == &s);
	REQUIRE_FALSE(logEntry.Exception());
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE(logEntry.FrameCount() == f);
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, m, tp, f, s));
}

TEST_CASE("LogEntry: message, stacktrace, exception", "[Log][LogEntry]")
{
	constexpr std::string_view m = "Message";
	const auto tp = std::chrono::system_clock::now();
	const auto e = std::logic_error("Test!");
	const auto s = std::stacktrace::current();
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(m, &s, &e, tp, std::nullopt, lt);

	REQUIRE(logEntry.Message() == m);
	REQUIRE(logEntry.Stacktrace() == &s);
	REQUIRE(logEntry.Exception() == &e);
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE_FALSE(logEntry.FrameCount().has_value());
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, e.what(), m, tp, s));
}

TEST_CASE("LogEntry: message, stacktrace, exception, frame", "[Log][LogEntry]")
{
	constexpr std::string_view m = "Message";
	const auto tp = std::chrono::system_clock::now();
	const auto e = std::logic_error("Test!");
	const auto s = std::stacktrace::current();
	constexpr std::uint64_t f = 42;
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(m, &s, &e, tp, f, lt);

	REQUIRE(logEntry.Message() == m);
	REQUIRE(logEntry.Stacktrace() == &s);
	REQUIRE(logEntry.Exception() == &e);
	REQUIRE(logEntry.TimePoint() == tp);
	REQUIRE(logEntry.FrameCount() == f);
	REQUIRE(logEntry.LogType() == lt);
	REQUIRE(logEntry.ToString() == PonyEngine::Log::LogFormat(lt, e.what(), m, tp, f, s));
}

TEST_CASE("LogEntry: ToString", "[Log][LogEntry]")
{
	constexpr std::string_view m = "Message";
	const auto tp = std::chrono::system_clock::now();
	const auto e = std::logic_error("Test!");
	const auto s = std::stacktrace::current();
	constexpr std::uint64_t f = 42;
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	const auto logEntry = PonyEngine::Log::Extension::LogEntry(m, &s, &e, tp, f, lt);

	std::string expected = PonyEngine::Log::LogFormat(lt, e.what(), m, tp, f, s);

	REQUIRE(logEntry.ToString() == expected);
	std::ostringstream oss;
	oss << logEntry;
	REQUIRE(oss.str() == expected);
	REQUIRE(std::format("{}", logEntry) == expected);
}

module;

#include "PonyEngine/Log/Log.h"

export module Game:GameService;

import std;

import PonyEngine.Application;
import PonyEngine.Job;
import PonyEngine.Log;

export namespace Game
{
	class GameService final : private PonyEngine::Application::ITickable
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit GameService(PonyEngine::Application::IApplication& application) noexcept;
		GameService(const GameService&) = delete;
		GameService(GameService&&) = delete;

		~GameService() noexcept;

		[[nodiscard("Pure function")]]
		PonyEngine::Application::ITickable& Tickable() noexcept;

		GameService& operator =(const GameService&) = delete;
		GameService& operator =(GameService&&) = delete;

	private:
		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		PonyEngine::Application::IApplication* application;
		PonyEngine::Log::ILogService* logService;
		PonyEngine::Job::IJobService* jobService;
	};
}

namespace Game
{
	class FillTask final : public PonyEngine::Job::ITask
	{
	public:
		std::span<float> data;
		float offset;
		PonyEngine::Log::ILogService* logService;

		virtual void Execute() noexcept override
		{
			for (std::size_t i = 0uz; i < data.size(); ++i)
			{
				data[i] = offset + i;
			}

			PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Fill finished");
		}
	};

	class SumTask final : public PonyEngine::Job::ITask
	{
	public:
		std::span<const float> lhs;
		std::span<const float> rhs;
		std::span<float> sum;
		PonyEngine::Log::ILogService* logService;

		virtual void Execute() noexcept override
		{
			for (std::size_t i = 0uz; i < sum.size(); ++i)
			{
				sum[i] = lhs[i] + rhs[i];
			}

			PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Sum finished");
		}
	};

	class AveTask final : public PonyEngine::Job::ITask
	{
	public:
		std::span<const float> lhs;
		std::span<const float> rhs;
		std::span<float> ave;
		PonyEngine::Log::ILogService* logService;

		virtual void Execute() noexcept override
		{
			for (std::size_t i = 0uz; i < ave.size(); ++i)
			{
				ave[i] = (lhs[i] + rhs[i]) / 2.f;
			}

			PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Ave finished");
		}
	};

	GameService::GameService(PonyEngine::Application::IApplication& application) noexcept :
		application{&application},
		logService{this->application->FindInterface<PonyEngine::Log::ILogService>()},
		jobService{&this->application->GetInterface<PonyEngine::Job::IJobService>()}
	{
		// Constructor logic can be added here.
		// The service may initialize its dependencies here.
		PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Game service constructed.");
	}

	GameService::~GameService() noexcept
	{
		// Destructor logic can be added here.
		// The service has to clean up here.
		PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Game service destructed.");
	}

	PonyEngine::Application::ITickable& GameService::Tickable() noexcept
	{
		return *this;
	}

	void GameService::Begin()
	{
		// Prepare the service for ticking.
		PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Game service begun.");
	}

	void GameService::End()
	{
		// Clean up the service after ticking.
		PONY_LOG(logService, PonyEngine::Log::LogType::Info, "Game service ended.");
	}

	void GameService::Tick()
	{
		// The service tick logic goes here.
		// This is the place to update the service state, process events, etc.

		std::vector<float> lhs;
		std::vector<float> rhs;
		std::vector<float> sum;
		std::vector<float> ave;

		constexpr std::size_t size = 5000000uz;
		lhs.resize(size);
		rhs.resize(size);
		sum.resize(size);
		ave.resize(size);

		auto lhsFillTask = FillTask();
		lhsFillTask.data = lhs;
		lhsFillTask.offset = -20.f;
		lhsFillTask.logService = logService;
		auto rhsFillTask = FillTask();
		rhsFillTask.data = rhs;
		rhsFillTask.offset = 50.f;
		rhsFillTask.logService = logService;
		auto sumTask = SumTask();
		sumTask.lhs = lhs;
		sumTask.rhs = rhs;
		sumTask.sum = sum;
		sumTask.logService = logService;
		auto aveTask = AveTask();
		aveTask.lhs = lhs;
		aveTask.rhs = rhs;
		aveTask.ave = ave;
		aveTask.logService = logService;

		const auto lhsFillJob = jobService->Schedule(lhsFillTask);
		const auto rhsFillJob = jobService->Schedule(rhsFillTask);
		const auto sumJob = jobService->Schedule(sumTask, std::array{lhsFillJob, rhsFillJob});
		const auto aveJob = jobService->Schedule(aveTask, std::array{lhsFillJob, rhsFillJob});
		jobService->Wait(std::array{sumJob, aveJob});
	}
}

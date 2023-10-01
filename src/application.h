#pragma once

#include <chrono>
#include <mutex>
#include <condition_variable>

#include <segement.h>
#include <window.h>

namespace Matrix::Application {

class Application {
public:
    // Just for brevity
    using duration = std::chrono::duration<double>;
    using Segement = Matrix::Segement::Segement;
    using RandInt = Matrix::Utility::RandomInt;

    Application(std::chrono::milliseconds period_ms)
        : m_window{}
        , rand_pos{0, m_window.GetWindowSize().second}
        , rand_size{m_window.GetWindowSize().first * (1/2), m_window.GetWindowSize().first}
        , m_period_ms{period_ms} {}

    void Run() {
        GenerateSegments();
       
        while (true) {
            clear();
            Update();
            refresh();
            RateSleep();
        }
        m_window.DestroyWindow();
    }

private:
    
    void Update() {
        for (auto& seg : m_segments) {
            seg.UpdateSegment();
        }
    }

    void GenerateSegments() {
        for (int i = 0; i < 80; i++) {
            m_segments.emplace_back(rand_pos.GetRandomInt(), rand_size.GetRandomInt(), rand_size.GetRandomInt());
            for (auto& seg : m_segments) {
                seg.ConfigureSegement();
            }
        }
    }

    void RateSleep() {
        std::unique_lock<std::mutex> lock{m_sleep_mtx};
        auto untilTime = m_last_rate_update + std::chrono::duration_cast<duration>(m_period_ms);
        m_sleep_cv.wait_until(lock, untilTime);

        m_last_rate_update = std::chrono::steady_clock::now();
    }

private:
    std::chrono::milliseconds m_period_ms;

    Window m_window;

    RandInt rand_pos;
    RandInt rand_size;

    std::vector<Segement> m_segments{};

    std::mutex m_sleep_mtx;
    std::condition_variable m_sleep_cv;
    std::chrono::steady_clock::time_point m_last_rate_update;
};

} // namespace Matrix::Application


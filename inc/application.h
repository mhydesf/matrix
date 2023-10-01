#pragma once

#include <chrono>
#include <cstddef>
#include <curses.h>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

#include <ncurses.h>
#include <symbol.h>
#include <window.h>

namespace Matrix::Application {

class Application {
public:
    Application(std::chrono::milliseconds period_ms)
        : m_period_ms{period_ms} {}

    void Run() {
        std::pair<int, int> dim = m_window.GetWindowSize();
        Matrix::Symbols::Symbol sym{};
        wchar_t wstr[] = { sym.GenerateRandomChar(), L'\0' };
        int i = 0;
        while (i < dim.second) {
            mvaddwstr(i, dim.first/2, wstr);
            refresh();
            RateSleep();
            i++;
        }
        m_window.DestroyWindow();
    }

private:
    void RateSleep() {
        std::unique_lock<std::mutex> lock{m_sleep_mtx};
        m_sleep_cv.wait_until(lock,
                              m_last_rate_update + std::chrono::duration_cast<std::chrono::duration<double>>(m_period_ms));

        m_last_rate_update = std::chrono::steady_clock::now();
    }

private:
    std::chrono::milliseconds m_period_ms;

    Window m_window;

    std::mutex m_sleep_mtx;
    std::condition_variable m_sleep_cv;
    std::chrono::steady_clock::time_point m_last_rate_update;
};

} // namespace Matrix::Application


#pragma once

#include <utility>
#include <clocale>
#include <ncurses.h>

namespace Matrix::Application {

class Window {
public:
    Window() {
        setlocale(LC_ALL, "");
        initscr();
        noecho();
        curs_set(0);
        nodelay(stdscr, TRUE);
        start_color();
    
        init_pair(1, COLOR_GREEN, COLOR_BLACK); // Define color pair 1: green text on black background
        attron(COLOR_PAIR(1) | A_BOLD | A_BLINK);

        getmaxyx(stdscr, m_height, m_width);
    }

    ~Window() {}

    void DestroyWindow() {
        endwin();
    }

    std::pair<int, int> GetWindowSize() {
        return std::make_pair(m_width, m_height);
    }

private:
    int m_width;
    int m_height;
};

} // namespace Matrix::Application

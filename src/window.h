#pragma once

#include <utility>
#include <clocale>

#include <curses.h>
#include <ncurses.h>

namespace Matrix::Application {

class Window {
public:
    Window() {
        CreateWindow(); 
    }

    ~Window() { DestroyWindow(); }

    void CreateWindow() {
        setlocale(LC_ALL, "");
        initscr();
        noecho();
        curs_set(0);
        nodelay(stdscr, TRUE);
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1) | A_BOLD);

        getmaxyx(stdscr, m_height, m_width);
    }

    int DestroyWindow() {
        attroff(COLOR_PAIR(1) | A_BOLD);
        return endwin();
    }
    int Refresh() { return refresh(); }
    int Clear() { return clear(); }

    std::pair<int, int> GetWindowSize() { return std::make_pair(m_height, m_width); }


private:
    int m_width;
    int m_height;
};

} // namespace Matrix::Application

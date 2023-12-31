#pragma once

#include <vector>
#include <iostream>

#include <curses.h>
#include <ncurses.h>
#include <randomint.h>

namespace Matrix::Symbols {

const std::vector<wchar_t> CODES = {
    0x30A0, 0x30A1, 0x30A2, 0x30A3, 0x30A4, 0x30A5, 0x30A6, 0x30A7,
    0x30A8, 0x30A9, 0x30AA, 0x30AB, 0x30AC, 0x30AD, 0x30AE, 0x30AF,
    0x30B0, 0x30B1, 0x30B2, 0x30B3, 0x30B4, 0x30B5, 0x30B6, 0x30B7,
    0x30B8, 0x30B9, 0x30BA, 0x30BB, 0x30BC, 0x30BD, 0x30BE, 0x30BF,
    0x30C0, 0x30C1, 0x30C2, 0x30C3, 0x30C4, 0x30C5, 0x30C6, 0x30C7,
    0x30C8, 0x30C9, 0x30CA, 0x30CB, 0x30CC, 0x30CD, 0x30CE, 0x30CF,
    0x30D0, 0x30D1, 0x30D2, 0x30D3, 0x30D4, 0x30D5, 0x30D6, 0x30D7,
    0x30D8, 0x30D9, 0x30DA, 0x30DB, 0x30DC, 0x30DD, 0x30DE, 0x30DF,
    0x30E0, 0x30E1, 0x30E2, 0x30E3, 0x30E4, 0x30E5, 0x30E6, 0x30E7,
    0x30E8, 0x30E9, 0x30EA, 0x30EB, 0x30EC, 0x30ED, 0x30EE, 0x30EF,
    0x30F0, 0x30F1, 0x30F2, 0x30F3, 0x30F4, 0x30F5, 0x30F6, 0x30F7,
    0x30F8, 0x30F9, 0x30FA, 0x30FB, 0x30FC, 0x30FD, 0x30FE, 0x30FF,
};

const int MIN_CODE_IDX = 0;
const int MAX_CODE_IDX = CODES.size() - 1;

class Symbol {
public:
    using RandomInt = Matrix::Utility::RandomInt;

    Symbol(int col, int row_start, int window_h, int window_w)
        : m_symbol{GenerateRandomChar()}
        , m_pos{std::make_pair<int, int>(std::move(col), std::move(row_start))}
        , m_win_dim{std::make_pair<int, int>(std::move(window_h), std::move(window_w))} {}
    ~Symbol() {}


    void UpdateSymbol(int height_pos, int width_pos, bool change_char = true) {
        if (change_char) { m_symbol = GenerateRandomChar(); }
        if (m_pos.first > m_win_dim.first) {
            m_pos.first = 0;
        } else{
            m_pos.first = height_pos;
        }
        m_pos.second = width_pos;
        Draw();
    }

    std::pair<int, int>& GetPosition() { return m_pos; }

private:
    wchar_t GenerateRandomChar() {
        int idx = rand.GetRandomInt();
        return CODES[idx];
    }
    
    void Draw() {
        wchar_t wstr[] = { m_symbol, L'\0' };
        mvaddwstr(m_pos.first, m_pos.second, wstr);
    }

private:
    RandomInt rand{MIN_CODE_IDX, MAX_CODE_IDX};

    wchar_t m_symbol;
    std::pair<int, int> m_pos;
    std::pair<int, int> m_win_dim;
};

} // namespace Matrix::Symbols


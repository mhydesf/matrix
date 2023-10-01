#pragma once

#include <array>
#include <vector>

#include <symbol.h>

namespace Matrix::Segement {

class Segement {
public:
    using Symbol = Matrix::Symbols::Symbol;
    using RandInt = Matrix::Utility::RandomInt;

    Segement(const int col, const int size, const int offset)
        : m_col{col}
        , m_size{size}
        , m_offset{offset}
        , m_symbols{{}}
    {
        ConfigureSegement();
    }

    ~Segement() {}

    void ConfigureSegement() {
        for (int i = 0; i < m_size; i++) {
            const int start_height = 0 - i - m_offset;
            m_symbols.emplace_back(start_height, m_col);
        }
    }

    void UpdateSegment() {
        for (auto& sym : m_symbols) {
            std::pair<int, int> curr_pos = sym.GetPosition();
            curr_pos.first += 1;
            sym.UpdateSymbol(curr_pos.first, curr_pos.second);
        }
    }

    std::vector<Symbol>& GetSymbols() { return m_symbols; }

private:
    int m_col;
    int m_size;
    int m_offset;
    std::vector<Symbol> m_symbols;
};

} // namespace Matrix::Segement


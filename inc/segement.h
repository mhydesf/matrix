#pragma once

#include <array>
#include <vector>

#include <symbol.h>

namespace Matrix::Segement {

template <int ARR_SIZE>
class Segement {
public:
    using Symbol = Matrix::Symbols::Symbol;

    Segement();
    ~Segement();

    void UpdateSegment() {
        for (Symbol sym : m_symbols) {
            sym.GenerateRandomChar();
        }
    }

private:
    std::array<Symbol, ARR_SIZE> m_symbols;
};

} // namespace Matrix::Segement

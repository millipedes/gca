#pragma once

#include "cellular_automata/cellular_automata.h"

namespace CellularAutomata {

auto one_dimension_simple(CellularAutomata<bool> ca_prev) -> CellularAutomata<bool>;

} // namespace CellularAutomata

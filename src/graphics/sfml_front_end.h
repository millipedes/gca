#pragma once

#include <SFML/Graphics.hpp>

#include "rules/cartesian_r_one.h"

namespace CellularAutomata {

auto render_automata(CellularAutomata<bool> c) -> void;

} // namespace CellularAutomata

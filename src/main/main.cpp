#include "graphics/sfml_front_end.h"

namespace ca = CellularAutomata;

int main(void) {
  ca::CellularAutomata<bool> c;
  ca::render_automata(c);
  return 0;
}

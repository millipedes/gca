#include "cartesian_r_one.h"

namespace CellularAutomata {

auto one_dimension_simple(CellularAutomata<bool> ca_prev) -> CellularAutomata<bool> {
  CellularAutomata<bool> ca_new = CellularAutomata(ca_prev);
  for(int i = 0; i < (int)ca_prev.the_cells.size(); i++) {
    const auto left_cell = (i - 1 >= 0
        ? ca_prev.the_cells[i - 1]
        : Cell(false));
    const auto right_cell = (i + 1 < (int)ca_prev.the_cells.size()
        ? ca_prev.the_cells[i + 1]
        : Cell(false));
    const auto center_cell = ca_prev.the_cells[i];
    if((std::get<bool>(left_cell.cell_values) 
          && !std::get<bool>(center_cell.cell_values)
          && !std::get<bool>(right_cell.cell_values)) ||
       (!std::get<bool>(left_cell.cell_values)
          && std::get<bool>(center_cell.cell_values)
          && std::get<bool>(right_cell.cell_values)) ||
       (!std::get<bool>(left_cell.cell_values)
          && std::get<bool>(center_cell.cell_values)
          && !std::get<bool>(right_cell.cell_values)) ||
       (!std::get<bool>(left_cell.cell_values)
          && std::get<bool>(right_cell.cell_values)
          && std::get<bool>(right_cell.cell_values))) {
      ca_new.the_cells[i].cell_values = true;
    } else {
      ca_new.the_cells[i].cell_values = false;
    }
  }
  return ca_new;
}

} // namespace CellularAutomata

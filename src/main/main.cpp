#include <functional>
#include <fstream>
#include <iostream>
#include <tuple>
#include <variant>
#include <vector>

template <typename... Args>
struct Cell {
  // Some basic examples include:
  // Cartesian: (x::double, y::double)
  // Polar:     (r::double, t::double)
  // 1dCA:      (n::uint32_t)
  std::tuple<Args...> cell_values;

  Cell(Args... args) : cell_values(std::make_tuple(args...)) {}

  auto print_cell_value() -> void {
    std::apply([](auto&&... args){ ((std::cout << " " << args << " "), ...);}, cell_values);
  }
};

// CA is defined via:
// L - D-Dimentional cellular space. A set of cells are placed here to form
//     regular network.
// S - Finite set of states (infered from the cells)
// M - Neighborhood vector of m which associates m distinct elements of L.
// R - Rule which takes S^m -> S (i.e. some function f (s1, s2, ... sm) which
//     takes cells to next state).
template <typename... Args>
struct CellularAutomata {
  std::vector<Cell<Args...>> the_cells;

  CellularAutomata& operator=(const CellularAutomata& other) {
    if(this != &other) {
      the_cells = other.the_cells;
    }
    return *this;
  }

  CellularAutomata(const CellularAutomata& other) : the_cells(other.the_cells) {}
  CellularAutomata(std::vector<Cell<Args...>> the_cells)
    : the_cells(the_cells) {}

  auto print_CA() -> void {
    for (auto& c : the_cells) {
      c.print_cell_value();
    }
    std::cout << std::endl;
  }
};

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

int main(void) {
  CellularAutomata<bool> ca = CellularAutomata<bool>(
      std::vector<Cell<bool>>{
        Cell(false), Cell(false), Cell(false), Cell(false), Cell(false),
        Cell(true),
        Cell(false), Cell(false), Cell(false), Cell(false), Cell(false),
      }
  );
  std::ofstream out_file("test.pbm");
  out_file << "P3" << std::endl;
  out_file << "1100 600" << std::endl;
  out_file << "255" << std::endl;
  for(int z = 0; z < 6; z++) {
    for(int j = 0; j < 100; j++) {
      for(int i = 0; i < (int)ca.the_cells.size(); i++) {
        for(int k = 0; k < 100; k++) {
          if(std::get<bool>(ca.the_cells[i].cell_values)) {
            out_file << "0 35 66" << std::endl;
          } else {
            out_file << "0 0 0" << std::endl;
          }
        }
      }
    }
    ca = one_dimension_simple(ca);
  }
  out_file.close();
  return 0;
}

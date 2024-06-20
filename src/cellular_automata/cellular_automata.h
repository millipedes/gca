#pragma once

#include <functional>
#include <fstream>
#include <iostream>
#include <tuple>
#include <variant>
#include <vector>

namespace CellularAutomata {

template <typename... Args>
struct Cell {
  std::tuple<Args...> cell_values;

  Cell(Args... args) : cell_values(std::make_tuple(args...)) {}

  Cell() = default;

  auto print_cell_value() -> void {
    std::apply([](auto&&... args){ ((std::cout << " " << args << " "), ...);}, cell_values);
  }
};

struct CartesianR1 {};

struct CartesianR2 {
  double width;
  double height;
};

using CoordinateSystem = std::variant<CartesianR1, CartesianR2>;

template <typename... Args>
struct CellularAutomata {
  CoordinateSystem coords;
  std::vector<Cell<Args...>> the_cells;

  CellularAutomata& operator=(const CellularAutomata& other) {
    if(this != &other) {
      the_cells = other.the_cells;
    }
    return *this;
  }

  CellularAutomata() = default;

  CellularAutomata(const CellularAutomata& other) : the_cells(other.the_cells) {}
  CellularAutomata(CoordinateSystem coords, std::vector<Cell<Args...>> the_cells)
    : coords(coords), the_cells(the_cells) {}

  auto print_CA() -> void {
    for (auto& c : the_cells) {
      c.print_cell_value();
    }
    std::cout << std::endl;
  }
};

} // namespace CellularAutomata

#include "sfml_front_end.h"

namespace CellularAutomata {

auto render_automata(CellularAutomata<bool> c) -> void {
  constexpr static auto square_h = 2.0f;
  constexpr static auto square_w = 16.0f / 9.0f * square_h;
  sf::RenderWindow window(sf::VideoMode(400, 400), "Example");
  sf::RectangleShape square(sf::Vector2f(square_h, square_w));
  square.setFillColor(sf::Color(0, 35, 66));
  square.setPosition(150.f, 150.f);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
        window.clear();
      if (event.type == sf::Event::Resized) {
        c = CellularAutomata<bool>(CartesianR1{}, std::vector<Cell<bool>>(801));
        c.the_cells[401] = Cell(true);
        for(int z = 0; z < 401; z++) {
          for(int i = 0; i < (int)c.the_cells.size(); i++) {
            if(std::get<bool>(c.the_cells[i].cell_values)) {
              square.setPosition(square_h * i, square_w * z);
              window.draw(square);
            }
          }
          c = one_dimension_simple(c);
        }
      }
    }
    window.display();
  }
}

} // namespace CellularAutomata

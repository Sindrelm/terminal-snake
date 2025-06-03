#include "game.h"
#include "state.h"
#include <iostream>
#include <vector>

int main() {
  std::cout << "Hello world";
  Game game;

  std::cout << game.to_string();

  auto& board = game.get_board();

  return 0;
}

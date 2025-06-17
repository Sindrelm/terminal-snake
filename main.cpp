#include "game.h"
#include "state.h"
#include <iostream>
#include <vector>

int main() {
  std::cout << "Hello world";
  Game game;

  game.init();
  game.run();

  return 0;
}

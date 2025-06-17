#ifndef GAME_H
#define GAME_H

#include "state.h"
#include "position.h"
#include "direction.h"
#include <vector>
#include <deque>
#include <string>
#include <iostream>

class Game {
  private:
  std::vector<std::vector<State>> board {
        {State::BORDER, State::BORDER, State::BORDER, State::BORDER, State::BORDER, State::BORDER, State::BORDER, State::BORDER},
        {State::BORDER, State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::BORDER},
        {State::BORDER, State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::BORDER},
        {State::BORDER, State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::BORDER},
        {State::BORDER, State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::BORDER},
        {State::BORDER, State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::BORDER},
        {State::BORDER, State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::NONE,   State::BORDER},
        {State::BORDER, State::BORDER, State::BORDER, State::BORDER, State::BORDER, State::BORDER, State::BORDER, State::BORDER}
  };
  
  bool running = true;

  std::deque<Position> snake;

  Direction snake_direction = Direction::DOWN;

  void update(const char input);
  void update_direction(const char input);

  bool has_apple() const;
  void spawn_apple();

  std::string to_string() const;

  std::string state_to_string(const State& state) const;

  char input();

  public:

    void run();

    void init();
};

#endif

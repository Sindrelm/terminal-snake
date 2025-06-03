#ifndef GAME_H
#define GAME_H

#include "state.h"
#include "position.h"
#include <vector>
#include <queue>
#include <string>

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

  std::queue<Position> snake;

  std::string state_to_string(const State& state) const;

  public:
    const std::vector<std::vector<State>>& get_board() const;

    std::string to_string() const;

};

#endif

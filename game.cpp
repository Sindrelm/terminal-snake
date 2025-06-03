#include "game.h"
#include "position.h"
#include "state.h"
#include <vector>
#include <string>

const std::vector<std::vector<State>>& Game::get_board() const {
  return board;
}



std::string Game::state_to_string(const State& state) const {
  switch(state) {
    case State::NONE: return " \' "; break;
    case State::BORDER: return " # "; break;
    case State::SNAKE: return " @ "; break;
    case State::APPLE: return " * "; break;
    default: return " ? "; break;
  }
}



std::string Game::to_string() const {
  std::string string;

  for(size_t i = 0; i < board.size(); ++i) {
      string += "\n";
    for (size_t j = 0; j < board[i].size(); ++j) {
      string += state_to_string(board[i][j]);
    }
  }

  return string;
}


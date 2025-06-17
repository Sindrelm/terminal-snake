#include "game.h"
#include "position.h"
#include "state.h"
#include "direction.h"
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <random>

bool Game::has_apple() const {
  for(size_t i = 0; i < board.size(); ++i) {
    for(size_t j = 0; j < board.size(); ++j) {
      if (board[i][j] == State::APPLE) {
        return true;
      }
    }
  }
  return false;
}

void Game::spawn_apple() {
  bool succesfull = false;
  while(!succesfull) {
    std::random_device r;
    std::mt19937 gen(r());
    std::uniform_int_distribution<> dist(1, 6);

    int x = dist(gen);
    int y = dist(gen);
    if (board[x][y] != State::SNAKE) {
      board[x][y] = State::APPLE;
      succesfull = true;
    }
  }
}

std::string Game::state_to_string(const State& state) const {
  switch(state) {
    case State::NONE: return " \' "; break;
    case State::BORDER: return " # "; break;
    case State::SNAKE: return " @ "; break;
    case State::APPLE: return " A "; break;
    default: return " ? "; break;
  }
}



std::string Game::to_string() const {
  std::string string;

  for(size_t i = 0; i < board.size(); ++i) {
    for (size_t j = 0; j < board[i].size(); ++j) {
      string += state_to_string(board[i][j]);
    }
    string += "\n";
  }

  return string;
}

void Game::run() {
  char s = 'w';
  while (running) {
    std::cout << "\033[2J\033[1;1H";
    s = input();
    update(s);
    std::cout << to_string();

    std::this_thread::sleep_for(std::chrono::milliseconds(350));
  }
  std::cout << "\n\n------GAME OVER-----\n\n";
}

void Game::update(char input) {
  //APPLE SPAWN
  if (!has_apple()) {
    spawn_apple();
  }

  Position next = snake.back();
  
  update_direction(input);
  //Moves down
  if(snake_direction == Direction::DOWN) {
    next.x += 1;
  }
  else if(snake_direction == Direction::UP) {
    next.x -= 1;
  }
  else if(snake_direction == Direction::RIGHT) {
    next.y += 1;
  }
  else if(snake_direction == Direction::LEFT) {
    next.y -= 1;
  }

  //Checks Collition
  if(board[next.x][next.y] == State::BORDER || board[next.x][next.y] == State::SNAKE) {
    running = false;
  }
  //Checks for Apple
  if(board[next.x][next.y] != State::APPLE) {
    Position& tail = snake.front();
    board[tail.x][tail.y] = State::NONE;
    snake.pop_front();
  }

  
  //updates board and snake
  board[next.x][next.y] = State::SNAKE;
  snake.push_back(next);
}

void Game::update_direction(char input) {
  //NO Backwardsmoves
  if((input == 'a' || input == 'd') && (snake_direction == Direction::RIGHT || snake_direction == Direction::LEFT)) {
    input = '.';
  } else if ((input == 'w' || input == 's') && (snake_direction == Direction::UP || snake_direction == Direction::DOWN)) {
    input = '.';
  }

  //UPDATES
  switch(input) {
    case 'w': snake_direction = Direction::UP; break;
    case 's': snake_direction = Direction::DOWN; break;
    case 'd': snake_direction = Direction::RIGHT; break;
    case 'a': snake_direction = Direction::LEFT; break;
    default: break;
  }
}

void Game::init() { 
  Position tail(3, 2);
  Position head(3, 3);

  board[head.x][head.y] = State::SNAKE;
  board[tail.x][tail.y] = State::SNAKE;
  
  snake.push_back(tail);
  snake.push_back(head);
}

char Game::input() {
    struct termios oldt, newt;
    char ch;
    
    // Turn off canonical mode and echo
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set non-blocking
    int bytesWaiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);

    ch = bytesWaiting > 0 ? getchar() : '\0';

    // Restore terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}



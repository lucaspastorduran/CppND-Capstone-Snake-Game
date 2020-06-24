#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, int speed_increase)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        speedIncrement(speed_increase*DIFFICULTY_TO_SPEED_RATIO)
  {
  }

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  void IncreaseSpeed();

  Direction direction = Direction::kUp;

  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  float speed{0.1f};


  // Snake defines its maximum velocity
  // Velocity below 1.0 can cause issues displaying the snake
  const float MAX_SPEED = 0.95f;
  const float DIFFICULTY_TO_SPEED_RATIO = 0.01f;
  float speedIncrement = 0.0f;
};

#endif
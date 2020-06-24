#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }

  // Store the last direction where Snake has moved
  previosuDirection = direction;
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

// Increase snake speed velocity according to game difficulty
// and limiting it to a maximum.
void Snake::IncreaseSpeed()
{
  if (speed >= MAX_SPEED)
  {
    return;
  }

  speed = std::min(MAX_SPEED, speed + speedIncrement);
}

void Snake::ChangeDirection(Direction nextDirection)
{
  // Ignore the command if next direction is the opposite to last movement and size > 1
  if (((previosuDirection == Direction::kUp && nextDirection == Direction::kDown) ||
      (previosuDirection == Direction::kDown && nextDirection == Direction::kUp) ||
      (previosuDirection == Direction::kLeft && nextDirection == Direction::kRight) ||
      (previosuDirection == Direction::kLeft && nextDirection == Direction::kRight) ||
      (previosuDirection == Direction::kRight && nextDirection == Direction::kLeft)) &&
      (size > 1))
  {
    return;
  }

  direction = nextDirection;
}


// Return de last direction where the snake has moved
Snake::Direction Snake::GetPreviousDirection() const
{
  return previosuDirection;
}